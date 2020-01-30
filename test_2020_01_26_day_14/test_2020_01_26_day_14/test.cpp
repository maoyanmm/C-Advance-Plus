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