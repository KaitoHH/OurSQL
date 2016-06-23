#pragma once
#include "File.h"

struct BufferId
{
	char *fileName;
	uint blockNum;
	BufferId(const char *f, uint bno) : blockNum(bno)
	{
		fileName = new char[strlen(f) + 1];
		strcpy(fileName, f);
	}
	~BufferId();
};

bool operator < (const BufferId &id1, const BufferId &id2);