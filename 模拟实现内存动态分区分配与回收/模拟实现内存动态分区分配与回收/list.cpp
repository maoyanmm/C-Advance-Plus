#include"list.h"

//菜单
void Menu(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR：传入的头为空！" << endl;
		return;
	}
	
	cout << "请输入空闲分区数" << endl;
	int n;
	cin >> n;
	Area* cur = Head;//设置表示当前的指针
	for (int i = 0; i < n; ++i)
	{
		printf("请输入第%d个空闲区首址：", i + 1);
		Area* tmp(new Area);
		cin >> tmp->_address;
		tmp->_num = i + 1;
		cur->_next = tmp;
		tmp->_prev = cur;
		cur = cur->_next;
	}
	cur->_next = nullptr;//把最后一个结点置空
	Area* cur2 = Head->_next;//第二个节点正式记录数据
	for (int i = 0; i < n; ++i)
	{
		printf("请输入第%d个空闲区大小：", i + 1);
		cin >> cur2->_capacity;
		cur2 = cur2->_next;
	}
	Print_Area(Head);

	cout << "--------动态分区分配算法---------" << endl;
	cout << "1.首次适应算法FF" << endl;
	cout << "2.循环首次适应算法NF" << endl;
	cout << "3.最佳适应算法BF" << endl;
	cout << "4.最坏适应算法WF" << endl;
	cout << "请输入：" << endl;
	cout << "算法的序号" << endl;
	
	int m;
	cin >> m;
	switch (m)
	{
	case 1:
		FF(Head);
		break;
	case 2:
		NF(Head);
		break;
	case 3:
		BF(Head);
		break;
	case 4:
		WF(Head);
		break;
	default:
		cout << "输入有误请重新输入" << endl;
		break;
	}
}

//打印
void Print_Area(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR：传入的头为空！" << endl;
		return;
	}

	cout << "分区号：";
	Area* cur = Head->_next;
	while (cur)
	{
		printf("%-5d", cur->_num);
		cur = cur->_next;
	}
	cout << endl;

	cout << "地址号：" ;
	Area* cur2 = Head->_next;
	while (cur2)
	{
		printf("%-5d", cur2->_address);
		cur2 = cur2->_next;
	}
	cout << endl;

	cout << "大小量：" ;
	Area* cur3 = Head->_next;
	while (cur3)
	{
		printf("%-5d", cur3->_capacity);
		cur3 = cur3->_next;
	}
	cout << endl;
}

//首次适应
void FF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR：传入的头为空！" << endl;
		return;
	}
	cout << "请输入作业数量：" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//记录作业的数组
	for (int i = 0; i < n; ++i)
	{
		printf("请输入第%d个的作业大小:\n",i+1);
		cin >> work[i];
	}
	//开始将所有的作业分配
	Area* cur = Head->_next;
	for (int i = 0; i < n; ++i)
	{
		cur = Head->_next;//每次都从第一个分区开始查找
		while (cur)
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//容量变化
				cur->_address += work[i];//地质变化
				break;
			}
			cur = cur->_next;
		}
		if (nullptr == cur)
		{
			printf("第%d个作业未能分配到足够大的空闲分区！\n", i + 1);
		}
	}
	Print_Area(Head);
}

//循环首次适应
void NF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR：传入的头为空！" << endl;
		return;
	}
	cout << "请输入作业数量：" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//记录作业的数组
	for (int i = 0; i < n; ++i)
	{
		printf("请输入第%d个的作业大小:\n", i + 1);
		cin >> work[i];
	}
	//开始将所有的作业分配
	Area* cur = Head;
	for (int i = 0; i < n; ++i)
	{
		if (cur->_next == nullptr)//如果是最后一个结点，就从第一个开始找起
		{
			cur = Head->_next;
		}
		else
		{
			cur = cur->_next;
		}
		Area* flag = cur;//设置标志位，为了下面的循环找分区有个出口
		int over = 0;//用来判断是否已分配，分配则为0
		do
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//容量变化
				cur->_address += work[i];//地质变化
				over = 1;
				break;
			}
			if (cur->_next == nullptr)//如果是最后一个结点，就从第一个开始找起
			{
				cur = Head->_next;
			}
			else
			{
				cur = cur->_next;
			}
		} while (cur != flag);

		if (flag == cur && 0 == over)//如果找了一圈没找到就是没法分配
		{
			printf("第%d个作业未能分配到足够大的空闲分区！\n", i + 1);
		}
	}
	Print_Area(Head);
	delete[] work;
}

