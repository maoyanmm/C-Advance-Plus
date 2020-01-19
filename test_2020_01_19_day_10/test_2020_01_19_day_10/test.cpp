#include<stdio.h>
#include<iostream>
using namespace std;
class Solution {
public:
	int myAtoi(string str) {
		int size = str.size();
		int flag = 0;
		int ans = 0;
		int ans_flag = 1;
		for (int i = 0; i < size; ++i)
		{
			if (str[i] <= '9' && str[i] >= '0')
			{
				if (ans > INT_MAX / 10)
				{
					if (1 == ans_flag)
					{
						return INT_MAX;
					}
					else
					{
						return INT_MIN;
					}
				}
				if (ans == INT_MAX / 10)
				{
					if (1 == ans_flag)
					{
						if (str[i] >= '7')
						{
							return INT_MAX;
						}
					}
					else
					{
						if (str[i] >= '8')
						{
							return INT_MIN;
						}
					}
				}
				ans = ans * 10 + (str[i] - '0');
				flag = 1;
			}
			else if (str[i] == '+')
			{
				if (0 == flag)
				{
					ans_flag = 1;
					flag = 1;
				}
				else
				{
					break;
				}
			}
			else if (str[i] == '-')
			{
				if (0 == flag)
				{
					ans_flag = -1;
					flag = 1;
				}
				else
				{
					break;
				}
			}
			else if (str[i] == ' ' && 0 == flag)
			{
				continue;
			}
			else
			{
				if (0 == flag)
				{
					return 0;
				}
				else
				{
					break;
				}
			}
		}
		return ans*ans_flag;
	}
};


class Solution {
public:
	int myAtoi(string str) {
		long long ans = 0;
		int flag = 1;
		int i = 0;
		while (str[i] == ' ')
		{
			++i;
		}
		if (str[i] == '-')
		{
			flag = -1;
			++i;
		}
		else if (str[i] == '+')
		{
			++i;
		}
		for (; i < str.size() && (str[i] >= '0' && str[i] <= '9'); ++i)
		{
			int tmp = str[i] - '0';
			ans = ans * 10 + tmp;
			if ((int)ans != ans)
			{
				if (1 == flag)
				{
					return INT_MAX;
				}
				else
				{
					return INT_MIN;
				}
			}
		}
		return ans*flag;
	}
};

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		int mid = (right - left) / 2 + left;
		vector<int> ans(2);
		while (left <= right)
		{
			mid = (right - left) / 2 + left;
			if (nums[mid] == target)
			{
				int index = mid;
				//ÅÐ¶Ï¿ªÊ¼
				while (index >= 0 && nums[index] == target)
				{
					--index;
				}
				ans[0] = ++index;
				//ÅÐ¶Ï½áÊø
				index = mid;
				while (index < nums.size() && nums[index] == target)
				{
					++index;
				}
				ans[1] = --index;
				break;
			}
			else if (nums[mid] > target)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		if (left > right)
		{
			ans[0] = -1;
			ans[1] = -1;
		}
		return ans;
	}
};

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> ans(2, -1);
		if (nums.empty())
		{
			return ans;
		}
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right)
		{
			int mid = (right - left) / 2 + left;
			if (nums[mid] == target)
			{
				right = mid - 1;
			}
			else if (nums[mid] > target)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		if (left <= nums.size() - 1 && nums[left] == target)
		{
			ans[0] = left;
		}
		else
		{
			return ans;
		}
		left = 0;
		right = nums.size() - 1;
		while (left <= right)
		{
			int mid = (right - left) / 2 + left;
			if (nums[mid] == target)
			{
				left = mid + 1;
			}
			else if (nums[mid] > target)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		if (right >= 0 && nums[right] == target)
		{
			ans[1] = right;
		}
		return ans;
	}
};