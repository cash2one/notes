/*******************************************************************************
                      Valid Parentheses(Easy)
 *******************************************************************************
 Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
 determine if the input string is valid.
 
 The brackets must close in the correct order, "()" and "()[]{}" are all valid 
 but "(]" and "([)]" are not.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 bool isValid(string s) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 �ַ���S�е�ÿһ���ַ�C
 if C�������� ( ([{ ) 
     ��ѹ��ջstack�С�
 if C�������ţ��ж�stack�ǲ��ǿյ�
     ����˵��û�������ţ�ֱ�ӷ���not valid��
     �ǿվ�ȡ��ջ�����ַ����Աȣ�
         �����ƥ��ģ��͵���ջ�����ַ�������ȡS�е���һ���ַ���
         �����ƥ�䣬˵������valid�ģ�ֱ�ӷ��ء�

 ��������һ���ַ���S�������ʱstack���ǿյģ���ʱ˵��S����valid�ģ���ΪֻҪ
 valid��һ��ȫ�����Եõ�ƥ��ʹ�����ŵ�����
 ******************************************************************************/
#include <iostream>
#include <string>
#include <stack>
 using namespace std;
 
 class Solution {
 public:
 bool isValid(string s)
 {
	 string left = "([{";
	 string right = ")]}";
	 
	 stack<char> stk;
	 
	 for (auto c : s) {
		 if (left.find(c) != string::npos) {
			 stk.push (c);
		 } else {
			 if (stk.empty () || stk.top () != left[right.find(c)])
				 return false;
			 else
				 stk.pop ();
		 }
	 }
	 
	 return stk.empty();
 }
 
 
 };

 int vaild_parentheses_test(string s,int expect)
 {
	 Solution solu;
 
	 cout << s << " : " << solu.isValid(s) << " (" << expect << ")" << endl;
 
	 return 0;
 }
 
 int main()
 {
	 vaild_parentheses_test("()[]",1);
	 vaild_parentheses_test("()[{]",0);
	 vaild_parentheses_test("(",0); 
	 vaild_parentheses_test("([{}])",1);
	 return 0;
 }
	 

