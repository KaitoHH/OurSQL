#pragma once
class Block
{
public:
	Block(int);
	~Block();
	int getBlockNum();
	bool isModified();
private:
	int blockNum;
	bool modified;
};

