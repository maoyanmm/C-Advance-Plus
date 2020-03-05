class Solution {
public:
	int direction[4][2] = { { 1, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } };
	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty())
		{
			return 0;
		}
		int count = 0;
		int row = grid.size();
		int col = grid[0].size();
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (grid[i][j] == '1')
				{
					++count;
					dfs(grid, i, j);
				}
			}
		}
		return count;
	}
	void dfs(vector<vector<char>>& grid, int i, int j)
	{
		grid[i][j] = '2';
		for (int index = 0; index < 4; ++index)
		{
			int tmp_i = i + direction[index][0];
			int tmp_j = j + direction[index][1];
			if (tmp_i >= 0 && tmp_j >= 0 && tmp_i < grid.size() && tmp_j < grid[0].size() && grid[tmp_i][tmp_j] == '1')
			{
				dfs(grid, tmp_i, tmp_j);
			}
		}
	}
};


class Solution {
public:
	int direction[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		if (grid.empty())
		{
			return 0;
		}
		int maxArea = 0;
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[0].size(); ++j)
			{
				if (grid[i][j] == 1)
				{
					int tmpArea = 0;
					dfs(grid, i, j, tmpArea);
					if (tmpArea > maxArea)
					{
						maxArea = tmpArea;
					}
				}
			}
		}
		return maxArea;
	}
	void dfs(vector<vector<int>>& grid, int i, int j, int& tmpArea)
	{
		++tmpArea;
		grid[i][j] = 2;
		for (int index = 0; index < 4; ++index)
		{
			int tmp_i = i + direction[index][0];
			int tmp_j = j + direction[index][1];
			if (tmp_i >= 0 && tmp_j >= 0 && tmp_i < grid.size() && tmp_j < grid[0].size() && grid[tmp_i][tmp_j] == 1)
			{
				dfs(grid, tmp_i, tmp_j, tmpArea);
			}
		}
	}
};


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
		queue<Employee*> q;
		for (int i = 0; i < employees.size(); ++i)
		{
			if (employees[i]->id == id)
			{
				q.push(employees[i]);
				break;
			}
		}
		int importance_count = 0;
		while (!q.empty())
		{
			importance_count += q.front()->importance;
			for (int i = 0; i < q.front()->subordinates.size(); ++i)
			{
				for (int j = 0; j < employees.size(); ++j)
				{
					if (employees[j]->id == q.front()->subordinates[i])
					{
						q.push(employees[j]);
						break;
					}
				}
			}
			q.pop();
		}
		return importance_count;
	}
};

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
		queue<int> q;
		unordered_map<int, Employee*> book;
		for (const auto& e : employees)
		{
			book[e->id] = e;
		}
		q.push(id);
		int importance_count = 0;
		while (!q.empty())
		{
			int tmp = q.front();
			importance_count += book[tmp]->importance;
			q.pop();
			for (const auto& e : book[tmp]->subordinates)
			{
				q.push(e);
			}
		}
		return importance_count;
	}
};


/*
// Definition for a Node.
class Node {
public:
int val;
vector<Node*> children;

Node() {}

Node(int _val) {
val = _val;
}

Node(int _val, vector<Node*> _children) {
val = _val;
children = _children;
}
};
*/
class Solution {
public:
	vector<vector<int>> levelOrder(Node* root) {
		queue<Node*> q;
		q.push(root);
		vector<vector<int>> ans;
		if (root == NULL)
		{
			return ans;
		}
		while (!q.empty())
		{
			vector<int> rowAns;
			int qSize = q.size();
			for (int i = 0; i < qSize; ++i)
			{
				rowAns.push_back(q.front()->val);
				for (const auto& e : q.front()->children)
				{
					q.push(e);
				}
				q.pop();
			}
			ans.push_back(rowAns);
		}
		return ans;
	}
};

class Solution {
public:
	struct Node
	{
		Node(int x, int y)
		{
			_x = x;
			_y = y;
		}
		int _x;
		int _y;
	};
	int orangesRotting(vector<vector<int>>& grid) {
		queue<Node> q;
		int time = 0;
		int direction[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[0].size(); ++j)
			{
				if (grid[i][j] == 2)
				{
					q.push(Node(i, j));
				}
			}
		}
		while (!q.empty())
		{
			int size = q.size();
			bool flag = false;
			for (int i = 0; i < size; ++i)
			{
				Node cur = q.front();
				q.pop();
				for (int i = 0; i < 4; ++i)
				{
					int nextX = cur._x + direction[i][0];
					int nextY = cur._y + direction[i][1];
					if (nextX >= 0 && nextY >= 0 && nextX < grid.size() && nextY < grid[0].size() && grid[nextX][nextY] == 1)
					{
						grid[nextX][nextY] = 2;
						q.push(Node(nextX, nextY));
						flag = true;
					}
				}
			}
			if (flag)
			{
				++time;
			}
		}
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[0].size(); ++j)
			{
				if (grid[i][j] == 1)
				{
					return -1;
				}
			}
		}
		return time;
	}
};