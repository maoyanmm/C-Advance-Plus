#include<vector>
using namespace std;
#include<iostream>
#include<string>
class BitMap
{
private:
	vector<int> _table;
public:
	BitMap(size_t range)
	{
		//>>5����Ϊ��һ���ֽ�32λ��>>5�൱�ڳ���32��+1����Ϊ���������32�ı������������ҲҪ���㣬����33/32 =1��ʵ��Ӧ��Ҫ2���ֽ�����
		_table.resize((range >> 5) + 1);
	}
	void set(int data)
	{
		//���������±�
		size_t int_index = data >> 5;
		//���һ���ֽ���ı���λλ��
		size_t bit_index = (data % 32);
		//����1���ͱ�ʾ���������
		_table[int_index] |= (1 << bit_index);
	}
	bool find(int data)
	{
		//���������±�
		size_t int_index = data >> 5;
		//���һ���ֽ���ı���λλ��
		size_t bit_index = (data % 32);
		//����һ����λ�Ƿ���1
		return ((_table[int_index] >> bit_index) & 1);
	}
	void reset(int data)
	{
		//���������±�
		size_t int_index = data >> 5;
		//���һ���ֽ���ı���λλ��
		size_t bit_index = (data % 32);
		//����һλ��0������λ��ʱ�����1��������1������λûӰ�죩
		_table[int_index] &= ~(1 << bit_index);
	}
};

template<class K,class Hfun1,class Hfun2,class Hfun3>
class BloomFilter
{
private:
	BitMap _bm;
	size_t _bit_num;
public:
	BloomFilter(size_t range)
		:_bm(range * 5)//��Ϊ�Ƕ��ӳ�䣬���Գ�ͻ�ĸ��ʴ�����Ҫ�࿪һЩ
		, _bit_num(range * 5)
	{ }
	void set(const K& key)
	{
		//�����������ϣ������λ��
		size_t index1 = Hfun1()(key) % _bit_num;
		size_t index2 = Hfun2()(key) % _bit_num;
		size_t index3 = Hfun3()(key) % _bit_num;
		//���뵽��Ӧ��λͼλ��
		_bm.set(index1);
		_bm.set(index2);
		_bm.set(index3);
	}
	bool test(const K& key)
	{
		//�����������ϣ������λ��
		size_t index1 = Hfun1()(key) % _bit_num;
		size_t index2 = Hfun2()(key) % _bit_num;
		size_t index3 = Hfun3()(key) % _bit_num;
		//������ÿ����Ӧ����λ�Ƿ���1����1����ܴ��ڣ���0��϶�������
		if (_bm.find(index1) == false)
		{
			return false;
		}
		if (_bm.find(index2) == false)
		{
			return false;
		}
		if (_bm.find(index3) == false)
		{
			return false;
		}
		return true;
	}
};

struct Hfun1
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};
struct Hfun2
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
		{
			hash = hash * 65599 + ch;
		}
		return hash;
	}
};
struct Hfun3
{
	size_t operator()(const string& str)
	{
		size_t magic = 0;
		size_t hash = 0;
		for (const auto& ch : str)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

void test()
{
	BloomFilter<string, Hfun1, Hfun2, Hfun3> bf(10);
	string str1 = "adsadsasdgs768s9829a";
	string str2 = "adsadsasdgs768s9829b";
	string str3 = "adsadsasdgs768s9829c";
	bf.set(str1);
	bf.set(str2);
	bf.set(str3);
	cout << "bf.test(str1)" << bf.test(str1) << endl;
	cout << "bf.test(str2)" << bf.test(str2) << endl;
	cout << "bf.test(str3)" << bf.test(str3+"A") << endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}