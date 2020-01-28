#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> vv(1);
		for (int i = 0; i < nums.size(); ++i)
		{
			int size = vv.size();
			for (int j = 0; j < size; ++j)
			{
				vector<int> tmp = vv[j];
				tmp.push_back(nums[i]);
				vv.push_back(tmp);
			}
		}
		return vv;
	}
};

class Solution {
public:
	int max = 0;
	void longest_path(vector<vector<int>>& vv, int i, int j, int count)
	{
		int flag = 0;
		if (j + 1 < vv[0].size() && vv[i][j + 1] > vv[i][j])
		{
			flag = 1;
			longest_path(vv, i, j + 1, count + 1);
		}
		if (i + 1 < vv.size() && vv[i + 1][j] > vv[i][j])
		{
			flag = 1;
			longest_path(vv, i + 1, j, count + 1);
		}
		if (i - 1 >= 0 && vv[i - 1][j] > vv[i][j])
		{
			flag = 1;
			longest_path(vv, i - 1, j, count + 1);
		}
		if (j - 1 >= 0 && vv[i][j - 1] > vv[i][j])
		{
			flag = 1;
			longest_path(vv, i, j - 1, count + 1);
		}
		if (0 == flag)
		{
			if (count > max)
			{
				max = count;
			}
		}
		return;
	}
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.empty())
		{
			return 0;
		}
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix[0].size(); ++j)
			{
				longest_path(matrix, i, j, 1);
			}
		}
		return max;
	}

};

class Solution {
public:
	int row, col;
	vector<vector<int>> direction = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
	vector<vector<int>> record;
	vector<vector<int>> score;

	int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.empty())
		{
			return 0;
		}
		row = matrix.size();
		col = matrix[0].size();
		record = vector<vector<int>>(row, vector<int>(col, 0));
		score = vector<vector<int>>(row, vector<int>(col, 0));
		int ans = 0;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (record[i][j] == 0)
				{
					ans = max(ans, def(matrix, i, j));
				}
			}
		}
		return ans;
	}
	int def(vector<vector<int>>& matrix, int i, int j)
	{
		if (score[i][j] != 0)
		{
			return score[i][j];
		}
		record[i][j] = 1;
		for (const auto& e : direction)
		{
			int x = i + e[0];
			int y = j + e[1];
			if (x >= 0 && y >= 0 && x < row && y < col && matrix[x][y] > matrix[i][j])
			{
				score[i][j] = max(score[i][j], def(matrix, x, y));
			}
		}
		return ++score[i][j];
	}
};