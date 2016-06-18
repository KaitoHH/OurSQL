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
	removeBlock
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
};

int _commandList_length = 10;


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
	file->writeToFile(temp);
	delete file;
	//buffer.addBlock(new Block(atoi((char *)par)));
}

void useBlock(char *cmd, void *par)
{
	if (buffer.getBlock(atoi((char *)par)) == nullptr)
		printf("Block not exist!\n");
}

void showBuffer(char *cmd, void *par)
{
	buffer.showBlock();
}

void showBlock(char *cmd, void *par)
{
	int bno = atoi((char *)par);
	buffer.getBlock(bno)->showBlock();
}

void addRecord(char *cmd, void *par)
{
	char *str = (char*)par;
	char name[100];
	int bno;
	char record[100];
	sscanf(str, "%s %d %s", name, &bno, record);
	Record *rec = new Record(record);
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