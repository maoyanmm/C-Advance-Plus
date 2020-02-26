class Solution {
public:
	int islandPerimeter(vector<vector<int>>& grid) {
		int ans = 0;
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[0].size(); ++j)
			{
				if (grid[i][j] == 1)
				{
					//碰到一个陆地最多会有4条边
					ans += 4;
					//如果上面连接了一个陆地，则会：这两个陆地的上下两条边重合
					if (i > 0 && grid[i - 1][j] == 1)
					{
						ans -= 2;
					}
					//如果左边连接了一个陆地，则会：这两个陆地的左右两条边重合
					if (j > 0 && grid[i][j - 1] == 1)
					{
						ans -= 2;
					}
				}
			}
		}
		return ans;
	}
};

class Solution {
public:

	vector<vector<int> > direction = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

	void solve(vector<vector<char>>& board) {
		if (board.empty())
		{
			return;
		}
		//如果有一串O，但是有一边连通到四个边的其中一边（边界），这一串O都是不被包围的
		//先将这些不被包围的O记录成#，最后遍历完再给#换成O。而其他的O肯定是被包围的
		int row = board.size();
		int col = board[0].size();
		//将最左边一列和最右边一列的O去处理
		for (int i = 0; i < row; ++i)
		{
			if (board[i][0] == 'O')
			{
				dfs(board, i, 0);
			}
			if (board[i][col - 1] == 'O')
			{
				dfs(board, i, col - 1);
			}
		}
		//将最上面一行和最下面一行的O去处理
		for (int i = 0; i < col; ++i)
		{
			if (board[0][i] == 'O')
			{
				dfs(board, 0, i);
			}
			if (board[row - 1][i] == 'O')
			{
				dfs(board, row - 1, i);
			}
		}
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (board[i][j] == 'O')
				{
					board[i][j] = 'X';
				}
				else if (board[i][j] == '#')
				{
					board[i][j] = 'O';
				}

			}
		}
	}
	void dfs(vector<vector<char> >& board, int x, int y)
	{
		board[x][y] = '#';
		for (int i = 0; i < 4; ++i)
		{
			int tmp_x = x + direction[i][0];
			int tmp_y = y + direction[i][1];
			if (tmp_x < 0 || tmp_y < 0 || tmp_x >= board.size() || tmp_y >= board[0].size())
			{
				continue;
			}
			if (board[tmp_x][tmp_y] == 'O')
			{
				dfs(board, tmp_x, tmp_y);
			}
		}
	}
};