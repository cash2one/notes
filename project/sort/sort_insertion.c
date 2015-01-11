/************************************************************************************
 1 ���Ӷ� n*n  nСʱ�Ƚ���Ч
 ************************************************************************************
 �ٸ�����:��������10�����ӣ�������10���ˣ����ӸߵͲ�ͬ��
 ��1����(��Ϊp1):
    ����ֱ������1�������ϡ�
 ��2����(��Ϊp2):
    �ߵ���2�������Աߣ���������Լ���p1�ߣ�ֱ�����¡����û��p1�ߣ�����p1���ڵ�2����
    ���ϣ��Լ�����1�������ϡ�
 ��3����:
    �ߵ���3�������Աߣ���������Լ���ǰ���Ǹ��˸ߣ�ֱ�����¡������յڶ����˵�������
    �������Լ���λ�����¡�
 ......
************************************************************************************/
   

/*
 1 Insert array[j] into the sorted sequence array[0] ... array[j-1]
 2 ele_num >= 1
 3 small to big
*/  
void sort_insertion(int array[],int ele_num)
{
    int i,j,key;
	for(j = 1; j < ele_num; j++){
        key = array[j];
		i = j - 1;
		while(i >= 0 && array[i] > key){
		    array[i+1] = array[i];
			i--;
		}
		array[i+1] = key;
	}
}

void sort_insertion_withgap(int array[],int nums,int gap)
{
    int i,j,key;
	for(i = gap; i < nums; i++){
		key = array[i];
		j = i - gap;
		while((j >= 0) && (array[j] > key)){
			array[j+gap] = array[j];
			j -= gap;
		}
		array[j+gap] = key;
	}	
}

void sort_insertion_v2(int array[],int nums)
{
	sort_insertion_withgap(array,nums,1);
}

