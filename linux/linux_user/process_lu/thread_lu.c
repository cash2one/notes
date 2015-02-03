typedef unsigned long int pthread_t; /* linux����ô���� */

#include <pthread.h>
/*Returns: nonzero if equal, 0 otherwise*/
int pthread_equal(pthread_t tid1,pthread_t tid2);


/*Returns: the thread ID of the calling thread*/
pthread_t pthread_self(void);

/*-----------------------------------------------------------------------------------
 @tidp
    The memory location pointed to by @tidp is set to the thread ID of the newly cre-
    ated thread when @pthread_create returns successfully. 
 @attr:
    The @attr argument is used to customize various thread attributes. set this to NULL 
    to create a thread with the default attributes.
 @start_rtn
    The newly created thread starts running at the address of the start_rtn function.
 @arg:
    If you need to pass more  than one argument to the @start_rtn function, then  you 
    need to store them in a structure and pass the address of the structure in @arg.
 @returns:
    0 if OK, error number on failure

 When a thread is created, there is no guarantee which will run first: the newly cre-
 ated thread or the calling thread. The newly created thread has access to the proce-
 ss address space and inherits the calling thread's floating-point environment and s-
 ignal mask; however, the set of pending signals for the thread is cleared.
 
 Note that the pthread functions usually return an error code when they fail. They d-
 on't set @errno like the other POSIX functions. The per-thread copy of @errno is pr-
 ovided only for compatibility with existing functions that use it. With threads,  it 
 is cleaner to return the error code from the function, thereby restricting the scope 
 of the error to the function that caused it, instead of relying on some global state 
 that is changed as a side effect of the function.
-----------------------------------------------------------------------------------*/
int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, 
                       void *(*start_rtn)(void *), void *restrict arg);


/*-----------------------------------------------------------------------------------
 @rval_ptr
    The rval_ptr argument is a typeless pointer,similar to the single argument passed 
    to the start routine.This pointer is available to other threads in the process by 
    calling the @pthread_join function.

 If any thread within a process calls exit, _Exit,or _exit,then the entire process t-
 erminates. Similarly, when the default action  is to terminate the process, a signal 
 sent to a thread will terminate the entire process 
 A single thread can exit in three ways, there by stopping its flow of control, with-
 out terminating the entireprocess.
 1 The thread can simply return from the start routine. The return value is the thre-
   ad's exit code.
 2 The thread can be canceled by another thread in the same process.
 3 The thread can call @pthread_exit.
-----------------------------------------------------------------------------------*/
void pthread_exit(void *rval_ptr);


/*-----------------------------------------------------------------------------------
 ���κ�һ��ʱ����ϣ��߳��ǿɽ�ϵģ�joinable�������Ƿ���ģ�detached����һ���ɽ�ϵ�
 �߳��ܹ��������߳��ջ�����Դ��ɱ�����ڱ������̻߳���֮ǰ�����Ĵ洢����Դ������ջ����
 ���ͷŵġ��෴��һ��������߳��ǲ��ܱ������̻߳��ջ�ɱ���ģ����Ĵ洢����Դ������ֹʱ
 ��ϵͳ�Զ��ͷš�

 ����һ���߳�Ĭ�ϵ�״̬�� joinable, ���һ���߳̽������е�û�б�join,������״̬������
 �����е� Zombie Process , ������һ������Դû�б�����(�˳�״̬��)�����Դ����߳���Ӧ��
 ���� @pthread_join ���ȴ��߳����н��������ɵõ��̵߳��˳����룬��������Դ(������wait,
 waitpid). ���ǵ���pthread_join(pthread_id)��������߳�û�����н����������߻ᱻ������
 ����Щ��������ǲ���ϣ����ˣ�������Web�������е����߳�Ϊÿ�����������Ӵ���һ�����߳�
 ���д����ʱ�����̲߳���ϣ����Ϊ����pthread_join������(��Ϊ��Ҫ��������֮��������
 ��)����ʱ���������߳��м������
            pthread_detach(pthread_self())
 ���߸��̵߳���
            pthread_detach(thread_id) //(������������������)
 �⽫�����̵߳�״̬����Ϊdetached,����߳����н�������Զ��ͷ�������Դ��
-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------
 @returns 
    0 if OK, error number on failure 

 The calling thread will block until the specified @thread calls @pthread_exit, retu-
 rns from its start routine, or is canceled. If  the thread simply  returned from its 
 start routine, @rval_ptr will contain the return code. If the  @thread was canceled, 
 the memory location specified by @rval_ptr is set to PTHREAD_CANCELED.
 
 By calling @pthread_join, we automatically place the thread with which we're joining 
 in the detached state (discussed shortly) so that its resources can be recovered. If 
 the thread was already in the detached state, @pthread_join can fail, returning EINVAL,
 although this behavior is implementation-specific.
 
 If we're not interested in a thread's return value, we can set @rval_ptr to NULL. In 
 this case, calling @pthread_join allows us to wait for the specified thread, but do-
 es not retrieve the thread's termination status.

 example: pthread_join_eg01()
-----------------------------------------------------------------------------------*/
int pthread_join(pthread_t thread,void **rval_ptr);

