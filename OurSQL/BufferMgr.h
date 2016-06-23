#pragma once
#include <vector>
#include <map>
#include <list>
#include "Block.h"
#include "bufferId.h"
#define MAX_BLOCK_SIZE 4

class BufferMgr
{
public:
	BufferMgr();
	~BufferMgr();
	void addBlock(const char*, Block *);
	void removeBlock(uint);
	Block* getBlock(const char*, uint);
	int getAndReleaseLruBlock();
	void clear();
	void showBlock();
	bool switchLog();
private:
	Block *block[MAX_BLOCK_SIZE];
	bufferId *blockInfo[MAX_BLOCK_SIZE];
	int curSize;
	bool logRecord;
	// 块号与BufferMgr内部序号的对应关系
	std::map<bufferId, int>numMap;

	// LRU列表
	std::list<int>leastList;

	// block在LRU列表中的对应指针
	std::map<int, std::list<int>::iterator>leastAddr;
};

