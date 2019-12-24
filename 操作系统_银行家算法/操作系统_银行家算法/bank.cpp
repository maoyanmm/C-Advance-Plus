#include"bank.h"
//请求大于了合法需求
//系统当前资源数不能满足请求，进入阻塞状态
//4351232

//打印各种资源
void Print_Resourse(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available)
{
	int n = Allocation.size();
	int m = Allocation[0].size();
	//打印和Available值相等的Work
	cout << endl;
	cout << "Work  ";
	for (int i = 0; i < m; ++i)
	{
		printf("R%d  ", i);
	}
	cout << endl;
	cout << "      ";
	for (int i = 0; i < m; ++i)
	{
		printf(" %d  ", Available[i]);
	}
	cout << endl;
	//打印表项
	cout << "      Allocation                  " << "              Need              " << "                 Finish     " << endl;
	cout << "    ";
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("R%-8d", j);
		}
		cout << "                  ";
	}
	cout << endl;
	//打印各个进程的各种资源
	for (int i = 0; i < n; ++i)
	{
		printf("P%d  ", i);
		for (int j = 0; j < m; ++j)
		{
			printf("%-10d", Allocation[i][j]);
		}
		cout << "               ";
		for (int j = 0; j < m; ++j)
		{
			printf("%-10d", Need[i][j]);
		}	
		cout << "                 ";
		cout << "false" << endl;
	}
}

//菜单
void menu()
{
	cout << "------银行家算法------" << endl;
	cout << "请输入进程数：" << endl;
	int n;
	cin >> n;
	cout << "请输入资源种类数：" << endl;
	int m;
	cin >> m;
	vector<vector<int>> Allocation(n, vector<int>(m, 0));//已分配资源
	vector<vector<int>> Need(n, vector<int>(m, 0));//尚需的资源
	vector<bool> Finish(n,false);//结束标志位
	vector<int> Available(m);//可利用资源
	vector<int> Request(m);//资源请求
	//输入各个进程已经分配的各个资源数Allocation
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("请输入P%d的R%d已分配资源Allocation：\n", i, j);
			cin >> Allocation[i][j];
		}
	}
	//输入各个进程尚需分配的各个资源数Need
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("请输入P%d的R%d尚需分配资源Need：\n", i, j);
			cin >> Need[i][j];
		}
	}
	//输入可利用资源
	for (int i = 0; i < m; ++i)
	{
		printf("请输入R%d可利用资源Available：\n", i);
		cin >> Available[i];
	}
	Print_Resourse(Allocation, Need, Finish, Available);
	Security(Allocation, Need, Finish, Available);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	while (1)
	{
		Bank(Allocation, Need, Finish, Available);
		cout << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;
	}
}

//判断是否安全
void Is_Safe(vector<vector<int>>& work_tmp, vector<int>& security_num, int resource_num, int process_num)
{
	//判断是否安全，是则打印work的分配情况 和 安全序列，否则不打印
	if (security_num[0] < 0)//如果有异常，在银行家算法和安全性算法里面都会讲数组的第一个元素设置成不同的负数
	{
		cout << "不安全！资源无法分配" << endl;
	}
	else
	{
		cout << "安全！" << endl;
		cout << "work分配流程：" << endl;
		for (int i = 0; i < process_num; ++i)
		{
			printf("找到P%d：因为Need%d <= Work，而且Finish[%d] = false\n", security_num[i], security_num[i], security_num[i]);
			printf("所以work = work + Allocation%d = ", security_num[i]);
			cout << "（  ";
			for (int q = 0; q < resource_num; ++q)
			{
				printf("%-3d", work_tmp[security_num[i]][q]);
			}
			cout << "）";
			printf("Finish[%d]置为true\n", i);
		}
		cout << endl;
		cout << "安全序列为：" << endl;
		for (int i = 0; i < process_num - 1; ++i)
		{
			cout << security_num[i] << "->";
		}
		cout << security_num[process_num - 1] << endl;
	}
	cout << endl;
}

