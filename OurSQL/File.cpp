#include "File.h"



File::File(const char* fileName)
{
	filePt = fopen(fileName, "rb+");
	fread(&firstDataBlock, UINT_SIZE, 1, filePt);
	fread(&lastDataBlock, UINT_SIZE, 1, filePt);
	fread(&firstFreeBlock, UINT_SIZE, 1, filePt);
	fread(&lastFreeBlock, UINT_SIZE, 1, filePt);
	fread(&dataBlockCount, UINT_SIZE, 1, filePt);
	fread(&totalBlockCount, UINT_SIZE, 1, filePt);
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
	printf("File Closed.\n");
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
	writeToFile(block);
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
	filePtChangeTo(offest);
	byte* buffer = new byte[BLOCK_SIZE];
	fread(buffer, BLOCK_SIZE, 1, filePt);
	return new Block(offest, buffer);
}

void File::writeToFile(Block *block)
{
	filePtChangeTo(block->getBlockNum());
	fwrite(block->getHead(), BLOCK_SIZE, 1, filePt);
}

void File::showFile()
{
	printf("Block Count:%d, Total Block Count:%d£¬ FDB:%d, LDB:%d, FFB:%d, LFB:%d\n"
		, dataBlockCount, totalBlockCount, firstDataBlock, lastDataBlock, firstFreeBlock, lastFreeBlock);
	uint bno = firstDataBlock;
	while (bno) {
		readBlock(bno)->showBlock();
		bno = readBlock(bno)->getNextBlockOffset();
	}

}

void File::setNextOffest(Block * temp, uint offest)
{
	temp->setNext() = offest;
	writeToFile(temp);
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
