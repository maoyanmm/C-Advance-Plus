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
	//���ø�������
	void reset();
	//��ʼ����������
	void init();
	//λ���㺯��
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
	//���м����ת����ʮ�����Ƶ�MD5ֵ
	std::string to_Hex_MD5(const Uint_32& num);
	//����һ���MD5ֵ�����ĸ��м�����仯��
	void cal_chunk_MD5(Uint_32* chunk);
	//ѭ������
	Uint_32 left_shift(Uint_32 num, int shiftNumber)
	{
		return ((num << shiftNumber) | (num >> (32 - shiftNumber)));
	}
	//�������һ�����ݵ�MD5ֵ
	void cal_final_MD5();
	//�����ļ���MD5ֵ
	std::string cal_file_MD5(const char* path);

private:
	static size_t _s[64];
	//Ҫ������м����
	Uint_32 _a;
	Uint_32 _b;
	Uint_32 _c;
	Uint_32 _d;
	//�����õ��Ĳ���k��
	Uint_32 _k[64];
	//���ݿ�
	char _chunk[CHUNK_BYTE];
	//���һ�����ݿ�Ĵ�С
	Uint_32 _lastByte;
	//�ļ��ܴ�С
	Uint_32 _totalByte;
};
