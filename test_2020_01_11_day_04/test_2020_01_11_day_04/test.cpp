#include<iostream>
using namespace std;
#include<vector>
#include<string>

class Solution {
public:
	int lengthOfLastWord(string s) {
		int size = s.size();
		int count = 0;
		for (int i = size - 1; i >= 0; --i)
		{
			if (s[i] == ' ' && count != 0)
			{
				break;
			}
			else if (s[i] != ' ')
			{
				++count;
			}
		}
		return count;
	}
};

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		vector<int> tmp1 = nums1;
		tmp1.resize(m);
		int flag1 = 0;
		int flag2 = 0;
		int flag = 0;
		while (flag1 < m && flag2 < n)
		{
			if (tmp1[flag1] > nums2[flag2])
			{
				nums1[flag] = nums2[flag2];
				++flag2;
			}
			else
			{
				nums1[flag] = tmp1[flag1];
				++flag1;
			}
			++flag;
		}
		for (int i = flag1; i < m; ++i)
		{
			nums1[flag++] = tmp1[i];
		}
		for (int i = flag2; i < n; ++i)
		{
			nums1[flag++] = nums2[i];
		}
	}
};


class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int flag1 = m - 1;
		int flag2 = n - 1;
		int flag = m + n - 1;
		while (flag1 >= 0 && flag2 >= 0)
		{
			if (nums1[flag1] > nums2[flag2])
			{
				nums1[flag] = nums1[flag1];
				--flag1;
			}
			else
			{
				nums1[flag] = nums2[flag2];
				--flag2;
			}
			--flag;
		}
		for (int i = flag1; i >= 0; --i)
		{
			nums1[flag--] = nums1[i];
		}
		for (int i = flag2; i >= 0; --i)
		{
			nums1[flag--] = nums2[i];
		}
	}
};