#include<unistd.h>

/*
@filedes:�����ܵ�,�����ļ��������ɲ��� filedes ���鷵��
returns: 0 if OK,-1 on error

�������: 
EMFILE �����������ļ������������
ENFILE ϵͳ�����ļ����������á�
EFAULT ���� filedes �����ַ���Ϸ���

1 �ܵ�ֻ������ؽ���ʹ��,��Щ��ؽ��̵Ĺ�ͬ�����Ƚ��̴����˹ܵ�
2 filedes[0]Ϊ�ܵ���Ķ�ȡ��,filedes[1]��Ϊ�ܵ���д���*/
int pipe(int filedes[2]);


#include <stdio.h>
/*
@cmd:Ҫִ�е�����,�� ps
@type:�򿪷�ʽ
      "r":�ļ�ָ�����ӵ�@cmd�ı�׼���
      "w":�ļ�ָ�����ӵ�@cmd�ı�׼����
function:����һ���ܵ�,����fork����һ���ӽ���,�رչܵ��Ĳ�ʹ�ö�,ִ��һ��shell��������@cmd,Ȼ��ȴ�������ֹ.
returns: file pointer if OK,NULL on error

1 ʹ��popen()�����Ĺܵ�����ʹ��pclose()�ر�
2 �ܵ����������ķ������ɵڶ�������type���Ƶġ��˲���������r����w���ֱ�������д��������ͬʱΪ����д��
3 ��Linux ϵͳ�£��ܵ������Բ���type�е�һ���ַ�����ķ�ʽ�򿪡����ԣ�������ڲ���type��д��rw���ܵ������Զ��ķ�ʽ�򿪡�
*/
FILE *popen(const char *cmd,const char *type);

/*Returns: termination status of @cmd,or -1 on error*/
int pclose(FILE *fp);




#include <sys/stat.h>
/*return: 0 if OK,-1 on error*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);

