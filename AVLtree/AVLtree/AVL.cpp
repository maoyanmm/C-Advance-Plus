#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct AVLnode
{
	AVLnode(const T& val = T())
	:_bf(0)
	, _val(val)
	, _left(nullptr)
	, _right(nullptr)
	, _parent(nullptr)
	{ }
	AVLnode<T>* _left;
	AVLnode<T>* _right;
	AVLnode<T>* _parent;
	T _val;
	int _bf;
};

template<class T>
class AVLtree
{
	typedef AVLnode<T> Node;
	typedef Node* pNode;
public:
	void In_Order()
	{
		_In_Order(_root);
		cout << endl;
	}
	bool Insert_Node(const T& val)
	{
		pNode parent = nullptr;
		pNode cur = _root;
		//�����Ϊ����ֱ�Ӵ���
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		//���뵽���ʵ�λ��
		while (cur)
		{
			parent = cur;
			if (cur->_val == val)
			{
				return false;
			}
			else if (cur->_val > val)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		//�����½ڵ㣬���Ӻú�parent�Ĺ�ϵ
		cur = new Node(val);
		if (val > parent->_val)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
		//���ϸ��½���ƽ������
		while (parent)
		{
			//�������߲����ˣ�����߸���
			if (parent->_left == cur)
			{
				--parent->_bf;
			}
			else
			{
				++parent->_bf;
			}
			//���ƽ�����ӵĴ�С
			//�������㣬˵�����������Ǵ�1����-1�䵽0�ģ���ԭ����һ�������������������Ҳ���Ǹ߶Ȳ��䣬���Բ��������Ľ�����Ӱ��
			if (parent->_bf == 0)
			{
				return true;
			}
			//���Ǵ�0���1�ģ�˵���߶�������һ����������������Ӱ��ģ���Ҫ���ϼ�������
			else if (abs(parent->_bf) == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			//�����ƽ���˾�Ҫ��ת���Ѹ߶Ƚ�����
			else if (abs(parent->_bf) == 2)
			{
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					Rotate_Left(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					Rotate_Right(parent);
				}
				//������������
				//˫��ת����������⣬��Ҫ�ж�curLeft��������ıߣ����Ӱ��parent �� cur ��ƽ������
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					pNode curLeft = cur->_left;
					int height = curLeft->_bf;
					Rotate_Right(cur);
					Rotate_Left(parent);
					if (height == 1)
					{
						parent->_bf = -1;
						cur->_bf = 0;
					}
					else if (height == -1)
					{
						parent->_bf = 0;
						cur->_bf = 1;
					}
				}
				//������������
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					pNode curRight = cur->_right;
					int height = curRight->_bf;
					Rotate_Left(cur);
					Rotate_Right(parent);
					//˫��ת����������⣬��Ҫ�ж�curRight��������ıߣ����Ӱ��parent �� cur ��ƽ������
					if (height == 1)
					{
						parent->_bf = 0;
						cur->_bf = -1;
					}
					else if (height == -1)
					{
						parent->_bf = 1;
						cur->_bf = 0;
					}
				}

				return true;

			}
			else
			{
				assert(false);
			}
		}
		return true;
	}
	int Height(pNode root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		//һ�����ĸ߶��ǣ���ߺ��ұ����ĸ߶�
		return Height(root->_left) > Height(root->_right) ? Height(root->_left) + 1 : Height(root->_right) + 1;
	}
	bool Is_Avl()
	{
		return _Is_Avl(_root);
	}
	bool _Is_Avl(pNode root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);
		//�ó����������ĸ߶Ȳ�
		int diff = rightHeight - leftHeight;
		//���ƽ�����Ӳ�ƽ�⡢�Լ����µ�ƽ�����Ӻ�������ĸ߶Ȳһ�£�����Avl��
		if (abs(diff) > 1 || diff != root->_bf)
		{
			cout << "��㣺" << root->_val << "��ƽ��" << endl;
			return false;
		}
		//�ݹ��ȥ�ж����������Ƿ�ƽ��
		return _Is_Avl(root->_left) && _Is_Avl(root->_right);
	}

private:
	void _In_Order(pNode root)
	{
		if (root)
		{
			_In_Order(root->_left);
			cout << root->_val << " ";
			_In_Order(root->_right);
		}
	}
	//����
	void Rotate_Right(pNode parent)
	{//һ�������Խ����Ҫ����
		pNode curLeft = parent->_left;
		pNode curLeftRight = curLeft->_right;
		//ÿ�ζ���һ�Խ������¶�����
		//��һ�ԣ�parent��curLeftRight
		parent->_left = curLeftRight;
		if (curLeftRight)
		{
			curLeftRight->_parent = parent;
		}
		//�ڶ��ԣ�curLeft��parent->_parent
		//����Ǹ��ڵ�
		if (parent == _root)
		{
			_root = curLeft;
			curLeft->_parent = nullptr;
		}
		else
		{
			pNode gParent = parent->_parent;
			if (gParent->_left == parent)
			{
				gParent->_left = curLeft;
			}
			else
			{
				gParent->_right = curLeft;
			}
			curLeft->_parent = gParent;
		}
		//�����ԣ�curLeft��parent
		curLeft->_right = parent;
		parent->_parent = curLeft;
		//����ƽ������
		parent->_bf = 0;
		curLeft->_bf = 0;
	}
	//����
	void Rotate_Left(pNode parent)
	{//һ�������Խ����Ҫ����
		pNode curRight = parent->_right;
		pNode curRightLeft = curRight->_left;
		//ÿ�ζ���һ�Խ������¶�����
		//��һ�ԣ�parent��curRightLeft
		parent->_right = curRightLeft;
		if (curRightLeft)
		{
			curRightLeft->_parent = parent;
		}
		//�ڶ��ԣ�curRight��parent->_parent
		//����Ǹ��ڵ�
		if (parent == _root)
		{
			_root = curRight;
			curRight->_parent = nullptr;
		}
		else
		{
			pNode gParent = parent->_parent;
			if (gParent->_left == parent)
			{
				gParent->_left = curRight;
			}
			else
			{
				gParent->_right = curRight;
			}
			curRight->_parent = gParent;
		}
		//�����ԣ�curRight��parent
		curRight->_left = parent;
		parent->_parent = curRight;
		//����ƽ������
		parent->_bf = 0;
		curRight->_bf = 0;
	}
	//����
	
private:
	pNode _root = nullptr;
};

void test1()
{
	AVLtree<int> avl;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i)
	{
		avl.Insert_Node(arr2[i]);
	}
	avl.In_Order();
	if (avl.Is_Avl())
	{
		cout << "ƽ��" << endl;
	}
	else
	{
		cout << "��ƽ��" << endl;
	}
}

int main()
{
	test1();
	system("pause");
	return 0;
}