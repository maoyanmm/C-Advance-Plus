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
		//����ǵ�һ�β��룬����Ҫnew
		if (_root == nullptr)
		{
			_root = new Node(value);
			return true;
		}
		pNode parent = nullptr;
		pNode cur = _root;
		//�ҵ��ʺ�value��λ��
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
		//���ӵ��ʺ�value�ķ���
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
		//���ҵ�Ҫɾ���Ľ��λ��
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
		//���û�ҵ�
		if (cur == nullptr)
		{
			return false;
		}
		//���Ҫɾ���Ľ������ǿյģ��ұ߿����ǿտ��ܲ���
		//�򽫣��ý��ĸ���� ���� �ýڵ���ұ�
		if (cur->_left == nullptr)
		{//���Ҫɾ���Ľ���Ǹ��ڵ㣬��ֵ��_rootָ��ý����ұ�
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
		//���Ҫɾ���Ľ���ұ��ǿյģ���߿����ǿտ��ܲ���
		//�򽫣��ý��ĸ���� ���� �ýڵ�����
		else if (cur->_right == nullptr)
		{//���Ҫɾ���Ľ���Ǹ��ڵ㣬��ֵ��_rootָ��ý������
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
		else//���ɾ���Ľ�����߶���Ϊ�գ��������ڵ㣩
		{//�������ǣ��ҵ��ý������ң����������ң��󣩽�㣬������������ǣ��������������С�����е���������
			//Ȼ��Ҫɾ���Ľ���ֵ����������ҽڵ㣨�൱�ڰ����ֵɾ���ˣ����������ҽڵ�ĸ��ڵ��������ҽڵ�����������϶�û������������Ϊ�����ҽڵ㣩
			pNode cur_left = cur->_left;
			pNode cur_left_parent = cur;
			//�����ҽڵ�
			while (cur_left->_right)
			{
				cur_left_parent = cur_left;
				cur_left = cur_left->_right;
			}
			//����Ҫɾ���Ľ���ֵ
			cur->_val = cur_left->_val;
			//�����ҽڵ�ĸ��ڵ��������ҽڵ��������
			if (cur_left_parent->_left == cur_left)
			{
				cur_left_parent->_left = cur_left->_left;
			}
			else
			{
				cur_left_parent->_right = cur_left->_left;
			}
			//���Ҫɾ��cur��������ʵ����ɾ�����ҽڵ㣬cur��ֵ�������Ǳ�������
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
	{//�������
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