/*******************************************************************************
                         Unique Paths(Medium) 
 *******************************************************************************
 A robot is located at the top-left corner of a m x n grid (marked 'Start' in the 
 diagram below).
 
 The robot can only move either down or right at any point in time. The robot is 
 trying to reach 
 the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 
 How many possible unique paths are there?
 
 
 Above is a 3 x 7 grid. How many possible unique paths are there?
 
 Note: m and n will be at most 100.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int uniquePaths(int m, int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;
 
class Solution {
public:
int uniquePaths(int m, int n) {

}

/* timeout */
int uniquePaths2(int m, int n) {
    if (m < 1 || n < 1) return 0;
    if (m == 1 && n == 1) return 1;
    return uniquePaths2(m - 1, n) + uniquePaths2(m, n - 1);
}

int uniquePaths3(int m, int n) {
    vector<vector<int> > v(m, vector<int>(n, 1));
	
    for(int i=1; i<m; ++i){
        for(int j=1; j<n; ++j){
            v[i][j] = v[i-1][j] + v[i][j-1];
        }
    }
	
    return v[m-1][n-1];
}



/*
 ��״̬Ϊ f[i][j]����ʾ����� (1; 1) ���� (i; j) ��·����������״̬ת�Ʒ���Ϊ��
 f[i][j]=f[i-1][j]+f[i][j-1]
 
 ��ߵ� f[j]����ʾ���º�� f[j]���빫ʽ�е� f[i[[j] ��Ӧ
 �ұߵ� f[j]����ʾ�ϵ� f[j]���빫ʽ�е� f[i-1][j] ��Ӧ
*/
int uniquePaths4(int m, int n) {
	vector<int> f(n,0);
	f[0] = 1;
	
	for (int i = 0; i < m; i++) {
	    for (int j = 1; j < n; j++) {
            f[j] = f[j - 1] + f[j];
	    }
    }
	
    return f[n - 1];
}




};


/*---------------------------------------------------------------------------------*/

int main()
{
   Solution solu;

   cout << "unique paths: " << solu.uniquePaths3(1,1) << endl;  
   cout << "unique paths: " << solu.uniquePaths3(2,2) << endl;
   cout << "unique paths: " << solu.uniquePaths3(3,3) << endl;

   return 0;
}

