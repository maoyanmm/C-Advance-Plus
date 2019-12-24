#include"bank.h"
//��������˺Ϸ�����
//ϵͳ��ǰ��Դ�������������󣬽�������״̬
//4351232

//��ӡ������Դ
void Print_Resourse(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available)
{
	int n = Allocation.size();
	int m = Allocation[0].size();
	//��ӡ��Availableֵ��ȵ�Work
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
	//��ӡ����
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
	//��ӡ�������̵ĸ�����Դ
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

//�˵�
void menu()
{
	cout << "------���м��㷨------" << endl;
	cout << "�������������" << endl;
	int n;
	cin >> n;
	cout << "��������Դ��������" << endl;
	int m;
	cin >> m;
	vector<vector<int>> Allocation(n, vector<int>(m, 0));//�ѷ�����Դ
	vector<vector<int>> Need(n, vector<int>(m, 0));//�������Դ
	vector<bool> Finish(n,false);//������־λ
	vector<int> Available(m);//��������Դ
	vector<int> Request(m);//��Դ����
	//������������Ѿ�����ĸ�����Դ��Allocation
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("������P%d��R%d�ѷ�����ԴAllocation��\n", i, j);
			cin >> Allocation[i][j];
		}
	}
	//������������������ĸ�����Դ��Need
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("������P%d��R%d���������ԴNeed��\n", i, j);
			cin >> Need[i][j];
		}
	}
	//�����������Դ
	for (int i = 0; i < m; ++i)
	{
		printf("������R%d��������ԴAvailable��\n", i);
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

//�ж��Ƿ�ȫ
void Is_Safe(vector<vector<int>>& work_tmp, vector<int>& security_num, int resource_num, int process_num)
{
	//�ж��Ƿ�ȫ�������ӡwork�ķ������ �� ��ȫ���У����򲻴�ӡ
	if (security_num[0] < 0)//������쳣�������м��㷨�Ͱ�ȫ���㷨���涼�ὲ����ĵ�һ��Ԫ�����óɲ�ͬ�ĸ���
	{
		cout << "����ȫ����Դ�޷�����" << endl;
	}
	else
	{
		cout << "��ȫ��" << endl;
		cout << "work�������̣�" << endl;
		for (int i = 0; i < process_num; ++i)
		{
			printf("�ҵ�P%d����ΪNeed%d <= Work������Finish[%d] = false\n", security_num[i], security_num[i], security_num[i]);
			printf("����work = work + Allocation%d = ", security_num[i]);
			cout << "��  ";
			for (int q = 0; q < resource_num; ++q)
			{
				printf("%-3d", work_tmp[security_num[i]][q]);
			}
			cout << "��";
			printf("Finish[%d]��Ϊtrue\n", i);
		}
		cout << endl;
		cout << "��ȫ����Ϊ��" << endl;
		for (int i = 0; i < process_num - 1; ++i)
		{
			cout << security_num[i] << "->";
		}
		cout << security_num[process_num - 1] << endl;
	}
	cout << endl;
}

//��ȫ���㷨
bool Security(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available)
{
	int process_num = Allocation.size();//������
	int resource_num = Allocation[0].size();//��Դ��
	//������Դ
	vector<vector<int>> all(Allocation);//�ѷ�����Դ�Ŀ���
	vector<vector<int>> nee(Need);//������Դ�Ŀ���
	vector<bool> fin(Finish);//������־λ�Ŀ���
	vector<int> work(Available);//������Դ�Ŀ���
	vector<vector<int>> work_tmp(Allocation);//������¼work�ı仯
	
	vector<int> security_num;//��¼��ȫ���е�����
	int over_num = 0;//��ʾ��ɵĽ��̸���
	bool result = true;//�����ķ����Ƿ�ȫ
	cout << endl;

	//���з���
	while (over_num < process_num)
	{
		int over = 0;
		for (int i = 0; i < process_num; ++i)
		{
			int flag = 0;
			for (int j = 0; j < resource_num; ++j)
			{
				if (!fin[i])//����ý��̵�finish��־λ��false
				{
					if (work[j] >= nee[i][j])//���work����need
					{
						++flag;//ÿ�˿�������һ�����������flag�ͼ�1
					}
				}
			}
			if (resource_num == flag)//���flag���Ѿ�������������������ڽ�������������ʾ�ý��̵������������Դ����������
			{//��ʽ�Է���
				security_num.push_back(i);
				fin[i] = true;//��ʾ����Դ�Ѿ����
				over = 1;//��ʾ��һ���Ѿ�����Դ�������
				++over_num;
				for (int k = 0; k < resource_num; ++k)
				{
					work[k] += all[i][k];
					nee[i][k] = 0;
					all[i][k] = 0;
				}
				//����¼�����鸳ֵ
				for (int q = 0; q < resource_num; ++q)
				{
					work_tmp[i] = work;
				}	
			}
		}
		if (0 == over)//���һ������û��һ�����̷��䵽��Դ��˵������
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

//���м��㷨
void Bank(vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<bool>& Finish, vector<int>& Available)
{
	int process_num = Allocation.size();//������
	int resource_num = Allocation[0].size();//��Դ��
	vector<int> Request(resource_num);//�������Դ
	vector<int> work(Available);//����Available
	vector<vector<int>> all(Allocation);//�ѷ�����Դ�Ŀ���
	vector<vector<int>> nee(Need);//������Դ�Ŀ���
	vector<int> ava(Available);//������Դ�Ŀ���
	
	//����������Դ
	cout << "��������Ҫ������Դ�Ľ��̺�P[i]��" << endl;
	int num_p;
	cin >> num_p;
	for (int i = 0; i < resource_num; ++i)
	{
		printf("������P%d���̵�R%d��Դ��������", num_p, i);
		cin >> Request[i];
	}
	
	//�ж������Ƿ�Ϸ�
	for (int i = 0; i < resource_num; ++i)
	{
		if (Need[num_p][i] < Request[i])//�������Ƿ�����ֱ���˳�
		{
			cout << "��������˺Ϸ�����" << endl;
			return;
		}
	}
	//�ж������Ƿ�������
	for (int i = 0; i < resource_num; ++i)
	{
		if (work[i] < Request[i])//����������㣬��ֱ���˳�
		{
			printf("ϵͳ��ǰ��Դ��������������P%d��������״̬\n", num_p);
			return;
		}
	}
	cout << endl;
	//���а�ȫ���㷨ǰ��Ҫ���������Դ���䣬���Ҹ�����ص���Դ
	for (int i = 0; i < resource_num; ++i)
	{//���ÿ����ĸ�����Դ�����㣬�����ȫ������������Դ������
		nee[num_p][i] -= Request[i];
		all[num_p][i] += Request[i];
		ava[i] -= Request[i];
	}
	//���밲ȫ�Լ��
	if (Security(all, nee, Finish, ava))
	{//���Ϊ�棬����ʽ���Է���
		for (int i = 0; i < resource_num; ++i)
		{
			Need[num_p][i] -= Request[i];
			Allocation[num_p][i] += Request[i];
			Available[i] -= Request[i];
		}
	}
	Print_Resourse(Allocation, Need, Finish, Available);
}