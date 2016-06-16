#pragma once
#include "Block.h"
#include <vector>
#include <map>
#include <list>
#define MAX_BLOCK_SIZE 4

class BufferMgr
{
public:
	BufferMgr();
	~BufferMgr();
	void addBlock(Block *);
	void removeBlock(int);
	Block* getBlock(int);
	int getAndReleaseLruBlock();

	void showBlock();
private:
	Block *block[MAX_BLOCK_SIZE];
	int curSize;

	// 存放空闲块在数组中的序号
	std::vector<int> freeList;

	// 块号与BufferMgr内部序号的对应关系
	std::map<int, int>numMap;

	// LRU列表
	std::list<int>leastList;

	// block在LRU列表中的对应指针
	std::map<int, std::list<int>::iterator>leastAddr;
};
