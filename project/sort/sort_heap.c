/************************************************************************************
�����: ��һ������Ķѣ��������"��ȫ������"������"������ȫ������"��
�����ԣ����ڵ�ļ�ֵ���Ǳ��̶ֹ������ϵ���κ�һ���ӽڵ�ļ�ֵ����ÿ���ڵ������������
        ��������һ������ѡ�
����: �����ڵ�ļ�ֵ���Ǵ��ڻ�����κ�һ���ӽڵ�ļ�ֵʱΪ���ѡ� 
��С��: �����ڵ�ļ�ֵ����С�ڻ�����κ�һ���ӽڵ�ļ�ֵʱΪ��С�ѡ�

�����һ������������ʾ������洢������±����0����ô�±�Ϊi�Ľڵ���ӽڵ���2i + 1��
2i + 2���丸�ڵ���±���(i - 1)/2(ȡ����)��

����ͼ�������ѣ�

			  1 			       11
			/	\			/	\
		   2	     3		   9       10
		  / \	/ \ 	        / \	 / \
		 4	 5	6  7	      5	 6	7	8
		/ \ / \ 		     / \ / \
	   8  9 10 11	        1  2 3  4 

���������ѱ�������0��ʼ��������
λ��:  0   1   2   3   4   5   6   7   8   9   10   11
��ͼ:  1   2   3   4   5   6   7   8   9   10  11
��ͼ:  11  9   10  5   6   7   8   1   2   3   4

 ==== ������ ====
 1 ���Ӷ� O(nlgn)
 2 ԭ�������㷨
*/

/*
  @array: �����׵�ַ
  @i    : ����Ԫ����������0��ʼ����
  @max  : maxС�ڵ�������ĸ���
  ����  : array[i]������������������������,���ô˺�������array[i]Ϊ������Ҳ������������*/
void adjust_heap(int array[], int i, int max)
{
    int left,right,largest,temp;

	left  = 2*i + 1;
	right = 2*i + 2;

	if(left < max && array[left] > array[i])
	{
	    largest = left;
	}
	else
	{
	    largest = i;
	}

	if(right < max && array[right] > array[largest])
	    largest = right;

	if(i != largest)
	{
	    temp = array[i];
		array[i] = array[largest];
		array[largest] = temp;

		adjust_heap(array,largest,max);
	}
}

/*@size: ����Ԫ�صĸ��� ���ڵ���2
  ���� : ��������
  ʵ�� : */
void build_heap(int array[],int size)
{
    int i;

	for(i = size/2 - 1; i >= 0; --i)
		adjust_heap(array,i,size);
}

/*������(��С����)
  @size: ����Ԫ�صĸ��� ���ڵ���2
  ���� : 1 ���������������Ͻ������ѣ���ʱ����Ԫ����array[0]��
         2 ����array[0]��array[size-1]��ֵ��
         3 ��array[0]��array[size-2]�Ͻ������ѣ���ʱ����Ԫ����array[0]��
         4 ����array[0]��array[size-2]��ֵ��
         5 ��array[0]��array[size-3]�Ͻ������ѣ���ʱ����Ԫ����array[0]��
         6 ...*/
void sort_heap(int array[],int size)
{
    int i,temp;
	
    build_heap(array,size); /*�ѽ��������ĸ���array[0]�ǽ�ֵ���Ľڵ㡣*/

	for(i = size - 1; i > 0; --i)
	{
	    temp = array[i];
		array[i] = array[0];
		array[0] = temp;

		adjust_heap(array,0,i);
	}
}

