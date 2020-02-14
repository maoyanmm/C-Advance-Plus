#pragma once
#include<string>
#define CHUNK_BYTE 64
typedef unsigned int uint_32;

class MD5
{
public:
	MD5();

	//初始化：_k[64],和调用reset重置
	void init();

	//重置:_a,_b,_c,_d
	void reset();

	//位运算函数 F G H I
	uint_32 F(uint_32 b, uint_32 c, uint_32 d)
	{
		return (b & c) | ((~b) & d);
	}
	uint_32 G(uint_32 b, uint_32 c, uint_32 d)
	{
		return (b & d) | (c & (~d));
	}
	uint_32 H(uint_32 b, uint_32 c, uint_32 d)
	{
		return b ^ c ^ d;
	}
	uint_32 I(uint_32 b, uint_32 c, uint_32 d)
	{
		return  c ^ (b | (~d));
	}

	//循环左移
	uint_32 left_shift(uint_32 number, int shiftNumber)
	{
		return ((number << shiftNumber) | (number >> (32 - shiftNumber)));
	}

	//计算一个数据块chunk的MD5值
	void cal_MD5(uint_32* chunk);

	//给最后一个块数据添加填充位和比特位长度
	void cal_finalMD5();

	//把abcd转成最后的MD5值
	std::string Hex_change_MD5(uint_32 num);

	std::string getStringMD5(const std::string& str);
	std::string getFileMD5(const char* filePath);
private:

	//循环左移的数组
	static int _leftShift[64];
	//_k[i] = floor(2^(32) * abs(sin(i + 1))) 
	uint_32 _k[64];
	//数据块（64byte）
	char _chunk[CHUNK_BYTE];
	//最后一块数据的字节数
	uint_32 _lastByte;
	//总字节数
	long long _totalByte;
	//MD5的buffer
	uint_32 _a;
	uint_32 _b;
	uint_32 _c;
	uint_32 _d;
};