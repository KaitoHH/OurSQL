#pragma once
#include "BufferMgr.h"
#include "File.h"
extern BufferMgr buffer;
void notFindException(char* cmd, void* par);

void exitCommand(char* cmd, void *par);

void newBlock(char*cmd, void *par);

void showBuffer(char*cmd, void *par);

void useBlock(char*cmd, void *par);

void showBlock(char*cmd, void *par);

void addRecord(char*cmd, void *par);

void removeRecord(char*cmd, void *par);

void newFile(char*cmd, void *par);

void showFile(char *cmd, void *par);

void removeBlock(char *cmd, void *par);