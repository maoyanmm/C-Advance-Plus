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
			if (j < p_size && (s[i] == p[j] || p[j] == '?'))//�������ͨ��ƥ�䣬��++
			{
				++i;
				++j;
			}
			else if (j < p_size && p[j] == '*')//���������*������stari��¼��ǰi��λ�ã�starj��¼*�����λ�ã�׼����ʼ��*�������ĸ��ƥ��s�����ĸ
			{
				flag = 1;
				star_i = i;
				star_j = ++j;
			}
			else if (1 == flag)//����н��������if��flag����Ϊ1����˵��ǰ�����ڽ���*��ƥ����ĸ
			{//�����star_iλ�õĺ�����ַ�����star_j������ַ�������ȫƥ�䣬��֮ǰstar_i��Ҳ������һ�ο�ʼƥ��star_j������ĸ��++��Ҳ�����ٴ�star_i+1Ϊ�׵��ַ����ٿ�ʼƥ��
				i = ++star_i;
				j = star_j;
			}
			else
			{
				return false;
			}
		}
		while (j < p_size && p[j] == '*')//�����while�˳���i�ߵ�ͷ�ˣ�����j����һ����������Ҫ��j�����ߣ��������*���ʾ��*��ƥ��Ŀ��ַ�
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

class Solution {
public:
	int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
		if (S == T)
		{
			return 0;
		}
		queue<int> myque;//������ʽ�����������
		myque.push(S);//������վpush
		int mini_steps = 1;//����Ҫ��һվ·
		vector<bool> have_gone(routes.size(), false);//�����жϸù������Ƿ�����
		unordered_map<int, vector<int>> umap;//��map�洢����Ԫ�أ�1��ĳ��վ�� 2���ܵ����վ��Ĺ�������·�ߣ�����
		for (int i = 0; i < routes.size(); ++i)//�������еĹ�������·�ߣ�
		{
			for (auto& e : routes[i])//����ĳ����������·�ߣ����Ե��������վ��
			{
				umap[e].push_back(i);//��վ����Ϊkeyֵ���������������Ե����վ��Ĺ��������ϣ�������Ϊvalue
			}
		}
		while (!myque.empty())
		{
			for (int i = myque.size(); i > 0; --i)//���������еĸ���վ��
			{
				int front_station = myque.front();
				myque.pop();
				//���濪ʼ���������Ե���front_station�ĸ���·�� ����˵ ��front_stationͣվ�Ĺ�����
				for (auto& route_index : umap[front_station])//���� ���Ե��� ȡ�����еĵ�һ��Ԫ�أ�ĳ��վ�㣩 ������·��
				{
					if (!have_gone[route_index])//����ù�������·�ߣ�û��������������
					{
						have_gone[route_index] = true;//��־λ����
						//���濪ʼ������ĳ��������������front_stationͣվ�Ĺ����������Ե��������վ��
						for (auto& station : routes[route_index])//���� �����Ǹ�վ��� ĳһ��·��
						{
							if (station == T)//�����������ܵ��յ㣬��ֱ�ӷ���mini_steps
							{
								return mini_steps;
							}
							myque.push(station);//ÿ�ζ�Ҫ���ù������ܵ��������վ���������У�����Ϊ�����һ���������������������
						}
					}
				}
			}
			++mini_steps;//������һ���++��˵�������й�������������һ�������վ��ͣվ�Ĺ��������ܵ��������վ���� û���յ�
		}
		return -1;
	}
};