#include<iostream>
using namespace std;
#include<vector>

bool dfs(double ans, const vector<double>& nums)
{
	if (nums.empty())
	{
		return 24 == ans;
	}
	for (int i = 0; i < nums.size(); ++i)
	{
		vector<double> numsb = nums;
		numsb.erase(numsb.begin() + i);

		if (dfs(ans + nums[i], numsb)
			|| dfs(ans - nums[i], numsb)
			|| dfs(ans*nums[i], numsb)
			|| dfs(ans / nums[i], numsb))
		{
			return true;
		}
	}
	return false;
}

int main()
{
	vector<double> nums(4);
	while (cin >> nums[0] >> nums[1] >> nums[2] >> nums[3])
	{
		if (dfs(0, nums))
		{
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
	}
	return 0;
}