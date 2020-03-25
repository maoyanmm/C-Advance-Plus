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
	bool dfs(TreeNode* cur, long* num)
	{
		if (cur == NULL)
		{
			return true;
		}
		if (!dfs(cur->left, num))
		{
			return false;
		}
		if (*num >= cur->val)
		{
			return false;
		}
		*num = cur->val;
		if (!dfs(cur->right, num))
		{
			return false;
		}
		return true;
	}
	bool isValidBST(TreeNode* root) {
		long* num = new long(LONG_MIN);
		return dfs(root, num);
	}
};

class Solution {
public:
	void DFS(int row, vector<vector<int>>& M)
	{
		for (int i = 0; i < M[0].size(); ++i)
		{
			if (M[row][i] == 1)
			{
				M[row][i] = 0;
				DFS(i, M);
			}
		}
	}
	int findCircleNum(vector<vector<int>>& M) {
		int count = 0;
		for (int i = 0; i < M.size(); ++i)
		{
			for (int j = 0; j < M[0].size(); ++j)
			{
				if (M[i][j] == 1)
				{
					++count;
					DFS(i, M);
				}
			}
		}
		return count;
	}
};