#include "CommandList.h"
#include "File.h"
#include <cstdio>

// 在此注册命令
void(*_commandFunctionList[])(char*, void*)
= {
	notFindException,
	newBlock,
	showBuffer,
	createTable,
	showTableStructure,
	createDatabase,
	removeDatabase,
	showDatabase,
	enterDatabase,
	leaveDatabase,
	removeTable,
	showAllTable,
	insertRecord,
	selectRecord,
	switchLog,
	deleteRecord,
	help
};

char * _commandNameList[]
= {
	"",
	"newblock",
	"showbuffer",
	"createtable",
	"showtable",
	"createdb",
	"removedb",
	"showdb",
	"using",
	"leavedb",
	"removetable",
	"showalltable",
	"insert",
	"select",
	"switchlog",
	"delete",
	"help"
};

int _commandList_length = 16;


void notFindException(char *cmd, void *par)
{
	if (strcmp(cmd, ""))
		printf("%s is not a correct command, use 'help' to see all commands.\n", cmd);
}

void help(char *cmd, void *par)
{
	printf("所有可使用的命令有:\n");
	for (int i = 1; i <= _commandList_length; i++) {
		printf("%s\n", _commandNameList[i]);
	}
}

void newBlock(char *cmd, void *par)
{
	char *tablename = (char*)par;
	if (!curDatabase.length())
		throw("Please select database first");
	if (!databaseCategory.existTable(curDatabase, tablename))
		throw("table not exist!");
	std::string *schemaName = CategoryMgr::makePath(curDatabase.c_str(), tablename, "schema");
	std::string *dataName = CategoryMgr::makePath(curDatabase.c_str(), tablename, "data");
	Table table(schemaName->c_str());
	File file(dataName->c_str());
	Block *temp = file.addNewBlock();
	file.readBlock(temp->getBlockNum());
}

void showBuffer(char *cmd, void *par)
{
	databaseBuffer.showBlock();
}

void removeRecord(char *cmd, void *par)
{
	char *str = (char*)par;
	char name[100];
	int bno, rindex;
	sscanf(str, "%s %d %d", name, &bno, &rindex);
	File *file = new File(name);
	Block *block = file->readBlock(bno);
	block->removeRecord(rindex);
	file->writeToFile(block);
	delete file;
}

void newFile(char *cmd, void *par)
{
	File::initFile((char*)par);
}

void removeBlock(char *cmd, void *par)
{
	char *str = (char*)par;
	char name[100];
	int bno, front;
	sscanf(str, "%s %d %d", name, &bno, &front);
	File *file = new File(name);
	file->removeBlock(file->readBlock(bno), front);
	delete file;
}

void createTable(char *cmd, void *par)
{
	if (!curDatabase.length())	throw("please select a database first!");
	char table[100];
	int attributeNumber;
	std::vector<Column> tableStructure;
	sscanf((char *)par, "%s %d", table, &attributeNumber);
	if (!databaseCategory.addTable(curDatabase, table))
		throw("table already exist!");
	for (int i = 0; i < attributeNumber; i++)
	{
		char tname[64];
		int length;
		char name[61];
		int sn = scanf("%s", &tname);
		ushort typeNum = Column::parseType(tname[0], length);
		if (!typeNum) {
			databaseCategory.removeTable(curDatabase, table);
			throw("Error Type!");
		}
		if (!~length) {
			scanf("%d", &length);
		}
		scanf("%s", name);
		getchar();
		Column c(typeNum, length, name);
		tableStructure.push_back(c);
	}
	std::string *filename = CategoryMgr::makePath(curDatabase.c_str(), table, "schema");
	Table::initTable(filename->c_str(), tableStructure);
	delete filename;
	filename = CategoryMgr::makePath(curDatabase.c_str(), table, "data");
	File::initFile(filename->c_str());
	delete filename;

}

void showTableStructure(char *cmd, void *par)
{
	if (!curDatabase.length())	throw("please select a database first!");
	char table[100];
	std::vector<Column> tableStructure;
	sscanf((char*)par, "%s", table);
	if (!databaseCategory.existTable(curDatabase, table))
		throw("database not exist!");
	std::string *filename = CategoryMgr::makePath(curDatabase.c_str(), table, "schema");
	Table t(filename->c_str());
	t.showTableStructure();
}

