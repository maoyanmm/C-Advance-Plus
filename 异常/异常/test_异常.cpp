#include<iostream>
#include<vector>
using namespace std;

//void resource()
//{
//	vector<int> v;
//	v.resize(10000000000);
//}
//
//int main()
//{
//	try{
//		resource();
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "Unkown Eception" << endl;
//	}
//	system("pause");
//	return 0;
//}

//double Division(int a, int b)
//{
//	if (0 == b)
//	{
//		throw "Division by zero!";
//	}
//	else
//	{
//		return (double)a / (double)b;
//	}
//}
//
//void Func()
//{
//	int len, time;
//	cin >> len >> time;
//	cout << Division(len, time) << endl;
//}
//
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (int str)
//	{
//		cout << str << endl;
//	}
//	catch (const char* str)
//	{
//		cout << str << endl;
//	}
//	catch (...)
//	{
//		cout << "Unkown error!" << endl;
//	}
//	system("pause");
//	return 0;
//}

class Exception
{
public:
	virtual void what()
	{
		cout << "程序异常！" << endl;
	}
};

class DivisionError :public Exception
{
public:
	virtual void what()
	{
		cout << "Division by zero!" << endl;
	}
};

class MallocError :public Exception
{
public:
	virtual void what()
	{
		cout << "Malloc too many!" << endl;
	}
};

int Divide()
{
	cout << "输入两个数" << endl;
	int a, b;
	cin >> a >> b;
	if (0 == b)
	{
		throw DivisionError();
	}
	return a / b;
}

int formalloc()
{
	int* p = (int*)malloc(0xffffffff);
	if (p == nullptr)
	{
		throw MallocError();
	}
	free(p);
}

int main()
{
	try
	{
		formalloc();
	}
	catch (Exception& e)
	{
		e.what();
	}
	catch (...)
	{
		cout << "未知错误！" << endl;
	}
	system("pause");
	return 0;
}
