#pragma once
#include<string>
#define CHUNK_BYTE 64
typedef unsigned int uint_32;

class MD5
{
public:
	MD5();

	//��ʼ����_k[64],�͵���reset����
	void init();

	//����:_a,_b,_c,_d
	void reset();

	//λ���㺯�� F G H I
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

	//ѭ������
	uint_32 left_shift(uint_32 number, int shiftNumber)
	{
		return ((number << shiftNumber) | (number >> (32 - shiftNumber)));
	}

	//����һ�����ݿ�chunk��MD5ֵ
	void cal_MD5(uint_32* chunk);

	//�����һ��������������λ�ͱ���λ����
	void cal_finalMD5();

	//��abcdת������MD5ֵ
	std::string Hex_change_MD5(uint_32 num);

	std::string getStringMD5(const std::string& str);
	std::string getFileMD5(const char* filePath);
private:

	//ѭ�����Ƶ�����
	static int _leftShift[64];
	//_k[i] = floor(2^(32) * abs(sin(i + 1))) 
	uint_32 _k[64];
	//���ݿ飨64byte��
	char _chunk[CHUNK_BYTE];
	//���һ�����ݵ��ֽ���
	uint_32 _lastByte;
	//���ֽ���
	long long _totalByte;
	//MD5��buffer
	uint_32 _a;
	uint_32 _b;
	uint_32 _c;
	uint_32 _d;
};