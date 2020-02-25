/*
// Employee info
class Employee {
public:
// It's the unique ID of each node.
// unique id of this employee
int id;
// the importance value of this employee
int importance;
// the id of direct subordinates
vector<int> subordinates;
};
*/
class Solution {
public:
	int getImportance(vector<Employee*> employees, int id) {
		for (int i = 0; i < employees.size(); ++i)
		{
			if (employees[i]->id == id)
			{
				int tmp_importance = 0;
				for (int j = 0; j < employees[i]->subordinates.size(); ++j)
				{
					tmp_importance += getImportance(employees, employees[i]->subordinates[j]);
				}
				return employees[i]->importance + tmp_importance;
			}
		}
		return 0;
	}
};

class Solution {
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		dfs(image, sr, sc);
		for (int i = 0; i < image.size(); ++i)
		{
			for (int j = 0; j < image[0].size(); ++j)
			{
				if (image[i][j] == -1)
				{
					image[i][j] = newColor;
				}
			}
		}
		return image;
	}
	void dfs(vector<vector<int>>& image, int sr, int sc)
	{
		int tmp = image[sr][sc];
		image[sr][sc] = -1;
		if (sr - 1 >= 0 && image[sr - 1][sc] == tmp)
		{
			dfs(image, sr - 1, sc);
		}
		if (sr + 1 < image.size() && image[sr + 1][sc] == tmp)
		{
			dfs(image, sr + 1, sc);
		}
		if (sc - 1 >= 0 && image[sr][sc - 1] == tmp)
		{
			dfs(image, sr, sc - 1);
		}
		if (sc + 1 < image[0].size() && image[sr][sc + 1] == tmp)
		{
			dfs(image, sr, sc + 1);
		}
	}
};

class Solution {
public:

	vector<vector<int> > direction = { { 1, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } };

	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		int row = image.size();
		int col = image[0].size();
		vector<vector<int> > book(row, vector<int>(col, 0));
		dfs(image, book, sr, sc, newColor);
		return image;
	}

	void dfs(vector<vector<int>>& image, vector<vector<int>>& book, int sr, int sc, int newColor)
	{
		int tmp = image[sr][sc];
		image[sr][sc] = newColor;
		book[sr][sc] = 1;
		for (int i = 0; i < 4; ++i)
		{
			int tmp_sr = sr + direction[i][0];
			int tmp_sc = sc + direction[i][1];
			if (tmp_sr < 0 || tmp_sc < 0 || tmp_sr >= image.size() || tmp_sc >= image[0].size())
			{
				continue;
			}
			if (image[tmp_sr][tmp_sc] == tmp && book[tmp_sr][tmp_sc] == 0)
			{
				dfs(image, book, tmp_sr, tmp_sc, newColor);
			}
		}
	}
};