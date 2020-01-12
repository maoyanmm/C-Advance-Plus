#include"sort.h"

void test1()
{
	int arr[] = { 5, 2, 4, 6, 1, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);
	PrintArray(arr, n);
	InsertSort(arr, n);
	PrintArray(arr, n);
}

void test2()
{
	int arr[] = { 9,1,2,5,7,4,8,6,3,5};
	int n = sizeof(arr) / sizeof(arr[0]);
	PrintArray(arr, n);
	ShellSort(arr, n);
	PrintArray(arr, n);
}

void test3()
{
	int arr[] = { 7,4,5,9,8,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	PrintArray(arr, n);
	SelectSort(arr, n);
	PrintArray(arr, n);
}

void test4()
{
	int arr[] = { 20,17,4,16,5,3};
	int n = sizeof(arr) / sizeof(arr[0]);
	PrintArray(arr, n);
	HeapSort(arr, n);
	PrintArray(arr, n);
}

void test5()
{
	int arr[] = { 6,1,2,7,9,3,4,5,10,8 };
	int n = sizeof(arr) / sizeof(arr[0]);
	PrintArray(arr, n);
	QuickSort(arr, 0,n-1);
	PrintArray(arr, n);
}

//bool cmp(int a, int b)
//{
//	return a > b;
//}
//
//struct ccc
//{
//	bool operator()(int a,int b)
//	{
//		return a > b;
//	}
//};

int main()
{
	/*test1();*/
	/*test2();*/
	/*test3();*/
	/*test4();*/
	test5();
	system("pause");
	return 0;
}