#include "Record.h"
#include <cstring>


Table::Table(const char * str)
{
	data = new byte[strlen(str) + 1];
	strcpy(data, str);
}


Table::~Table()
{
}

ushort Table::getLength()
{
	return strlen(data);
}

byte * Table::getData()
{
	return data;
}
