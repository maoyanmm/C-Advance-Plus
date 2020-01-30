class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> vv(m, vector<int>(n, 0));
		vv[0][0] = 1;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (i - 1 >= 0)
				{
					vv[i][j] += vv[i - 1][j];
				}
				if (j - 1 >= 0)
				{
					vv[i][j] += vv[i][j - 1];
				}
			}
		}
		return vv[m - 1][n - 1];
	}
};


class Solution {
public:
	int jumpFloor(int number) {
		int a = 1;
		int b = 2;
		int c = a + b;
		if (number <= 2)
		{
			return number;
		}
		number -= 2;
		while (number--)
		{
			c = a + b;
			a = b;
			b = c;
		}
		return c;
	}
};


class Solution {
public:
	int jumpFloorII(int number) {
		if (1 == number)
		{
			return 1;
		}
		else
		{
			return 2 * jumpFloorII(number - 1);
		}
	}
};

class Solution {
public:
	int FindGreatestSumOfSubArray(vector<int> array) {
		int size = array.size();
		vector<int> score(array);
		int max = array[0];
		for (int i = 1; i < size; ++i)
		{
			if (score[i - 1] > 0)
			{
				score[i] += score[i - 1];
			}
		}
		for (int i = 0; i < size; ++i)
		{
			if (score[i] > max)
			{
				max = score[i];
			}
		}
		return max;
	}
};