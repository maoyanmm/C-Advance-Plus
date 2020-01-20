#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
class Solution {
public:
	bool isPalindrome(string s) {
		int left = 0;
		int right = s.size() - 1;
		while (left < right)
		{
			while (left < right && !isalpha(s[left]) && !isdigit(s[left]))
			{
				++left;
			}
			while (left < right && !isalpha(s[right]) && !isdigit(s[right]))
			{
				--right;
			}
			if (left >= right)
			{
				break;
			}
			if (isalpha(s[left]) && isalpha(s[right]))
			{
				if (!((s[left] == s[right]) || (s[left] + 32 == s[right]) || (s[left] == s[right] + 32)))
				{
					return false;
				}
			}
			else if (isdigit(s[left]) && isdigit(s[right]))
			{
				if (s[left] != s[right])
				{
					return false;
				}
			}
			else
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
	int compress(vector<char>& chars) {
		int size = chars.size();
		int index = 0;
		int count = 1;
		for (int i = 1; i < size; ++i)
		{
			if (chars[i] == chars[i - 1])
			{
				++count;
			}
			else
			{
				chars[index++] = chars[i - 1];
				if (count > 1)
				{
					string str = to_string(count);
					for (int j = 0; j < str.size(); ++j)
					{
						chars[index++] = str[j];
					}
				}
				count = 1;
			}
		}
		chars[index++] = chars[size - 1];
		if (count > 1)
		{
			string str = to_string(count);
			for (int j = 0; j < str.size(); ++j)
			{
				chars[index++] = str[j];
			}
		}
		return index;
	}
};