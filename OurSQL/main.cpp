#include "Cmd.h"
#include "BufferMgr.h"

BufferMgr buffer;
int main()
{
	Cmd cmd = Cmd();
	while (cmd.waitForCommand());
	return 0;
}