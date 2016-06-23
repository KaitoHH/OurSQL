#include "Cmd.h"
#include "CommandList.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::string;
Cmd::Cmd(void)
{
}

Cmd::~Cmd(void)
{
}

bool Cmd::waitForCommand()
{
	cout << _CMD_NAME_;
	string s;
	do {
		getline(cin, s);
	} while (s == "");

	// 解析命令，分离命令和参数
	char *cmd;
	void *par;
	parse_command(s.c_str(), cmd, par);
	//printf("command:%s,par:%s\n",cmd,par);

	// 寻找对应函数入口
	void(*ptr)(char*, void*);
	ptr = get_entry(cmd);

	try {
		// 执行函数
		(*ptr)(cmd, par);
	}
	catch (char *errorMsg) {
		cout << "执行 " << cmd << " 时发生了错误:" << std::endl;
		cout << errorMsg << std::endl;
	}

	return !cin.fail();
}

void Cmd::parse_command(const char* s, char*& cmd, void*& par)
{
	const char *split = strstr(s, " ");
	if (split == NULL) {
		par = NULL;
		cmd = new char[strlen(s) + 1];
		strcpy(cmd, s);
	}
	else {
		par = new char[strlen(split)];
		strcpy((char *)par, split + 1);
		int len = split - s;
		cmd = new char[len + 1];
		strncpy(cmd, s, len);
		cmd[len] = NULL;
	}

}

void(*Cmd::get_entry(char* cmd))(char*, void*)
{
	for (int i = 1; i < _commandList_length; i++) {
		if (!strcmp(_commandNameList[i], cmd))
			return _commandFunctionList[i];
	}
	return _commandFunctionList[0];
}