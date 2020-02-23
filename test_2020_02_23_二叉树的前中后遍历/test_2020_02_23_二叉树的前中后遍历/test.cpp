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
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		recursion(root, result);
		return result;
	}
	void recursion(TreeNode* root, vector<int>& result)
	{
		if (root)
		{
			result.push_back(root->val);
			if (root->left)
			{
				recursion(root->left, result);
			}
			if (root->right)
			{
				recursion(root->right, result);
			}
		}

	}
};


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
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		traverse_begind(result, root, NULL);
		return result;
	}
	void traverse_begind(vector<int>& result, TreeNode* root, TreeNode* got)
	{
		if (root)
		{
			if (root->left && root->left != got)
			{
				traverse_begind(result, root->left, got);
			}
			if (root->right && root->right != got)
			{
				traverse_begind(result, root->right, got);
			}
			result.push_back(root->val);
			got = root;
		}
	}
};