/*-----------------------------------------------------------------------------------
 @function: 
    One thread can request that another in the same process be canceled by calling t-
    he @pthread_cancel function.
 @Returns : 
    0 if OK, error number on failure

 In the default circumstances, @pthread_cancel will cause the thread specified by @tid 
 to behave as if it had called @pthread_exit with an argument of PTHREAD_CANCELED. H-
 owever, a thread can elect  to ignore or otherwise  control how it is canceled. Note 
 that @pthread_cancel doesn't  wait for the thread to terminate ; it merely makes the 
 request.
-----------------------------------------------------------------------------------*/
int pthread_cancel(pthread_t tid);


/*-----------------------------------------------------------------------------------
 A thread can arrange for functions to be called when it exits, similar to the way t-
 hat the @atexit function can be used by a process to arrange that functions are to be 
 called when the process exits. The functions are known as "thread cleanup handlers".
 More than one cleanup handler can be established for a thread. The handlers are rec-
 orded in a stack, which means that they are executed  in the reverse order from that
 with which they were registered.

 The @pthread_cleanup_push function schedules the cleanup function, @rtn, to be call-
 ed with the single argument, @arg, when the thread performs one of the following ac-
 tions:
    1 Makes a call to @pthread_exit
    2 Responds to a cancellation request
    3 Makes a call to pthread_cleanup_pop with a nonzero execute argument
 If the execute argument is set to zero, the cleanup function is not called. In eith-
 er case, @pthread_cleanup_pop removes the cleanup handler established by the last c-
 all to @pthread_cleanup_push.
 
 A restriction with these functions is that, because they can be implemented as macr-
 os, they must be used in matched pairs within  the same scope in a thread. The macro 
 deefinition of @pthread_cleanup_push can include a { character, in which case the m-
 atching } character is in the @pthread_cleanup_pop definition.

 example: pthread_cleanup_push_eg01()
-----------------------------------------------------------------------------------*/
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);


/*-----------------------------------------------------------------------------------
 @Returns: 
    0 if OK, error number on failure
    
 By default, a thread's termination status is retained until we call @pthread_join f-
 or that thread. A thread's underlying storage can be reclaimed immediately on termi-
 nation if the thread has been detached. After a thread is detached, we can't use the
 @pthread_join function to wait for its termination status, because calling @pthread_join 
 for a detached thread results in undefined behavior. We can detach a thread by call-
 ing @pthread_detach.
 
 we can create a thread that is already in the detached state by modifying the thread 
 attributes we pass to @pthread_create.
-----------------------------------------------------------------------------------*/
int pthread_detach(pthread_t tid);


/*-----------------------------------------------------------------------------------
 @mutex:
 @attr:
    To initialize a mutex with the default attributes, we set @attr to NULL.
 @return: 
    0 if OK, error number on failure

 A mutex variable is represented by the pthread_mutex_t data type.Before we can use a 
 mutex variable, we must first initialize it by either setting it to the constant
 PTHREAD_MUTEX_INITIALIZER (for statically allocated mutexes only) or calling
 pthread_mutex_init. If we allocate the mutex dynamically (by calling malloc,for exa-
 mple), then we need to call pthread_mutex_destroy before freeing the memory
-----------------------------------------------------------------------------------*/
#define PTHREAD_MUTEX_INITIALIZER 
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