void createDatabase(char *cmd, void *par)
{
	if (curDatabase.length())
		throw("Please leave database first");
	if (databaseCategory.addDataBase((char*)par)) {
		printf("create database success!\n");
	}
	else {
		throw("Failed! already exist.");
	}
}

void removeDatabase(char *cmd, void *par)
{
	if (curDatabase.length())
		throw("Please leave database first");
	if (databaseCategory.removeDataBase((char*)par)) {
		printf("remove database success!\n");
	}
	else {
		throw("Failed! not exist.");
	}
}

void showDatabase(char*cmd, void *par)
{
	databaseCategory.showDatabase();
}

void enterDatabase(char *cmd, void *par)
{
	if (!databaseCategory.existDataBase((char*)par))
		throw("database not exist.");
	curDatabase = (char*)par;
}

void leaveDatabase(char *cmd, void *par)
{
	databaseBuffer.clear();
	curDatabase.clear();
}

void removeTable(char *cmd, void *par)
{
	if (!curDatabase.length())
		throw("Please select database first");
	if (databaseCategory.removeTable(curDatabase, (char*)par)) {
		printf("delete table success!\n");
	}
	else {
		throw("table not exist.");
	}
}

void showAllTable(char *cmd, void *par)
{
	if (!curDatabase.length())
		throw("Please select database first");
	databaseCategory.showTable(curDatabase);
}

void insertRecord(char *cmd, void *par)
{
	char *tablename = (char*)par;
	if (!curDatabase.length())
		throw("Please select database first");
	if (!databaseCategory.existTable(curDatabase, tablename))
		throw("table not exist!");
	std::string *schemaName = CategoryMgr::makePath(curDatabase.c_str(), tablename, "schema");
	std::string *dataName = CategoryMgr::makePath(curDatabase.c_str(), tablename, "data");
	Table table(schemaName->c_str());
	File file(dataName->c_str());
	std::vector<byte*> originalData;
	for (int i = 0; i < table.getColumnSize(); i++) {
		byte* data = table.getColumnData(i);
		originalData.push_back(data);
	}
	int length;
	byte* record = table.formRecord(originalData, length);
	file.addRecord(record, length);
}

void switchLog(char *cmd, void *par)
{
	printf("Buffer Log: %d\n", databaseBuffer.switchLog());
}

void selectRecord(char *cmd, void *par)
{
	Table *table;
	File *file;
	bool showall;
	byte *column;
	int index;
	char condition;
	queryShell(par, table, file, showall, column, index, condition);
	table->printTitle();
	uint bno = file->getHead();
	while (bno) {
		Block *b = file->readBlock(bno);
		int cnt = b->getRecordCount();
		for (int i = 0; i < cnt; i++) {
			byte* byt = b->getRecordData(i);
			uint len = b->getRecordLength(i);
			if (showall || Table::condition(table->compareRecord(byt, column, index), condition))
				table->printRecord(byt);
		}
		bno = b->getNextBlockOffset();
	}
}

void deleteRecord(char *cmd, void *par)
{
	Table *table;
	File *file;
	bool showall;
	byte *column;
	int index;
	char condition;
	queryShell(par, table, file, showall, column, index, condition);
	uint bno = file->getHead();
	while (bno) {
		Block *b = file->readBlock(bno);
		int cnt = b->getRecordCount();
		for (int i = 0; i < cnt; i++) {
			byte* byt = b->getRecordData(i);
			uint len = b->getRecordLength(i);
			if (showall || Table::condition(table->compareRecord(byt, column, index), condition)) {
				file->removeRecord(b->getBlockNum(), i);
				cnt--;
				i--;
			}
		}
		bno = b->getNextBlockOffset();
	}
}

void queryShell(void *par, Table *&table, File *&file, bool &showall, byte *&column, int &index, char &condition)
{
	char *tablename = new char[64];
	char t[64];
	sscanf((char*)par, "%s %s", tablename, t);
	if (!curDatabase.length())
		throw("Please select database first");
	if (!databaseCategory.existTable(curDatabase, tablename))
		throw("table not exist!");
	std::string *schemaName = CategoryMgr::makePath(curDatabase.c_str(), tablename, "schema");
	std::string *dataName = CategoryMgr::makePath(curDatabase.c_str(), tablename, "data");
	table = new Table(schemaName->c_str());
	file = new File(dataName->c_str());
	if (!strcmp("where", t)) {
		int k = scanf("c%d %c", &index, &condition);
		if (k == 2) {
			column = table->getColumnData(index - 1);
			showall = false;
		}
	}
}