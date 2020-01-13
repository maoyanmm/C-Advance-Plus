class Solution {
public:
	vector<int> sortedSquares(vector<int>& A) {
		for (int i = 0; i < A.size(); ++i)
		{
			A[i] = pow(A[i], 2);
		}
		sort(A.begin(), A.end());
		return A;
	}
};


class Solution {
public:
	vector<int> sortedSquares(vector<int>& A) {
		int left = 0;
		int right = A.size() - 1;
		vector<int> result = A;
		int i = A.size() - 1;
		while (left <= right)
		{
			if (pow(A[left], 2) < pow(A[right], 2))
			{
				result[i--] = pow(A[right--], 2);
			}
			else
			{
				result[i--] = pow(A[left++], 2);
			}
		}
		return result;
	}
};


class Solution {
public:
	string reverseOnlyLetters(string S) {
		int left = 0;
		int right = S.size() - 1;
		while (left < right)
		{
			while (left < right && !(S[left] >= 'a' && S[left] <= 'z') && !(S[left] >= 'A' && S[left] <= 'Z'))
			{
				++left;
			}
			while (left < right && !(S[right] >= 'a' && S[right] <= 'z') && !(S[right] >= 'A' && S[right] <= 'Z'))
			{
				--right;
			}
			swap(S[left++], S[right--]);
			left;
		}
		return S;
	}
};


class Solution {
public:
	string reverseOnlyLetters(string S) {
		int size = S.size();
		stack<char> st;
		for (int i = 0; i < size; ++i)
		{
			if (isalpha(S[i]))
			{
				st.push(S[i]);
			}
		}
		for (int i = 0; i < size; ++i)
		{
			if (isalpha(S[i]))
			{
				S[i] = st.top();
				st.pop();
			}
		}
		return S;
	}
};