/*-----------------------------------------------------------------------------------
 @return: 0 if OK, error number on failure

 To lock a mutex, we call @pthread_mutex_lock. If the mutex is already locked, the c-
 alling thread will block until the mutex is unlocked. To unlock a mutex, we call
 @pthread_mutex_unlock.

 If a thread can't afford to block, it can use @pthread_mutex_trylock to lock the mu-
 tex conditionally. If the mutex is unlocked at the time @pthread_mutex_trylock is c-
 alled, then @pthread_mutex_trylock will lock the mutex without blocking and return 0. 
 Otherwise, @pthread_mutex_trylock will fail, returning EBUSY without locking the mu-
 tex.
-----------------------------------------------------------------------------------*/
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);


/*-----------------------------------------------------------------------------------
 Reader-writer locks are well suited for situations in which data structures are read
 more often than they are modified. When a reader-writer lock is held in write mode ,
 the data structure it protects can be modified safely, since only one thread at a t-
 ime can hold the lock in write mode. When the reader-writer lock is held in read mo-
 de , the data structure it protects can be read by multiple threads , as long as the 
 threads first acquirethe lock in read mode.

 Reader-writer locks are also called shared-exclusive locks.When a reader-writer lock 
 is read locked, it is said to be locked in shared mode.When it is write locked,it is
 said to be locked in exclusive mode.

 As with mutexes, reader-writer locks must be initialized before use and destroyed b-
 efore freeing their underlying memory.
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 @attr:
 @return: 
    0 if OK, error number on failure

 A reader-writer lock  is initialized by calling @pthread_rwlock_init . We can pass a 
 null pointer for @attr if we want the reader-writer lock to have the default attrib-
 utes. The Single UNIX Specification defines the  PTHREAD_RWLOCK_INITIALIZER constant 
 in the XSI option. It can be used to initialize a statically allocated reader-writer
 lock when the default attributes are sufficient. Before freeing the memory backing a 
 reader-writer lock, we need to call @pthread_rwlock_destroy to clean it up. If 
 @pthread_rwlock_init allocated any resources for the reader-writer lock, 
 @pthread_rwlock_destroy frees those resources. If we free the memory backing a reader-writer 
 lock without first calling @pthread_rwlock_destroy, any resources assigned to the l-
 ock will be lost.
-----------------------------------------------------------------------------------*/
#define PTHREAD_RWLOCK_INITIALIZER
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);


/*-----------------------------------------------------------------------------------
 @return: 
    0 if OK, error number on failure
    
 To lock a reader-writer lock in read mode , we call @pthread_rwlock_rdlock. To write 
 lock a reader-writer lock, we call @pthread_rwlock_wrlock. Regardless of how we lock 
 a reader-writer lock, we can unlock it by calling @pthread_rwlock_unlock.

 Implementations might place  a limit on the number of times a reader-writer lock can 
 be locked in shared mode, so we need to check the return value of @pthread_rwlock_rdlock.
 Even though @pthread_rwlock_wrlock and @pthread_rwlock_unlock have error returns, a-
 nd technically we should always check for errors when we call functions that can po-
 tentially fail , we don't need to check them if we design our locking properly . The 
 only error returns defined are when we use them improperly, such as with an uniniti-
 alized lock, or when we might deadlock by attempting to acquirea lock we already own. 
 However,be aware that specific implementations might define additional error returns.
-----------------------------------------------------------------------------------*/
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);



/*-----------------------------------------------------------------------------------
 @return: 
    0 if OK, error number on failure
    
 The Single UNIX Specification also defines conditional versions of the reader-writer
 locking primitives.

 When the lock can be acquired, these functions return 0. Otherwise , they return the
 error EBUSY. These functions can be used to avoid deadlocks in situations where con-
 forming to a lock hierarchy is difficult, as we discussed previously.
-----------------------------------------------------------------------------------*/
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);

