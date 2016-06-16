#include "Block.h"


Block::Block(int _blockNum)
{
	head = new byte[BLOCK_SIZE];
	*(int *)head = _blockNum;
}

Block::~Block()
{
}

int Block::getBlockNum()
{
	return *(int *)head;
}

bool Block::isModified()
{
	return modified;
}

const byte * Block::getBlockAddr()
{
	return (const byte*)head;
}

FILE * Block::getFilePos()
{
	return fp;
}

void Block::writeToFiles()
{
	fwrite(head, BLOCK_SIZE, 1, fp);
}

void Block::deleteBlock()
{
	*(head + 4) = 0;
}
