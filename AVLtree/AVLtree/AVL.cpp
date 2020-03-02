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
		//�����ԣ�curRight��parent
		curRight->_left = parent;
		parent->_parent = curRight;
		//����ƽ������
		parent->_bf = 0;
		curRight->_bf = 0;
	}
	//����
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