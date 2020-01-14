class Solution {
public:
	vector<int> sortArrayByParity(vector<int>& A) {
		int size = A.size();
		int left = 0;
		int right = size - 1;
		while (left < right)
		{
			while (left < right && A[left] % 2 == 0)
			{
				++left;
			}
			while (left < right && A[right] % 2 != 0)
			{
				--right;
			}
			swap(A[left], A[right]);
		}
		return A;
	}
};

class Solution {
public:
	int pivotIndex(vector<int>& nums) {
		int right_sum = 0;
		int left_sum = 0;
		int size = nums.size();
		for (int i = 0; i < size; ++i)
		{
			right_sum += nums[i];
		}
		for (int i = 0; i < size; ++i)
		{
			right_sum -= nums[i];
			if (right_sum == left_sum)
			{
				return i;
			}
			left_sum += nums[i];
		}
		return -1;
	}
};


class Solution {
public:
	int pivotIndex(vector<int>& nums) {
		int left_sum = 0;
		int sum = 0;
		int size = nums.size();
		for (const auto& e : nums)
		{
			sum += e;
		}
		for (int i = 0; i < size; ++i)
		{
			if (left_sum == sum - left_sum - nums[i])
			{
				return i;
			}
			left_sum += nums[i];
		}
		return -1;
	}
};