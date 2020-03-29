#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<map>
#include<stack>


int exp_max = 0;
void dfs(vector<vector<int>>& le, vector<bool>& book, int now_time, int& T, int exp_tmp, int index)
{
	if (le[index][0] < now_time)
	{
		if (exp_tmp > exp_max)
		{
			exp_max = exp_tmp;
		}
		return;
	}
	exp_tmp += le[index][1];
	now_time += T;
	book[index] = true;
	for (int i = 0; i < le.size(); ++i)
	{
		if (!book[i])
		{
			dfs(le, book, now_time, T, exp_tmp, i);
		}
	}
	book[index] = false;
}

int main()
{
	int N, T;
	while (cin >> N >> T)
	{
		exp_max = 0;
		vector<vector<int>> le(N, vector<int>(2,0));
		for (int i = 0; i < N; ++i)
		{
			cin >> le[i][0] >> le[i][1];
		}
		for (int i = 0; i < N; ++i)
		{
			vector<bool> book(N, false);
			dfs(le, book, 0, T, 0, i);
		}
		cout << exp_max << endl;
	}
	return 0;
}


void Show(map<char, int> mp)
{
	auto it = mp.begin();
	for (; it != mp.end(); ++it)
	{
		cout << it->first << ":" << it->second << endl;
	}
}

int main()
{
	int N;
	while (cin >> N)
	{
		map<char, int> mp1, mp2, mp3;
		string str1, str2;
		cin >> str1 >> str2;
		for (const auto& e1 : str1)
		{
			++mp1[e1];
		}
		for (const auto& e2 : str2)
		{
			++mp2[e2];
		}
		if (1 == N)
		{
			Show(mp1);
		}
		if (2 == N)
		{
			Show(mp2);
		}
		N -= 2;
		while (N--)
		{
			auto it1 = mp1.begin();
			auto it2 = mp2.begin();
			for (; it1 != mp1.end(); ++it1)
			{
				mp3[it1->first] += it1->second;
			}
			for (; it2 != mp2.end(); ++it2)
			{
				mp3[it2->first] += it2->second;
			}
			if (0 == N)
			{
				break;
			}
			mp1 = mp2;
			mp2 = mp3;
			mp3.clear();
		}
		Show(mp3);
	}
	return 0;

}
