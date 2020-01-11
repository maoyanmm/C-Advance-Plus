#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<assert.h>
#include<functional>

//��ӡ����
void PrintArray(int* a, int n);

//��������
void InsertSort(int* a, int n);
//ϣ������
void ShellSort(int* a, int n);

//ѡ������
void SelectSort(int* a, int n);

//���µ���
void ShiftDown(int* a, int n, int root);

//������
void HeapSort(int* a, int n);

//����ȡ�н���
void GetMidSwap(int* a, int left, int right);

//���ֿ���
int PartSort(int* a, int left, int right);

int PartSort2(int* a, int left, int right);

int PartSort3(int* a, int left, int right);

//����
void QuickSort(int* a, int left, int right);

//�ǵݹ����
void QuickSortNor(int* a, int n);

//���ֹ鲢����
void _MergeSort(int* a, int left, int right, int* tmp);

//�鲢����
void MergeSort(int* a, int n);

//��������
void CountSort(int* a, int n);


