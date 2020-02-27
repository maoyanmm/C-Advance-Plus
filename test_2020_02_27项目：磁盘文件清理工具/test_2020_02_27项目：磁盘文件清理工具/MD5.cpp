#include"MD5.h"
#include<fstream>

Uint_32 MD5::_s[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

MD5::MD5()
{
	init();
}

void MD5::reset()
{
	_a = 0x67452301;
	_b = 0xefcdab89;
	_c = 0x98badcfe;
	_d = 0x10325476;
	memset(_chunk, 0, CHUNK_BYTE);
	_lastByte = 0;
	_totalByte = 0;
}

void MD5::init()
{
	for (int i = 0; i < 64; i++)
	{
		_k[i] = (size_t)(abs(sin(i + 1)) * pow(2, 32));
	}
	reset();
}

//���м����ת����ʮ�����Ƶ�MD5ֵ
std::string MD5::to_Hex_MD5(const Uint_32& num)
{
	std::string table = "0123456789abcdef";
	std::string ans;
	for (int i = 0; i < 4; ++i)
	{
		//ÿ��ѭ�����Ƶ�ȡ������һ���ֽڣ�8λ��
		char tmp = (num >> (i * 8)) & (0xff);
		//ȡ����8λ��ǰ4λ
		ans += table[(tmp >> 4) & 0xf];
		//ȡ����8λ�ĺ�4λ
		ans += table[tmp & 0xf];
	}
	return ans;
}

//����һ���MD5ֵ�����ĸ��м�����仯��
void MD5::cal_chunk_MD5(Uint_32* chunk)
{
	Uint_32 a = _a;
	Uint_32 b = _b;
	Uint_32 c = _c;
	Uint_32 d = _d;
	Uint_32 tmp_4 = 0;
	int g = 0;
	for (int i = 0; i < 64; ++i)
	{
		if (i >= 0 && i <= 15)
		{
			tmp_4 = F(b, c, d);
			g = i;
		}
		else if (i >= 16 && i <= 31)
		{
			tmp_4 = G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i <= 47)
		{
			tmp_4 = H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		else
		{
			tmp_4 = I(b, c, d);
			g = (7 * i) % 16;
		}
		int tmp_d = d;
		d = c;
		c = b;
		b = b + left_shift(a + tmp_4 + chunk[g] + _k[i], _s[i]);
		a = tmp_d;
	}
	_a += a;
	_b += b;
	_c += c;
	_d += d;
}

//�������һ�����ݵ�MD5ֵ
void MD5::cal_final_MD5()
{
	//pָ��ָ�����һ�����ݿ��ĩβ
	char* p = _chunk + _lastByte;
	//�ȸ����8������λ��1000 000����Ϊ�����Ƿ�Ҫ�µ����ݿ飬��Ҫ���������Ϣ
	*p = 0x80;
	//�ٴ�ָ��ĩβ����Ϊ������һ���ֽڣ�
	++p;
	//ʣ��64-�������ݿ��С-�ո����һ���ֽ�
	Uint_32 remainByte = CHUNK_BYTE - _lastByte - 1;
	memset(p, 0, remainByte);
	//���ʣ��Ĳ���8���ֽڣ�64bit�����������������MD5��֮�󴴽��µ����ݿ�ȥ�����Ϣ
	if (remainByte < 8)
	{
		cal_chunk_MD5((Uint_32*)_chunk);
		memset(_chunk, 0, CHUNK_BYTE);
	}
	unsigned long long file_bytes = 8 * _totalByte;
	//ǿת��long long��Ϊ��������ƫ�Ƶ�ʱ�����ƫ��8���ֽ�
	((unsigned long long*)_chunk)[7] = file_bytes;
	cal_chunk_MD5((Uint_32*)_chunk);
}

//�����ļ���MD5ֵ
std::string MD5::cal_file_MD5(const char* filePath)
{
	std::string ans;
	std::ifstream in_file(filePath, std::ifstream::binary);
	if (!in_file.is_open())
	{
		perror("file open failed!");
		return ans;
	}
	while (!in_file.eof())
	{
		in_file.read(_chunk, CHUNK_BYTE);
		//���������һ�鲻��64�ֽ�
		if (in_file.gcount() != CHUNK_BYTE)
		{
			break;
		}
		_totalByte += CHUNK_BYTE;
		cal_chunk_MD5((Uint_32*)_chunk);
	}
	_lastByte = in_file.gcount();
	_totalByte += _lastByte;
	if (_lastByte != CHUNK_BYTE)
	{
		cal_final_MD5();
	}
	return to_Hex_MD5(_a).append(to_Hex_MD5(_b)).append(to_Hex_MD5(_c)).append(to_Hex_MD5(_d));
}