/*******************************************************************************
                 Median of Two Sorted Arrays (Hard)
 *******************************************************************************
 There are two sorted arrays A and B of size m and n respectively. Find the median 
 of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 double findMedianSortedArrays(int A[], int m, int B[], int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 ��Ŀ�������ģ����������Ѿ�����õ����飨����Ϊ�գ����ҵ���������Ԫ���е�k���Ԫ
 �ء�����һ�ָ��Ӿ������ʽ�ǣ��ҵ�����Ԫ�ص���λ������ƪ��������ֻ���۸���һ����
 �����⣺����ҵ����������е�k���Ԫ�أ��������������õ������������λ������Ŀ��
 Leetcode��4�� Median of Two Sorted Arrays
 
 ����1���������������ܹ���n��Ԫ�أ���ô��Ȼ��������O(n)ʱ���O(n)�ռ�ķ�������
 merge sort��˼·��������õ�����ȡ���±�Ϊk-1��Ԫ�ؾ���������Ҫ�Ĵ𰸡������
 ���Ƚ������뵽��������û�и��õķ����أ�

 ����2�����ǿ��Է��֣����������ǲ���Ҫ��������ô���ӵĲ����ģ���Ϊ���ǽ�����Ҫ
 ��k���Ԫ�ء����ǿ�����һ������������¼��ǰ�Ѿ��ҵ���m���Ԫ���ˡ�ͬʱ����ʹ����
 ��ָ��pA��pB���ֱ�ָ��A��B����ĵ�һ��Ԫ�ء�ʹ��������merge sort��ԭ���������
 A��ǰԪ��С����ôpA++��ͬʱm++���������B��ǰԪ��С����ôpB++��ͬʱm++�����յ�m
 ����k��ʱ�򣬾͵õ������ǵĴ𰸡���O(k)ʱ�䣬O(1)�ռ䡣
 ���ǣ���k�ܽӽ���n��ʱ������������Ǻܷ�ʱ��ġ���Ȼ�����ǿ����ж�һ�£����k
 ��n/2��Ļ������ǿ��Դ�����Ԫ�ؿ�ʼ�ҡ������������Ҫ������Ԫ�ص���λ���أ�ʱ
 �仹��O(n/2)=O(n)�ġ���û�и��õķ����أ�
 ���ǿ��Կ��Ǵ�k���֡��������ÿ�ζ��ܹ��޳�һ��һ���ڵ�k��Ԫ��֮ǰ��Ԫ�أ���ô��
 ����Ҫ����k�Ρ��������ÿ�����Ƕ��޳�һ���أ����������������ڶ��ֵ�˼�룬���ǿ���
 �������ǣ�
 
 Assume that the number of elements in A and B are both larger than k/2, and if 
 we compare the k/2-th smallest element in A(i.e. A[k/2-1]) and the k-th smallest 
 element in B(i.e. B[k/2 - 1]), there are three results:(Becasue k can be odd or 
 even number, so we assume k is even number here for simplicy. The following is 
 also true when k is an odd number.)
     A[k/2-1] = B[k/2-1]
     A[k/2-1] > B[k/2-1]
     A[k/2-1] < B[k/2-1]
     
 if A[k/2-1] < B[k/2-1], that means all the elements from A[0] to A[k/2-1](i.e. 
 the k/2 smallest elements in A) are in the range of k smallest elements in the 
 union of A and B. Or, in the other word, A[k/2 - 1] can never be larger than the 
 k-th smalleset element in the union of A and B.
 
  Why?
  We can use a proof by contradiction. Since A[k/2 - 1] is larger than the k-th 
  smallest element in the union of A and B, then we assume it is the (k+1)-th 
  smallest one. Since it is smaller than B[k/2 - 1], then B[k/2 - 1] should be 
  at least the (k+2)-th smallest one. So there are at most (k/2-1) elements 
  smaller than A[k/2-1] in A, and at most (k/2 - 1) elements smaller than 
  A[k/2-1] in B.So the total number is k/2+k/2-2, which, no matter when k is odd 
  or even, is surly smaller than k(since A[k/2-1] is the (k+1)-th smallest element). 
  So A[k/2-1] can never larger than the k-th smallest element in the union of A 
  and B if A[k/2-1]<B[k/2-1];
  Since there is such an important conclusion, we can safely drop the first k/2 
  element in A, which are definitaly smaller than k-th element in the union of 
  A and B. This is also true for the A[k/2-1] > B[k/2-1] condition, which we 
  should drop the elements in B.
  When A[k/2-1] = B[k/2-1], then we have found the k-th smallest element, that 
  is the equal element, we can call it m. There are each (k/2-1) numbers smaller 
  than m in A and B, so m must be the k-th smallest number. So we can call a 
  function recursively, when A[k/2-1] < B[k/2-1], we drop the elements in A, 
  else we drop the elements in B.
 
  We should also consider the edge case, that is, when should we stop?
  1. When A or B is empty, we return B[k-1]( or A[k-1]), respectively;
  2. When k is 1(when A and B are both not empty), we return the smaller one of A[0] and B[0]
  3. When A[k/2-1] = B[k/2-1], we should return one of them
 
  In the code, we check if m is larger than n to garentee that the we always 
  know the smaller array, for coding simplicy.


 ����
 ����һ���ǳ�������⡣�����ͨ�õ���ʽ�ǣ����������Ѿ�����õ����飬�ҵ�������
 ��Ԫ���е� k ���Ԫ�ء�O(m + n) �Ľⷨ�Ƚ�ֱ�ۣ�ֱ��merge�������飬Ȼ�����k��
 ��Ԫ�ء��������ǽ�����Ҫ�� k ���Ԫ�أ��ǲ���Ҫ��������ô���ӵĲ����ġ�������
 һ������������¼��ǰ�Ѿ��ҵ��� m ���Ԫ���ˡ�ͬʱ����ʹ������ָ�� pA �� pB����
 ��ָ�� A �� B ����ĵ�һ��Ԫ�أ�ʹ��������merge sort��ԭ���������A��ǰԪ��С��
 ��ô pA++��ͬʱ m++���������B��ǰԪ��С����ô pB++��ͬʱ m++�����յ�m����k ��
 ʱ�򣬾͵õ������ǵĴ𰸣�O(k)ʱ�䣬O(1) �ռ䡣���ǣ��� k �ܽӽ� m + n��ʱ��
 �����������O(m + n) �ġ�
 
 ��û�и��õķ����أ����ǿ��Կ��Ǵ� k ���֡��������ÿ�ζ��ܹ�ɾ��һ��һ���ڵ� k 
 ��Ԫ��֮ǰ��Ԫ�أ���ô������Ҫ���� k �Ρ��������ÿ�����Ƕ�ɾ��һ���أ����� A 
 �� B ��������ģ�����Ӧ�ó���������������Ϣ�������ڶ��ֲ��ң�Ҳ�ǳ��������
 �����򡱡�

 ���� A �� B ��Ԫ�ظ��������� k/2�����ǽ� A �ĵ� k/2 ��Ԫ�أ��� A[k/2-1]���� B 
 �ĵ� k/2��Ԫ�أ��� B[k/2-1]�����бȽϣ����������������Ϊ�˼������ȼ���k Ϊż
 �������õ��Ľ��۶���k ������Ҳ�ǳ����ģ���
 1 A[k/2-1] == B[k/2-1]
 2 A[k/2-1] > B[k/2-1]
 3 A[k/2-1] < B[k/2-1]
 ��� A[k/2-1] < B[k/2-1]����ζ�� A[0] �� A[k/2-1 �Ŀ϶��� A �� B �� top k Ԫ��
 �ķ�Χ�ڣ����仰˵��A[k/2-1]�����ܴ��� A �� B �ĵ�k ��Ԫ�ء���������֤����
 ��ˣ����ǿ��Է��ĵ�ɾ�� A ������� k/2 ��Ԫ�ء�ͬ���� A[k/2-1] > B[k/2-1] 
 ʱ������ɾ�� B����� k/2 ��Ԫ�ء�
 �� A[k/2-1] == B[k/2-1] ʱ��˵���ҵ��˵� k ���Ԫ�أ�ֱ�ӷ��� A[k/2-1] �� B[k/2-1]
 ���ɡ�
 ��ˣ����ǿ���дһ���ݹ麯������ô����ʲôʱ��Ӧ����ֹ�أ�
 1 �� A �� B�ǿ�ʱ��ֱ�ӷ��� B[k-1]�� A[k-1]��
 2 �� k=1�ǣ����� min(A[0], B[0])��
 3 �� A[k/2-1] == B[k/2-1] ʱ������ A[k/2-1] �� B[k/2-1]


 ******************************************************************************/

#define	min(a,b)	((a) < (b) ? (a) : (b))
   
 class Solution	
 {  
 public:
 	
 double findKth(int a[], int m, int b[], int n, int k)	
 {  
 	if (m > n)//always assume that m is equal or smaller than n
 		return findKth(b, n, a, m, k);
	
 	if (m == 0)  
 		return b[k - 1];
	
 	if (k == 1)  
 		return min(a[0], b[0]);
	
 	//divide k into two parts  
 	int pa = min(k/2,m), pb = k - pa;  
	
 	if (a[pa - 1] < b[pb - 1])	
 		return findKth(a + pa, m - pa, b, n, k - pa);  
 	else if (a[pa - 1] > b[pb - 1])  
 		return findKth(a, m, b + pb, n - pb, k - pb);  
 	else  
 		return a[pa - 1];  
 }  	

double findMedianSortedArrays(int A[], int m, int B[], int n)  
{  
    int total = m + n;
	
    if (total & 0x1)
        return findKth(A, m, B, n, total / 2 + 1);	
    else  
        return (findKth(A, m, B, n, total / 2) + findKth(A, m, B, n, total / 2 + 1)) / 2;	
}



};	

