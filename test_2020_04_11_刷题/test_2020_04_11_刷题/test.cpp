class Solution {
public:
	bool IsHui(const string& str)
	{
		int left = 0;
		int right = str.size() - 1;
		while (left < right)
		{
			if (str[left] != str[right])
			{
				return false;
			}
			++left;
			--right;
		}
		return true;
	}
	int minCut(string s) {
		int size = s.size();
		vector<int> book(size + 1, -1);
		book[0] = 0;
		for (int i = 0; i < size; ++i)
		{
			if (book[i] >= 0)
			{
				int count = book[i];
				for (int j = i; j < size; ++j)
				{
					string sub_str = s.substr(i, j - i + 1);
					int count_tmp = count + 1;
					if (IsHui(sub_str) == true)
					{
						if (book[j + 1] == -1)
						{
							book[j + 1] = count + 1;
						}
						else if (count_tmp < book[j + 1])
						{
							book[j + 1] = count_tmp;
						}
					}
				}
			}
		}
		return book[size] - 1;
	}
};


#include<iostream>
using namespace std;
#include<vector>

int main()
{
	int N, V;
	while (cin >> N >> V)
	{
		vector<int> weight(N, 0);
		vector<int> value(N, 0);
		for (int i = 0; i < N; ++i)
		{
			cin >> value[i] >> weight[i];
		}
		vector<vector<int> > dp(N + 1, vector<int>(V + 1, 0));
		for (int i = 1; i < N + 1; ++i)
		{
			for (int j = 1; j < V + 1; ++j)
			{
				if (weight[i - 1] > j)
				{
					dp[i][j] = dp[i - 1][j];
				}
				else
				{
					int tmp_value = dp[i - 1][j - weight[i - 1]] + value[i - 1];
					dp[i][j] = max(tmp_value, dp[i - 1][j]);
				}
			}
		}
		cout << dp[N][V] << endl;
	}
	return 0;
}