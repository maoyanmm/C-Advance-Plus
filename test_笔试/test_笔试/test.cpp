#include<iostream>
using namespace std;
#include<vector>
//    A:1   B:2/3   C:1/3   D:1/5   E:5/4   F:2/3
int max_num = 0;
void dfs(int tmp_num, int now_money, vector<int>& nums, vector<int>& price, vector<bool> book, int index)
{
	if (now_money - price[index] < 0)
	{
		if (tmp_num > max_num)
		{
			max_num = tmp_num;
		}
		return;
	}
	book[index] = true;
	now_money -= price[index];
	tmp_num += nums[index];
	for (int i = 0; i < 6; ++i)
	{
		if (!book[i])
		{
			dfs(tmp_num, now_money, nums, price, book, i);
		}
	}
}

int main()
{
	int N;
	while (cin >> N)
	{
		max_num = 0;
		vector<int> nums(6, 0);
		vector<int> price(6, 0);
		vector<bool> book(6, false);
		nums[0] = 2; price[0] = 2;
		nums[1] = 3; price[1] = 2;
		nums[2] = 1; price[2] = 3;
		nums[3] = 5; price[3] = 1;
		nums[4] = 4; price[4] = 5;
		nums[5] = 3; price[5] = 2;
		for (int i = 0; i < 6; ++i)
		{
			dfs(0, N, nums, price, book, i);
		}
		cout << max_num << endl;
	}
	return 0;
}

