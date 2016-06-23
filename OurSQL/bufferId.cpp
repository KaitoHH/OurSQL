#include "BufferId.h"

bool operator<(const BufferId & id1, const BufferId & id2)
{

	int comp = strcmp(id1.fileName, id2.fileName);
	if (!comp) {
		return id1.blockNum < id2.blockNum;
	}
	else {
		return comp < 0;
	}

}

BufferId::~BufferId()
{
	delete[] fileName;
}
