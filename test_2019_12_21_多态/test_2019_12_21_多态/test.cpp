#include<iostream>
using namespace std;

class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1;
};
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2;
};

class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};

typedef void(*vfptr)();

void PrintVfptr(vfptr* p)
{
	while (*p)
	{
		vfptr tmp = *p;
		cout << "µØÖ·£º" << tmp << "  ";
		tmp();
		++p;
	}
}

int main()
{
	Base1 b1;
	Base2 b2;
	Derive d1;



	cout << "Base1µÄ£º" << endl;
	vfptr* p1 = (vfptr*)(*((int*)(&d1)));
	PrintVfptr(p1);

	cout << "Base2µÄ£º" << endl;
	/*vfptr* p2 = (vfptr*)*((int*)((Base1*)(&d1) + 1));*/
	Base2* p2 = &d1;

	PrintVfptr((vfptr*)(*(int*)p2));

	system("pause");
	return 0;
}