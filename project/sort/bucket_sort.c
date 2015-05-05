/************************************************************************************
 http://blog.csdn.net/houapple/article/details/6480100
 
 Ͱ���� (Bucket sort)����ν����������һ�������㷨��������ԭ���ǽ����зֵ�����������
 Ͱ���ÿ��Ͱ���ٸ��������п�����ʹ�ñ�������㷨�����Եݻط�ʽ����ʹ��Ͱ�������
 ���򣩡�Ͱ�����Ǹ볲�����һ�ֹ��ɽ������Ҫ������������ڵ���ֵ�Ǿ��ȷ����ʱ��Ͱ
 ����ʹ������ʱ�䣨����n��������Ͱ���򲢲��� �Ƚ����������ܵ� O(n log n) ���޵�Ӱ�졣

 ����Ҫ�Դ�СΪ[1..1000]��Χ�ڵ�n������A[1..n]���򣬿��԰�Ͱ��Ϊ��СΪ10�ķ�Χ�������
 �ԣ��輯��B[1]�洢[1..10]������������B[2]�洢(10..20]����������������B[i]�洢((i-1)*10, 
 i*10]��������i = 1,2,..100���ܹ���100��Ͱ��Ȼ���A[1..n]��ͷ��βɨ��һ�飬��ÿ��A[i]��
 ���Ӧ��ͰB[j]�С� Ȼ���ٶ���100��Ͱ��ÿ��Ͱ�������������ʱ����ð�ݣ�ѡ���������ţ�
 һ����˵�κ����򷨶����ԡ�����������ÿ��Ͱ��������֣���ÿ��Ͱ�е����ִ�С���������
 �����͵õ����������ź����һ�������ˡ� 
 
 ������n�����֣���m��Ͱ�����������ƽ���ֲ��ģ���ÿ��Ͱ����ƽ����n/m�����֡������ÿ��
 Ͱ�е����ֲ��ÿ���������ô�����㷨�ĸ��Ӷ���O(n+m*n/m*log(n/m))=O(n+nlogn-nlogm)   
 ����ʽ��������m�ӽ�n��ʱ��Ͱ�����ӶȽӽ�O(n)����Ȼ�����ϸ��Ӷȵļ����ǻ��������n��
 ������ƽ���ֲ��������ġ���������Ǻ�ǿ�ģ�ʵ��Ӧ����Ч����û����ô�á�������е�����
 ������ͬһ��Ͱ�У��Ǿ��˻���һ��������ˡ�
*/

#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
  
extern void sort_quick(int a[], int p, int q);/* not necessary */  
  
struct barrel {   
    int node[10];   
    int count;/* the num of node */  
};   
  
void bucket_sort(int data[], int size)   
{   
    int max, min, num, pos;   
    int i, j, k;   
    struct barrel *pBarrel;   
  
    max = min = data[0];   
    for (i = 1; i < size; i++) {   
        if (data[i] > max) {   
            max = data[i];   
        } else if (data[i] < min) {   
            min = data[i];   
        }   
    }   
    num = (max - min + 1) / 10 + 1;
    pBarrel = (struct barrel*)malloc(sizeof(struct barrel) * num);
    memset(pBarrel, 0, sizeof(struct barrel) * num);   
  
    /* put data[i] into barrel which it belong to */  
    for (i = 0; i < size; i++) {   
        k = (data[i] - min + 1) / 10;/* calculate the index of data[i] in barrel */  
        (pBarrel + k)->node[(pBarrel + k)->count] = data[i];   
        (pBarrel + k)->count++;   
    }   
       
    pos = 0;   
    for (i = 0; i < num; i++) {   
        sort_quick((pBarrel+i)->node, 0, (pBarrel+i)->count);/* sort node in every barrel */  
  
        for (j = 0; j < (pBarrel+i)->count; j++) {   
            data[pos++] = (pBarrel+i)->node[j];   
        }   
    }   
    free(pBarrel);   
}   
  
int main_t()   
{   
    int data[] = {78, 17, 39, 26, 72, 94, 21, 12, 23, 91}, i;   
    int size = sizeof(data) / sizeof(int);   
    bucket_sort(data, size);   
  
    for (i = 0; i < size; i++)   
        printf("%d ", data[i]); 

	return 0;
}  

