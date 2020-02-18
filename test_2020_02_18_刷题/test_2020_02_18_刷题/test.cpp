class Solution {
public:
	void merge(vector<int>& A, int m, vector<int>& B, int n) {
		int cur_a = m;
		for (int i = 0; i < n; ++i)
		{
			A[cur_a++] = B[i];
		}
		sort(A.begin(), A.end());
	}
};

class Solution {
public:
	void merge(vector<int>& A, int m, vector<int>& B, int n) {
		int index_b = n - 1;
		int index_a = m - 1;
		int index = m + n - 1;
		for (int i = index; i >= 0; --i)
		{
			if ((index_a >= 0 && index_b >= 0) && (A[index_a] > B[index_b]))
			{
				A[i] = A[index_a--];
			}
			else if ((index_a >= 0 && index_b >= 0) && (A[index_a] <= B[index_b]))
			{
				A[i] = B[index_b--];
			}
			else if (index_a >= 0)
			{
				A[i] = A[index_a--];
			}
			else
			{
				A[i] = B[index_b--];
			}
		}
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
		if (NULL == l1)
		{
			return l2;
		}
		else if (NULL == l2)
		{
			return l1;
		}
		else if (l1->val > l2->val)
		{
			l2->next = mergeTwoLists(l1, l2->next);
		}
		else
		{
			l1->next = mergeTwoLists(l1->next, l2);
		}
		if (l1->val <= l2->val)
		{
			return l1;
		}
		return l2;
	}
};