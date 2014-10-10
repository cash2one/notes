/*
����: ���n���ַ���ȫ���� ����
  ����: "abc" 
  ���: abc; acb; bac; bca; cab; cba;
  ����: "aab"
  ���: aab; aba; baa;

����: 


��ʽ:
  a1,a1,...a1, a2,a2,...a2,.......,an,an,...an
  ���У�a1�ĸ���ΪN1, a2�ĸ���ΪN2,�Դ����ƣ��ܸ���ΪM��
  ����Եõ����ظ��������������Ŀ,Ϊ(��֪�Ƿ�����֤��):
  M!/(N1!*N2!*...*Nn!)
*/

#include<stdio.h>
#include<string.h>

int count = 0;

static void permutation(char *string,int first,int end)
{
    int i,temp,j;
	
    if(first == end){
	    printf("\r\n%s        %d",string,++count);
		return;
    }

    for(i = first; i <= end; ++i){
        
        if((string[i] == string[first]) && (i != first))       /*��ͬ��Ԫ�ز�����*/
			continue;
      
		for(j = i+1; j <= end; ++j)                            /*a��b��ͬ������ж��b��aֻ�����һ��b����*/
		    if((string[i] == string[j]) && (i != first))
				break;

		if(j <= end)
			continue;
		
        temp = string[i];string[i] = string[first];string[first] = temp;
	    permutation(string,first+1,end);
        temp = string[i];string[i] = string[first];string[first] = temp;
    }
}


void full_permutation(char *string)
{
	if(NULL == string)
	{
		printf("\r\nIn Para Error");
		return;
	}

    permutation(string,0,strlen(string)-1);
}





/********************** �����ǲ��Ժ��� **********************/

int factorial(int n)
{
    if((1 == n) || (0 == n))
		return 1;

	return n*factorial(n-1);
}

int permutation_num(char *string)
{
    int num = 1;
	int i,len;
    int count[256] = {0};

	if(NULL == string || '\0' == *string)
		return;

	len = strlen(string);

    do
    {
        count[*string]++;
    }while(*string++ != '\0');

	for(i = 0; i < 256; ++i)
	{			
	    if(0 != count[i])
	        num = num*factorial(count[i]);
	}

	return factorial(len)/num;
}



int main(int argc,char **argv)
{
    if(NULL == argv[1])
    {
    	printf("\r\nIn Para Error %d",argc);
		return;
    }
	printf("\r\nTotal:%d",permutation_num(argv[1]));
	full_permutation(argv[1]);
}

