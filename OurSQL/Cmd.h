#pragma once


#define _CMD_NAME_ "OurSQL>"

extern void (*_commandFunctionList[])(char* , void*);
extern char * _commandNameList[];
extern int _commandList_length;

class Cmd
{
public:
	Cmd(void);
	~Cmd(void);
	bool waitForCommand();
private:
	void parse_command(const char*,char*& ,void*&);
	void(*get_entry(char *cmd))(char* , void*);
};
