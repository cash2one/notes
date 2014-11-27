
/*******************************************************************************
 Given a string s, partition s such that every substring of the partition is a 
 palindrome.Return all possible palindrome partitioning of s.
 
 For example, given s = ��aab�� , Return
 [
   ["aa","b"],
   ["a","a","b"]
 ]
 
 class Solution {
 public:
    vector<vector<string>> partition(string s) {
        
    }
 };
 *******************************************************************************/



/*
 LeetCode, Palindrome Partitioning
 ʱ�临�Ӷ� O(2^n) ���ռ临�Ӷ� O(n)*/

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
    vector< vector<string> > partition(string s) 
	{
        vector< vector<string> > result;
        vector<string> path; /* һ�� partition ����*/
        dfs(s, path, result, 0, 1);
        return result;
    }
	
	bool isPalindrome(const string &s, int start, int end) 
	{
		while (start < end && s[start] == s[end]) 
		{
			++start;
			--end;
		}
		return start >= end;
	}
	
/* s[0, prev-1] ֮���Ѿ�������֤�ǻ��Ĵ�
 prev ��ʾ s[prev-1] �� s[prev] ֮��Ŀ�϶λ�ã� start ͬ��
 
 partition 1:aaabbb
 aaa,bbb,
 aaa,bb,b,
 aaa,b,bb,
 aaa,b,b,b,
 aa,a,bbb,
 aa,a,bb,b,
 aa,a,b,bb,
 aa,a,b,b,b,
 a,aa,bbb,
 a,aa,bb,b,
 a,aa,b,bb,
 a,aa,b,b,b,
 a,a,a,bbb,
 a,a,a,bb,b,
 a,a,a,b,bb,
 a,a,a,b,b,b,
 partition 1:aabb
 aa,bb,
 aa,b,b,
 a,a,bb,
 a,a,b,b,
 */ 
void dfs(string &s, vector<string>&path,vector< vector<string> > &result, size_t prev, size_t start) 
{
    if (start == s.size()) 
	{
        if (isPalindrome(s, prev, start - 1)) 
		{
            path.push_back(s.substr(prev, start - prev));
            result.push_back(path);
            path.pop_back();
        }
		
        return;
    }

    dfs(s, path, result, prev, start + 1);/*����*/
	
    if (isPalindrome(s, prev, start - 1)) 
	{
	    path.push_back(s.substr(prev, start - prev));
        dfs(s, path, result, start, start + 1);
        path.pop_back();
    }
}


};


//LeetCode, Palindrome Partitioning
// ʱ�临�Ӷ� O(2^n) ���ռ临�Ӷ� O(n)
class Solution2 
{
public:
vector< vector<string> > partition(string s) 
{
    vector< vector<string> > result;
    vector<string> path;
    DFS(s, path, result, 0);
    return result;
}
	
bool isPalindrome(const string &s, int start, int end) 
{
    while (start < end && s[start] == s[end]) 
	{
        ++start;
        --end;
    }
	
    return start >= end;
}

/* ���������� s[start] ��ͷ�� partition ���� 
 partition 2:aaabbb
 a,a,a,b,b,b,
 a,a,a,b,bb,
 a,a,a,bb,b,
 a,a,a,bbb,
 a,aa,b,b,b,
 a,aa,b,bb,
 a,aa,bb,b,
 a,aa,bbb,
 aa,a,b,b,b,
 aa,a,b,bb,
 aa,a,bb,b,
 aa,a,bbb,
 aaa,b,b,b,
 aaa,b,bb,
 aaa,bb,b,
 aaa,bbb,
 partition 2:aabb  ---->�Դ�Ϊ��˵����ִ�в���
 a,a,b,b,
 a,a,bb,
 aa,b,b,
 aa,bb,
 ------------------
 a�ǣ���abb    ������ a,xxx
 aa�ǣ���bb    ������aa,xxx
 aab���� pass
 aabb���� pass
 ------------------
   ��abb
   a�ǣ���bb    ������a,a,xx
   ab���� pass
   abb���� pass
 --------------------
 */
void DFS(string &s, vector<string>& path,vector< vector<string> > &result, int start) 
{
    if (start == s.size()) 
	{
        result.push_back(path);
        return;
    }
	
    for (int i = start; i < s.size(); i++) 
	{
        if (isPalindrome(s, start, i)) 
	    { 
            path.push_back(s.substr(start, i - start + 1));
            DFS(s, path, result, i + 1); 
            path.pop_back(); 
        }
    }
}

};



/******************************************************************************/
void pp_test2(string s)
{
    Solution2 test;	
	vector< vector<string> > result;
    vector<string> str;
	
    cout << "partition 2:" << s << endl;
	result = test.partition(s);

    for (unsigned int i = 0; i < result.size( ); i++)
    {
        str = result[i];
		
        for (unsigned int j = 0; j < str.size( ); j++)
            cout << str[j] << ",";
		
		cout << endl;
    }

	cout << endl;

}

void pp_test(string s)
{
    Solution test;	
	vector< vector<string> > result;
    vector<string> str;
	
    cout << "partition 1:" << s << endl;
	result = test.partition(s);

    for (unsigned int i = 0; i < result.size( ); i++)
    {
        str = result[i];
		
        for (unsigned int j = 0; j < str.size( ); j++)
            cout << str[j] << ",";
		
		cout << endl;
    }

	cout << endl;

	
	pp_test2(s);
}

int main()
{
	pp_test("aab");
	pp_test("abccba");	
	pp_test("aaabbb");
	
	pp_test("aabb");

	return 0;
}
