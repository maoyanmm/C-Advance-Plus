#include<iostream>
#include<mutex>
#include<thread>
#include<stdlib.h>
#include<memory>
using namespace std;

template<class T>
class Auto_ptr
{
public:
	Auto_ptr(T* p = nullptr)
		:_ptr(p)
	{

	}
	~Auto_ptr()
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}
	Auto_ptr(const Auto_ptr<T>& p)
	{
		_ptr = p._ptr;
		p._ptr = nullptr;
	}
	Auto_ptr<T>& operator=(Auto_ptr<T>& p)
	{
		if (&p != this)
		{
			if (_ptr)
			{
				delete _ptr;
			}
			_ptr = p._ptr;
			p._ptr = nullptr;
		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

class A
{
public:
	int _a = 1;
	int _b = 2;

	~A()
	{
		cout << "~A（）" << endl;
	}
};

//int main()
//{
//	/*Auto_ptr<int> ptr(new int(3));
//	cout << *ptr << endl; */
//	Auto_ptr<A> ptr(new A);
//	cout << ptr->_a << endl;
//	Auto_ptr<A> ptr2(new A);
//	ptr = ptr2;
//	cout << ptr->_a << endl;
//	system("pause");
//	return 0;
//}

template<class T>
class Unique_ptr
{
public:
	Unique_ptr(T* p = nullptr)
	{
		_ptr = p;
	}

	~Unique_ptr()
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	Unique_ptr(const Unique_ptr<T>& p) = delete;
	Unique_ptr<T>& operator=(const Unique_ptr<T>& p) = delete;

	int* _ptr;
};

template<class T>
class Shared_ptr
{
public:
	Shared_ptr(T* p)
		:_ptr(p)
		, _count(new int(1))
		, _mtx(new mutex)
	{

	}
	Shared_ptr(Shared_ptr<T>& p)
		:_ptr(p._ptr)
		, _count(p._count)
		, _mtx(p._mtx)
	{
		addRef();
	}
	Shared_ptr<T>& operator=(const Shared_ptr<T>& p)
	{
		if (&p != this)
		{
			//判断现有资源是否可以释放
			Release();
			//指向新的Shared指针
			_ptr = p._ptr;
			_count = p._count;
			_mtx = p._mtx;
			//++_count
			addRef();
		}
		return *this;
	}
	~Shared_ptr()
	{
		Release();
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	int UseCount()
	{
		return *_count;
	}
private:
	int	addRef()
	{
		_mtx->lock();
		++(*_count);
		_mtx->unlock();
		return *_count;
	}
	void Release()
	{
		bool Release_flag = false;

		_mtx->lock();
		if (--(*_count) == 0)
		{
			/*_delete(_ptr);*/
			delete _ptr;
			delete _count;
			Release_flag = true;
		}
		_mtx->unlock();

		if (Release_flag)
		{
			delete _mtx;;
		}
	}
private:
	T* _ptr;
	int* _count;
	mutex* _mtx;
};

mutex mtx;
void test1(Shared_ptr<int> p, int n)
{
	for (int i = 0; i < n; ++i)
	{
		/*mtx.lock();*/
		++(*p);
		/*mtx.unlock();*/
		Shared_ptr<int> copy(p);
	}
}
template<class T>
class Deletearry
{
public:
	void operator()(T* p)
	{
		delete[] p;
	}
};

template<class T>
class Freetearry
{
public:
	void operator()(T* p)
	{
		free(p);
	}
};

class B
{
public:
	~B()
	{
		cout << "~B()" << endl;
	}
};

int main()
{
	Shared_ptr<int> p(new int(1));
	thread t1(test1, p, 100000);
	thread t2(test1, p, 100000);
	t1.join();
	t2.join();
	cout << "*p = " << *p << endl;
	cout << "_count = " << p.UseCount() << endl;

	/*shared_ptr<int> p(new int[3],Deletearry<int>());
	shared_ptr<B> p2(new B[3]);
	shared_ptr<B> p3((B*)malloc(100));*/

	/*Shared_ptr<int> p4(new int[3]);*/
	system("pause");
	return 0;
}

