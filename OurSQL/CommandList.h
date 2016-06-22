#pragma once
#include "BufferMgr.h"
#include "File.h"
#include "Table.h"
extern BufferMgr buffer;
void notFindException(char* cmd, void* par);

void exitCommand(char* cmd, void *par);

/* newblock filename
** 向filename添加一个新文件快
*/
void newBlock(char*cmd, void *par);

void showBuffer(char*cmd, void *par);

// 暂不能使用
void useBlock(char*cmd, void *par);

// 暂不能使用
void showBlock(char*cmd, void *par);

/* addrecord filename blocknum record
** 向filename的第blocknum块添加一条记录
*/
void addRecord(char*cmd, void *par);

/* addrecord filename blocknum recordnum
** 向filename的第blocknum块删除第recordnum条记录
*/
void removeRecord(char*cmd, void *par);

/* newfile filename
** 格式化一个数据文件filename
*/
void newFile(char*cmd, void *par);

/* showfile filename
** 打印数据文件filename
*/
void showFile(char *cmd, void *par);

/* removeblock filename blocknum front
** 删除数据文件filename的第blocknum块，front为被删除块的前一块
*/
void removeBlock(char *cmd, void *par);

void print(char *cmd, void *par);

/*创建一个table*/
void createTable(char *cmd, void *par);

/*打印表结构*/
void showTableStructure(char *cmd, void *par);