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

bool Block::canAddRecord(Record *r)
{
	ushort top = UINT_SIZE + 2 * USHORT_SIZE + 2 * USHORT_SIZE * getRecordCount();
	return (top + 2 * USHORT_SIZE <= getFree() - r->getLength());
}

bool Block::addRecord(Record *r)
{
	if (!canAddRecord(r))	return false;
	setRecordLength(getRecordCount()) = r->getLength();
	ushort pos = getFree() - r->getLength();
	byte *p = head + pos;
	strncpy(p, r->getData(), r->getLength());
	setRecordCount()++;
	return true;
}

byte * Block::getRecordData(ushort index)
{
	if (index >= getRecordCount())	return nullptr;
	return head + getRecordPointer(index);
}

ushort Block::getRecordLength(ushort index)
{
	setRecordLength(index);
}

bool Block::removeRecord(ushort index)
{
	if (index >= getRecordCount())	return false;
	
	int recordLength = getRecordLength(index);
	// 删除最后一块不需要移动
	if (index != getRecordCount() - 1) {
		//将index后面的所有指针空间向左移,指向的Records部分向右移,更新Free指针
		byte *last = head + getRecordPointer(index) + recordLength;
		for (int i = index + 1; i < getRecordCount(); i++) {
			int curRecordLength = getRecordLength(i);
			// 指针位置左移
			setRecordLength(i - 1) = curRecordLength;
			setRecordPointer(i - 1) = getRecordPointer(i) + recordLength;

			// Record右移
			byte* buffer = new byte[curRecordLength];
			strncpy(buffer, getRecordData(i), curRecordLength);
			last -= curRecordLength;
			strncpy(last, buffer, curRecordLength);
			delete[] buffer;
		}
	}
	//更新Free指针
	setFree() += recordLength;
	setRecordCount()--;
	return true;
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

ushort Block::getFree()
{
	return setFree();
}

ushort Block::getRecordPointer(ushort index)
{
	return setRecordPointer(index);
}

ushort & Block::setRecordCount()
{
	return *(ushort *)(head + UINT_SIZE);
}

ushort & Block::setRecordLength(ushort index)
{
	return *(ushort *)(head + UINT_SIZE + 2 * USHORT_SIZE + index * 2 * USHORT_SIZE);
}

ushort & Block::setRecordPointer(ushort index)
{
	return *(ushort *)(head + UINT_SIZE + 3 * USHORT_SIZE + index * 2 * USHORT_SIZE);
}

uint Block::getNextBlockOffset()
{
	return *(uint *)(head);
}

ushort Block::getRecordCount()
{
	return setRecordCount();
}
