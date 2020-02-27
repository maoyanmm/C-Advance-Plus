#pragma once
#include<math.h>
#include<algorithm>
#include<string>
typedef unsigned int Uint_32;
#define CHUNK_BYTE 64

class MD5
{
public:
	MD5();
	//重置各个数据
	void reset();
	//初始化各个数据
	void init();
	//位运算函数
	Uint_32 F(Uint_32 b, Uint_32 c, Uint_32 d)
	{
		return (b & c) | ((~b) & d);
	}
	Uint_32 G(Uint_32 b, Uint_32 c, Uint_32 d)
	{
		return (b & d) | (c & (~d));
	}
	Uint_32 H(Uint_32 b, Uint_32 c, Uint_32 d)
	{
		return  b ^ c ^ d;
	}
	Uint_32 I(Uint_32 b, Uint_32 c, Uint_32 d)
	{
		return c ^ (b | (~d));
	}
	//将中间变量转换成十六进制的MD5值
	std::string to_Hex_MD5(const Uint_32& num);
	//计算一块的MD5值（将四个中间变量变化）
	void cal_chunk_MD5(Uint_32* chunk);
	//循环左移
	Uint_32 left_shift(Uint_32 num, int shiftNumber)
	{
		return ((num << shiftNumber) | (num >> (32 - shiftNumber)));
	}
	//计算最后一块数据的MD5值
	void cal_final_MD5();
	//计算文件的MD5值
	std::string cal_file_MD5(const char* path);

private:
	static size_t _s[64];
	//要计算的中间变量
	Uint_32 _a;
	Uint_32 _b;
	Uint_32 _c;
	Uint_32 _d;
	//计算用到的参数k表
	Uint_32 _k[64];
	//数据块
	char _chunk[CHUNK_BYTE];
	//最后一块数据块的大小
	Uint_32 _lastByte;
	//文件总大小
	Uint_32 _totalByte;
};
