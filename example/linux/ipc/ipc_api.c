#include<unistd.h>

/*@filedes:�����ܵ�,�����ļ��������ɲ��� filedes ���鷵��
  Returns: 0 if OK,-1 on error
  filedes[0]Ϊ�ܵ���Ķ�ȡ��
  filedes[1]��Ϊ�ܵ���д���
  �������: 
    EMFILE �����������ļ������������
    ENFILE ϵͳ�����ļ������ʿ��á�
    EFAULT ���� filedes �����ַ���Ϸ���
�ܵ�ֻ������ؽ���ʹ��,��Щ��ؽ��̵Ĺ�ͬ�����Ƚ��̴����˹ܵ�*/
int pipe(int filedes[2]);


#include <sys/stat.h>
/*return: 0 if OK,-1 on error*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);


