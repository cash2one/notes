typedef unsigned long int pthread_t; /*linux����ô����*/


#include <pthread.h>
/*Returns: nonzero if equal, 0 otherwise*/
int pthread_equal(pthread_t tid1,pthread_t tid2);


/*Returns: the thread ID of the calling thread*/
pthread_t pthread_self(void);

/*
@tidp:�����߳�ID
@attr:�߳�����,ΪNULLʱʹ��Ĭ������
@start_rtn:�´������̴߳�@start_rtn�����ĵ�ַ��ʼ����
@arg:@start_rtn�����Ĳ���
returns: 0 if OK, error number on failure

1 �´������߳̿��Է��ʽ��̵ĵ�ַ�ռ�
2 �̳е����̵߳ĸ��㻷�����ź�������,��δ���źż������
3 ����֤�´����̺߳͵����̵߳�ִ��˳��*/
int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);

