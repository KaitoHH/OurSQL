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
class Column
{
public:
	Column();
	Column(byte _dataType, ushort _dataLength, char* _dataName);
	byte get_dataType();
	ushort get_dataLength();
	char* get_dataName();
private:
	byte dataType;
	ushort dataLength;
	char* dataName;
};