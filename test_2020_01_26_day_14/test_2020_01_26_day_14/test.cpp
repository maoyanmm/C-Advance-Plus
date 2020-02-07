#include<iostream>
using namespace std;
#include<queue>
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		queue<TreeNode*> qq;
		vector<int> ans;
		if (root == NULL)
		{
			return ans;
		}
		qq.push(root);
		while (!qq.empty())
		{
			int tmp = qq.front()->val;
			ans.push_back(tmp);
			int i = qq.size();
			while (i--)
			{
				if (qq.front()->right)
				{
					qq.push(qq.front()->right);
				}
				if (qq.front()->left)
				{
					qq.push(qq.front()->left);
				}
				qq.pop();;
			}
		}
		return ans;
	}
};

class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> ans;
		helper(ans, root, 0);
		return ans;
	}

	void helper(vector<int>& ans, TreeNode* root, int n)
	{
		if (root == NULL)
		{
			return;
		}
		if (ans.size() == n)
		{
			ans.push_back(root->val);
		}
		if (root->right)
		{
			helper(ans, root->right, n + 1);
		}
		if (root->left)
		{
			helper(ans, root->left, n + 1);
		}
	}
};


class Solution {
public:
	bool isMatch(string s, string p) {
		int s_size = s.size();
		int p_size = p.size();
		int i = 0;
		int j = 0;
		int star_i = 0;
		int star_j = 0;
		int flag = 0;
		while (i < s_size)
		{
			if (j < p_size && (s[i] == p[j] || p[j] == '?'))//如果是普通的匹配，则++
			{
				++i;
				++j;
			}
			else if (j < p_size && p[j] == '*')//如果遇到了*，则用stari记录当前i的位置，starj记录*后面的位置，准备开始用*后面的字母来匹配s里的字母
			{
				flag = 1;
				star_i = i;
				star_j = ++j;
			}
			else if (1 == flag)//如果有进入上面的if，flag会置为1，则说明前面正在进行*的匹配字母
			{//如果以star_i位置的后面的字符串和star_j后面的字符串不完全匹配，则将之前star_i（也就是上一次开始匹配star_j的首字母）++，也就是再从star_i+1为首的字符串再开始匹配
				i = ++star_i;
				j = star_j;
			}
			else
			{
				return false;
			}
		}
		while (j < p_size && p[j] == '*')//上面的while退出是i走到头了，但是j并不一定，这里需要将j往后走，如果遇到*则表示，*是匹配的空字符
		{
			++j;
		}
		if (j == p_size)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class Solution {
public:
	int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
		if (S == T)
		{
			return 0;
		}
		queue<int> myque;//用来形式广度优先搜索
		myque.push(S);//将出发站push
		int mini_steps = 1;//最少要坐一站路
		vector<bool> have_gone(routes.size(), false);//用来判断该公交车是否坐过
		unordered_map<int, vector<int>> umap;//该map存储两个元素：1、某个站点 2、能到达该站点的公交车（路线）数组
		for (int i = 0; i < routes.size(); ++i)//遍历所有的公交车（路线）
		{
			for (auto& e : routes[i])//遍历某个公交车（路线）可以到达的所有站点
			{
				umap[e].push_back(i);//将站点作为key值，将公交车（可以到达该站点的公交车集合）数组作为value
			}
		}
		while (!myque.empty())
		{
			for (int i = myque.size(); i > 0; --i)//遍历队列中的各个站点
			{
				int front_station = myque.front();
				myque.pop();
				//下面开始遍历：可以到达front_station的各个路线 或者说 在front_station停站的公交车
				for (auto& route_index : umap[front_station])//遍历 可以到达 取出队列的第一个元素（某个站点） 的所有路线
				{
					if (!have_gone[route_index])//如果该公交车（路线）没有坐过（经过）
					{
						have_gone[route_index] = true;//标志位坐过
						//下面开始遍历：某个公交车（能在front_station停站的公交车）可以到达的所有站点
						for (auto& station : routes[route_index])//遍历 到达那个站点的 某一条路线
						{
							if (station == T)//如果这个公交能到终点，就直接返回mini_steps
							{
								return mini_steps;
							}
							myque.push(station);//每次都要将该公交车能到达的所有站点插入队列中，来作为后面的一层搜索（广度优先搜索）
						}
					}
				}
			}
			++mini_steps;//遍历完一层才++；说明：所有公交车（能在这一层的所有站点停站的公交车）能到达的所有站点中 没有终点
		}
		return -1;
	}
};