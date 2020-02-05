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
			for (int j = i; dp[i] && j < size; ++j)//每次都是从最短的已经划分了的单词的下一个字母继续遍历
			{
				if (dict.find(s.substr(i, j - i + 1)) != dict.end())
				{
					dp[j + 1] = true;//如果能找到就在划分的单词后面的位置置为true
				}
			}
		}
		return dp[size];//如果直到最后一位都被划分完毕那就是真的
	}
};

class Solution {
public:
	int minimumTotal(vector<vector<int> > &triangle) {
		int size = triangle.size();
		for (int i = size - 2; i >= 0; --i)
		{
			//从底部往上遍历
			for (int j = 0; j < triangle[i].size(); ++j)
			{
				//每次都加上：下面一行相邻的两个数值的最小值（子问题）
				//最后答案就是：加到最后就是把所有子问题的最小值加起来
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
		if (obstacleGrid[0][0] == 1 || obstacleGrid[row - 1][col - 1] == 1)//如果开头和末尾是有障碍的就直接返回0
		{
			return 0;
		}
		obstacleGrid[0][0] = 1;//第一个点是有一条路径到达的
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (i == 0 && j == 0)//跳过初始的位置
				{
					continue;
				}
				if (obstacleGrid[i][j] == 1)
				{//如果有障碍就置为-1，这是为了区分：1到底是障碍还是有1条路径到达
					obstacleGrid[i][j] = -1;//这是为了节省空间，所以直接在原来的数组上操作，省去了开辟和这个数组一样大的空间
				}
				else
				{
					if (i - 1 >= 0 && obstacleGrid[i - 1][j] != -1)//在这这里判断的时候，判断的1都是路径1，而不是障碍了，所以这里判断-1为障碍
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
		for (int i = 1; i < col; ++i)//第一行的每个元素都只能从左边走过来
		{
			grid[0][i] += grid[0][i - 1];
		}
		for (int i = 1; i < row; ++i)//第一列的每个元素都只能从上面走过来
		{
			grid[i][0] += grid[i - 1][0];
		}
		for (int i = 1; i < row; ++i)
		{
			for (int j = 1; j < col; ++j)
			{//子问题：每个点的最短路径等于上面和左边的最小值
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
		vector<int> value(N);//存储每个物品的价值
		vector<int> capacity(N);//存储每个物品的容量
		for (int i = 0; i < N; ++i)
		{
			cin >> value[i] >> capacity[i];
		}
		vector<vector<int>> dp(N + 1, vector<int>(V + 1, 0));
		//有N+1行，但是从1开始遍历，所以每行表示每个物品
		//有V+1列，但是从1开始遍历，所以每列表示从1开始到最大容量 的 各种情况下 的 物品最大价值存储
		for (int i = 1; i < N + 1; ++i)
		{
			for (int j = 1; j < V + 1; ++j)
			{
				if (capacity[i - 1] > j)//如果不下，那就等于上次的最优存储
				{//这里的capacity[i-1]是因为这里的i从1开始
					dp[i][j] = dp[i - 1][j];
				}
				else//如果能放下，有两种情况：1、放 2、不放
					//放和不放取决于放了之后是否是最优的，于是创建一个临时变量。
				{//dp[i-1][j-capacity[i-1]]：i-1：上面一行，j-capacity[i-1]：装了i-1这个物品之后还剩的容量。所以整体就是：当前的tmp_best == 装了i-1物品的价值 + 装了这个物品后剩余的容量还可以装的最优的方案
					int tmp_best = value[i - 1] + dp[i - 1][j - capacity[i - 1]];
					dp[i][j] = max(tmp_best, dp[i - 1][j]);
				}
			}
		}
		//返回最后一个元素就是最优的方案
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
		{//从头开始找已经可以划分成回文串的数字记号（第一个默认为0，这样才能开始，但是每个字符都可能被记录，所以dp的长度是length+1）
			if (dp[i] >= 0)
			{
				for (int j = i; j < length; ++j)
				{
					if (Is_hui(s.substr(i, j - i + 1)))//以i（也就是上次划分成回文串的最后一个字母的后面一个字母）开始往后加长度，找出各种回文串
					{
						int tmp = dp[i] + 1;//找到回文串后，记录划分的次数，就是上次的+1
						if (dp[j + 1] == -1)//如果这次划分的末尾，在以前没有被划分过，就直接赋值
						{
							dp[j + 1] = tmp;
						}
						else if (tmp < dp[j + 1])//如果这次划分的末尾，在以前有被划分过，就记录最小的划分次数
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
		//多了一行一列相当于：word1和word2多了一个空字符
		vector<vector<int> > dp(leng1 + 1, vector<int>(leng2 + 1, 0));
		//下面用word1（ab）->word2(abc)
		for (int i = 0; i <= leng1; ++i)//在第一列：由（空、a、ab）到（空）的需要变换的次数
		{
			dp[i][0] = i;
		}
		for (int i = 0; i <= leng2; ++i)//在第一行：由空到（空、a、ab、abc）的变换次数
		{
			dp[0][i] = i;
		}
		for (int i = 1; i <= leng1; ++i)//遍历word1 下标0~leng1-1 用 1~leng1
		{
			for (int j = 1; j <= leng2; ++j)//遍历word2 下标0~leng2-1 用 1~leng2
			{
				if (word1[i - 1] == word2[j - 1])
				{//如果这次的两个字母相等，比如word1的ab 的 b 等于 word2的ab的b。
					//这时的最小操作数等于word1和word2都将b去除时候的最小操作数。也可以理解为：这次加了b和没加b的操作数都一样少
					dp[i][j] = dp[i - 1][j - 1];
				}
				else
				{//如果不同，次数肯定要+1，加在dp 的上和左和左上的最小值
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
		//子问题：T的前i个字符串 在 S的前j个字符串 中有多少个子串
		//第一行代表：空字符串在S的前0个、前1个...前s_leng个中有多少个子串
		//很显然第一行都是1，因为只有给S中的字符全部删去，才能是空字符
		for (int i = 0; i < s_leng + 1; ++i)
		{
			dp[0][i] = 1;
		}
		for (int i = 1; i < t_leng + 1; ++i)
		{
			for (int j = 1; j < s_leng + 1; ++j)
			{//如果相同，等于左上+左：
				//现在相对于左上来说是：S多加了一个字符，T也多加了一个字符，去匹配
				//现在相对于左来说是：多匹配了S的一个字符
				if (S[j - 1] == T[i - 1])
				{
					dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
				}
				else
				{//如果不同，就等于左边的dp值：意思是如果T的前i个字符 匹配S的前j个字符时，如果第i个和第j个字符不相等，
					//那么不加这个第j个字符的子串和加了这个第j个字符的子串去匹配的子串数，答案都是一样的
					dp[i][j] = dp[i][j - 1];
				}
			}
		}
		return dp[t_leng][s_leng];
	}
};