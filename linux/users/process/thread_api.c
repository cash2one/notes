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

/*If any thread within a process calls exit, _Exit,or _exit,then the entire process terminates. 
  Similarly,when the default action is to terminate the process, a signal sent to a thread will terminate the entire process 
  A single thread can exit in three ways, there by stopping its flow of control, without terminating the entireprocess.
  1 The thread can simply return from the start routine. The return value is the thread's exit code.
  2 The thread can be canceled by another thread in the same process.
  3 The thread can call @pthread_exit.*/
void pthread_exit(void *rval_ptr);

/*
function: ��ȡ�߳�@thread�ķ���״̬(@rval_ptrָ�򷵻�״̬)
returns : 0 if OK, error number on failure 

1 �����߳�һֱ����,ֱ��ָ���̵߳���@pthread_exit�������������з��ػ��߱�ȡ��
2 ��������������з���,@rval_ptr������������
3 ����̱߳�ȡ��,��@rval_ptrָ�����ڴ浥Ԫ����Ϊ PTHREAD_CANCELED
4 ����Է���״̬������Ȥ,���԰�@rval_ptr��NULL*/
int pthread_join(pthread_t thread,void **rval_ptr);

/*
function: ȡ��ͬһ�����е��߳�@tid
Returns : 0 if OK, error number on failure
1 @pthread_cancel���ȴ��߳���ֹ,�������������.�߳̿��Ժ����������
2 ����߳��յ������˳�,�൱�ڵ�����pthread_exit(PTHREAD_CANCELED)*/
int pthread_cancel(pthread_t tid);


/*
function:ע��"�߳����������",�߳��˳�ʱ����,ִ�е�˳����ע��˳���෴.
���������������������
1 ����pthread_exitʱ
2 ��Ӧȡ������ʱ
3 �÷����������pthread_cleanup_popʱ,pthread_cleanup_pop(0)������������������.
���������������ɾ��������*/
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);

