#include "BufferMgr.h"
#include <cstring>


BufferMgr::BufferMgr()
{
	logRecord = false;
	curSize = 0;
	memset(block, 0, sizeof(block));
}


BufferMgr::~BufferMgr()
{
	clear();
}

void BufferMgr::addBlock(const char *file, Block *b)
{
	if (numMap.find(BufferId(file, b->getBlockNum())) != numMap.end())
		return;
	int nextBlock;
	if (curSize < MAX_BLOCK_SIZE) {
		nextBlock = curSize++;
	}
	else {
		// LRU替换策略
		nextBlock = getAndReleaseLruBlock();
		removeBlock(nextBlock);
	}
	BufferId *bid = new BufferId(file, b->getBlockNum());
	block[nextBlock] = b;
	blockInfo[nextBlock] = bid;
	numMap[*bid] = nextBlock;
	leastList.push_front(nextBlock);
	leastAddr[nextBlock] = leastList.begin();
	if (logRecord)
		printf("[Buffer Mgr]Block #%d in %s is added to Buffer\n", b->getBlockNum(), file);
}

void BufferMgr::removeBlock(uint bno)
{
	if (logRecord)
		printf("[Buffer Mgr]Block #%d in %s is now removed\n", block[bno]->getBlockNum(), blockInfo[bno]->fileName);
	// 写回文件
	if (block[bno]->isModified()) {
		File file(blockInfo[bno]->fileName);
		file.writeToFile(block[bno]);
		if (logRecord)
			printf("[Buffer Mgr]Block #%d in %s is written back to files\n", block[bno]->getBlockNum(), blockInfo[bno]->fileName);
	}
	numMap.erase(*blockInfo[bno]);
	delete block[bno];
	//delete blockInfo[bno];
	blockInfo[bno] = nullptr;
	block[bno] = nullptr;
}

Block * BufferMgr::getBlock(const char* file, uint BlockNum)
{
	BufferId id = BufferId(file, BlockNum);
	if (numMap.find(id) == numMap.end())
		return nullptr;
	int retBlock = numMap[id];

	// 更新LRU表
	auto p = leastAddr[retBlock];
	leastList.push_front(*p);
	leastAddr[*p] = leastList.begin();
	leastList.erase(p);
	if (logRecord)
		printf("[Buffer Mgr]Block #%d in %s is found in Buffer\n", blockInfo[retBlock]->blockNum, blockInfo[retBlock]->fileName);
	return block[retBlock];
}

int BufferMgr::getAndReleaseLruBlock()
{
	int least = leastList.back();
	leastList.pop_back();
	return least;
}

void BufferMgr::showBlock()
{
	printf("%5s|%30s|%10s|\n", "no", "table", "blockNum");
	for (int i = 0; i < MAX_BLOCK_SIZE; i++) {
		if (block[i] != nullptr)
			printf("%5d|%30s|%10d\n", i, blockInfo[i]->fileName, blockInfo[i]->blockNum);
	}
}

bool BufferMgr::switchLog()
{
	return logRecord = !logRecord;
}

void BufferMgr::clear()
{
	if (logRecord)
		printf("[Buffer Mgr]Now writing buffer back to files...\n");
	// 写回文件
	for (auto i = numMap.begin(); i != numMap.end(); i++) {
		Block *b = block[i->second];
		if (b->isModified()) {
			File file(i->first.fileName);
			file.writeToFile(b);
			printf("[Buffer Mgr]Block #%d in %s\n", i->first.blockNum, i->first.fileName);
		}
	}
}
