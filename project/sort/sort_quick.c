/*
       ==== �������� ====
 1 ���Ӷ� �����ʱ��: thet(n^2)  ƽ������ʱ��: thet(nlgn) 
*/

/*
  ��array[first]~aray[end]�ֳ������֣�array[first]~aray[q]��array[q+1]~aray[end]
  ǰһ����С�ڵ���array[q]����һ���ִ���array[q]
  ����q�Ƿ���ֵ�����Ǹ���һ���ķ�����������ġ�*/
int partition(int array[],int first,int end)
{
  int pivot,s_i,j,temp;

  s_i = first - 1;
  pivot = array[end];/*��������������ѡ*/

  for(j = first; j < end; ++j)
  {
      if(array[j] <= pivot)
      {
          s_i++;
		  temp = array[j];
		  array[j] = array[s_i];
		  array[s_i] = temp;
      }
  }
  
  temp = array[end];
  array[end] = array[s_i+1];
  array[s_i+1] = temp;

  return (s_i + 1);
}

/* 
 @array: array[first] ~ array[end] ����
 @first: ��һ��Ԫ������   һ��Ϊ��
 @end  : ���һ��Ԫ������ һ��Ϊ����Ԫ�ظ�����1
*/
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
