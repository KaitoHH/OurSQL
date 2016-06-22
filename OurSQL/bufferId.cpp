#include "bufferId.h"

bool operator<(const bufferId & id1, const bufferId & id2)
{

	int comp = strcmp(id1.fileName, id2.fileName);
	if (!comp) {
		return id1.blockNum < id2.blockNum;
	}
	else {
		return comp < 0;
	}

}

bufferId::~bufferId()
{
	delete[] fileName;
}
