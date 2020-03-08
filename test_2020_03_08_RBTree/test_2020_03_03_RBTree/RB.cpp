#include<utility>

enum COLOUR
{
	RED,
	BLACK
};

template<class K,class V>
class RBNode
{
private:
	std::pair<K, V> _data;
	RBNode* _parent;
	RBNode* _left;
	RBNode* _right;
	COLOUR _colour;
public:
	RBNode(std::pair<K, V> data = std::pair<K, V>())
		:_parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _colour(RED)
	{ }
};

template<class K, class V>
class RBTree
{
	typedef RBNode Node;
	typedef Node* pNode;
private:
	pNode _head;
public:
	RBTree()
	{
		_head = new Node();
		_head->_left = _head;
		_head->_right = _head;
		_head->_parent = _head;
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
		pNode cur = new Node(data);
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
		while (cur != _head->_parent && parent->_colour == RED)
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
			//向上逐层更新
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
					return true;
				}
				//如果三代的关系不是全是左或者全是右：
				//双旋
				else
				{
					if ()
				}
			}
		}
	}
};