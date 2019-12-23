#include<iostream>
using namespace std;

//空闲分区结构体
typedef struct Area
{
	int _address;
	int _capacity;
	int _num;
	struct Area* _prev;
	struct Area* _next;
}Area;

//打印
void Print_Area(Area* Head);

//菜单
void Menu(Area* Head);

//首次适应
void FF(Area* Head);

//循环首次适应
void NF(Area* Head);

//交换函数
void Swap(Area* curx, Area* cury);

//最佳的排序
void BF_sort(Area* Head,int count);

//最佳适应
void BF(Area* Head);

//最坏的排序
void WF_sort(Area* Head, int count);

//最坏适应
void WF(Area* Head);