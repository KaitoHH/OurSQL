#include "Table.h"
#include <cstring>

void Table::initTable(const char* newFileName)
{
	FILE *new_f = fopen(newFileName, "wb");
	fclose(new_f);
}
Table::Table(const char * _fileName)
{
	fileName = fopen(_fileName, "rb+");
}

Table::~Table()
{
	fclose(fileName);
}

bool  Table::structTable(std::vector<Column> tableStructure)
{
	int size = tableStructure.size();
	fwrite(&size, C_SIZE, 1, fileName);
	fseek(fileName, C_SIZE, 0);
	for (int i = 0; i < size; i++)
	{
		byte type = tableStructure[i].get_dataType();
		ushort length = tableStructure[i].get_dataLength();
		//char name[61];
		//strcpy(name, tableStructure[i].get_dataName());
		fwrite(&type, TYPE_SIZE, 1, fileName);
		fwrite(&length, LENGTH_SIZE, 1, fileName);
		//fwrite(name, sizeof(name), 1, fileName);
		fwrite(tableStructure[i].get_dataName(), NAME_SIZE, 1, fileName);
		//fseek(fileName, C_SIZE*(i + 1), 0);
	}
	return true;
}

bool Table::readStructure(std::vector<Column> &tableStructure)
{
	int size;
	fread(&size, sizeof(int), 1, fileName);
	fseek(fileName, C_SIZE, 0);
	for (int i = 0; i < size; i++)
	{
		byte type;
		ushort length;
		char name[61];
		fread(&type, TYPE_SIZE, 1, fileName);
		fread(&length, LENGTH_SIZE, 1, fileName);
		fread(name, NAME_SIZE, 1, fileName);
		Column c(type, length, name);
		tableStructure.push_back(c);
	}
	return true;
}

void Table::showTableStructure()
{
	std::vector<Column> t;
	readStructure(t);
	int n = t.size();
	//char* s = t[0].get_dataName();
	for (int i = 0; i < n; i++)
	{
		printf("Type:%c   LENGTH:%hu   Name:%s\n", t[i].get_dataType(), t[i].get_dataLength(), t[i].get_dataName());
		//printf("%s",t[i].get_dataName());
	}

}