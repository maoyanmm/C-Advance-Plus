/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};*/
class Solution {
public:
	ListNode* ReverseList(ListNode* pHead) {
		if (pHead == NULL || pHead->next == NULL)
		{
			return pHead;
		}
		ListNode* slow = pHead;
		ListNode* mid = pHead->next;
		ListNode* fast = mid->next;
		pHead->next = NULL;
		while (mid)
		{
			mid->next = slow;
			slow = mid;
			mid = fast;
			if (mid == NULL)
			{
				break;
			}
			fast = fast->next;
		}
		return slow;
	}
};