#include<iostream>
#include<vector>
#include<string>
using namespace std;
//��ӡ������Դ
void Print_Resourse(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available);

//�˵�
void menu();

//�ж��Ƿ�ȫ
void Is_Safe(vector<vector<int>>& work_tmp, vector<int>& security_num,int resource_num, int process_num);

//��ȫ���㷨
bool Security(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available);

//���м��㷨
void Bank(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available);
