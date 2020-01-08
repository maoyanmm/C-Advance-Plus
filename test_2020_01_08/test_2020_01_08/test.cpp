#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
	void rotate(vector<int>& nums, int k) {
		int n = nums.size();
		k %= n;
		Reverse(nums, 0, n - 1);
		Reverse(nums, 0, k - 1);
		Reverse(nums, k, n - 1);
	}
	void Reverse(vector<int>& nums, int start, int end)
	{
		while (start < end)
		{
			swap(nums[start], nums[end]);
			++start;
			--end;
		}
	}
};

class Solution {
public:
	string toLowerCase(string str) {
		if (str.empty())
		{
			return str;
		}
		for (auto& e : str)
		{
			if (e >= 'A' && e <= 'Z')
			{
				e += 32;
			}
		}
		return str;
	}
};