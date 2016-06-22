#include "Cmd.h"
#include "BufferMgr.h"

BufferMgr dataBaseBuffer;

int main()
{
	Cmd cmd = Cmd();
	while (cmd.waitForCommand());
	return 0;
}