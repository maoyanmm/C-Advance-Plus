#include<iostream>
using namespace std;
#include<vector>
int row, col;

void best_route(vector<vector<int>>& maze, vector<vector<int>>& route_tmp, vector<vector<int>>& route_best, int i, int j)
{
	maze[i][j] = 1;
	route_tmp.push_back({ i, j });
	if (i == row - 1 && j == col - 1)
	{
		if (route_best.empty() || route_tmp.size() < route_best.size())
		{
			route_best = route_tmp;
		}
	}
	if (i - 1 >= 0 && maze[i - 1][j] == 0)
	{
		best_route(maze, route_tmp, route_best, i - 1, j);
	}
	if (i + 1 < row && maze[i + 1][j] == 0)
	{
		best_route(maze, route_tmp, route_best, i + 1, j);
	}
	if (j - 1 >= 0 && maze[i][j - 1] == 0)
	{
		best_route(maze, route_tmp, route_best, i, j - 1);
	}
	if (j + 1 < col && maze[i][j + 1] == 0)
	{
		best_route(maze, route_tmp, route_best, i, j + 1);
	}
	maze[i][j] = 0;
	route_tmp.pop_back();
}

int main()
{
	while (cin >> row >> col)
	{
		vector<vector<int>> maze(row, vector<int>(col, 0));
		vector<vector<int>> route_tmp;
		vector<vector<int>> route_best;
		for (auto& i : maze)
		{
			for (auto& j : i)
			{
				cin >> j;
			}
		}
		best_route(maze, route_tmp, route_best, 0, 0);
		for (auto& e : route_best)
		{
			cout << "(" << e[0] << "," << e[1] << ")" << endl;
		}
	}
	return 0;
}