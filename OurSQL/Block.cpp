#include "Block.h"
#include <cstring>

Block::Block(uint _blockNum) :blockNum(_blockNum)
{
	head = new byte[BLOCK_SIZE];
	memset(head, 0, sizeof(byte)*BLOCK_SIZE);
	setFree() = BLOCK_SIZE;

}

Block::~Block()
{
}

uint Block::getBlockNum()
{
	return blockNum;
}

bool Block::canAddRecord(Record)
{
	return false;
}

bool Block::addRecord(Record)
{
	return false;
}

byte * Block::getRecordData(ushort index)
{
	if (index >= getRecordCount()) {
		return nullptr;
	}
	return head + getRecordPointer(index);
}

ushort Block::getRecordLength(ushort index)
{
	return *(ushort *)(head + UINT_SIZE + 2 * USHORT_SIZE + index * 2 * USHORT_SIZE);
}

bool Block::removeRecord(ushort index)
{
	return false;
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

ushort& Block::setFree()
{
	return *(ushort *)(head + UINT_SIZE + USHORT_SIZE);
}

ushort Block::getRecordPointer(ushort index)
{
	return *(ushort *)(head + UINT_SIZE + 3 * USHORT_SIZE + index * 2 * USHORT_SIZE);
}

uint Block::getNextBlockOffset()
{
	return *(uint *)(head);
}

ushort Block::getRecordCount()
{
	return *(ushort *)(head + UINT_SIZE);
}
