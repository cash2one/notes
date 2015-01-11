/**************************************************************************
 1 ���Ӷ� nlgn  
 **************************************************************************/

#include <stdio.h>
#include <stdbool.h>

/*******************************************************************************  
  1 ���Ѿ��ź����array[first...middle]��array[middle+1 ... end]�ϲ���һ����������
  2 first <= middle < end

  array[first...middle]��Ϊ�����飬array[middle+1 ... end]��Ϊ�����顣
  a ���������Ԫ�ؿ�������ʱ����ArrayL�������鿽����ArrayR��
  b �������鶼�Ǵ�С�����ź���ģ���ô�ϲ���һ�����������أ��������˿��Ƶ�����˵��:
    �����������������������˿��ƣ����泯������С���������档��ʼ����ȡ��������С��
    �Ǹ������Ұ������������������ƾ��Ǵ�С��������ġ�

  ������Ҫע��:
  1 ���������Ԫ�ظ���Ҳ��һ��
  2 Ҳ����ѵ��˿���һֱ��С�ƣ�������һֱ�����ȡ�ơ�
  3 Ҳ���Ҷѵ����Ѿ�ȡ�꣬�����ж�ֱ�Ӵ����ȡ�ơ�
 *******************************************************************************/
void merge(int array[],int first, int middle, int end)
{
    int IndexL,IndexR,i;
	bool EmptyFlagL,EmptyFlagR;
	int LengthL = middle - first + 1;
	int LengthR = end - middle;
    int ArrayL[LengthL],ArrayR[LengthR];

	for(i = 0; i < LengthL; i++)
	{
	    ArrayL[i] = array[first + i];
	}

	for(i = 0; i < LengthR; i++)
	{
	    ArrayR[i] = array[middle + 1 + i];
	}

	IndexL  = 0; IndexR  = 0; EmptyFlagL = false; EmptyFlagR = false;

    for(i = first; i <= end; i++)
    {
        if( ((ArrayL[IndexL] <= ArrayR[IndexR]) && !EmptyFlagL) || EmptyFlagR)
        {
			array[i] = ArrayL[IndexL];
		    IndexL++;
			
			if(LengthL == IndexL) 
				EmptyFlagL = true;
        }
		else
		{
			array[i] = ArrayR[IndexR];
		    IndexR++;
			
			if(LengthR == IndexR) 
				EmptyFlagR = true;
		}	
    }	
}

/*1 ������array[first]��array[end]��Ԫ�ش�С��������
  2 end > first*/
void sort_merge(int array[], int first, int end)
{
    int middle;

    if(first < end)
    {
	    middle = (first + end)/2;
	
	    sort_merge(array,first,middle);
	    sort_merge(array,middle + 1 ,end);

	    merge(array,first,middle,end);
    }
}

#if 0
int main()
{
    int i;
    int array[8] = {8,1,5,7,4,2,3,9};

	//merge(array,0,3,7);
	sort_merge(array,0,7);

    for(i = 0; i < 8; i++)
	    printf("\r\narray[%d] = %d",i,array[i]);
}
#endif
