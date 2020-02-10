class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> s1;
		unordered_set<int> s2;
		vector<int> ans;
		for (const auto& e : nums1)
		{
			s1.insert(e);
		}
		for (const auto& e : nums2)
		{
			s2.insert(e);
		}
		for (const auto& e : s2)
		{
			if (s1.count(e))
			{
				ans.push_back(e);
			}
		}
		return ans;
	}
};

class Solution {
public:
	int repeatedNTimes(vector<int>& A) {
		unordered_map<int, int> mp;
		int N = A.size() / 2;
		int ans = 0;
		for (const auto& e : A)
		{
			++mp[e];
			if (mp[e] == N)
			{
				ans = e;
				break;
			}
		}
		return ans;
	}
};