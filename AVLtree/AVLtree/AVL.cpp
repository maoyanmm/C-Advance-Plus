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
			curRight = nullptr;
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

				return true;

			}
			else
			{
				assert(false);
			}
		}
		return true;
	}
private:
	pNode _root = nullptr;
};