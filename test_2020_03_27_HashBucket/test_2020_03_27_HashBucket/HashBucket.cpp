#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
#include<vector>

template<class V>
struct HashNode
{
	V _data;
	HashNode<V>* _next;

	HashNode(const V& data = V())
		:_data(data)
		, _next(nullptr)
	{ }
};

//前置声明
template<class K, class V, class KeyOfValue>
class HashBucket;
//迭代器
template<class K, class V, class KeyOfValue>
struct HashIterator
{
	typedef HashNode<V> Node;
	typedef Node* pNode;
	typedef HashIterator<K, V, KeyOfValue> Self;
	typedef typename HashBucket<K, V, KeyOfValue> HSbucket;

	pNode _node;
	HSbucket* _hb;
	
	HashIterator(pNode node, HSbucket* hb)
		:_node(node)
		, _hb(hb)
	{

	}

	V& operator*()
	{
		return _node->_data;
	}
	V* operator->()
	{
		return &_node->_data;
	}
	bool operator!=(const Self& it)
	{
		return _node != it->_node;
	}
	Self& operator++()
	{
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			KeyOfValue kov;
			int table_size = _hb->_table.size();
			int index = kov(_node->_data) % table_size;
			++index;
			for (; index < table_size; ++index)
			{
				if (_hb->_table[index] != nullptr)
				{
					_node = _hb->_table[index];
					break;
				}
			}
			if (index == table_size)
			{
				_node = nullptr;
			}
		}
		return *this;
	}
};

//哈希桶
template<class K,class V,class KeyOfValue>
class HashBucket
{
public:
	friend HashIterator<K, V, KeyOfValue>;
	typedef HashNode<V> Node;
	typedef Node* pNode;
	typedef typename HashIterator<K,V,KeyOfValue> iterator;
private:
	vector<pNode> _table;
	size_t _size;
public:
	iterator begin()
	{
		for (int i = 0; i < _table.size(); ++i)
		{
			if (_table[i])
			{
				KeyOfValue kov;
				return iterator(_table[i], this);
			}
		}
		return iterator(nullptr, this);
	}
	HashBucket()
		:_size(0)
	{
		_table.resize(5,nullptr);
	}
	bool Insert(const V& data)
	{
		//检查容量
		ChekckCapacity();
		//先确定数组下标
		KeyOfValue kov;
		int index = kov(data) % _table.size();
		//插入
		pNode cur = _table[index];
		//判断是否已经有这个元素，直到cur为空
		while (cur)
		{
			if (kov(cur->_data) == kov(data))
			{
				return false;
			}
			cur = cur->_next;
		}
		//创建新节点
		cur = new Node(data);
		//让新节点指向这个链表的头，头插
		cur->_next = _table[index];
		//更新数组的元素
		_table[index] = cur;
		++_size;
		return true;
	}
	void ChekckCapacity()
	{
		//负载因子可以是1
		if (_size / _table.size() < 1)
		{
			return;
		}
		KeyOfValue kov;
		vector<pNode> new_table(_size * 2);
		for (int i = 0; i < _table.size(); ++i)
		{
			pNode cur = _table[i];
			while (cur)
			{
				//先保存后一个节点
				pNode next = cur->_next;
				//确定这个数据在新表的位置
				int index = kov(cur->_data) % new_table.size();
				//头插
				cur->_next = new_table[index];
				//更新数组元素
				new_table[index] = cur;
				//继续遍历
				cur = next;
			}
			_table[i] = nullptr;
		}
		_table.swap(new_table);
	}
};

//模拟unordered_map
template<class K,class V>
class MyUnorderedMap
{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
	
private:
	HashBucket<K, pair<K,V>, MapKeyOfValue> _hb;
public:
	typedef typename HashBucket<K, pair<K, V>, MapKeyOfValue>::iterator iterator;
	bool Insert(const pair<K, V>& data)
	{
		return _hb.Insert(data);
	}
	iterator begin()
	{
		return _hb.begin();
	}

};

//模拟unordered_set
template<class K>
class MyUnorderedSet
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& data)
		{
			return data;
		}
	};
private:
	HashBucket<K, K, SetKeyOfValue> _hb;
public:
	bool Insert(const K& data)
	{
		return _hb.Insert(data);
	}
};

void test_mymap()
{
	MyUnorderedMap<int, string> mmp;
	mmp.Insert(make_pair(1,"one"));
	mmp.Insert(make_pair(11, "two"));
	mmp.Insert(make_pair(256, "asd"));
	mmp.Insert(make_pair(12, "oasde"));
	mmp.Insert(make_pair(6, "onasd"));
	mmp.Insert(make_pair(3, "oasde"));
	MyUnorderedMap<int, string>::iterator it = mmp.begin();
	for (int i = 0; i < 5; ++i)
	{
		cout << it->first << "-->" << it->second << endl;
		++it;
	}
}

int main()
{
	test_mymap();
	system("pause");
	return 0;
}