#pragma once
#include <cstdio>
#include <vector>
#include "Column.h"

typedef char byte;
typedef unsigned short int ushort;
//enum CONDITION {GREAT,LESS,EQUAL};
/* Table在文件中的结构
** -------------------------------------------------------
** |                          TCB                        | 64 bytes
** -------------------------------------------------------
** |Conlum 1 data type|Conlum 1 data length|Conlum 1 name| 64 bytes
** -------------------------------------------------------
** |Conlum 2 data type|Conlum 2 data length|Conlum 2 name| 64 bytes
** -------------------------------------------------------
** |Conlum 3 data type|Conlum 3 data length|Conlum 3 name| 64 bytes
** -------------------------------------------------------
** |Conlum n data type|Conlum n data length|Conlum n name| 64 bytes
** -------------------------------------------------------
** 0                  1                    3             63
** --------------
** |Conlum Count|
** --------------
** 0            2
** data type为一个byte类型，data length为一个ushort类型
** 由于一块大小4K，为了使块中能够至少一个记录能因此data length的和不能超过4k(4084 bytes)
** 有关Block的组织结构，见"Block.h"
**
** Record的结构
** -------------------------------------------------------------------------------------------------------------------------------
** |Variable-Data 1 pointer|Variable-Data 1 length|VarData 2 pt|VarData 2 len|...|FixData 1|FixData 2|...|VarData 1|VarData 2|...|
** -------------------------------------------------------------------------------------------------------------------------------
** 一个可变长度的数据指针占2字节,长度占2字节
** 指针是record内的偏移量
*/
class Table
{
public:
	Table(const char *);
	static void initTable(const char *, std::vector<Column>);
	~Table();
	static bool structTable(std::vector<Column> _tableStructure, FILE*);
	void showTableStructure();
	byte* parseRecord(byte* record, ushort index);
	byte* formRecord(std::vector<byte*>&, int&);
	byte* getColumnData(ushort index);
	int getColumnSize();
	int compareRecord(byte* record, byte* conditionData, int dataPostion);
	void printTitle();
	void printRecord(byte* record);
	static int condition(int, char ch);
private:
	FILE *fileName;
	std::vector<ushort> variableAttributePosition;
	int fixedLength;
	std::vector<Column*> tableStructure;
};

