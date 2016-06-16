#include "Block.h"


Block::Block(int _blockNum) :blockNum(_blockNum), modified(false)
{

}

Block::~Block()
{
}

int Block::getBlockNum()
{
	return blockNum;
}

bool Block::isModified()
{
	return modified;
}
