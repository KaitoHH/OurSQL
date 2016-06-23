#pragma once
#include "BufferMgr.h"
#include "CategoryMgr.h"
#include "File.h"
#include "Table.h"
extern BufferMgr databaseBuffer;
extern CategoryMgr databaseCategory;
extern std::string curDatabase;
void notFindException(char* cmd, void* par);


/* newblock filename
** 向filename添加一个新文件快
*/
void newBlock(char*cmd, void *par);

void showBuffer(char*cmd, void *par);

// 暂不能使用
void showBlock(char*cmd, void *par);

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

/*创建一个table*/
void createTable(char *cmd, void *par);

/*打印表结构*/
void showTableStructure(char *cmd, void *par);

/*创建record*/
void createRecord(char *cmd, void *par);

void createDatabase(char *cmd, void *par);

void removeDatabase(char *cmd, void *par);

void showDatabase(char*cmd, void *par);

void leaveDatabase(char *cmd, void *par);

void enterDatabase(char *cmd, void *par);

void removeTable(char *cmd, void *par);

void showAllTable(char *cmd, void *par);

void insertRecord(char *cmd, void *par);