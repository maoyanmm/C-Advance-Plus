#include<iostream>
using namespace std;
#include<unordered_set>
#include<string>
#include<vector>


class Solution {
public:

	unordered_set<string> us;
	void dfs(string& tiles, string sub, vector<bool> book)
	{
		if (sub != "")
		{
			us.insert(sub);
		}
		for (int i = 0; i < tiles.size(); ++i)
		{
			if (!book[i])
			{
				book[i] = true;
				dfs(tiles, sub + tiles[i], book);
				book[i] = false;
			}
		}
	}
	int numTilePossibilities(string tiles) {
		vector<bool> book(tiles.size(), false);
		dfs(tiles, "", book);
		return us.size();
	}
};

class Solution {
public:
	int direction[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	bool ans = false;
	void dfs(vector<vector<char>>& board, string sub_word, string& word, vector<vector<bool>> book, int x, int y)
	{
		sub_word += board[x][y];
		book[x][y] = true;
		if (sub_word == word)
		{
			ans = true;
			return;
		}
		for (int i = 0; i < 4; ++i)
		{
			int tmp_x = x + direction[i][0];
			int tmp_y = y + direction[i][1];
			if (tmp_x >= 0 && tmp_y >= 0 && tmp_x < board.size() && tmp_y < board[0].size() && !book[tmp_x][tmp_y] && board[tmp_x][tmp_y] == word[sub_word.size()])
			{
				dfs(board, sub_word, word, book, tmp_x, tmp_y);
			}
		}
	}
	bool exist(vector<vector<char>>& board, string word) {
		int row = board.size();
		int col = board[0].size();
		if (word.size() == 0)
		{
			return true;
		}
		vector<vector<bool>> book(row, vector<bool>(col, false));
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (board[i][j] == word[0])
					dfs(board, "", word, book, i, j);
				if (ans)
				{
					return true;
				}
			}
		}
		return false;
	}
};