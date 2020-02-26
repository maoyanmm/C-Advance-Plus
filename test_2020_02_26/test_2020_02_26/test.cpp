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
					//����һ��½��������4����
					ans += 4;
					//�������������һ��½�أ���᣺������½�ص������������غ�
					if (i > 0 && grid[i - 1][j] == 1)
					{
						ans -= 2;
					}
					//������������һ��½�أ���᣺������½�ص������������غ�
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
		//�����һ��O��������һ����ͨ���ĸ��ߵ�����һ�ߣ��߽磩����һ��O���ǲ�����Χ��
		//�Ƚ���Щ������Χ��O��¼��#�����������ٸ�#����O����������O�϶��Ǳ���Χ��
		int row = board.size();
		int col = board[0].size();
		//�������һ�к����ұ�һ�е�Oȥ����
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
		//��������һ�к�������һ�е�Oȥ����
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