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


#include <sys/stat.h>
/*return: 0 if OK,-1 on error*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);

