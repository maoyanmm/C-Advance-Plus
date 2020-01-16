#include<iostream>
using namespace std;
#include<map>
#include<string>

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		int size = nums.size();
		vector<int> ans(2);
		for (int i = 0; i < size; ++i)
		{
			for (int j = i + 1; j < size; ++j)
			{
				if (nums[i] + nums[j] == target)
				{
					ans[0] = i;
					ans[1] = j;
					break;
				}
			}
		}
		return ans;
	}
};


class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		map<int, int> mp;
		vector<int> vv(2);
		int size = nums.size();
		for (int i = 0; i < size; ++i)
		{
			int ans = target - nums[i];
			if (mp.find(ans) != mp.end())
			{
				vv[0] = mp[ans];
				vv[1] = i;
				break;
			}
			else
			{
				mp.insert(make_pair(nums[i], i));
			}
		}
		
		return vv;
	}
};


class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> vv(2);
		map<int, int> mp;
		int size = nums.size();
		for (int i = 0; i < size; ++i)
		{
			mp.insert(make_pair(nums[i], i));
		}
		for (int i = 0; i < size; ++i)
		{
			int ans = target - nums[i];
			if (mp.find(ans) != mp.end() && mp[ans] != i)
			{
				vv[0] = mp[ans];
				vv[1] = i;
				break;
			}
		}
		return vv;
	}
};



class Solution {
public:
	string addBinary(string a, string b) {
		int size_a = a.size();
		int size_b = b.size();
		if (size_b > size_a)
		{
			swap(a, b);
			swap(size_a, size_b);
		}
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		int carry = 0;
		int i = 0;
		for (i = 0; i < size_b; ++i)
		{
			if (0 == carry)
			{
				int tmp = (a[i] - '0') + (b[i] - '0');
				if (tmp > 1)
				{
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				a[i] = tmp % 2 + '0';
			}
			else
			{
				int tmp = (a[i] - '0') + (b[i] - '0') + 1;
				if (tmp > 1)
				{
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				a[i] = tmp % 2 + '0';
			}
		}
		for (; i < size_a; ++i)
		{
			if (1 == carry)
			{
				int tmp = (a[i] - '0') + 1;
				if (tmp <= 1)
				{
					carry = 0;
				}
				a[i] = tmp % 2 + '0';
			}
			else
			{
				break;
			}
		}
		if (1 == carry)
		{
			a.resize(size_a + 1);
			a[size_a] = '1';
		}
		reverse(a.begin(), a.end());
		return a;
	}
};