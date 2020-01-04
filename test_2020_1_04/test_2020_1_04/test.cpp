#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	bool Find(int target, vector<vector<int> > array) {
		if (array.empty())
		{
			return false;
		}
		int row = array.size();
		int col = array[0].size();
		int i = 0;
		int j = col - 1;
		for (; i <= row - 1 && j >= 0;)
		{
			if (array[i][j] == target)
			{
				return true;
			}
			else if (array[i][j] < target)
			{
				++i;
			}
			else
			{
				--j;
			}
		}
		return false;
	}
};