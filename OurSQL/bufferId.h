#pragma once
#include "File.h"

struct bufferId
{
	char *fileName;
	uint blockNum;
	bufferId(const char *f, uint bno) : blockNum(bno)
	{
		fileName = new char[strlen(f) + 1];
		strcpy(fileName, f);
	}
	~bufferId();
};

bool operator < (const bufferId &id1, const bufferId &id2);