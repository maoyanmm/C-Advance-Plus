#include<iostream>
using namespace std;
#include<vector>

 struct ListNode {
        int val;
      struct ListNode *next;
     ListNode(int x) :
            val(x), next(NULL) {
      }
  };

class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		int count = 0;
		ListNode* cur = head;
		while (cur != NULL)
		{
			++count;
			cur = cur->next;
		}
		vector<int> arr(count);
		cur = head;
		for (int i = count - 1; i >= 0; --i)
		{
			arr[i] = cur->val;
			cur = cur->next;
		}
		return arr;
	}
};