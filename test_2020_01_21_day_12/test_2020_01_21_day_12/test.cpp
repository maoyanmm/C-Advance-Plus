#include<iostream>
using namespace std;
#include<math.h>
#include<algorithm>
#include<stack>
class Solution {
public:
	int findUnsortedSubarray(vector<int>& nums) {
		int left = 0;
		int right = nums.size() - 1;
		int _min = 0;
		int _max = 0;	
		while (left < right && nums[left] <= nums[left + 1])
		{
			++left;
		}
		while (left < right && nums[right] >= nums[right - 1])
		{
			--right;
		}
		if (left == right)
		{
			return 0;
		}
		_max = max(nums[right - 1], nums[left]);
		_min = min(nums[right], nums[left + 1]);
		for (int i = left; i < right + 1; ++i)
		{
			if (nums[i] > _max)
			{
				_max = nums[i];
			}
			if (nums[i] < _min)
			{
				_min = nums[i];
			}
		}
		for (int i = 0; i < nums.size(); ++i)
		{
			if (_min < nums[i])
			{
				left = i;
				break;
			}
		}
		for (int i = nums.size() - 1; i >= 0; --i)
		{
			if (_max > nums[i])
			{
				right = i;
				break;
			}
		}
		return right - left + 1;
	}
};

stack<int> st;
int ans = 0;
for (int i = 0; i < tokens.size(); ++i)
{
	int size = tokens[i].size();
	if (tokens[i][size - 1] >= '0' && tokens[i][size - 1] <= '9')
	{
		int flag = 1;
		int j = 0;
		int digit = 0;
		if (tokens[i][0] == '-')
		{
			flag = -1;
		}
		if (tokens[i][0] == '+' || tokens[i][0] == '-')
		{
			++j;
		}
		for (; j < size; ++j)
		{
			digit = digit * 10 + (tokens[i][j] - '0');
		}
		digit *= flag;
		st.push(digit);
	}
	else
	{
		switch (tokens[i][0])  //»òÕßswitch(*tokens[i].c_str())
		{
		case '+':
		{
					int tmp = st.top();
					st.pop();
					ans = st.top() + tmp;
					st.pop();
					break;
		}
		case '-':
		{
					int tmp = st.top();
					st.pop();
					ans = st.top() - tmp;
					st.pop();
					break;
		}
		case '*':
		{
					int tmp = st.top();
					st.pop();
					ans = st.top() * tmp;
					st.pop();
					break;
		}
		case '/':
		{
					int tmp = st.top();
					st.pop();
					ans = st.top() / tmp;
					st.pop();
					break;
		}
		default:
			break;
		}
		st.push(ans);
	}
}
return st.top();