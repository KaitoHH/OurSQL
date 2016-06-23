#include "File.h"
#include "BufferMgr.h"

extern BufferMgr databaseBuffer;
File::File(const char* filename) :fileName(filename)
{
	filePt = fopen(filename, "rb+");
	fread(&firstDataBlock, UINT_SIZE, 1, filePt);
	fread(&lastDataBlock, UINT_SIZE, 1, filePt);
	fread(&firstFreeBlock, UINT_SIZE, 1, filePt);
	fread(&lastFreeBlock, UINT_SIZE, 1, filePt);
	fread(&dataBlockCount, UINT_SIZE, 1, filePt);
	fread(&totalBlockCount, UINT_SIZE, 1, filePt);
	int bno = firstDataBlock;
	while (bno) {
		hasFreeBlock.push_back(bno);
		bno = readBlock(bno)->getNextBlockOffset();
	}
}


File::~File()
{
	filePtChangeTo(0);
	fwrite(&firstDataBlock, UINT_SIZE, 1, filePt);
	fwrite(&lastDataBlock, UINT_SIZE, 1, filePt);
	fwrite(&firstFreeBlock, UINT_SIZE, 1, filePt);
	fwrite(&lastFreeBlock, UINT_SIZE, 1, filePt);
	fwrite(&dataBlockCount, UINT_SIZE, 1, filePt);
	fwrite(&totalBlockCount, UINT_SIZE, 1, filePt);
	fclose(filePt);
	//printf("File Closed.\n");
}

void File::filePtChangeTo(uint offest)
{
	fseek(filePt, offest*BLOCK_SIZE, SEEK_SET);
}

Block* File::addNewBlock()
{
	Block *block;
	if (firstFreeBlock) {
		setNextOffest(readBlock(lastDataBlock), firstFreeBlock);
		block = readBlock(firstFreeBlock);
		firstFreeBlock = block->getNextBlockOffset();
	}
	else {
		if (lastDataBlock)
			setNextOffest(readBlock(lastDataBlock), totalBlockCount);
		filePtChangeTo(totalBlockCount);
		block = new Block(totalBlockCount);
		totalBlockCount++;
	}
	block->clear();
	block->setNext() = 0;
	lastDataBlock = block->getBlockNum();
	dataBlockCount++;
	if (!firstDataBlock)
		firstDataBlock = lastDataBlock;
	return block;
}

void File::removeBlock(Block *block, uint front)
{
	databaseBuffer.addBlock(fileName, block);
	if (front) {
		setNextOffest(readBlock(front), block->getNextBlockOffset());
	}
	else {
		firstDataBlock = readBlock(block->getNextBlockOffset())->getBlockNum();
	}
	if (block->getBlockNum() == lastDataBlock) {
		lastDataBlock = front;
	}
	block->clear();
	//writeToFile(block);
	if (firstFreeBlock) {
		setNextOffest(readBlock(lastFreeBlock), block->getBlockNum());
		lastFreeBlock = block->getBlockNum();
	}
	else {
		firstFreeBlock = lastFreeBlock = block->getBlockNum();
	}
	dataBlockCount--;
}

Block * File::readBlock(uint offest)
{
	// 先从databaseBuffer中找
	Block *target = databaseBuffer.getBlock(fileName, offest);
	if (target != nullptr) {
		return target;
	}
	filePtChangeTo(offest);
	byte* _buffer = new byte[BLOCK_SIZE];
	fread(_buffer, BLOCK_SIZE, 1, filePt);

	target = new Block(offest, _buffer);
	// 置入databaseBuffer
	databaseBuffer.addBlock(fileName, target);
	return target;
}

void File::writeToFile(Block *block)
{
	filePtChangeTo(block->getBlockNum());
	fwrite(block->getHead(), BLOCK_SIZE, 1, filePt);
}

void File::showFile()
{
	printf("Block Count:%d, Total Block Count:%d， FDB:%d, LDB:%d, FFB:%d, LFB:%d\n"
		, dataBlockCount, totalBlockCount, firstDataBlock, lastDataBlock, firstFreeBlock, lastFreeBlock);
	uint bno = firstDataBlock;
	while (bno) {
		readBlock(bno)->showBlock();
		bno = readBlock(bno)->getNextBlockOffset();
	}

}

const char * File::getFileName()
{
	return fileName;
}

void File::setNextOffest(Block * temp, uint offest)
{
	temp->setNext() = offest;
	databaseBuffer.addBlock(fileName, temp);
	//writeToFile(temp);
}

void File::initFile(const char * filename)
{
	FILE *fp = fopen(filename, "wb");
	uint *d = new uint(0);
	for (int i = 0; i < 5; i++)
		fwrite(d, UINT_SIZE, 1, fp);
	*d = 1;
	fwrite(d, UINT_SIZE, 1, fp);
	delete d;
	fclose(fp);
}
