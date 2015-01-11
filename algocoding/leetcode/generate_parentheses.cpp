/*******************************************************************************
                        Generate Parentheses(Medium) 
 *******************************************************************************
 Given n pairs of parentheses, write a function to generate all combinations of 
 well-formed parentheses.
 
 For example, given n = 3, a solution set is:
 
 "((()))", "(()())", "(())()", "()(())", "()()()"

 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 vector<string> generateParenthesis(int n) {
		 
	 }
 };
 ************************************************************************************
                              algo
 ************************************************************************************
 �������ĸ������ǿ����������������ڲ��������������Ҫ�����кϷ����������д�ӡ������
 ���һ������Ϊ2n�ĺϷ����У���1��2n��λ�ö��������¹��������ŵĸ������ڵ��������ŵ�
 ���������ԣ����ǾͿ��԰����������ȥ��ӡ���ţ�������λ��k���ǻ�ʣ��left�������ź�right
 �������ţ�
 ���left>0�������ǿ���ֱ�Ӵ�ӡ�����ţ�����Υ������
 ���left>=right�������ǲ��ܴ�ӡ�����ţ���Ϊ��ӡ��Υ���Ϸ����еĹ��򣬷�����Դ�ӡ�����š�
 ���left��right��Ϊ�㣬��˵�������Ѿ����һ���Ϸ����У����Խ����ӡ������
 ͨ�����ѣ����ǿ��Ժܿ�ؽ�����⣬���n=2������Ľ�ռ����£�

 http://blog.csdn.net/yutianzuijin/article/details/13161721
 ***********************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /* abs */

using namespace std;
class Solution {
public:
vector<string> generateParenthesis(int n) {
	vector<string> result;
	string s;
    generate(n,n,s,result);
	return result;
}

void generate(int leftNum,int rightNum,string s,vector<string> &result)
{
    if(leftNum==0&&rightNum==0){
        result.push_back(s);
    }
    if(leftNum>0){
        generate(leftNum-1,rightNum,s+'(',result);
    }
    if(rightNum>0&&leftNum<rightNum){
        generate(leftNum,rightNum-1,s+')',result);
    }
}

};


/***********************************************************************************/

void generate_parenthesis_test(int n)
{
    Solution solu;
	vector<string> result;
	vector<string>::iterator it;
	result = solu.generateParenthesis(n);
    cout << "parenthesis: " << n << endl;
    for(it = result.begin(); it != result.end(); it++){
	    cout << *it << endl;
    }
}


int main()
{
	generate_parenthesis_test(0);
	generate_parenthesis_test(1);
	generate_parenthesis_test(2);
	generate_parenthesis_test(3);
	generate_parenthesis_test(4);
	generate_parenthesis_test(5);

	return 0;
}

