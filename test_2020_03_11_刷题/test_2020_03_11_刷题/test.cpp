

class Solution {
public:
	bool different_one(string str1, string str2)
	{
		int count = 0;
		for (size_t i = 0; i < str1.size(); ++i)
		{
			if (str1[i] != str2[i])
			{
				++count;
			}
		}
		if (count == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		wordList.push_back(beginWord);
		int size = wordList.size();
		vector<int> book(size, 0);
		int count = 1;
		size_t i = 0;
		bool flag = false;
		for (; i < size; ++i)
		{
			if (endWord == wordList[i])
			{
				flag = true;
				book[i] = 1;
				break;
			}
		}
		if (!flag)
		{
			return 0;
		}
		queue<int> q;
		q.push(i);
		while (!q.empty())
		{
			int qSize = q.size();
			for (i = 0; i < qSize; ++i)
			{
				string str1 = wordList[q.front()];
				q.pop();
				if (str1 == beginWord)
				{
					return count;
				}

				for (size_t j = 0; j < size; ++j)
				{
					if (book[j] == 0 && different_one(str1, wordList[j]))
					{
						q.push(j);
						book[j] = 1;
					}
				}
			}
			++count;
		}
		return 0;
	}
};


class Solution {
public:
	int openLock(vector<string>& deadends, string target) {
		queue<string> q;
		int step = 0;
		unordered_set<string> book;
		unordered_set<string> deadendsSet(deadends.begin(), deadends.end());
		if (deadendsSet.count("0000") > 0)
		{
			return -1;
		}
		q.push("0000");
		book.insert("0000");
		while (!q.empty())
		{
			int qSize = q.size();
			while (qSize--)
			{
				string subStr = q.front();
				q.pop();
				if (subStr == target)
				{
					return step;
				}
				for (int i = 0; i < 4; ++i)
				{
					string subStr1 = subStr;
					string subStr2 = subStr;
					subStr1[i] = subStr1[i] == '9' ? '0' : subStr1[i] + 1;
					subStr2[i] = subStr2[i] == '0' ? '9' : subStr2[i] - 1;
					if (deadendsSet.count(subStr1) == 0 && book.count(subStr1) == 0)
					{
						q.push(subStr1);
						book.insert(subStr1);
					}
					if (deadendsSet.count(subStr2) == 0 && book.count(subStr2) == 0)
					{
						q.push(subStr2);
						book.insert(subStr2);
					}
				}
			}
			++step;
		}
		return -1;
	}
};


class Solution {
public:
	class Compare
	{
	public:
		bool operator()(int left, int right)const
		{
			return left > right;
		}
	};
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> mp;
		for (const auto& e : words)
		{
			++mp[e];
		}
		multimap<int, string, Compare> mtp;
		for (const auto& e : mp)
		{
			mtp.insert(make_pair(e.second, e.first));
		}
		vector<string> ans;
		for (const auto& e : mtp)
		{
			if (k-- == 0)
			{
				break;
			}
			ans.push_back(e.second);
		}
		return ans;
	}
};