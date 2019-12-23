#include"list.h"

//�˵�
void Menu(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR�������ͷΪ�գ�" << endl;
		return;
	}
	
	cout << "��������з�����" << endl;
	int n;
	cin >> n;
	Area* cur = Head;//���ñ�ʾ��ǰ��ָ��
	for (int i = 0; i < n; ++i)
	{
		printf("�������%d����������ַ��", i + 1);
		Area* tmp(new Area);
		cin >> tmp->_address;
		tmp->_num = i + 1;
		cur->_next = tmp;
		tmp->_prev = cur;
		cur = cur->_next;
	}
	cur->_next = nullptr;//�����һ������ÿ�
	Area* cur2 = Head->_next;//�ڶ����ڵ���ʽ��¼����
	for (int i = 0; i < n; ++i)
	{
		printf("�������%d����������С��", i + 1);
		cin >> cur2->_capacity;
		cur2 = cur2->_next;
	}
	Print_Area(Head);

	cout << "--------��̬���������㷨---------" << endl;
	cout << "1.�״���Ӧ�㷨FF" << endl;
	cout << "2.ѭ���״���Ӧ�㷨NF" << endl;
	cout << "3.�����Ӧ�㷨BF" << endl;
	cout << "4.���Ӧ�㷨WF" << endl;
	cout << "�����룺" << endl;
	cout << "�㷨�����" << endl;
	
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
		cout << "������������������" << endl;
		break;
	}
}

//��ӡ
void Print_Area(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR�������ͷΪ�գ�" << endl;
		return;
	}

	cout << "�����ţ�";
	Area* cur = Head->_next;
	while (cur)
	{
		printf("%-5d", cur->_num);
		cur = cur->_next;
	}
	cout << endl;

	cout << "��ַ�ţ�" ;
	Area* cur2 = Head->_next;
	while (cur2)
	{
		printf("%-5d", cur2->_address);
		cur2 = cur2->_next;
	}
	cout << endl;

	cout << "��С����" ;
	Area* cur3 = Head->_next;
	while (cur3)
	{
		printf("%-5d", cur3->_capacity);
		cur3 = cur3->_next;
	}
	cout << endl;
}

//�״���Ӧ
void FF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR�������ͷΪ�գ�" << endl;
		return;
	}
	cout << "��������ҵ������" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//��¼��ҵ������
	for (int i = 0; i < n; ++i)
	{
		printf("�������%d������ҵ��С:\n",i+1);
		cin >> work[i];
	}
	//��ʼ�����е���ҵ����
	Area* cur = Head->_next;
	for (int i = 0; i < n; ++i)
	{
		cur = Head->_next;//ÿ�ζ��ӵ�һ��������ʼ����
		while (cur)
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//�����仯
				cur->_address += work[i];//���ʱ仯
				break;
			}
			cur = cur->_next;
		}
		if (nullptr == cur)
		{
			printf("��%d����ҵδ�ܷ��䵽�㹻��Ŀ��з�����\n", i + 1);
		}
	}
	Print_Area(Head);
}

//ѭ���״���Ӧ
void NF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR�������ͷΪ�գ�" << endl;
		return;
	}
	cout << "��������ҵ������" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//��¼��ҵ������
	for (int i = 0; i < n; ++i)
	{
		printf("�������%d������ҵ��С:\n", i + 1);
		cin >> work[i];
	}
	//��ʼ�����е���ҵ����
	Area* cur = Head;
	for (int i = 0; i < n; ++i)
	{
		if (cur->_next == nullptr)//��������һ����㣬�ʹӵ�һ����ʼ����
		{
			cur = Head->_next;
		}
		else
		{
			cur = cur->_next;
		}
		Area* flag = cur;//���ñ�־λ��Ϊ�������ѭ���ҷ����и�����
		int over = 0;//�����ж��Ƿ��ѷ��䣬������Ϊ0
		do
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//�����仯
				cur->_address += work[i];//���ʱ仯
				over = 1;
				break;
			}
			if (cur->_next == nullptr)//��������һ����㣬�ʹӵ�һ����ʼ����
			{
				cur = Head->_next;
			}
			else
			{
				cur = cur->_next;
			}
		} while (cur != flag);

		if (flag == cur && 0 == over)//�������һȦû�ҵ�����û������
		{
			printf("��%d����ҵδ�ܷ��䵽�㹻��Ŀ��з�����\n", i + 1);
		}
	}
	Print_Area(Head);
	delete[] work;
}

//��������
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

//��ѵ�������
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

//�����Ӧ
void BF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR�������ͷΪ�գ�" << endl;
		return;
	}
	cout << "��������ҵ������" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//��¼��ҵ������
	for (int i = 0; i < n; ++i)
	{
		printf("�������%d������ҵ��С:\n", i + 1);
		cin >> work[i];
	}
	
	int count = 0;//��������
	Area* cur1 = Head->_next;
	while (cur1)
	{
		++count;
		cur1 = cur1->_next;
	}
	

	//��ʼ�����е���ҵ����
	Area* cur = Head->_next;
	for (int i = 0; i < n; ++i)
	{
		BF_sort(Head, count);//ÿ�β���ǰ����
		cur = Head->_next;//ÿ�ζ��ӵ�һ��������ʼ����
		while (cur)
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//�����仯
				cur->_address += work[i];//��ַ�仯
				break;
			}
			cur = cur->_next;
		}
		if (nullptr == cur)
		{
			printf("��%d����ҵδ�ܷ��䵽�㹻��Ŀ��з�����\n", i + 1);
		}
	}
	Print_Area(Head);
}

//�������
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

//���Ӧ
void WF(Area* Head)
{
	if (Head == nullptr)
	{
		cout << "ERROR�������ͷΪ�գ�" << endl;
		return;
	}
	cout << "��������ҵ������" << endl;
	int n;
	cin >> n;
	int* work = new int[n];//��¼��ҵ������
	for (int i = 0; i < n; ++i)
	{
		printf("�������%d������ҵ��С:\n", i + 1);
		cin >> work[i];
	}

	int count = 0;//��������
	Area* cur1 = Head->_next;
	while (cur1)
	{
		++count;
		cur1 = cur1->_next;
	}


	//��ʼ�����е���ҵ����
	Area* cur = Head->_next;
	for (int i = 0; i < n; ++i)
	{
		WF_sort(Head, count);//ÿ�β���ǰ����
		cur = Head->_next;//ÿ�ζ��ӵ�һ��������ʼ����
		while (cur)
		{
			if (cur->_capacity >= work[i])
			{
				cur->_capacity -= work[i];//�����仯
				cur->_address += work[i];//��ַ�仯
				break;
			}
			cur = cur->_next;
		}
		if (nullptr == cur)
		{
			printf("��%d����ҵδ�ܷ��䵽�㹻��Ŀ��з�����\n", i + 1);
		}
	}
	Print_Area(Head);
}