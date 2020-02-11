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

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> mp1;
        vector<int> ans;
        for(const auto& e:nums1)
        {
            ++mp1[e];
        }
        for(const auto& e:nums2)
        {
            if(--mp1[e] >= 0)
            {
                ans.push_back(e);
            }
        }
        return ans;
    }
};

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> mp;
        for(const auto& e:nums)
        {
            ++mp[e];
            if(mp[e] >= 2)
            {
                return true;
            }
        }
        return false;
    }
};

class Solution {
public:
    vector<string> uncommonFromSentences(string A, string B) {
        unordered_map<string,int> mp;
        vector<string> ans;
        int left = 0;
        int right = 0;
        while(right < A.size())
        {
            if(A[right] == ' ')
            {
                ++mp[A.substr(left,right-left)];
                left = ++right;
            }
            else
            {
                ++right;
            }
        }
        ++mp[A.substr(left,right-left)];
        left = 0;
        right = 0;
        while(right < B.size())
        {
            if(B[right] == ' ')
            {
                ++mp[B.substr(left,right-left)];
                left = ++right;
            }
            else
            {
                ++right;
            }
        }
        ++mp[B.substr(left,right-left)];
        for(const auto& e:mp)
        {
            if(e.second == 1)
            {
                ans.push_back(e.first);
            }
        }
        return ans;
    }
};
