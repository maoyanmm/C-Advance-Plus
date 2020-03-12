class Solution {
public:
	vector<string> mapString = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	void dfs(string digits, vector<string>& ans, string sub, int depth)
	{
		if (depth == digits.size())
		{
			if (!sub.empty())
			{
				ans.push_back(sub);
			}
			return;
		}
		int index = digits[depth] - '0';
		string str = mapString[index];
		for (int i = 0; i < str.size(); ++i)
		{
			dfs(digits, ans, sub + str[i], depth + 1);
		}
	}

	vector<string> letterCombinations(string digits) {
		vector<string> ans;
		dfs(digits, ans, "", 0);
		return ans;
	}

};

class Solution {
public:
	vector<int> hours = { 8, 4, 2, 1 };
	vector<int> minutes = { 32, 16, 8, 4, 2, 1 };
	void dfs(int depth, int num, vector<pair<int, int>>& ret, pair<int, int> nowTime, vector<bool> use_hours, vector<bool> use_minutes)
	{
		if (depth == num)
		{
			ret.push_back(nowTime);
			return;
		}
		for (int i = 0; i < hours.size(); ++i)
		{
			pair<int, int> tmpTime = nowTime;
			tmpTime.first += hours[i];
			if (!use_hours[i] && tmpTime.first < 12)
			{
				use_hours[i] = true;
				dfs(depth + 1, num, ret, tmpTime, use_hours, use_minutes);
			}
		}
		for (int i = 0; i < minutes.size(); ++i)
		{
			pair<int, int> tmpTime = nowTime;
			tmpTime.second += minutes[i];
			if (!use_minutes[i] && tmpTime.second < 60)
			{
				use_minutes[i] = true;
				dfs(depth + 1, num, ret, tmpTime, use_hours, use_minutes);
			}
		}
	}
	string int_to_string(int num)
	{
		string ans;
		if (num == 0)
		{
			return "0";
		}
		while (num)
		{
			ans += (num % 10) + '0';
			num /= 10;
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
	vector<string> readBinaryWatch(int num) {
		vector<string> ans;
		vector<pair<int, int>> ret;
		vector<bool> use_hours(hours.size(), false);
		vector<bool> use_minutes(minutes.size(), false);
		pair<int, int> pp(0, 0);
		dfs(0, num, ret, pp, use_hours, use_minutes);
		for (auto& time : ret)
		{
			string timeHour = int_to_string(time.first);
			string timeMinute = int_to_string(time.second);
			if (timeMinute.size() == 1)
			{
				timeMinute.insert(timeMinute.begin(), '0');
			}
			string lastTime = timeHour + ":" + timeMinute;
			ans.push_back(lastTime);
		}
		return ans;
	}
};



