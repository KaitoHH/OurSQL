#include "CommandList.h"
#include <cstdio>

// ÔÚ´Ë×¢²áÃüÁî
void(*_commandFunctionList[])(char*, void*)
= {
	notFindException,
	exitCommand,
	newBlock,
	useBlock,
	showBuffer
};

char * _commandNameList[]
= {
	"",
	"exit",
	"newblock",
	"useblock",
	"showbuffer",
};

int _commandList_length = 4;


void notFindException(char* cmd, void* par)
{
	printf("%s is not a correct command.\n", cmd);
}

void exitCommand(char* cmd, void *par)
{
	printf("Close the window to exit.\n");
}

void newBlock(char*cmd, void *par)
{
	buffer.addBlock(new Block(atoi((char *)par)));
}

void useBlock(char*cmd, void *par)
{
	if (buffer.getBlock(atoi((char *)par)) == nullptr)
		printf("Block not exist!\n");
}

void showBuffer(char*cmd, void *par)
{
	buffer.showBlock();
}