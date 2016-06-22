#pragma once
#include <cstdio>
#include <vector>
#include "Column.h"

typedef char byte;
typedef unsigned short int ushort;

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
*/
class Table
{
public:
	Table(const char *);
	static void initTable(const char *);
	~Table();
	bool structTable(std::vector<Column> tableStructure); 
	bool readStructure(std::vector<Column> &tableStructure);
	void showTableStructure();
	//Record parseRecord();
	//formRecord();

	//ushort getLength();


private:
	FILE *fileName;

};

