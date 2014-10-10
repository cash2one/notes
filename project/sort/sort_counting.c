/* ��������
   ���Ӷ�: thet(n)
   ����: n������Ԫ�ص�ֵ������0��k֮�䡣
   ԭ��:����һ������Ԫ��x��ȷ����С��x��Ԫ�صĸ����������Ϳ��԰�xֱ�ӷ������յ������С�
 */

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
