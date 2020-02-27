#include<iostream>
using namespace std;

template<class T>
struct BSTnode
{
	BSTnode(const T& value = T())
		:_left(nullptr)
		, _right(nullptr)
		, _val(value)
	{

	}

	T _val;
	BSTnode<T>* _left;
	BSTnode<T>* _right;
};

template<class T>
class BSTree
{
public:
	typedef BSTnode<T> Node;
	typedef BSTnode<T>* pNode;

	pNode Find(const T& value)
	{
		pNode cur = _root;
		while (cur)
		{
			if (cur->_val == value)
			{
				return cur;
			}
			else if (cur->_val > value)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		return cur;
	}

	bool Insert(const T& value)
	{
		//如果是第一次插入，则需要new
		if (_root == nullptr)
		{
			_root = new Node(value);
			return true;
		}
		pNode parent = nullptr;
		pNode cur = _root;
		//找到适合value的位置
		while (cur)
		{
			parent = cur;
			if (cur->_val == value)
			{
				return false;
			}
			else if (cur->_val > value)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		//连接到适合value的方向
		if (value > parent->_val)
		{
			parent->_right = new Node(value);
		}
		else
		{
			parent->_left = new Node(value);
		}
		return true;
	}

	bool Erase(const T& value)
	{
		pNode parent = nullptr;
		pNode cur = _root;
		//先找到要删除的结点位置
		while (cur)
		{
			if (cur->_val == value)
			{
				break;
			}
			parent = cur;
			if (cur->_val > value)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		//如果没找到
		if (cur == nullptr)
		{
			return false;
		}
		//如果要删除的结点左边是空的，右边可能是空可能不是
		//则将：该结点的父结点 连接 该节点的右边
		if (cur->_left == nullptr)
		{//如果要删除的结点是根节点，则值用_root指向该结点的右边
			if (cur == _root)
			{
				_root = cur->_right;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
		}
		//如果要删除的结点右边是空的，左边可能是空可能不是
		//则将：该结点的父结点 连接 该节点的左边
		else if (cur->_right == nullptr)
		{//如果要删除的结点是根节点，则值用_root指向该结点的左边
			if (cur == _root)
			{
				_root = cur->_left;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
		}
		else//如果删除的结点两边都不为空（包括根节点）
		{//处理方法是：找到该结点的左（右）子树的最右（左）结点，这个结点的属性是：在左子树中最大，小于所有的右子树。
			//然后将要删除的结点的值等于这个最右节点（相当于把这个值删除了），再用最右节点的父节点连接最右节点的左子树（肯定没有右子树，因为是最右节点）
			pNode cur_left = cur->_left;
			pNode cur_left_parent = cur;
			//找最右节点
			while (cur_left->_right)
			{
				cur_left_parent = cur_left;
				cur_left = cur_left->_right;
			}
			//覆盖要删除的结点的值
			cur->_val = cur_left->_val;
			//用最右节点的父节点连接最右节点的左子树
			if (cur_left_parent->_left == cur_left)
			{
				cur_left_parent->_left = cur_left->_left;
			}
			else
			{
				cur_left_parent->_right = cur_left->_left;
			}
			//最后要删除cur，但这里实际是删除最右节点，cur的值在这里是被覆盖了
			cur = cur_left;
		}
		delete cur;
		cur = nullptr;
		return true;
	}

	void InOrder()
	{
		pNode cur = _root;
		_InOrder(cur);
		cout << endl;
	}
	void _InOrder(pNode root)
	{//中序遍历
		if (root)
		{
			_InOrder(root->_left);
			cout << root->_val << " ";
			_InOrder(root->_right);
		}
	}

private:
	pNode _root = nullptr;
};

void test1()
{
	BSTree<int> root;
	root.Insert(5);
	root.Insert(3);
	root.Insert(1);
	root.Insert(0);
	root.Insert(2);
	root.Insert(4);
	root.Insert(7);
	root.Insert(6);
	root.Insert(8);
	root.Insert(9);
	root.InOrder();
	root.Erase(8);
	root.InOrder();
	root.Erase(2);
	root.InOrder();
	root.Erase(1);
	root.InOrder();
	root.Erase(7);
	root.InOrder();
	root.Erase(5);
	root.InOrder();
}

int main()
{
	test1();
	system("pause");
	return 0;
}