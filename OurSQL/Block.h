#pragma once
#include <cstdio>
#include "Record.h"
#define BLOCK_SIZE 4096
#define UINT_SIZE sizeof(uint)
#define USHORT_SIZE sizeof(ushort)
typedef char byte;
typedef unsigned int uint;
typedef unsigned short int ushort;

/*
** Block 的结构
** -----------------------------------------------------------------------------------------------------------
** |Next|Count|Free|Record1.Length|Record1.Pointer|Record2...|..Free Space..|Record n|Record n-1|...|Record 1|
** -----------------------------------------------------------------------------------------------------------
** 0    4     6    8              10              12
** 4字节大小的为uint, 2字节大小的为ushort
** 一般而言，外部的指针占4字节，块内部指针/内部大小占2字节
** 内部指针实质是一个相对于块头的偏移量
*/
class Block
{
public:
	Block(uint);
	Block(uint, byte*);
	~Block();
	uint getBlockNum();

	// 块中的信息
	const byte* getBlockAddr();
	uint getNextBlockOffset();
	ushort getRecordCount();

	// Record操作
	bool canAddRecord(Record*);
	bool addRecord(Record*);
	byte* getRecordData(ushort index);
	ushort getRecordLength(ushort index);
	bool removeRecord(ushort index);

	ushort& setNext();
	void clear();
	bool isModified();
	void modify();
	byte* getHead();

	void showBlock();
private:
	uint blockNum;
	byte *head;
	bool modified;

	ushort getFree();
	ushort getRecordPointer(ushort index);
	ushort& setFree();
	ushort& setRecordCount();
	ushort& setRecordLength(ushort index);
	ushort& setRecordPointer(ushort index);

};

