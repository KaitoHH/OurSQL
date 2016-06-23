#include "CategoryMgr.h"
#include <iostream>
#include <fstream>
#include <direct.h>

// 读文件
CategoryMgr::CategoryMgr()
{
	std::ifstream fin(CATGORY_NAME);
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		std::string s;
		fin >> s;
		database[s] = std::set<std::string>();
		int m;
		fin >> m;
		for (int j = 0; j < m; j++) {
			std::string table;
			fin >> table;
			database[s].insert(table);
		}
	}
	fin.close();
}

// 写文件
CategoryMgr::~CategoryMgr()
{
	std::ofstream fout(CATGORY_NAME);
	fout << database.size() << std::endl;
	for (auto i = database.begin(); i != database.end(); i++) {
		fout << i->first << " ";
		fout << i->second.size() << std::endl;
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			fout << *j << std::endl;
		}
	}
}

bool CategoryMgr::addDataBase(std::string dbName)
{
	if (database.find(dbName) != database.end()) {
		return false;
	}
	database[dbName] = std::set<std::string>();
	_mkdir(dbName.c_str());
	return true;
}

bool CategoryMgr::addTable(std::string dbName, std::string tableName)
{
	if (database.find(dbName) == database.end() || database[dbName].find(tableName) != database[dbName].end())
		return false;
	database[dbName].insert(tableName);
	return true;
}

bool CategoryMgr::existDataBase(std::string dbName)
{
	return database.find(dbName) != database.end();
}

bool CategoryMgr::existTable(std::string dbName, std::string tableName)
{
	return database.find(dbName) != database.end() && database[dbName].find(tableName) != database[dbName].end();
}

bool CategoryMgr::removeDataBase(std::string dbName)
{
	if (database.find(dbName) == database.end())
		return false;
	database[dbName].clear();
	database.erase(dbName);
	return true;
}

bool CategoryMgr::removeTable(std::string dbName, std::string tableName)
{
	if (database.find(dbName) == database.end() || database[dbName].find(tableName) == database[dbName].end())
		return false;
	database[dbName].erase(tableName);
	return true;
}

void CategoryMgr::showDatabase()
{
	int cnt = 0;
	for (auto i = database.begin(); i != database.end(); i++) {
		printf("#%3d | ", ++cnt);
		std::cout << i->first << std::endl;
	}
}

bool CategoryMgr::showTable(std::string dbName)
{
	if (!existDataBase(dbName))	return false;
	int cnt = 0;
	for (auto i = database[dbName].begin(); i != database[dbName].end(); i++) {
		printf("#%3d | ", ++cnt);
		std::cout << *i << std::endl;
	}
}

std::string * CategoryMgr::makePath(const char* dbName, const char* tableName, const char* type)
{
	std::string name = dbName;
	std::string table = tableName;
	std::string fix = type;
	std::string * str = new std::string(name + "\\" + table + "." + fix);
	return str;
}
