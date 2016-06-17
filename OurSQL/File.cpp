#include "File.h"



File::File(const char* fileName)
{
	filePt = fopen(fileName, "rb+");
	fscanf(filePt, "%ud%ud%ud", firstDataBlock, firstFreeBlock, blockCount);
}


File::~File()
{
}

void File::filePtChangeTo(uint offest)
{
	fseek(filePt, offest*BLOCK_SIZE, SEEK_SET);
}
