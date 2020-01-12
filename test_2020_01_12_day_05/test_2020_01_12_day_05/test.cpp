#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<algorithm>

class Solution {
public:
	bool containsDuplicate(vector<int>& nums) {
		if (nums.empty())
		{
			return false;
		}
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 1; ++i)
		{
			if (nums[i] == nums[i + 1])
			{
				return true;
			}
		}
		return false;
	}
};


class Solution {
public:
	bool isLongPressedName(string name, string typed) {
		int size_name = name.size();
		int size_typed = typed.size();
		if (size_name > size_typed)
		{
			return false;
		}
		int pos = 0;
		for (int i = 0; i < size_name; ++i)
		{
			pos = typed.find(name[i], pos);
			if (pos < 0)
			{
				return false;
			}
			++pos;
		}
		return true;
	}
};