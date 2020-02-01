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

class Solution {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		int size = s.size();
		vector<bool> dp(size + 1, false);
		dp[0] = true;
		for (int i = 0; i < size; ++i)
		{
			for (int j = i; dp[i] && j < size; ++j)//ÿ�ζ��Ǵ���̵��Ѿ������˵ĵ��ʵ���һ����ĸ��������
			{
				if (dict.find(s.substr(i, j - i + 1)) != dict.end())
				{
					dp[j + 1] = true;//������ҵ����ڻ��ֵĵ��ʺ����λ����Ϊtrue
				}
			}
		}
		return dp[size];//���ֱ�����һλ������������Ǿ������
	}
};

class Solution {
public:
	int minimumTotal(vector<vector<int> > &triangle) {
		int size = triangle.size();
		for (int i = size - 2; i >= 0; --i)
		{
			//�ӵײ����ϱ���
			for (int j = 0; j < triangle[i].size(); ++j)
			{
				//ÿ�ζ����ϣ�����һ�����ڵ�������ֵ����Сֵ�������⣩
				//���𰸾��ǣ��ӵ������ǰ��������������Сֵ������
				triangle[i][j] += triangle[i + 1][j]<triangle[i + 1][j + 1] ? triangle[i + 1][j] : triangle[i + 1][j + 1];
			}
		}
		return triangle[0][0];
	}
};

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
		int row = obstacleGrid.size();
		int col = obstacleGrid[0].size();
		if (obstacleGrid[0][0] == 1 || obstacleGrid[row - 1][col - 1] == 1)//�����ͷ��ĩβ�����ϰ��ľ�ֱ�ӷ���0
		{
			return 0;
		}
		obstacleGrid[0][0] = 1;//��һ��������һ��·�������
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (i == 0 && j == 0)//������ʼ��λ��
				{
					continue;
				}
				if (obstacleGrid[i][j] == 1)
				{//������ϰ�����Ϊ-1������Ϊ�����֣�1�������ϰ�������1��·������
					obstacleGrid[i][j] = -1;//����Ϊ�˽�ʡ�ռ䣬����ֱ����ԭ���������ϲ�����ʡȥ�˿��ٺ��������һ����Ŀռ�
				}
				else
				{
					if (i - 1 >= 0 && obstacleGrid[i - 1][j] != -1)//���������жϵ�ʱ���жϵ�1����·��1���������ϰ��ˣ����������ж�-1Ϊ�ϰ�
					{
						obstacleGrid[i][j] += obstacleGrid[i - 1][j];
					}
					if (j - 1 >= 0 && obstacleGrid[i][j - 1] != -1)
					{
						obstacleGrid[i][j] += obstacleGrid[i][j - 1];
					}
				}
			}
		}
		return obstacleGrid[row - 1][col - 1];
	}
};

class Solution {
public:
	int minPathSum(vector<vector<int> > &grid) {
		int row = grid.size();
		int col = grid[0].size();
		for (int i = 1; i < col; ++i)//��һ�е�ÿ��Ԫ�ض�ֻ�ܴ�����߹���
		{
			grid[0][i] += grid[0][i - 1];
		}
		for (int i = 1; i < row; ++i)//��һ�е�ÿ��Ԫ�ض�ֻ�ܴ������߹���
		{
			grid[i][0] += grid[i - 1][0];
		}
		for (int i = 1; i < row; ++i)
		{
			for (int j = 1; j < col; ++j)
			{//�����⣺ÿ��������·�������������ߵ���Сֵ
				grid[i][j] += min(grid[i][j - 1], grid[i - 1][j]);
			}
		}
		return grid[row - 1][col - 1];
	}
};

