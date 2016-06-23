#include"Column.h"
#include<cstring>
#include "cstdio"
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

byte Column::getDataType() const
{
	return dataType;
}

ushort Column::getDataLength() const
{
	return dataLength;
}

char* Column::getDataName()const
{
	return dataName;
}

const char * Column::getTypeName() const
{
	return conlumnForm[getDataType()];
}

bool Column::isFixLength() const
{
	return ~conlumnLen[getDataType()];
}

Column& Column::operator=(const Column &p1)
{
	this->dataType = p1.getDataType();
	this->dataLength = p1.getDataLength();
	strcpy(this->dataName, p1.getDataName());
	return *this;
}

byte Column::parseType(char _type, int &length)
{
	for (int i = 1; i <= typeCnt; i++) {
		if (conlumnType[i] == _type) {
			length = conlumnLen[i];
			return i;
		}
	}
	return 0;
}

byte * Column::getData()
{
	byte *data = new byte[dataLength];
	scanf(conlumnFormat[dataLength], &data);	// ¶ÁÈë*
	return data;
}

