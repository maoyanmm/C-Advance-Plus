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

//将中间变量转换成十六进制的MD5值
std::string MD5::to_Hex_MD5(const Uint_32& num)
{
	std::string table = "0123456789abcdef";
	std::string ans;
	for (int i = 0; i < 4; ++i)
	{
		//每次循环右移的取出最后的一个字节（8位）
		char tmp = (num >> (i * 8)) & (0xff);
		//取出这8位的前4位
		ans += table[(tmp >> 4) & 0xf];
		//取出这8位的后4位
		ans += table[tmp & 0xf];
	}
	return ans;
}

//计算一块的MD5值（将四个中间变量变化）
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

//计算最后一块数据的MD5值
void MD5::cal_final_MD5()
{
	//p指针指向最后一个数据块的末尾
	char* p = _chunk + _lastByte;
	//先给最后8个比特位置1000 000，因为无论是否要新的数据块，都要填充冗余信息
	*p = 0x80;
	//再次指向末尾（因为多填了一个字节）
	++p;
	//剩余64-最后的数据块大小-刚刚填的一个字节
	Uint_32 remainByte = CHUNK_BYTE - _lastByte - 1;
	memset(p, 0, remainByte);
	//如果剩余的不够8个字节（64bit）则后面填零计算这块MD5，之后创建新的数据块去填充信息
	if (remainByte < 8)
	{
		cal_chunk_MD5((Uint_32*)_chunk);
		memset(_chunk, 0, CHUNK_BYTE);
	}
	unsigned long long file_bytes = 8 * _totalByte;
	//强转成long long是为了让数组偏移的时候可以偏移8个字节
	((unsigned long long*)_chunk)[7] = file_bytes;
	cal_chunk_MD5((Uint_32*)_chunk);
}

//计算文件的MD5值
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
		//如果读的这一块不够64字节
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