#include"sort.h"

//打印数组
void PrintArray(int* a, int n)
{
	assert(a);
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
//交换
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//插入排序
void InsertSort(int* a, int n)
{
	assert(a);
	for (int i = 0; i < n - 1; ++i)
	{
		int end = i;//当前要和tmp比较的下标
		int tmp = a[end + 1];//将要插入的数字保存
		while (end >= 0 && a[end] > tmp)//为tmp找到合适的位置
		{
			a[end + 1] = a[end];//向后移动
			--end;
		}
		a[end + 1] = tmp;//找到了比tmp小的位置，将tmp放在这个比tmp小的数的后面
	}
}
//希尔排序
void ShellSort(int* a, int n)
{
	assert(a);
	int gap = n;//间隔
	while (gap > 1)//如果gap==1，再进循环则会变成0
	{
		gap /= 2; 
		for (int i = 0; i < n - gap; ++i)//最后的位置加上gap后不能大于数组的长度，所以是i<n-gap
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0 && a[end] > tmp)
			{
				a[end + gap] = a[end];
				end -= gap;//每次向前比较，间隔是gap
			}
			a[end + gap] = tmp;
		}
	}
}

//选择排序
void SelectSort(int* a, int n)
{
	assert(a);
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int max = begin; 
		int min = begin;
		for (int i = begin; i <= end; ++i)
		{
			if (a[i] > a[max])
			{
				max = i;
			}
			if (a[i] < a[min])
			{
				min = i;
			}
		}
		swap(a[min], a[begin]);
		if (max == begin)
		{
			max = min;
		}
		swap(a[max], a[end]);
		++begin;
		--end;
	}
}

//向下调整
void ShiftDown(int* a, int n, int root)
{
	assert(a);
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child < n && a[child + 1] > a[child])
		{
			++child;
		}
		if (a[child] > a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//堆排序
void HeapSort(int* a, int n)
{
	assert(a);
	int root = (n - 2) / 2;
	for (int i = root; i >= 0; --i)
	{
		ShiftDown(a, n, i);
	}
	int end = n - 1;
	while (end > 0)
	{
		swap(a[end], a[0]);
		--end;
		ShiftDown(a, end, 0);
	}
}