#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<assert.h>
#include<functional>

//打印数组
void PrintArray(int* a, int n);

//插入排序
void InsertSort(int* a, int n);
//希尔排序
void ShellSort(int* a, int n);

//选择排序
void SelectSort(int* a, int n);

//向下调整
void ShiftDown(int* a, int n, int root);

//堆排序
void HeapSort(int* a, int n);

//三数取中交换
void GetMidSwap(int* a, int left, int right);

//部分快排
int PartSort(int* a, int left, int right);

int PartSort2(int* a, int left, int right);

int PartSort3(int* a, int left, int right);

//快排
void QuickSort(int* a, int left, int right);

//非递归快排
void QuickSortNor(int* a, int n);

//部分归并排序
void _MergeSort(int* a, int left, int right, int* tmp);

//归并排序
void MergeSort(int* a, int n);

//计数排序
void CountSort(int* a, int n);


