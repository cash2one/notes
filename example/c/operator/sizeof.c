/*******************************************************************************
sizeof��C/C++�е�һ����������operator���������þ��Ƿ���һ���������������ռ����
���ֽ������䷵��ֵ����Ϊsize_t����ͷ�ļ�stddef.h�ж��塣����һ�������ڱ���ϵͳ��
ֵ��һ�㶨��Ϊ��
        typedef unsigned int size_t;
        
sizeof�������﷨��ʽ�����£�
1) sizeof( object );    // sizeof( ���� );
2) sizeof( type_name ); // sizeof( ���� );
3) sizeof object;       // sizeof ����; һ�㲻�ã�֪������

*/
#include <stdio.h>


struct _tag{
    int a;
	int b;
	int c;
};

/* �������Ͳ�ʱ���������Ƶ���ָ��ʹ�ã��� */
void sizeof_test01(int tmp[3])
{
    int a;
	int *p;
	int array[3];
	char *string = "abcde";

	printf("sizeof(int)     :%d %d\r\n",sizeof(int),sizeof(a));	
	printf("sizeof(void *)  :%d %d\r\n",sizeof(void *),sizeof(p));
	printf("sizeof(array[3]):%d \r\n",sizeof(array));
	printf("sizeof(tmp[3])  :%d \r\n",sizeof(tmp));
	printf("sizeof(string)  :%d %d %d\r\n",sizeof(string),sizeof(*string),sizeof("abcde"));
	
}

void sizeof_test02(struct _tag s,struct _tag *sp)
{
    int temp[3];
	printf("sizeof(s)       :%d %d\r\n",sizeof(s),sizeof(struct _tag));
	printf("sizeof(sp/*sp)  :%d %d\r\n",sizeof(sp),sizeof(*sp));	
	
	sizeof_test01(temp);
}

void sizeof_test03()
{
    struct _tag ss;

	sizeof_test02(ss,&ss);
}


int main()
{
   sizeof_test03();
}
