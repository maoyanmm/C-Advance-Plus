#include<iostream>
#include<vector>
#include<string>
using namespace std;
//打印各种资源
void Print_Resourse(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available);

//菜单
void menu();

//判断是否安全
void Is_Safe(vector<vector<int>>& work_tmp, vector<int>& security_num,int resource_num, int process_num);

//安全性算法
bool Security(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available);

//银行家算法
void Bank(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available);
