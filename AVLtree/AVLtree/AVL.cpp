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
		//如果跟为空则直接创建
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		//插入到合适的位置
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
		//创建新节点，连接好和parent的关系
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
		//向上更新结点的平衡因子
		while (parent)
		{
			//如果是左边插入了，则左边高了
			if (parent->_left == cur)
			{
				--parent->_bf;
			}
			else
			{
				++parent->_bf;
			}
			//检查平衡因子的大小
			//还等于零，说明：这个结点是从1或者-1变到0的，由原来的一个子树变成两个子树，也就是高度不变，所以不会对上面的结点产生影响
			if (parent->_bf == 0)
			{
				return true;
			}
			//这是从0变成1的，说明高度增加了一个，对上面结点是有影响的，需要向上继续更新
			else if (abs(parent->_bf) == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			//如果不平衡了就要旋转，把高度降下来
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
				//先右旋后左旋
				//双旋转场景情况特殊，需要判断curLeft插入的是哪边，这会影响parent 和 cur 的平衡因子
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
				//先左旋后右旋
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					pNode curRight = cur->_right;
					int height = curRight->_bf;
					Rotate_Left(cur);
					Rotate_Right(parent);
					//双旋转场景情况特殊，需要判断curRight插入的是哪边，这会影响parent 和 cur 的平衡因子
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
		//一棵树的高度是：左边和右边最大的高度
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
		//得出左右子树的高度差
		int diff = rightHeight - leftHeight;
		//如果平衡因子不平衡、自己更新的平衡因子和现在算的高度差不一致，则不是Avl树
		if (abs(diff) > 1 || diff != root->_bf)
		{
			cout << "结点：" << root->_val << "不平衡" << endl;
			return false;
		}
		//递归的去判断他的子树是否平衡
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
	//右旋
	void Rotate_Right(pNode parent)
	{//一共有三对结点需要连接
		pNode curLeft = parent->_left;
		pNode curLeftRight = curLeft->_right;
		//每次都将一对结点的上下都连接
		//第一对：parent和curLeftRight
		parent->_left = curLeftRight;
		if (curLeftRight)
		{
			curLeftRight->_parent = parent;
		}
		//第二对：curLeft和parent->_parent
		//如果是根节点
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
		//第三对：curLeft和parent
		curLeft->_right = parent;
		parent->_parent = curLeft;
		//更新平衡因子
		parent->_bf = 0;
		curLeft->_bf = 0;
	}
	//左旋
	void Rotate_Left(pNode parent)
	{//一共有三对结点需要连接
		pNode curRight = parent->_right;
		pNode curRightLeft = curRight->_left;
		//每次都将一对结点的上下都连接
		//第一对：parent和curRightLeft
		parent->_right = curRightLeft;
		if (curRightLeft)
		{
			curRightLeft->_parent = parent;
		}
		//第二对：curRight和parent->_parent
		//如果是根节点
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
		//第三对：curRight和parent
		curRight->_left = parent;
		parent->_parent = curRight;
		//更新平衡因子
		parent->_bf = 0;
		curRight->_bf = 0;
	}
	//插入
	
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
		cout << "平衡" << endl;
	}
	else
	{
		cout << "不平衡" << endl;
	}
}

int main()
{
	test1();
	system("pause");
	return 0;
}