#include "Record.h"
#include <cstring>


Record::Record(const char * str)
{
	data = new byte[strlen(str) + 1];
	strcpy(data, str);
}


Record::~Record()
{
}

ushort Record::getLength()
{
	return strlen(data);
}

byte * Record::getData()
{
	return data;
}
