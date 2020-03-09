#include<utility>
#include<stdlib.h>
#include<iostream>

enum COLOUR
{
	RED,
	BLACK
};

template<class K,class V>
struct RBNode
{
	std::pair<K, V> _data;
	RBNode* _parent;
	RBNode* _left;
	RBNode* _right;
	COLOUR _colour;

	RBNode(std::pair<K, V> data = std::pair<K, V>())
		:_parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _colour(RED)
		, _data(data)
	{ }
};

template<class K, class V>
class RBTree
{
	typedef RBNode<K,V> Node;
	typedef Node* pNode;
private:
	pNode _head;
private:
	//右旋
	void Rotate_Right(pNode parent)
	{
		pNode curLeft = parent->_left;
		pNode curLeftRight = curLeft->_right;

		//分三对连接
		//第一对：parent和curLeftRight
		parent->_left = curLeftRight;
		if (curLeftRight)
		{
			curLeftRight->_parent = parent;
		}
		//第二对：gParent和curLeft
		//如果parent是根
		if (parent == _head->_parent)
		{
			_head->_parent = curLeft;
			curLeft->_parent = _head;
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
		//第三对：parent和curLeft
		curLeft->_right = parent;
		parent->_parent = curLeft;
	}
	//左旋
	void Rotate_Left(pNode parent)
	{
		pNode curRight = parent->_right;
		pNode curRightLeft = curRight->_left;
		//分三对处理
		//第一对：parent和curRightLeft
		parent->_right = curRightLeft;
		if (curRightLeft)
		{
			curRightLeft->_parent = parent;
		}
		//第二对：curRight和gParent
		//如果parent是根
		if (parent == _head->_parent)
		{
			_head->_parent = curRight;
			curRight->_parent = _head;
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
		//第三对：parent和curRight
		curRight->_left = parent;
		parent->_parent = curRight;
	}
	//中序遍历
	void _In_Order(pNode root)
	{
		if (root)
		{
			_In_Order(root->_left);
			std::cout << root->_data.first << "-->" << root->_data.second << std::endl;
			_In_Order(root->_right);
		}
	}
public:
	RBTree()
	{
		_head = new Node();
		_head->_left = _head;
		_head->_right = _head;
		_head->_parent = _head;
	}
	//获取最左边的节点
	pNode Left_Most()
	{
		pNode root = _head->_parent;
		while (root && root->_left)
		{	
			root = root->_left;
		}
		return root;
	}
	//获取最右边的节点
	pNode Right_Most()
	{
		pNode root = _head->_parent;
		while (root && root->_right)
		{
			root = root->_right;
		}
		return root;
	}
	//中序遍历
	void In_Order()
	{
		_In_Order(_head->_parent);
		std::cout << std::endl;
	}
	bool Insert(std::pair<K, V> data)
	{
		//说明还没有结点
		if (_head->_parent == _head)
		{
			pNode root = new Node(data);
			root->_colour = BLACK;
			_head->_left = _head->_right = _head->_parent = root;
			root->_parent = _head;
			return true;
		}
		pNode cur = _head->_parent;
		pNode parent = nullptr;
		//找到合适的位置插入
		while (cur)
		{
			parent = cur;
			if (cur->_data.first > data.first)
			{
				cur = cur->_left;
			}
			else if (cur->_data.first < data.first)
			{
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(data);
		//左边
		if (parent->_data.first > data.first)
		{
			parent->_left = cur;
		}
		//右边
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		//分情况调整
		//如果父节点是黑色，则不需要调整
		while (cur != _head->_parent && cur->_parent->_colour == RED)
		{
			parent = cur->_parent;
			pNode gParent = parent->_parent;
			pNode uncle = nullptr;
			//获取叔叔结点
			if (gParent->_left == parent)
			{
				uncle = gParent->_right;
			}
			else
			{
				uncle = gParent->_left;
			}

			//如果叔叔结点存在，而且颜色是红色：
			//向上逐层更新，暂不需要旋转
			if (uncle && uncle->_colour == RED)
			{
				//更新颜色
				parent->_colour = BLACK;
				uncle->_colour = BLACK;
				gParent->_colour = RED;
				//更新结点
				cur = gParent;
			}
			//如果叔叔结点不存在或者颜色是黑色：
			//则需要旋转
			else
			{
				//如果cur是parent的左孩子、parent是gParent的左孩子 或者 cur是parent的右孩子、parent是gParent的右孩子：
				//进行单旋
				if ((gParent->_left == parent && parent->_left == cur) || (gParent->_right == parent && parent->_right == cur))
				{
					if (parent->_left == cur)
					{
						Rotate_Right(gParent);
					}
					else
					{
						Rotate_Left(gParent);
					}
					gParent->_colour = RED;
					parent->_colour = BLACK;
					break;
				}
				//如果三代的关系不是全是左或者全是右：
				//双旋
				else
				{
					//下面只做了单旋，第二次旋转放在下一次循环
					//这是双旋的场景，但是旋一次后就变成了上面的单旋的场景了，所以cur不更新成gParent
					if (parent->_right == cur)
					{
						Rotate_Left(parent);
						//因为交换完之后parent在下面cur在上面
						//所以要把两个指向更改一下
						std::swap(cur, parent);
					}
					else
					{
						Rotate_Right(parent);
						//因为交换完之后parent在下面cur在上面
						//所以要把两个指向更改一下
						std::swap(cur, parent);
					}
				}
			}
		}
		//根始终是黑色的
		_head->_parent->_colour = BLACK;
		_head->_left = Left_Most();
		_head->_right = Right_Most();
		return true;
	}
};

void test()
{
	RBTree<int, int> rb;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i)
	{
		rb.Insert(std::make_pair(arr2[i], arr2[i] + 10));
	}
	rb.In_Order();
}

int main()
{
	test();
	system("pause");
	return 0;
}