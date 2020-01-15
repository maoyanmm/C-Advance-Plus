class Solution {
public:
	vector<int> plusOne(vector<int>& digits) {
		int size = digits.size();
		if (digits[size - 1] < 9)
		{
			digits[size - 1] += 1;
			return digits;
		}
		digits[size - 1] = 0;
		reverse(digits.begin(), digits.end());
		for (int i = 1; i < size; ++i)
		{
			if (digits[i] + 1 > 9)
			{
				digits[i] = 0;
			}
			else
			{
				++digits[i];
				break;
			}
		}
		if (digits[size - 1] == 0)
		{
			digits.resize(size + 1);
			digits[size] = 1;
		}
		reverse(digits.begin(), digits.end());
		return digits;
	}
};


class Solution {
public:
	int thirdMax(vector<int>& nums) {
		int max1 = nums[0];
		int max2 = nums[0];
		int max3 = nums[0];
		int flag2 = 0;
		int flag3 = 0;
		int size = nums.size();
		for (int i = 0; i < size; ++i)
		{
			if (nums[i] > max1)
			{
				max1 = nums[i];
			}
		}
		for (int i = 0; i < size; ++i)
		{
			if (1 == flag2)
			{
				if (nums[i] < max1 && nums[i] > max2)
				{
					max2 = nums[i];
				}
			}
			else
			{
				if (nums[i] != max1)
				{
					max2 = nums[i];
					flag2 = 1;
				}
			}
		}
		for (int i = 0; i < size; ++i)
		{
			if (1 == flag3)
			{
				if (nums[i] < max2 && nums[i] > max3)
				{
					max3 = nums[i];
				}
			}
			else
			{
				if (nums[i] != max1 && nums[i] != max2)
				{
					max3 = nums[i];
					flag3 = 1;
				}
			}
		}
		if (max1 == max2 || max2 == max3 || max1 == max3)
		{
			return max1;
		}
		return max3;
	}
};