#include<iostream>
using namespace std;
#include<string>
class Solution {
public:
	bool canConstruct(string ransomNote, string magazine) {
		int size1 = ransomNote.size();
		int size2 = magazine.size();
		if (size2 < size1)
		{
			return false;
		}
		for (int i = 0; i < size1; ++i)
		{
			int flag = 0;
			for (int j = 0; j < size2; ++j)
			{
				if (magazine[j] != '0' && magazine[j] == ransomNote[i])
				{
					magazine[j] = '0';
					flag = 1;
					break;
				}
			}
			if (0 == flag)
			{
				return false;
			}
		}
		return true;
	}
};


class Solution {
public:
	bool canConstruct(string ransomNote, string magazine) {
		int arr[26] = { 0 };
		int size1 = ransomNote.size();
		int size2 = magazine.size();
		if (size2 < size1)
		{
			return false;
		}
		for (int i = 0; i < size2; ++i)
		{
			++arr[magazine[i] - 97];
		}
		for (int i = 0; i < size1; ++i)
		{
			if (arr[ransomNote[i] - 97] > 0)
			{
				--arr[ransomNote[i] - 97];
			}
			else
			{
				return false;
			}
		}
		return true;
	}
};



class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0)
		{
			return false;
		}
		int count = 0;
		int tmp = x;
		while (tmp)
		{
			tmp /= 10;
			++count;
		}
		string str;
		str.resize(count);
		tmp = x;
		for (int i = count - 1; i >= 0; --i)
		{
			str[i] = tmp % 10;
			tmp /= 10;
		}
		int left = 0;
		int right = count - 1;
		while (left < right)
		{
			if (str[left] != str[right])
			{
				return false;
			}
			++left;
			--right;
		}
		return true;
	}
};


class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0)
		{
			return false;
		}
		int tmp = x;
		int y = 0;
		while (tmp)
		{
			if (y > INT_MAX / 10)
			{
				return false;
			}
			y = y * 10 + tmp % 10;
			tmp /= 10;
		}
		if (x == y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};


class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0 || (0 == x % 10 && x != 0))
		{
			return false;
		}
		int y = 0;
		while (x > y)
		{
			y = y * 10 + x % 10;
			x /= 10;
		}
		return x == y || x == y / 10;
	}
};