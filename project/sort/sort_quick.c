/************************************************************************************
                            ==== �������� ====
*************************************************************************************    
 1 ���Ӷ� �����ʱ��: thet(n^2)  ƽ������ʱ��: thet(nlgn) 
 2 Quicksort is a sorting algorithm whose worst-case running time is ��(n^2) on an 
   input array of n numbers. In spite of this slow worst-case running time, quicksort 
   is often the best practical choice for sorting because it is remarkably efficient 
   on the average: its expected running time is ��(n lg n), and the constant factors 
   hidden in the ��(n lg n) notation are quite small. It also has the advantage of 
   sorting in place (see page 16), and it works well even in virtual memory environments.
************************************************************************************/

/*-----------------------------------------------------------------------------------
  ��array[first]~aray[end]�ֳ������֣�array[first]~aray[q]��array[q+1]~aray[end]
  ǰһ����С�ڵ���array[q]����һ���ִ���array[q]
  ����q�Ƿ���ֵ�����Ǹ���һ���ķ�����������ġ�
-----------------------------------------------------------------------------------*/
int partition(int array[],int first,int end)
{
  int pivot,s_i,j,temp;

  s_i = first - 1;
  pivot = array[end];/*��������������ѡ��ѡȡ��Ԫ�ؾ���q��ֵ*/

  for(j = first; j < end; ++j){
      if(array[j] <= pivot){
          s_i++;
		  temp = array[j];
		  array[j] = array[s_i];
		  array[s_i] = temp;
      }
  }

  s_i++;
  temp = array[end];
  array[end] = array[s_i];
  array[s_i] = temp;

  return (s_i);
}

/*-----------------------------------------------------------------------------------
 @array: array[first] ~ array[end] ����
 @first: ��һ��Ԫ������   һ��Ϊ��
 @end  : ���һ��Ԫ������ һ��Ϊ����Ԫ�ظ�����1
-----------------------------------------------------------------------------------*/
void sort_quick(int array[],int first,int end)
{
    int q;
	
    if(first < end)
    {
        q = partition(array,first,end);
		sort_quick(array,first,q-1);
		sort_quick(array,q+1,end);
    }
}

/*-----------------------------------------------------------------------------------
**                       sort_quick����ʾ��
**-----------------------------------------------------------------------------------
 0 1 2 3 4 5 6 7   <---- ����
 ---------------
 2 8 7 1 3 5 6 4   <---- ��ʼ��ѡȡ���һ��Ԫ����Ϊ�ֽ��,s_i = -1
 
 2 8 7 1 3 5 6 4   <---- j=0; s_i =-1->0 swap(a[0],a[0]) 
 2 8 7 1 3 5 6 4   <---- j=1; s_i = 0->0  
 2 8 7 1 3 5 6 4   <---- j=2; s_i = 0->0  
 2 1 7 8 3 5 6 4   <---- j=3; s_i = 0->1 swap(a[3],a[1])
 2 1 3 8 7 5 6 4   <---- j=4; s_i = 1->2 swap(a[4],a[2])
 2 1 3 8 7 5 6 4   <---- j=5; s_i = 2->2 
 2 1 3 8 7 5 6 4   <---- j=6; s_i = 2->2  
 2 1 3 4 7 5 6 8   <---- j=7; s_i = 2->3 swap(a[7),a[3])��������������return 3;

 2 1 3   4 7 5 6 8   ��������ķ����ֱ�����������������

 2 1 3  ----> 
 
*/
