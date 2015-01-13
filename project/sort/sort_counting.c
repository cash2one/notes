/************************************************************************************
                            ==== �������� ====
*************************************************************************************    
 1 ���Ӷ�: thet(n)
 2 ����: n������Ԫ�ص�ֵ������0��k֮�䡣
 3 ԭ��:����һ������Ԫ��x��ȷ����С��x��Ԫ�صĸ����������Ϳ��԰�xֱ�ӷ������յ������С�
 4 An important property of counting sort is that it is stable: numbers with the same 
   value appear in the output array in the same order as they do in the input array. 
   That is, ties between two numbers are broken by the rule that whichever number 
   appears first in the input array appears first in the output array. Normally, the 
   property of stability is important only when satellite data are carried around with 
   the element being sorted. Counting sort's stability is important for another reason: 
   counting sort is often used as a subroutine in radix sort. As we shall see in the 
   next section, counting sort's stability is crucial to radix sort's correctness.
************************************************************************************/ 

#include<stddef.h>
#include<stdlib.h>
#define CS_MAX 100 /*0 ~ 100*/

void sort_counting(int array[],int size)
{
    int i,value,location;
    int temp[CS_MAX+1] = {0};
	int *p = NULL;

	p = (int *)malloc(size*sizeof(int));

	for(i = 0; i < size; ++i)
	{
	    *(p+i) = array[i];
	    temp[array[i]]++;               /*��ʱtemp[i]�д�ŵ���i���ֵĴ���*/
	}

	for(i = 1; i <= CS_MAX; ++i)
	{
	    temp[i] = temp[i] + temp[i-1];  /*��ʱtemp[i]��С�ڵ���i��Ԫ�صĸ���*/
	}

	for(i = 0; i < size; ++i)
	{
        value = *(p+i);
		location = temp[value]-1;
		temp[value]--;                  /*�������ظ���ֵҪռ�ݶ���ط�*/
		array[location] = value;
	}

	free(p);
}
