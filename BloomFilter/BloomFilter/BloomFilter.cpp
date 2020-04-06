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
		//>>5是因为：一个字节32位，>>5相当于除以32。+1是因为：如果不是32的倍数，多出来的也要计算，例如33/32 =1，实际应该要2个字节来算
		_table.resize((range >> 5) + 1);
	}
	void set(int data)
	{
		//算出数组的下标
		size_t int_index = data >> 5;
		//算出一个字节里的比特位位置
		size_t bit_index = (data % 32);
		//或上1，就表示有这个数了
		_table[int_index] |= (1 << bit_index);
	}
	bool find(int data)
	{
		//算出数组的下标
		size_t int_index = data >> 5;
		//算出一个字节里的比特位位置
		size_t bit_index = (data % 32);
		//看那一比特位是否是1
		return ((_table[int_index] >> bit_index) & 1);
	}
	void reset(int data)
	{
		//算出数组的下标
		size_t int_index = data >> 5;
		//算出一个字节里的比特位位置
		size_t bit_index = (data % 32);
		//将那一位与0，其他位这时是与的1（但是与1对其他位没影响）
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
		:_bm(range * 5)//因为是多个映射，所以冲突的概率大，所以要多开一些
		, _bit_num(range * 5)
	{ }
	void set(const K& key)
	{
		//计算出各个哈希函数的位置
		size_t index1 = Hfun1()(key) % _bit_num;
		size_t index2 = Hfun2()(key) % _bit_num;
		size_t index3 = Hfun3()(key) % _bit_num;
		//插入到对应的位图位置
		_bm.set(index1);
		_bm.set(index2);
		_bm.set(index3);
	}
	bool test(const K& key)
	{
		//计算出各个哈希函数的位置
		size_t index1 = Hfun1()(key) % _bit_num;
		size_t index2 = Hfun2()(key) % _bit_num;
		size_t index3 = Hfun3()(key) % _bit_num;
		//逐个检查每个对应比特位是否是1，是1则可能存在，是0则肯定不存在
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