/*----------------------------------------------------------------------------------- 
 ��������Ϊ����������Ƶģ�����������Ϊ�˵ȴ�����Ƶ� 
 �뻥������ͬ�����������������ȴ����������������ġ��������������Զ�����һ���̣߳�ֱ��
 ĳ�����������Ϊֹ��ͨ�����������ͻ�����ͬʱʹ�á�

 ��������ʹ���ǿ���˯�ߵȴ�ĳ���������֡����������������̼߳乲���ȫ�ֱ�������ͬ����
 һ�ֻ��ƣ� ��Ҫ��������������һ���̵߳ȴ�"������������������"��������һ���߳�ʹ"��
 ������"���������������źţ���

 �����ļ�����ڻ������ı����½��еġ����һ������Ϊ�٣�һ���߳��Զ����������ͷŵȴ�״
 ̬�ı�Ļ������������һ���̸߳ı��������������źŸ���������������������һ��������
 �������̣߳����»�û�����������������������������̹���ɶ�д���ڴ棬�����������Ա�
 ����ʵ���������̼���߳�ͬ����

 ���������ڱ��������ٽ������Ӷ���֤�κ�ʱ��ֻ��һ���̻߳��߽������ٽ���ִ�С���ʱ��һ
 ���̻߳��ĳ���������󣬷����Լ���Ҫ�ȴ�ĳ��������Ϊ�棬�����߳̾Ϳ��Եȴ���ĳ������
 �ϡ���������������һ����������֮������

 �������������������Ծ�̬���䲢��̬��ʼ��������Ҳ���Զ�̬���䲢Ҫ��̬�س�ʼ�����ǡ�
 ��̬��ʼ����������ָ�����̼乲�����ԣ��Ӷ������ڲ�ͬ���̼乲��ĳ��������������������
 ��ǰ���Ǹû����������������������������Щ���̹�����ڴ�����
-----------------------------------------------------------------------------------*/

/*
 return: 0 if OK, error number on failure
*/
#define PTHREAD_COND_INITIALIZER 
int pthread_cond_init(pthread_cond_t *restrict cond,const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);

/*-----------------------------------------------------------------------------------
 @tsptr
    The timeout value specifies how long we are willing to wait expressed as a @timespec 
    structure. we need to specify how long we are willing to wait as an absolute time 
    instead of a relative time. For example,suppose we are willing to wait 3 minutes. 
    Instead of translating 3 minutes into a @timespec structure, we need to translate 
    now+3 minutes into a @timespec structure.
 @return: 
    0 if OK, error number on failure
    
 We @use pthread_cond_wait to wait for a condition to be true . A variant is provided 
 to return an error code if the condition hasn't been satisfied in the specified amo-
 unt of time.

 The mutex passed to @pthread_cond_wait protects the condition . The caller passes it 
 locked to the function , which then atomically places the calling thread on the list 
 of threads waiting  for the condition and unlocks the mutex . This closes the window
 between the time that the condition is checked and the time that  the thread goes to 
 sleep waiting for the condition to change, so that the thread doesn't  miss a change 
 in the condition. When @pthread_cond_wait returns, the mutex is again locked.

 If the timeout expires without the condition occurring, @pthread_cond_timedwait will 
 reacquire the mutex and return the error ETIMEDOUT. When it returns from a successf-
 ul call to @pthread_cond_wait or @pthread_cond_timedwait, a thread needs to reevalu-
 ate the condition, since another thread might have run and already changed the cond-
 ition.
-----------------------------------------------------------------------------------*/
int pthread_cond_wait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex);
int pthread_cond_timedwait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex,
                                  const struct timespec *restrict tsptr);

/*-----------------------------------------------------------------------------------
 @return: 
    0 if OK, error number on failure

 There are two functions to notify threads that a condition has been satisfied. The
 @pthread_cond_signal function will wake up at least one thread waiting on a conditi-
 on (���û�еȴ����̣߳���ʲôҲ���� ), whereas the @pthread_cond_broadcast function 
 will wake up all threads waiting on a condition. 

 if a thread calls  @pthread_cond_signal and no thread is currently blocked in a call 
 to @pthread_cond_wait, the signal is lost.
  
 The POSIX specification allows for implementations of pthread_cond_signal to wake up 
 more than one thread, to make the implementation simpler.

 When we call @pthread_cond_signal or @pthread_cond_broadcast, we are said to be sig-
 naling the thread or condition. We have to be careful to signal the threads only af-
 ter changing the state of the condition.

 example: pthread_cond_eg01()
-----------------------------------------------------------------------------------*/
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);

