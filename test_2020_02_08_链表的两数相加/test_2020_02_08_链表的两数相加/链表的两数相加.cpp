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
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int carry = 0;
		ListNode* ans = new ListNode(0);
		ans->next = nullptr;
		ListNode* cur = ans;
		while (l1 && l2)
		{
			int tmp = l1->val + l2->val + carry;
			carry = tmp / 10;
			tmp %= 10;
			cur->next = new ListNode(0);
			cur = cur->next;
			cur->next = nullptr;
			cur->val = tmp;
			l1 = l1->next;
			l2 = l2->next;
		}
		while (l1)
		{
			int tmp = l1->val + carry;
			carry = tmp / 10;
			tmp %= 10;
			cur->next = new ListNode(0);
			cur = cur->next;
			cur->next = nullptr;
			cur->val = tmp;
			l1 = l1->next;
		}
		while (l2)
		{
			int tmp = l2->val + carry;
			carry = tmp / 10;
			tmp %= 10;
			cur->next = new ListNode(0);
			cur = cur->next;
			cur->next = nullptr;
			cur->val = tmp;
			l2 = l2->next;
		}
		if (1 == carry)
		{
			cur->next = new ListNode(0);
			cur = cur->next;
			cur->next = nullptr;
			cur->val = 1;
		}
		return ans->next;
	}
};