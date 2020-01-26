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