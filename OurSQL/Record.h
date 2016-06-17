#pragma once
typedef char byte;
typedef unsigned short int ushort;

class Record
{
public:
	Record(const char *);
	~Record();

	ushort getLength();

	// 返回这个Record存放数据的首地址
	byte* getData();

private:
	byte* data;
};

