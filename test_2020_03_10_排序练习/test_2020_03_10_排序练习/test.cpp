#include<iostream>
using namespace std;
#include<vector>
#include<stack>
struct Node
{
	int _left;
	int _right;
	Node(int l, int r)
	{
		_left = l;
		_right = r;
	}
};

void Print_Array(vector<int>& num)
{
	for (auto& e : num)
	{
		cout << e << " ";
	}
	cout << endl;
}

int Part_Sort(vector<int>& num, int left, int right)
{
	int key = num[left];
	int begin = left;
	while (left < right)
	{
		while (left < right && num[right] >= key)
		{
			--right;
		}
		while (left < right && num[left] <= key)
		{
			++left;
		}
		swap(num[left], num[right]);
	}
	int mid = left;
	swap(num[mid], num[begin]);
	return mid;
}

void Quick_Sort(vector<int>& num, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = Part_Sort(num, left, right);
	Quick_Sort(num, left, mid - 1);
	Quick_Sort(num, mid + 1, right);
}

void Quick_Sort_Nor(vector<int>& num)
{
	stack<Node> st;
	int left = 0;
	int right = num.size() - 1;
	Node node(left, right);
	st.push(node);
	while (!st.empty())
	{
		left = st.top()._left;
		right = st.top()._right;
		st.pop();

		int mid = Part_Sort(num, left, right);
		if (left < mid-1)
		{
			st.push(Node(left, mid - 1));
		}
		if (mid+1 < right)
		{
			st.push(Node(mid + 1, right));
		}
	}
}

void _Merge_Sort(vector<int>& tmp, vector<int>& num, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = (right - left) / 2 + left;
	_Merge_Sort(tmp, num, left, mid);
	_Merge_Sort(tmp, num, mid + 1, right);
	int index = left;
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (num[begin1] <= num[begin2])
		{
			tmp[index++] = num[begin1++];
		}
		else
		{
			tmp[index++] = num[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[index++] = num[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = num[begin2++];
	}
	for (int i = left; i <= right; ++i)
	{
		num[i] = tmp[i];
	}
}

void Merge_Sort(vector<int>& num)
{
	vector<int> tmp = num;
	_Merge_Sort(tmp, num, 0, num.size() - 1);
	num = tmp;
}

void Shell_Sort(vector<int>& num)
{
	int gap = num.size();
	while (gap >= 1)
	{
		gap /= 2;
		for (int i = 0; i < num.size() - gap; ++i)
		{
			int card = num[i + gap];
			int j = i;
			for (; j >= 0 && num[j] > card; j -= gap)
			{
				num[j + gap] = num[j];
			}
			num[j + gap] = card;
		}
	}
}

void Shift_Down(vector<int>& num, int root, int size)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && num[child + 1] > num[child])
		{
			++child;
		}
		if (num[child] > num[parent])
		{
			swap(num[child], num[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void Heap_Sort(vector<int>& num)
{
	//½¨¶Ñ
	int size = num.size();
	for (int i = (size-2)/2; i >= 0; --i)
	{
		Shift_Down(num, i, size);
	}
	while (size > 1)
	{
		swap(num[0], num[--size]);
		Shift_Down(num, 0, size);
	}
}

void test()
{
	vector<int> arr = { 8, 6, 4, 1, 9, 2, 3, 5, 6, 1, 0, 9, 7, 2 };
	Heap_Sort(arr);
	Print_Array(arr);
}

int main()
{
	test();
	system("pause");
	return 0;
}