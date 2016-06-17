#pragma once
typedef char byte;
typedef unsigned short int ushort;

class Record
{
public:
	Record();
	~Record();

	ushort getSize();

	// 返回这个Record存放数据的首地址
	byte* getData();

private:

};

