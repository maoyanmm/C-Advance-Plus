class Solution {
public:
	int multiply(int A, int B) {
		if (B > 0)
		{
			return A + multiply(A, --B);
		}
		else
		{
			return 0;
		}
	}
};

class Solution {
public:

	bool match_symbol(const char* s, const char* p)
	{
		if (*s == '\0' && *p == '\0')
		{
			return true;
		}
		if (*s == '\0' && *p == '*')
		{
			return match_symbol(s, p + 1);
		}
		if (*s == '\0' || *p == '\0')
		{
			return false;
		}
		if (*s == *p || *p == '?')
		{
			return match_symbol(s + 1, p + 1);
		}
		else if (*p == '*')
		{
			return match_symbol(s, p + 1) || match_symbol(s + 1, p) || match_symbol(s + 1, p + 1);
		}
		else
		{
			return false;
		}
	}

	bool isMatch(string s, string p) {
		return match_symbol(s.c_str(), p.c_str());
	}
};

class Solution {
public:
	bool isMatch(string s, string p) {
		int i = 0, j = 0, istar = -1, jstar = -1, s_size = s.size(), p_size = p.size();
		while (i < s_size)
		{
			if (i < s_size && j < p_size && (s[i] == p[j] || p[j] == '?'))
			{
				++i;
				++j;
			}
			else if (j < p_size && p[j] == '*')
			{
				istar = i;
				jstar = j;
				++j;
			}
			else if (jstar > -1)
			{
				i = ++istar;
				j = jstar + 1;
			}
			else
			{
				return false;
			}
		}
		while (j < p_size)
		{
			if (p[j] != '*')
			{
				return false;
			}
			++j;
		}
		return true;
	}
};


class Solution {
public:
	bool isMatch(string s, string p) {
		int s_size = s.size();
		int p_size = p.size();
		vector<vector<bool> > dp(p_size + 1, vector<bool>(s_size + 1, false));
		dp[0][0] = true;
		for (int i = 1; i <= p_size; ++i)
		{
			if (p[i - 1] == '*')
			{
				dp[i][0] = true;
			}
			else
			{
				break;
			}
		}
		int i = 0;
		int j = 0;
		for (i = 1; i <= p_size; ++i)
		{
			for (j = 1; j <= s_size; ++j)
			{
				if ((s[j - 1] == p[i - 1] || p[i - 1] == '?') && (dp[i - 1][j - 1]))
				{
					dp[i][j] = true;
				}
				else if (p[i - 1] == '*' && (dp[i - 1][j - 1] || dp[i][j - 1] || dp[i - 1][j]))
				{
					dp[i][j] = true;
				}
			}
		}
		return dp[p_size][s_size];
	}
};