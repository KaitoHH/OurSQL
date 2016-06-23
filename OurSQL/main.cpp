#include "Cmd.h"
#include "BufferMgr.h"
#include "CategoryMgr.h"
BufferMgr databaseBuffer;
CategoryMgr databaseCategory;
std::string curDatabase;
int main()
{
	Cmd cmd = Cmd();
	while (cmd.waitForCommand());
	return 0;
}