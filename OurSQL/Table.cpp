#include "Table.h"
#include <cstring>

void Table::initTable(const char* newFileName, std::vector<Column> _tableStructure)
{
	FILE *new_f = fopen(newFileName, "wb");
	structTable(_tableStructure, new_f);
	fclose(new_f);
}
Table::Table(const char * _fileName)
{
	fileName = fopen(_fileName, "rb+");
	fixedLength = 0;
	if (fileName == nullptr)
		return;
	int size;
	fread(&size, sizeof(int), 1, fileName);
	fseek(fileName, C_SIZE, 0);
	for (int i = 0; i < size; i++)
	{
		byte type;
		ushort length;
		char name[61];
		fread(&type, TYPE_SIZE, 1, fileName);
		fread(&length, LENGTH_SIZE, 1, fileName);
		fread(name, NAME_SIZE, 1, fileName);
		Column *c = new Column(type, length, name);
		if (type == 'v')
			variableAttributePosition.push_back(i);
		else
			fixedLength += length;
		tableStructure.push_back(c);
	}
}

Table::~Table()
{
	for (int i = 0; i < tableStructure.size(); i++)
		delete tableStructure[i];
	fclose(fileName);
}

bool  Table::structTable(std::vector<Column> tableStructure, FILE *fileName)
{
	fseek(fileName, 0, 0);
	//tableStructure = _tableStructure;
	int size = tableStructure.size();
	fwrite(&size, C_SIZE, 1, fileName);
	fseek(fileName, C_SIZE, 0);
	for (int i = 0; i < size; i++)
	{
		byte type = tableStructure[i].get_dataType();
		ushort length = tableStructure[i].get_dataLength();
		/*if (tableStructure[i].get_dataType() == 'v')
			variableAttributePosition.push_back(i);
			else
			fixedLength += length;*/
		//char name[61];-
		//strcpy(name, tableStructure[i].get_dataName());
		fwrite(&type, TYPE_SIZE, 1, fileName);
		fwrite(&length, LENGTH_SIZE, 1, fileName);
		//fwrite(name, sizeof(name), 1, fileName);
		fwrite(tableStructure[i].get_dataName(), NAME_SIZE, 1, fileName);
		//fseek(fileName, C_SIZE*(i + 1), 0);
	}
	return true;
}

//bool Table::readStructure(std::vector<Column> _tableStructure)
//{
//	
//	_tableStructure = tableStructure;
//	return true;
//}

void Table::showTableStructure()
{
	/*std::vector<Column> t;
	readStructure(t);
	int n = t.size();*/
	//char* s = t[0].get_dataName();
	for (int i = 0; i < tableStructure.size(); i++)
	{
		printf("Type:%c   LENGTH:%hu   Name:%s\n", tableStructure[i]->get_dataType(),
			tableStructure[i]->get_dataLength(), tableStructure[i]->get_dataName());
		//printf("%s",t[i].get_dataName());
	}

}

/*将数据组织成record的格式，并返回指针*/
byte* Table::formRecord(std::vector<byte* > &originalData)
{
	byte* record;
	//数据存放起始点
	ushort startPoint = variableAttributePosition.size() * 4;
	ushort length = fixedLength;
	for each (ushort var in variableAttributePosition)
	{
		length += strlen(originalData[var]);
	}
	record = new byte[length];
	//处理定长数据
	for (int i = 0; i < tableStructure.size(); i++)
	{
		if (tableStructure[i]->get_dataType() == 'v')
			continue;
		memcpy(record + startPoint, originalData[i], tableStructure[i]->get_dataLength());
		startPoint += tableStructure[i]->get_dataLength();
		int a1=*(int*)(originalData[i]);
	}
	//处理变长数据
	for (int i = 0; i < variableAttributePosition.size(); i++)
	{
		ushort vLength = strlen(originalData[variableAttributePosition[i]])+1;
		memcpy(record + 2 * i, &startPoint, sizeof(ushort));
		memcpy(record + 2 * i + 2, &vLength, sizeof(ushort));
		memcpy(record + startPoint, originalData[variableAttributePosition[i]], vLength);
		startPoint += strlen(originalData[variableAttributePosition[i]]);
	}
	return record;
}

byte* Table::parseRecord(byte* record, ushort index)
{
	byte* data;
	ushort position;
	index -= 1;
	int preVariableNumber = 0;
	for each (ushort var in variableAttributePosition)
	{
		if (var < index)
			preVariableNumber++;
	}
	if (tableStructure[index]->get_dataType() == 'v')
	{
		ushort length;
		memcpy(&position, record + 2 * preVariableNumber, 2);
		memcpy(&length, record + 2 * preVariableNumber + 2, 2);
		data = new byte[length];
		memcpy(data, record + position, length);
	}
	else
	{
		data = new byte[tableStructure[index]->get_dataLength()];
		position = 4 * variableAttributePosition.size();
		for (int i = 0; i < index; i++)
		{
			if (tableStructure[i]->get_dataType() == 'v')
			{
				continue;
			}
			position += tableStructure[i]->get_dataLength();
		}
		memcpy(data, record + position, tableStructure[index]->get_dataLength());
	}
	return data;
}

