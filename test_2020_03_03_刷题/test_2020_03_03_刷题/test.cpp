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
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* cur = head;
		ListNode* behind = head;
		ListNode* prev = NULL;
		while (--n && behind)
		{
			behind = behind->next;
		}
		if (behind == NULL)
		{
			return NULL;
		}
		while (behind->next)
		{
			behind = behind->next;
			prev = cur;
			cur = cur->next;
		}
		if (cur == head)
		{
			return head->next;
		}
		if (prev)
		{
			prev->next = cur->next;
		}
		return head;
	}
};