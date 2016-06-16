#pragma once
#include "BufferMgr.h"

extern BufferMgr buffer;
void notFindException(char* cmd, void* par);

void exitCommand(char* cmd, void *par);

void newBlock(char*cmd, void *par);

void showBuffer(char*cmd, void *par);

void useBlock(char*cmd, void *par);