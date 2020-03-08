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
		//˵����û�н��
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
		//�ҵ����ʵ�λ�ò���
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
		//���
		if (parent->_data.first > data.first)
		{
			parent->_left = cur;
		}
		//�ұ�
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		//���������
		//������ڵ��Ǻ�ɫ������Ҫ����
		while (cur != _head->_parent && parent->_colour == RED)
		{
			parent = cur->_parent;
			pNode gParent = parent->_parent;
			pNode uncle = nullptr;
			//��ȡ������
			if (gParent->_left == parent)
			{
				uncle = gParent->_right;
			}
			else
			{
				uncle = gParent->_left;
			}

			//�����������ڣ�������ɫ�Ǻ�ɫ��
			//����������
			if (uncle && uncle->_colour == RED)
			{
				//������ɫ
				parent->_colour = BLACK;
				uncle->_colour = BLACK;
				gParent->_colour = RED;
				//���½��
				cur = gParent;
			}
			//��������㲻���ڻ�����ɫ�Ǻ�ɫ��
			else
			{
				//���cur��parent�����ӡ�parent��gParent������ ���� cur��parent���Һ��ӡ�parent��gParent���Һ��ӣ�
				//���е���
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
				//��������Ĺ�ϵ����ȫ�������ȫ���ң�
				//˫��
				else
				{
					if ()
				}
			}
		}
	}
};