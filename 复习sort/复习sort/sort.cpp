#include"sort.h"

//��ӡ����
void PrintArray(int* a, int n)
{
	assert(a);
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
//����
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//��������
void InsertSort(int* a, int n)
{
	assert(a);
	for (int i = 0; i < n - 1; ++i)
	{
		int end = i;//��ǰҪ��tmp�Ƚϵ��±�
		int tmp = a[end + 1];//��Ҫ��������ֱ���
		while (end >= 0 && a[end] > tmp)//Ϊtmp�ҵ����ʵ�λ��
		{
			a[end + 1] = a[end];//����ƶ�
			--end;
		}
		a[end + 1] = tmp;//�ҵ��˱�tmpС��λ�ã���tmp���������tmpС�����ĺ���
	}
}
//ϣ������
void ShellSort(int* a, int n)
{
	assert(a);
	int gap = n;//���
	while (gap > 1)//���gap==1���ٽ�ѭ�������0
	{
		gap /= 2; 
		for (int i = 0; i < n - gap; ++i)//����λ�ü���gap���ܴ�������ĳ��ȣ�������i<n-gap
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0 && a[end] > tmp)
			{
				a[end + gap] = a[end];
				end -= gap;//ÿ����ǰ�Ƚϣ������gap
			}
			a[end + gap] = tmp;
		}
	}
}

//ѡ������
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

//���µ���
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

//������
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

//���ֿ���
int PartSort(int* a, int left, int right)
{
	assert(a);
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
//����
void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left >= right)
	{
		return;
	}
	int mid = PartSort2(a, left, right);
	QuickSort(a, left, mid - 1);
	QuickSort(a, mid + 1, right);
}