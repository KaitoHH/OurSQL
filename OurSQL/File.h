#pragma once
#include <cstdio>
#include <set>
#include "Block.h"
#define MAX_FILENAME_LENGTH 64

/* 文件结构
** ------------
** |   FCB    | 4k
** ------------
** | Block #1 | 4k
** ------------
** | Block #2 | 4k
** ------------
** | Block #3 | 4k
** ------------
** | Block #4 | 4k
** ------------
** | Block ...| 4k
** ------------
** FCB结构
** ---------------------------------------------------------------------------------------------------------
** |First Data Block|Last Data Block|First Free Block|Last Free Block|Data Block Count|Total Block Count|...
** ---------------------------------------------------------------------------------------------------------
** 0                4               8                12              16               20                24
** 由于每个Block中会包含下一个Block的指针,因此只需记录第一个数据/空闲Block的指针即可。
** 每一个Block可能有数据,也可能为空闲Block, Block不保证连续存放
** 与Block类似,指向Block的指针实质是一个相对文件头的偏移块数
** 有关Block的组织结构，见"Block.h"
*/
class File
{
public:
	File(const char*);
	static void initFile(const char*);
	~File();
	// 将文件指针定向到第offest块
	void filePtChangeTo(uint offest);
	Block* addNewBlock();
	void removeBlock(Block *, uint front);
	Block* readBlock(uint offest);
	void writeToFile(Block *);
	void showFile();
	const char* getFileName();
	void addRecord(byte* head, uint length);
	void removeRecord(uint bno, uint index);
	uint getHead();
private:
	FILE *filePt;
	uint firstDataBlock;
	uint firstFreeBlock;
	uint lastDataBlock;
	uint lastFreeBlock;
	uint dataBlockCount;
	uint totalBlockCount;

	const char *fileName;
	// 修改Block的next指针
	void setNextOffest(Block *, uint offest);
	// 还能够存放record的数据块
	std::set<uint>hasFreeBlock;
};

