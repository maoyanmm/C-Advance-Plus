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

int main()
{
	/*test1();*/
	/*test2();*/
	test3();
	system("pause");
	return 0;
}