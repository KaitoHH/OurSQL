#include "CommandList.h"
#include <cstdio>

// ÔÚ´Ë×¢²áÃüÁî
void(*_commandFunctionList[])(char*, void*)
= {
	notFindException,
	exitCommand,
	newBlock,
	useBlock,
	showBuffer,
	showBlock,
	addRecord,
	removeRecord,
	newFile,
	showFile,
	removeBlock,
	print,
	createTable,
	showTableStructure
};

char * _commandNameList[]
= {
	"",
	"exit",
	"newblock",
	"useblock",
	"showbuffer",
	"showblock",
	"addrecord",
	"removerecord",
	"newfile",
	"showfile",
	"removeblock",
	"print",
	"createtable",
	"showtable"
};

int _commandList_length = 13;


void notFindException(char *cmd, void *par)
{
	printf("%s is not a correct command.\n", cmd);
}

void exitCommand(char *cmd, void *par)
{
	printf("Close the window to exit.\n");
}

void newBlock(char *cmd, void *par)
{
	File *file = new File((char*)par);
	Block *temp = file->addNewBlock();
	dataBaseBuffer.addBlock(file->getFileName(), temp);
	delete file;
	//buffer.addBlock(new Block(atoi((char *)par)));
}

void useBlock(char *cmd, void *par)
{

}

void showBuffer(char *cmd, void *par)
{
	dataBaseBuffer.showBlock();
}

void showBlock(char *cmd, void *par)
{

}

void addRecord(char *cmd, void *par)
{
	char *str = (char*)par;
	char name[100];
	int bno;
	char record[100];
	sscanf(str, "%s %d %s", name, &bno, record);
	Table *rec = new Table(record);
	File *file = new File(name);
	Block *block = file->readBlock(bno);
	block->addRecord(rec);
	file->writeToFile(block);
	delete file;
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

void showFile(char *cmd, void *par)
{
	File *file = new File((char*)par);
	file->showFile();
	delete file;
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

void print(char *cmd, void *par)
{
	char str[100];
	int times = 0;
	int rtn = sscanf((char *)par, "%d %s", &times, str);
	printf("%d\n", rtn);
	while (times--)
		printf("%s\n", str);
}

void createTable(char *cmd, void *par)
{
	char table[100];
	int attributeNumber;
	std::vector<Column> tableStructure;
	sscanf((char *)par, "%s %d", table, &attributeNumber);
	for (int i = 0; i < attributeNumber; i++)
	{
		byte type;
		ushort length;
		char name[61];
		int sn = scanf("%c %hu %s", &type, &length, name);
		getchar();
		if (sn != 3) printf("error");
		Column c(type, length, name);
		tableStructure.push_back(c);
	}
	Table::initTable(table);
	Table t(table);
	t.structTable(tableStructure);
}

void showTableStructure(char *cmd, void *par)
{
	char table[100];
	std::vector<Column> tableStructure;
	sscanf((char*)par, "%s", table);
	Table t(table);
	//t.readStructure(tableStructure);
	t.showTableStructure();
}