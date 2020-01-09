#include<iostream>
using namespace std;
class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		int right = nums.size() - 1;
		int left = 0;
		int size = nums.size();
		int count = 0;
		if (size == 0)
		{
			return 0;
		}
		while (left < right)
		{
			while (left < right && nums[right] == val)
			{
				--right;
				++count;
			}
			while (left < right && nums[left] != val)
			{
				++left;
			}
			if (left == right)
			{
				break;
			}
			if (nums[left] == val)
			{
				++count;
				swap(nums[left], nums[right]);
				--right;
			}
		}
		if (nums[left] == val)
			++count;
		return size - count;
	}
};


class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int n = nums.size();
		int left = 0;
		int right = n - 1;
		int mid = (right - left) / 2 + left;
		if (nums[0] > target)
		{
			return 0;
		}
		if (nums[right] < target)
		{
			return right + 1;
		}
		while (left <= right)
		{
			mid = (right - left) / 2 + left;
			if (nums[mid] == target)
			{
				return mid;
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
		return right + 1;
	}
};