#pragma once
#define C_SIZE 64
#define TYPE_SIZE 1
#define LENGTH_SIZE 2
#define NAME_SIZE 61
typedef char byte;
typedef unsigned short int ushort;

/* table行的结构
** |Conlum n data type|Conlum n data length|Conlum n name| 64 bytes
** -------------------------------------------------------
** 0                  1                    3             63
** data type为一个byte类型，data length为一个ushort类型
** data type中v表示varchar c表示char  i表示int   d表示double   f表示float
*/
static const char conlumnType[] = { 0,'v','c','i','d','f' };
static const int conlumnLen[] = { 0,-1,1,4,4,2 };
static const char conlumnFormat[][5] = { "","%s","%c","%d","%lf","%f" };
static const char conlumnForm[][10] = { "","varchar","char","int","double","float" };
static const int typeCnt = 5;
class Column
{
public:
	Column();
	Column(byte _dataType, ushort _dataLength, char* _dataName);
	byte getDataType() const;
	ushort getDataLength()const;
	char* getDataName()const;
	const char* getTypeName()const;
	bool isFixLength()const;
	Column& operator=(const Column &p1);
	static byte parseType(char _type, int &length);
	byte* getData();
private:
	byte dataType;
	ushort dataLength;
	char* dataName;
	//Column operator=(const Column &p1);
};


