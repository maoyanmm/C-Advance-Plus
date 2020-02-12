#include<iostream>
using namespace std;
#include<string>

int main()
{
	string str1;
	string str2;
	while (getline(cin, str1) && cin >> str2)
	{
		if (str2.empty() || str1.empty())
		{
			cout << str1 << endl;
			continue;
		}
		int size1 = str1.size();
		int count = 0;
		for (int i = 0; i < str2.size(); ++i)
		{
			int left = 0;
			int right = 0;
			char tmp = str2[i];
			while (right < str1.size())
			{
				if (str1[right] == tmp)
				{
					++right;
					++count;
				}
				else
				{
					str1[left] = str1[right];
					++left;
					++right;
				}
			}
		}
		str1.resize(size1 - count);
		cout << str1 << endl;
	}
	return 0;
}

#include<iostream>
using namespace std;
#include<string>

int main()
{
	string str1;
	string str2;
	while (getline(cin, str1) && getline(cin, str2))
	{
		int size1 = str1.size();
		for (int i = 0; i < size1; ++i)
		{
			int tmp;
			if ((tmp = str2.find(str1[i])) == -1)
			{
				cout << str1[i];
			}
		}
		cout << endl;
	}
	return 0;
}

#include<iostream>
using namespace std;
#include<vector>
int main()
{
	vector<int> nums;
	int n;
	while (cin >> n)
	{
		nums.resize(n);
		vector<int> dp(n, 0);
		int max = 0;
		for (int i = 0; i < n; ++i)
		{
			cin >> nums[i];
			if (0 == i)
			{
				dp[i] = nums[i];
			}
			else
			{
				if (nums[i] + dp[i - 1] < nums[i])
				{
					dp[i] = nums[i];
				}
				else
				{
					dp[i] = nums[i] + dp[i - 1];
				}
			}
			if (0 == i)
			{
				max = dp[i];
			}
			else
			{
				if (dp[i] > max)
				{
					max = dp[i];
				}
			}
		}
		cout << max << endl;

	}
	return 0;
}