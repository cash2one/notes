typedef unsigned long int pthread_t; /*linux����ô����*/
/*
���κ�һ��ʱ����ϣ��߳��ǿɽ�ϵģ�joinable�������Ƿ���ģ�detached����
һ���ɽ�ϵ��߳��ܹ��������߳��ջ�����Դ��ɱ�����ڱ������̻߳���֮ǰ�����Ĵ洢����Դ������ջ���ǲ��ͷŵġ�
�෴��һ��������߳��ǲ��ܱ������̻߳��ջ�ɱ���ģ����Ĵ洢����Դ������ֹʱ��ϵͳ�Զ��ͷš�

����һ���߳�Ĭ�ϵ�״̬��joinable, ���һ���߳̽������е�û�б�join,������״̬�����ڽ����е�Zombie Process,
������һ������Դû�б����գ��˳�״̬�룩�����Դ����߳���Ӧ�õ���pthread_join���ȴ��߳����н�����
���ɵõ��̵߳��˳����룬��������Դ��������wait,waitpid).���ǵ���pthread_join(pthread_id)��
������߳�û�����н����������߻ᱻ����������Щ��������ǲ���ϣ����ˣ�
������Web�������е����߳�Ϊÿ�����������Ӵ���һ�����߳̽��д����ʱ��
���̲߳���ϣ����Ϊ����pthread_join����������Ϊ��Ҫ��������֮���������ӣ���
��ʱ���������߳��м������
pthread_detach(pthread_self())
���߸��̵߳���
pthread_detach(thread_id)�������������������أ�
�⽫�����̵߳�״̬����Ϊdetached,����߳����н�������Զ��ͷ�������Դ��
*/

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
4 ����Է���״̬������Ȥ,���԰�@rval_ptr��NULL
5 ������@pthread_join����ʱ�����ȴ��߳�@thread����Դ���ջء�*/
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

/*
By default, a thread's termination status is retained until we call @pthread_join for that thread. 
A thread's underlying storage can be reclaimed immediately on termination if the thread has been detached.
After a thread is detached, we can't use the @pthread_join function to wait for its termination status, 
because calling @pthread_join for a detached thread results in undefined behavior.
We can detach a thread by calling @pthread_detach.

Returns: 0 if OK, error number on failure*/
int pthread_detach(pthread_t tid);

/*
@mutex:
@attr:����,@attr==NULLʱ��Ĭ�ϵ����Գ�ʼ��������,
return: 0 if OK, error number on failure

1 ��������� pthread_mutex_t ������������ʾ,ʹ��ǰ�����ʼ��,��ʼֵ��PTHREAD_MUTEX_INITIALIZER*/
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);

/*return: 0 if OK, error number on failure
�����̬�ط��以����(����ͨ��malloc),��ô���ͷ��ڴ�ǰ��Ҫ����@pthread_mutex_destroy*/
int pthread_mutex_destroy(pthread_mutex_t *mutex);

/*return: 0 if OK, error number on failure
@pthread_mutex_lock�Ի���������,����������Ѿ�����,���߳̽�����ֱ��������������*/
int pthread_mutex_lock(pthread_mutex_t *mutex);

/*return: 0 if OK, error number on failure
If a thread can't afford to block, it can use @pthread_mutex_trylockto lock the
mutex conditionally.If the mutex is unlocked at the time @pthread_mutex_trylock is called,  
then @pthread_mutex_trylock will lock the mutex without blocking and return  0. 
Otherwise, @pthread_mutex_trylock will fail, returning EBUSY without locking the mutex.*/
int pthread_mutex_trylock(pthread_mutex_t *mutex);

/*return: 0 if OK, error number on failure*/
int pthread_mutex_unlock(pthread_mutex_t *mutex);


/*
@attr:����,@attr==NULLʱ��Ĭ�ϵ����Գ�ʼ����д��
return: 0 if OK, error number on failure

1 ��д����ʹ��֮ǰ�����ʼ��
*/
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);

/*return: 0 if OK, error number on failure

1 ���ͷŶ�д��ռ�õ��ڴ�֮ǰ,��Ҫ����@pthread_rwlock_destroy��������
2 ���@pthread_rwlock_initΪ��д����������Դ,@pthread_rwlock_destroy���ͷ���Щ��Դ
3 ����ڵ���@pthread_rwlock_destroy֮ǰ���ͷ��˶�д��ռ�õ��ڴ�ռ�,��ô��������������Դ�Ͷ�ʧ��*/
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);


/*return: 0 if OK, error number on failure*/
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure*/
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure
������д�����������������*/
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure
When the lock can be acquired, these functions return 0. Otherwise, they return the error EBUSY.*/
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure
When the lock can be acquired, these functions return 0. Otherwise, they return the error EBUSY.*/
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);