//安全性算法
bool Security(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available)
{
	int process_num = Allocation.size();//进程数
	int resource_num = Allocation[0].size();//资源数
	//拷贝资源
	vector<vector<int>> all(Allocation);//已分配资源的拷贝
	vector<vector<int>> nee(Need);//尚需资源的拷贝
	vector<bool> fin(Finish);//结束标志位的拷贝
	vector<int> work(Available);//可用资源的拷贝
	vector<vector<int>> work_tmp(Allocation);//用来记录work的变化
	
	vector<int> security_num;//记录安全序列的数组
	int over_num = 0;//表示完成的进程个数
	bool result = true;//给最后的返回是否安全
	cout << endl;

	//进行分配
	while (over_num < process_num)
	{
		int over = 0;
		for (int i = 0; i < process_num; ++i)
		{
			int flag = 0;
			for (int j = 0; j < resource_num; ++j)
			{
				if (!fin[i])//如果该进程的finish标志位是false
				{
					if (work[j] >= nee[i][j])//如果work满足need
					{
						++flag;//每此可以满足一个种类的需求，flag就加1
					}
				}
			}
			if (resource_num == flag)//如果flag（已经满足需求的数量）等于进程种类数，表示该进程的所有种类的资源需求都满足了
			{//正式试分配
				security_num.push_back(i);
				fin[i] = true;//表示该资源已经完成
				over = 1;//表示这一轮已经有资源分配过了
				++over_num;
				for (int k = 0; k < resource_num; ++k)
				{
					work[k] += all[i][k];
					nee[i][k] = 0;
					all[i][k] = 0;
				}
				//给记录的数组赋值
				for (int q = 0; q < resource_num; ++q)
				{
					work_tmp[i] = work;
				}	
			}
		}
		if (0 == over)//如果一轮下来没有一个进程分配到资源，说明死锁
		{
			security_num.resize(1);
			security_num[0] = -3;
			result = false;
			break;
		}
	}
	Is_Safe(work_tmp, security_num, resource_num, process_num);
	return result;
}

//银行家算法
void Bank(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available)
{
	int process_num = Allocation.size();//进程数
	int resource_num = Allocation[0].size();//资源数
	vector<int> Request(resource_num);//请求的资源
	vector<int> work(Available);//拷贝Available
	vector<vector<int>> all(Allocation);//已分配资源的拷贝
	vector<vector<int>> nee(Need);//尚需资源的拷贝
	vector<int> ava(Available);//可用资源的拷贝
	
	//输入请求资源
	cout << "请输入需要请求资源的进程号P[i]：" << endl;
	int num_p;
	cin >> num_p;
	for (int i = 0; i < resource_num; ++i)
	{
		printf("请输入P%d进程的R%d资源请求量：", num_p, i);
		cin >> Request[i];
	}
	
	//判断请求是否合法
	for (int i = 0; i < resource_num; ++i)
	{
		if (Need[num_p][i] < Request[i])//如果请求非法，则直接退出
		{
			cout << "请求大于了合法需求" << endl;
			return;
		}
	}
	//判断请求是否能满足
	for (int i = 0; i < resource_num; ++i)
	{
		if (work[i] < Request[i])//如果不能满足，则直接退出
		{
			printf("系统当前资源数不能满足请求，P%d进入阻塞状态\n", num_p);
			return;
		}
	}
	cout << endl;
	//进行安全性算法前需要将请求的资源分配，并且更新相关的资源
	for (int i = 0; i < resource_num; ++i)
	{//先用拷贝的各个资源来计算，如果安全才用真正的资源来计算
		nee[num_p][i] -= Request[i];
		all[num_p][i] += Request[i];
		ava[i] -= Request[i];
	}
	//进入安全性检查
	if (Security(all, nee, Finish, ava))
	{//如果为真，则正式的试分配
		for (int i = 0; i < resource_num; ++i)
		{
			Need[num_p][i] -= Request[i];
			Allocation[num_p][i] += Request[i];
			Available[i] -= Request[i];
		}
	}
	Print_Resourse(Allocation, Need, Finish, Available);
}