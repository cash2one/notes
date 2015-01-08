/*******************************************************************************
            Longest Substring Without Repeating Characters (Medium)
 *******************************************************************************
 Given a string, find the length of the longest substring without repeating characters. 
 For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
 which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int lengthOfLongestSubstring(string s) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 ��������ɨ�裬�������ظ���ĸʱ������һ���ظ���ĸ�� index+1����Ϊ�µ�������ʼλ�ã�
 ֱ�����һ����ĸ�����Ӷ��� O ( n )��
 ******************************************************************************/
#include <iostream>	 
#include <string>
using namespace std;


 class Solution {
 public:

int lengthOfLongestSubstring(string s) {
    int last[256];  /* ��¼�ַ��ϴγ��ֹ���λ�� */
    int start = 0; /* ��¼��ǰ�Ӵ�����ʼλ�� */
	int max_len = 0;
	
    fill(last, last + 256, -1);

    for (int i = 0; i < s.size(); i++) {
        if (last[s[i]] >= start) {
            max_len = max(i - start, max_len);
            start = last[s[i]] + 1;
        }
        last[s[i]] = i;
    }
	
    return max((int)s.size() - start, max_len); /* ���������һ�Σ�����"abcd" */    		 
}


};



int longest_substring_test(string s,int expect)
{
    Solution solu;

	cout << "longest len: " << solu.lengthOfLongestSubstring(s);
	cout << " (" << expect << ")" << endl;
}

int main()
{
	longest_substring_test("#$%^",4);
	longest_substring_test("abcd)(+~!a",9);

	return 0;
}