//交换函数
void Swap(Area* curx, Area* cury,Area* now)
{
	cury->_prev = curx->_prev;
	curx->_prev->_next = cury;
	curx->_prev = cury;
	curx->_next = cury->_next;
	if (cury->_next)
	cury->_next->_prev = curx;
	cury->_next = curx;
	now = curx;
}

//最佳的排序函数
void BF_sort(Area* Head,int count)
{
	Area* cur1 = Head;
	for (int i = 0; i < count - 1; ++i)
	{
		Area* curx = cur1->_next;
		Area* cury = cur1->_next;
		Area* now = cur1->_next;
		for (int j = 0; j < count - i - 1; ++j)
		{
			curx = now;
			cury = curx->_next;
			if (curx->_capacity > cury->_capacity)
			{
				Swap(curx, cury, now);
			}
			else
			{
				now = cury;
			}
		}
	}
}

//最佳适应
void BF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR：传入的头为空！" << endl;
		return;
	}
	cout << "请输入作业数量：" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//记录作业的数组
	for (int i = 0; i < n; ++i)
	{
		printf("请输入第%d个的作业大小:\n", i + 1);
		cin >> work[i];
	}
	
	int count = 0;//给结点计数
	Area* cur1 = Head->_next;
	while (cur1)
	{
		++count;
		cur1 = cur1->_next;
	}
	

	//开始将所有的作业分配
	Area* cur = Head->_next;
	for (int i = 0; i < n; ++i)
	{
		BF_sort(Head, count);//每次查找前排序
		cur = Head->_next;//每次都从第一个分区开始查找
		while (cur)
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//容量变化
				cur->_address += work[i];//地址变化
				break;
			}
			cur = cur->_next;
		}
		if (nullptr == cur)
		{
			printf("第%d个作业未能分配到足够大的空闲分区！\n", i + 1);
		}
	}
	Print_Area(Head);
}

//最坏的排序
void WF_sort(Area* Head, int count)
{
	Area* cur1 = Head;
	for (int i = 0; i < count - 1; ++i)
	{
		Area* curx = cur1->_next;
		Area* cury = cur1->_next;
		Area* now = cur1->_next;
		for (int j = 0; j < count - i - 1; ++j)
		{
			curx = now;
			cury = curx->_next;
			if (curx->_capacity < cury->_capacity)
			{
				Swap(curx, cury, now);
			}
			else
			{
				now = cury;
			}
		}
	}
}

//最坏适应
void WF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR：传入的头为空！" << endl;
		return;
	}
	cout << "请输入作业数量：" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//记录作业的数组
	for (int i = 0; i < n; ++i)
	{
		printf("请输入第%d个的作业大小:\n", i + 1);
		cin >> work[i];
	}

	int count = 0;//给结点计数
	Area* cur1 = Head->_next;
	while (cur1)
	{
		++count;
		cur1 = cur1->_next;
	}


	//开始将所有的作业分配
	Area* cur = Head->_next;
	for (int i = 0; i < n; ++i)
	{
		WF_sort(Head, count);//每次查找前排序
		cur = Head->_next;//每次都从第一个分区开始查找
		while (cur)
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//容量变化
				cur->_address += work[i];//地址变化
				break;
			}
			cur = cur->_next;
		}
		if (nullptr == cur)
		{
			printf("第%d个作业未能分配到足够大的空闲分区！\n", i + 1);
		}
	}
	Print_Area(Head);
}