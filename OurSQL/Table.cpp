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
		if (!c->isFixLength())
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
		byte type = tableStructure[i].getDataType();
		ushort length = tableStructure[i].getDataLength();
		/*if (tableStructure[i].getDataType() == 'v')
			variableAttributePosition.push_back(i);
			else
			fixedLength += length;*/
			//char name[61];-
			//strcpy(name, tableStructure[i].getDataName());
		fwrite(&type, TYPE_SIZE, 1, fileName);
		fwrite(&length, LENGTH_SIZE, 1, fileName);
		//fwrite(name, sizeof(name), 1, fileName);
		fwrite(tableStructure[i].getDataName(), NAME_SIZE, 1, fileName);
		//fseek(fileName, C_SIZE*(i + 1), 0);
	}
	return true;
}

void Table::showTableStructure()
{
	printf("%8s|%8s|%8s\n", "Type", "Length", "Name");
	for (int i = 0; i < tableStructure.size(); i++)
	{
		printf("%8s|%8hu|%8s\n", tableStructure[i]->getTypeName(),
			tableStructure[i]->getDataLength(), tableStructure[i]->getDataName());
	}

}

/*将数据组织成record的格式，并返回指针*/
byte* Table::formRecord(std::vector<byte* > &originalData, int& length)
{
	byte* record;
	//数据存放起始点
	ushort startPoint = variableAttributePosition.size() * 4;
	length = fixedLength;
	for each (ushort var in variableAttributePosition)
	{
		length += strlen(originalData[var]) + 5;
	}
	record = new byte[length];
	//处理定长数据
	for (int i = 0; i < tableStructure.size(); i++)
	{
		if (!tableStructure[i]->isFixLength())
			continue;
		memcpy(record + startPoint, originalData[i], tableStructure[i]->getDataLength());
		startPoint += tableStructure[i]->getDataLength();
		int a1 = *(int*)(originalData[i]);
	}
	//处理变长数据
	for (int i = 0; i < variableAttributePosition.size(); i++)
	{
		ushort vLength = strlen(originalData[variableAttributePosition[i]]) + 1;
		memcpy(record + 2 * i, &startPoint, sizeof(ushort));
		memcpy(record + 2 * i + 2, &vLength, sizeof(ushort));
		memcpy(record + startPoint, originalData[variableAttributePosition[i]], vLength);
		startPoint += strlen(originalData[variableAttributePosition[i]]) + 1;
	}
	return record;
}

byte * Table::getColumnData(ushort index)
{
	return tableStructure[index]->getData();
}

int Table::getColumnSize()
{
	return tableStructure.size();
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
	if (!tableStructure[index]->isFixLength())
	{
		ushort length;
		memcpy(&position, record + 2 * preVariableNumber, 2);
		memcpy(&length, record + 2 * preVariableNumber + 2, 2);
		data = new byte[length];
		memcpy(data, record + position, length);
	}
	else
	{
		data = new byte[tableStructure[index]->getDataLength()];
		position = 4 * variableAttributePosition.size();
		for (int i = 0; i < index; i++)
		{
			if (!tableStructure[i]->isFixLength())
			{
				continue;
			}
			position += tableStructure[i]->getDataLength();
		}
		memcpy(data, record + position, tableStructure[index]->getDataLength());
	}
	return data;
}

int Table::compareRecord(byte* record, byte* conditionData, int dataPostion)
{
	byte* recordData = parseRecord(record, dataPostion);
	switch (tableStructure[dataPostion]->getDataType())
	{
	case 1:return strcmp(recordData, conditionData);
	case 2: return *recordData - *conditionData; break;
	case 3:return *(int*)recordData > *(int*)conditionData; break;
	case 4:return *(double*)recordData - *(double*)conditionData; break;
	case 5:return *(float*)recordData - *(float*)conditionData; break;
	default: return 0; break;
	}
}

void Table::printTitle()
{
	//printf("%8s", tableStructure[0]->getDataName());
	for (int i = 0; i < tableStructure.size(); i++)
	{
		printf("%8s|", tableStructure[i]->getDataName());
	}
}

void Table::printRecord(byte* record)
{
	for (int i = 1; i <= tableStructure.size(); i++)
	{
		switch (tableStructure[i-1]->getDataType())
		{
		case 1:printf("%8s|", parseRecord(record, i)); break;
		case 2:printf("%8c|", *parseRecord(record, i)); break;
		case 3:printf("%8d|", *(int*)parseRecord(record, i)); break;
		case 4:printf("%8lf|", *(double*)parseRecord(record, i)); break;
		case 5:printf("%8s|", *(float*)parseRecord(record, i)); break;
		default:
			break;
		}
	}
}