/*
 PTHREAD_PROCESS_SHARED
    the spin lock can be acquired by threads that have access to the lock's underlyi-
    ng memory, even if those threads are from different processes. 
 PTHREAD_PROCESS_PRIVATE
    the spin lock can be accessed only from threads within the process that initiali-
    zed it.
*/
#define PTHREAD_PROCESS_SHARED
#define PTHREAD_PROCESS_PRIVATE
/*-----------------------------------------------------------------------------------
 @pshared
    The @pshared argument represents the process-shared attribute,which indicates how 
    the spin lock will be acquired. PTHREAD_PROCESS_SHARED PTHREAD_PROCESS_PRIVATE
 @return: 
    0 if OK, error number on failure

 A spin lock is like a mutex, except that instead of blocking a process by sleeping ,  
 the process is blocked by busy-waiting ( spinning ) until the lock can be acquired . 
 A spin lock could be used in situations where locks are held for short periods of t-
 imes and threads don't want to incur the cost of being descheduled.
-----------------------------------------------------------------------------------*/
int pthread_spin_init(pthread_spinlock_t *lock,int pshared);
int pthread_spin_destroy(pthread_spinlock_t *lock);


/*-----------------------------------------------------------------------------------
 @return: 
    0 if OK, error number on failure
-----------------------------------------------------------------------------------*/
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);




/*-----------------------------------------------------------------------------------
 @count
    specify the number of threads that must reach the barrier beforeall of the threa-
    ds will be allowed to continue.
 @attr
    specify the attributes of the barrier object. we can set @attr to NULL to initia-
    lize a barrier with the default attributes. 
 @return: 
    0 if OK, error number on failure

 Barriers are asynchronization mechanism that can be used to coordinate multiple thr-
 eads working in parallel. A barrier allows each thread to wait until all cooperating
 threads have reached the same point , and then continue executing from there . We've 
 already seen one form of barrier--the pthread_join function acts as a barrier to al-
 low one thread to wait until another thread exits.
 
 Barrier objects are more general than this, however . They allow an arbitrary number 
 of threads to wait until all of the threads have completed processing, but the thre-
 ads don't have to exit. They can continue working after all threads have reached th-
 e barrier.
 
 We can use the @pthread_barrier_init function to initialize a barrier, and we can u-
 se the @pthread_barrier_destroy function to deinitialize a barrier. 

 If the @pthread_barrier_init function allocated  any resources for the barrier , the 
 resources will be freed when we deinitialize the barrier by calling the 
 @pthread_barrier_destroy function.    
-----------------------------------------------------------------------------------*/
int pthread_barrier_init(pthread_barrier_t *restrict barrier,
const pthread_barrierattr_t *restrict attr,unsigned int count);
int pthread_barrier_destroy(pthread_barrier_t *barrier);

#define PTHREAD_BARRIER_SERIAL_THREAD
/*-----------------------------------------------------------------------------------
 @Returns: 
    0 or PTHREAD_BARRIER_SERIAL_THREAD if OK, error number on failure

 We use the @pthread_barrier_wait function to indicate that a thread is done with its 
 work and is ready to wait for all the other threads to catch up.

 The @thread calling pthread_barrier_wait is put to sleep if the barrier count(set in
 the call to @pthread_barrier_init ) is not yet satisfied . If the thread is the last 
 one to call @pthread_barrier_wait , thereby satisfying the barrier count, all of the 
 threads are awakened.
 
 To one arbitrary thread, it will appear as if the @pthread_barrier_wait function re-
 turned a value of PTHREAD_BARRIER_SERIAL_THREAD . The remaining threads see a return 
 value of 0.This allows one thread to continue as the master to act on the results of 
 the work done by all of the other threads.
 
 Once the barrier count is reached and the threads are unblocked , the barrier can be
 used again. However, the barrier count can't be changed unless we call the
 @pthread_barrier_destroy function followed by the @pthread_barrier_init function wi-
 th a different count.
-----------------------------------------------------------------------------------*/
int pthread_barrier_wait(pthread_barrier_t *barrier);


/*-----------------------------------------------------------------------------------
 set/get the concurrency level. Compile and link with -pthread.
-----------------------------------------------------------------------------------*/	
int pthread_setconcurrency(int new_level);
int pthread_getconcurrency(void);

