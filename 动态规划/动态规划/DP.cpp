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

#include<iostream>
using namespace std;
#include<vector>

int main()
{
	int N, V;
	while (cin >> N >> V)
	{
		vector<int> value(N);//�洢ÿ����Ʒ�ļ�ֵ
		vector<int> capacity(N);//�洢ÿ����Ʒ������
		for (int i = 0; i < N; ++i)
		{
			cin >> value[i] >> capacity[i];
		}
		vector<vector<int>> dp(N + 1, vector<int>(V + 1, 0));
		//��N+1�У����Ǵ�1��ʼ����������ÿ�б�ʾÿ����Ʒ
		//��V+1�У����Ǵ�1��ʼ����������ÿ�б�ʾ��1��ʼ��������� �� ��������� �� ��Ʒ����ֵ�洢
		for (int i = 1; i < N + 1; ++i)
		{
			for (int j = 1; j < V + 1; ++j)
			{
				if (capacity[i - 1] > j)//������£��Ǿ͵����ϴε����Ŵ洢
				{//�����capacity[i-1]����Ϊ�����i��1��ʼ
					dp[i][j] = dp[i - 1][j];
				}
				else//����ܷ��£������������1���� 2������
					//�źͲ���ȡ���ڷ���֮���Ƿ������ŵģ����Ǵ���һ����ʱ������
				{//dp[i-1][j-capacity[i-1]]��i-1������һ�У�j-capacity[i-1]��װ��i-1�����Ʒ֮��ʣ������������������ǣ���ǰ��tmp_best == װ��i-1��Ʒ�ļ�ֵ + װ�������Ʒ��ʣ�������������װ�����ŵķ���
					int tmp_best = value[i - 1] + dp[i - 1][j - capacity[i - 1]];
					dp[i][j] = max(tmp_best, dp[i - 1][j]);
				}
			}
		}
		//�������һ��Ԫ�ؾ������ŵķ���
		cout << dp[N][V] << endl;
	}
	return 0;
}

class Solution {
public:
	bool Is_hui(string str)
	{
		int left = 0;
		int right = str.size() - 1;
		while (left < right)
		{
			if (str[left] != str[right])
			{
				return false;
			}
			++left;
			--right;
		}
		return true;
	}
	int minCut(string s) {
		int length = s.size();
		vector<int> dp(length + 1, -1);
		dp[0] = 0;
		for (int i = 0; i < length; ++i)
		{//��ͷ��ʼ���Ѿ����Ի��ֳɻ��Ĵ������ּǺţ���һ��Ĭ��Ϊ0���������ܿ�ʼ������ÿ���ַ������ܱ���¼������dp�ĳ�����length+1��
			if (dp[i] >= 0)
			{
				for (int j = i; j < length; ++j)
				{
					if (Is_hui(s.substr(i, j - i + 1)))//��i��Ҳ�����ϴλ��ֳɻ��Ĵ������һ����ĸ�ĺ���һ����ĸ����ʼ����ӳ��ȣ��ҳ����ֻ��Ĵ�
					{
						int tmp = dp[i] + 1;//�ҵ����Ĵ��󣬼�¼���ֵĴ����������ϴε�+1
						if (dp[j + 1] == -1)//�����λ��ֵ�ĩβ������ǰû�б����ֹ�����ֱ�Ӹ�ֵ
						{
							dp[j + 1] = tmp;
						}
						else if (tmp < dp[j + 1])//�����λ��ֵ�ĩβ������ǰ�б����ֹ����ͼ�¼��С�Ļ��ִ���
						{
							dp[j + 1] = tmp;
						}
					}
				}
			}
		}
		return dp[length] - 1;
	}
};

class Solution {
public:
	int minDistance(string word1, string word2) {
		int leng1 = word1.size();
		int leng2 = word2.size();
		if (leng1 == 0 || leng2 == 0)
		{
			return max(leng1, leng2);
		}
		//����һ��һ���൱�ڣ�word1��word2����һ�����ַ�
		vector<vector<int> > dp(leng1 + 1, vector<int>(leng2 + 1, 0));
		//������word1��ab��->word2(abc)
		for (int i = 0; i <= leng1; ++i)//�ڵ�һ�У��ɣ��ա�a��ab�������գ�����Ҫ�任�Ĵ���
		{
			dp[i][0] = i;
		}
		for (int i = 0; i <= leng2; ++i)//�ڵ�һ�У��ɿյ����ա�a��ab��abc���ı任����
		{
			dp[0][i] = i;
		}
		for (int i = 1; i <= leng1; ++i)//����word1 �±�0~leng1-1 �� 1~leng1
		{
			for (int j = 1; j <= leng2; ++j)//����word2 �±�0~leng2-1 �� 1~leng2
			{
				if (word1[i - 1] == word2[j - 1])
				{//�����ε�������ĸ��ȣ�����word1��ab �� b ���� word2��ab��b��
					//��ʱ����С����������word1��word2����bȥ��ʱ�����С��������Ҳ�������Ϊ����μ���b��û��b�Ĳ�������һ����
					dp[i][j] = dp[i - 1][j - 1];
				}
				else
				{//�����ͬ�������϶�Ҫ+1������dp ���Ϻ�������ϵ���Сֵ
					dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]);
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]) + 1;
				}
			}
		}
		return dp[leng1][leng2];
	}
};


class Solution {
public:
	int numDistinct(string S, string T) {
		int s_leng = S.size();
		int t_leng = T.size();
		vector<vector<int> > dp(t_leng + 1, vector<int>(s_leng + 1, 0));
		//�����⣺T��ǰi���ַ��� �� S��ǰj���ַ��� ���ж��ٸ��Ӵ�
		//��һ�д������ַ�����S��ǰ0����ǰ1��...ǰs_leng�����ж��ٸ��Ӵ�
		//����Ȼ��һ�ж���1����Ϊֻ�и�S�е��ַ�ȫ��ɾȥ�������ǿ��ַ�
		for (int i = 0; i < s_leng + 1; ++i)
		{
			dp[0][i] = 1;
		}
		for (int i = 1; i < t_leng + 1; ++i)
		{
			for (int j = 1; j < s_leng + 1; ++j)
			{//�����ͬ����������+��
				//���������������˵�ǣ�S�����һ���ַ���TҲ�����һ���ַ���ȥƥ��
				//�������������˵�ǣ���ƥ����S��һ���ַ�
				if (S[j - 1] == T[i - 1])
				{
					dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
				}
				else
				{//�����ͬ���͵�����ߵ�dpֵ����˼�����T��ǰi���ַ� ƥ��S��ǰj���ַ�ʱ�������i���͵�j���ַ�����ȣ�
					//��ô���������j���ַ����Ӵ��ͼ��������j���ַ����Ӵ�ȥƥ����Ӵ������𰸶���һ����
					dp[i][j] = dp[i][j - 1];
				}
			}
		}
		return dp[t_leng][s_leng];
	}
};