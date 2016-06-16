#pragma once
#include <cstdio>
#define BLOCK_SIZE 4096
typedef char byte;
typedef unsigned int uint;
/*
** Block �Ľṹ
** --------------------
** |BlockNum|used|Next|
** --------------------
** 0        4    5    9
*/
class Block
{
public:
	Block(int);
	~Block();
	int getBlockNum();
	bool isModified();
	const byte* getBlockAddr();
	FILE* getFilePos();
	void writeToFiles();
	void deleteBlock();

private:
	byte *head;
	FILE *fp;
	bool modified;
};

