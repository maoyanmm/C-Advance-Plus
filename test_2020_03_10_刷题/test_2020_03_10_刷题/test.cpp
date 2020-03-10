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
		stack<TreeNode*> st;
		vector<int> ans;
		TreeNode* cur = root;
		while (cur || !st.empty())
		{
			while (cur)
			{
				ans.push_back(cur->val);
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top()->right;
			st.pop();
		}
		return ans;
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
	vector<int> inorderTraversal(TreeNode* root) {
		stack<TreeNode*> st;
		vector<int> ans;
		TreeNode* cur = root;
		while (!st.empty() || cur)
		{
			while (cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top();
			st.pop();
			ans.push_back(cur->val);
			cur = cur->right;
		}
		return ans;
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
		stack<TreeNode*> st;
		vector<int> ans;
		TreeNode* cur = root;
		TreeNode* got = NULL;
		while (cur || !st.empty())
		{
			while (cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top();
			if (cur->right && cur->right != got)
			{
				cur = cur->right;
			}
			else
			{
				st.pop();
				got = cur;
				ans.push_back(cur->val);
				cur = NULL;
			}
		}
		return ans;
	}
};

/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL)
		{
			return l2;
		}
		if (l2 == NULL)
		{
			return l1;
		}
		if (l1->val <= l2->val)
		{
			l1->next = mergeTwoLists(l1->next, l2);
		}
		else
		{
			l2->next = mergeTwoLists(l1, l2->next);
		}
		return l1->val <= l2->val ? l1 : l2;
	}
};

/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* head = new ListNode(0);
		ListNode* cur = head;
		while (1)
		{
			if (l1 == NULL || l2 == NULL)
			{
				cur->next = l1 == NULL ? l2 : l1;
				break;
			}
			if (l1->val <= l2->val)
			{
				cur->next = l1;
				l1 = l1->next;
			}
			else
			{
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		ListNode* ans = head->next;
		delete head;
		head = NULL;
		return ans;
	}
};