#include<iostream>
using namespace std;

//���з����ṹ��
typedef struct Area
{
	int _address;
	int _capacity;
	int _num;
	struct Area* _prev;
	struct Area* _next;
}Area;

//��ӡ
void Print_Area(Area* Head);

//�˵�
void Menu(Area* Head);

//�״���Ӧ
void FF(Area* Head);

//ѭ���״���Ӧ
void NF(Area* Head);

//��������
void Swap(Area* curx, Area* cury);

//��ѵ�����
void BF_sort(Area* Head,int count);

//�����Ӧ
void BF(Area* Head);

//�������
void WF_sort(Area* Head, int count);

//���Ӧ
void WF(Area* Head);