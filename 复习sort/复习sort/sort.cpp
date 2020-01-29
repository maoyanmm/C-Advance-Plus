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

//三数取中交换
void GetMidSwap(int* a, int left, int right)
{
	assert(a);
	int mid = (right - left) / 2 + left;
	if ((a[right] > a[left] && a[left] > a[mid]) || (a[mid] > a[left] && a[left] > a[right]))
	{
		return;
	}
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
		{
			swap(a[mid], a[left]);
		}
		else
		{
			swap(a[right], a[left]);
		}
	}
	else
	{
		if (a[mid] < a[right])
		{
			swap(a[right], a[left]);
		}
		else
		{
			swap(a[mid], a[left]);
		}
	}
}
//部分快排
int PartSort(int* a, int left, int right)
{
	assert(a);
	GetMidSwap(a, left, right);
	int key = a[left];
	while (left < right)
	{
		while (left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
		while (left < right && a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];
	}
	a[left] = key;
	return left;
}
int PartSort2(int* a, int left, int right)
{
	assert(a);
	GetMidSwap(a, left, right);
	int key = a[left];
	int begin = left;
	while (left < right)
	{
		while (left < right && a[right] >= key)
		{
			--right;
		}
		while (left < right && a[left] <= key)
		{
			++left;
		}
		swap(a[left], a[right]);
	}
	swap(a[left], a[begin]);
	return left;
}
int PartSort3(int* a, int left, int right)
{
	assert(a);
	GetMidSwap(a, left, right);
	int key = a[left];
	int prev = left; 
	int cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] <= key && ++prev != cur)
		{
			swap(a[cur], a[prev]);
		}
		++cur;
	}
	swap(a[prev], a[left]);
	return prev;
}
//快排
void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left >= right)
	{
		return;
	}
	int mid = PartSort3(a, left, right);
	QuickSort(a, left, mid - 1);
	QuickSort(a, mid + 1, right);
}
//非递归快排
void QuickSortNor(int* a, int n)
{
	stack<int> st;
	int left = 0;
	int right = n - 1;
	int mid = (right - left) / 2 + left;
	st.push(right);
	st.push(left);
	while (!st.empty())
	{
		left = st.top();
		st.pop();
		right = st.top();
		st.pop();
		mid = PartSort3(a, left, right);
		if (mid + 1 < right)
		{
			st.push(right);
			st.push(mid + 1);
		}
		if (left < mid - 1)
		{
			st.push(mid - 1);
			st.push(left);
		}
	}
}
//部分归并排序
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
	{
		return;
	}
	int mid = (right - left) / 2 + left;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	memcpy(a + left, tmp + left, sizeof(int)*(right - left + 1));
}
//归并排序
void MergeSort(int* a, int n)
{
	int* tmp = new int[n];
	_MergeSort(a, 0, n - 1, tmp);
	delete[] tmp;
}
//计数排序
void CountSort(int* a, int n)
{
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < n; ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	int range = max - min + 1;
	vector<int> count_arr(range,0);
	for (int i = 0; i < n; ++i)
	{
		++count_arr[a[i] - min];
	}
	int index = 0;
	for (int i = 0; i < range; ++i)
	{
		while (count_arr[i]--)
		{
			a[index++] = i + min;
		}
	}
}