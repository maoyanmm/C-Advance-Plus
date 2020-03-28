class Solution {
public:
	set<string> ans;
	void dfs(string& s, int index, string tmp_word)
	{
		tmp_word += s[index];
		if (tmp_word.size() == s.size())
		{
			ans.insert(tmp_word);
			return;
		}
		char tmp = s[index];
		s[index] = '0';
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] != '0')
			{
				dfs(s, i, tmp_word);
			}
		}
		s[index] = tmp;
	}
	vector<string> permutation(string s) {
		for (int i = 0; i < s.size(); ++i)
		{
			dfs(s, i, "");
		}
		vector<string> result(ans.begin(), ans.end());
		return result;
	}
};
