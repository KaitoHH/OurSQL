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

byte Column::get_dataType() const
{
	return dataType;
}

ushort Column::get_dataLength() const
{
	return dataLength;
}

char* Column::get_dataName()const
{
	return dataName;
}

Column& Column::operator=(const Column &p1)
{
	this->dataType = p1.get_dataType();
	this->dataLength = p1.get_dataLength();
	strcpy(this->dataName, p1.get_dataName());
	return *this;
}
