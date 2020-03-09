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
	//����
	void Rotate_Right(pNode parent)
	{
		pNode curLeft = parent->_left;
		pNode curLeftRight = curLeft->_right;

		//����������
		//��һ�ԣ�parent��curLeftRight
		parent->_left = curLeftRight;
		if (curLeftRight)
		{
			curLeftRight->_parent = parent;
		}
		//�ڶ��ԣ�gParent��curLeft
		//���parent�Ǹ�
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
		//�����ԣ�parent��curLeft
		curLeft->_right = parent;
		parent->_parent = curLeft;
	}
	//����
	void Rotate_Left(pNode parent)
	{
		pNode curRight = parent->_right;
		pNode curRightLeft = curRight->_left;
		//�����Դ���
		//��һ�ԣ�parent��curRightLeft
		parent->_right = curRightLeft;
		if (curRightLeft)
		{
			curRightLeft->_parent = parent;
		}
		//�ڶ��ԣ�curRight��gParent
		//���parent�Ǹ�
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
		//�����ԣ�parent��curRight
		curRight->_left = parent;
		parent->_parent = curRight;
	}
	//�������
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
	//��ȡ����ߵĽڵ�
	pNode Left_Most()
	{
		pNode root = _head->_parent;
		while (root && root->_left)
		{	
			root = root->_left;
		}
		return root;
	}
	//��ȡ���ұߵĽڵ�
	pNode Right_Most()
	{
		pNode root = _head->_parent;
		while (root && root->_right)
		{
			root = root->_right;
		}
		return root;
	}
	//�������
	void In_Order()
	{
		_In_Order(_head->_parent);
		std::cout << std::endl;
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
		cur = new Node(data);
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
		while (cur != _head->_parent && cur->_parent->_colour == RED)
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
			//���������£��ݲ���Ҫ��ת
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
			//����Ҫ��ת
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
					break;
				}
				//��������Ĺ�ϵ����ȫ�������ȫ���ң�
				//˫��
				else
				{
					//����ֻ���˵������ڶ�����ת������һ��ѭ��
					//����˫���ĳ�����������һ�κ�ͱ��������ĵ����ĳ����ˣ�����cur�����³�gParent
					if (parent->_right == cur)
					{
						Rotate_Left(parent);
						//��Ϊ������֮��parent������cur������
						//����Ҫ������ָ�����һ��
						std::swap(cur, parent);
					}
					else
					{
						Rotate_Right(parent);
						//��Ϊ������֮��parent������cur������
						//����Ҫ������ָ�����һ��
						std::swap(cur, parent);
					}
				}
			}
		}
		//��ʼ���Ǻ�ɫ��
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