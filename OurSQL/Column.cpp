#include"Column.h"
#include<cstring>
Column::Column()
{
	dataType = ' ';
	dataLength = 0;
	dataName = "";
}

Column::Column(byte _dataType, ushort _dataLength, char* _dataNmae)
{
	dataType = _dataType;
	dataLength = _dataLength;
	dataName = new char[strlen(_dataNmae) + 1];
	strcpy(dataName, _dataNmae);
	//dataName = _dataNmae;
}

byte Column::get_dataType()
{
	return dataType;
}

ushort Column::get_dataLength()
{
	return dataLength;
}

char* Column::get_dataName()
{
	return dataName;
}

