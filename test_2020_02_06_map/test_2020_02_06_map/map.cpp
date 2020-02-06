#include<iostream>
using namespace std;
#include<string>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<functional>

#if 1

class Solution {
public:
	class Compare
	{
	public:
		bool operator()(const pair<string, int>& left, const pair<string, int>& right)const
		{
			if (left.second > right.second)
			{
				return true;
			}
			if (left.second == right.second)
			{
				if (left.first < right.first)
				{
					return true;
				}
			}
			return false;
		}
	};

	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> m;
		for (auto& e : words)
		{
			++m[e];
		}
		multiset<pair<string, int>, Compare> ms(m.begin(), m.end());
		vector<string> ans;
		for (auto& e : ms)
		{
			ans.push_back(e.first);
			if (--k == 0)
			{
				break;
			}
		}
		return ans;
	}
};
class Solution {
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> m;
		for (auto& e : words)
		{
			++m[e];
		}
		multimap<int, string, greater<int>> mp;
		for (auto& e : m)
		{
			mp.insert(make_pair(e.second, e.first));
		}
		vector<string> ans;
		multimap<int, string>::iterator it = mp.begin();
		for (it = mp.begin(); it != mp.end() && k; ++it, --k)
		{
			ans.push_back(it->second);
		}
		return ans;
	}
};
class Solution {
public:

	static bool Compare(const pair<string, int>& left, const pair<string, int>& right)
	{
		if (left.second > right.second)
		{
			return true;
		}
		if (left.second == right.second)
		{
			if (left.first < right.first)
			{
				return true;
			}
		}
		return false;
	}

	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> m;
		for (auto& e : words)
		{
			++m[e];
		}
		vector<pair<string, int>> ans;
		for (auto& e : m)
		{
			ans.push_back(e);
		}
		sort(ans.begin(), ans.end(), Compare);
		vector<string> last;
		for (int i = 0; i < k; ++i)
		{
			last.push_back(ans[i].first);
		}
		return last;
	}
};
#endif

int main()
{
	/*map<int, string> m;
	m.insert(pair<int, string>(2, "two"));
	m.insert(make_pair(1, "one"));
	m[3] = "three";
	for (auto& e : m)
	{
	cout << e.first << "-->" << e.second << endl;
	}
	auto ret = m.insert(make_pair(11, "222"));
	if (ret.second)
	{
	cout << "插入成功" << endl;
	}
	else
	{
	cout << "插入失败" << endl;
	}
	for (auto& e : m)
	{
	cout << e.first << "-->" << e.second << endl;
	}
	m.erase(1);
	if (0 == m.count(1))
	{
	cout << "1没了" << endl;
	}*/
	/*int array[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0, 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
	multiset<int> s(array, array + sizeof(array) / sizeof(array[0]));
	for (auto& e : s)
	{
	cout << e << endl;
	}*/
	/*vector<string> ans{ "ab", "ab", "cd", "ab", "cd" };
	Solution s;
	s.topKFrequent(ans, 2);
	multimap<pair<string, int>, greater<int>()>;*/
	vector<int> v;
	sort(v.begin(), v.end(), greater<int>());
	system("pause");
	return 0;
}