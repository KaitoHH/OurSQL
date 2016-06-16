#include "BufferMgr.h"
#include <cstring>


BufferMgr::BufferMgr()
{
	curSize = 0;
	memset(block, 0, sizeof(block));
}


BufferMgr::~BufferMgr()
{
}

void BufferMgr::addBlock(Block *b)
{
	int nextBlock;
	if (freeList.size()) {
		nextBlock = freeList[0];
	}
	else if (curSize < MAX_BLOCK_SIZE) {
		nextBlock = curSize++;
	}
	else {
		// LRU替换策略
		nextBlock = getAndReleaseLruBlock();
		delete block[nextBlock];
	}
	block[nextBlock] = b;
	numMap[b->getBlockNum()] = nextBlock;
	leastList.push_front(nextBlock);
	leastAddr[nextBlock] = leastList.begin();
}

void BufferMgr::removeBlock(uint bno)
{
	if (block[bno]->isModified()) {
		// TODO:写回文件
		printf("TODO:block #%d is written back to files.\n", bno);
		block[bno]->writeToFiles();
		//fwrite(block[bno]->getBlockAddr(), BLOCK_SIZE, 1, block[bno]->getFilePos());
	}
	delete block[bno];
	block[bno] = nullptr;
	freeList.push_back(bno);
}

Block * BufferMgr::getBlock(uint BlockNum)
{
	if (numMap.find(BlockNum) == numMap.end())
		return nullptr;
	int retBlock = numMap[BlockNum];

	// 更新LRU表
	auto p = leastAddr[retBlock];
	leastList.push_front(*p);
	leastAddr[*p] = leastList.begin();
	leastList.erase(p);

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
	for (int i = 0; i < MAX_BLOCK_SIZE; i++) {
		if (block[i] != nullptr)
			printf("%3d|%3d\n", i, block[i]->getBlockNum());
	}
}
