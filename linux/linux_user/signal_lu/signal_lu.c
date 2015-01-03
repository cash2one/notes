#include <signal.h>

/************************************************************************************
 @signo:
    the name of the signal,SIGABRT etc.
 @func:
    The value of @func is 
    (a) the constant SIG_IGN, 
    (b) the constant SIG_DFL, or 
    (c) the address of a function to be called when the signal occurs. 
    If we specify SIG_IGN, we are telling the system to ignore the signal.(Remember 
    that we cannot ignore the two signals SIGKILL and SIGSTOP.) When we specify SIG_DFL, 
    we are setting the action associated with the signal to its default value. When we 
    specify the address of a function to be called when the signal occurs, we are 
    arranging to "catch" the signal. We call the function either the signal handler 
    or the signal-catching function.
  @function: ���ź�@signoע�ᴦ����@func.
  @returns : previous disposition of signal if OK,SIG_ERR on error

 1 ���ı��źŵĴ���ʽ�Ͳ���ȷ����ǰ����ʽ
 2 �źŴ�����ԭ�� void (*func)(int)
 3 @signal��һ��������@signal������������Σ���һ����int�ͣ��ڶ����Ǻ���ָ��(��ָ���
   ������һ��int����Σ���������ķ���ֵΪvoid)��@signal����ֵ��һ������ָ��(��ָ���
   ������һ��int����Σ���������ķ���ֵΪvoid)��
 ***********************************************************************************/
void signal();/* for source insight jump */
void (*signal(int signo,void (*func)(int)))(int);


/*******************************************************************************
 pid>0   The signal is sent to the process whose process ID is @pid.
 pid==0  The signal is sent to all processes whose process group ID equals the
         process group ID of the sender and for which the sender has permission to 
         send the signal. Note that the term all processes excludes an 
         implementation-defined set of system processes. For most UNIX systems, this 
         set of system processes includes the kernel processes and init(pid 1).
 pid<0   The signal is sent to all processes whose process group ID equals the absolute 
         value of @pid and for which the sender has permission to send the signal. 
         Again, the set of all processes excludes certain system processes, as 
         described earlier.
 pid==-1 The signal is sent to all processes on the system for which the sender has
         permission to send the signal. As before, the set of processes excludes
         certain system processes.
 @signo: If is 0, then the normal error checking is performed by @kill,but no 
         signal is sent.
 return: 0 if OK,-1 on error

 The superuser can send a signal to any process.  For other users, the basic rule
 is that the real or effective user ID of the sender has to equal the real or 
 effective user ID of the receiver.If the implementation supports _POSIX_SAVED_IDS
 (as POSIX.1 now requires), the saved set-user-ID of the receiver is checked 
 instead of its effective user ID.One special case for the permission testing also  
 exists: if the signal being sent is SIGCONT,a process can send it to any other 
 process in the same session.

 If we send the process the null signal and it doesn't exist, @kill returns -1 
 and errno is set to ESRCH.

 If the call to kill causes the signal to be generated for the calling process 
 and if the signal is not blocked, either @signo or some other pending, unblocked 
 signal is delivered to the process before @kill returns. 
 ******************************************************************************/
int kill(pid_t pid,int signo);


/*******************************************************************************
 return: 0 if OK,-1 on error

 raise(signo); �ȼ��� kill(getpid(), signo);
 ******************************************************************************/
int raise(int signo);

#include <unistd.h>

/*******************************************************************************
 @seconds:��
 function:����@seconds������SIGALRM�ź�
 Returns: 0 or number of seconds until previously set alarm

 1 ÿ������ֻ������һ������,�������alarmʱ,��ǰ���õ����ӻ�û�г�ʱ,����@seconds
   �������ӵĳ�ʱʱ�䡣�ϴ����ӵĲ���ֵ��Ϊ���ε���alarm�ķ���ֵ
 2 ����ϴ����ӻ�û��ʱ,���ұ��ε���@secondsΪ0,��ȡ����ǰ������,����ֵ��Ϊ���ε�
   ��alarm�ķ���ֵ
 3 SIGALRM�źŵ�Ĭ�϶�������ֹ����
 ******************************************************************************/
unsigned int alarm(unsigned int seconds);

/*******************************************************************************
 function:�������ֱ������һ���ź�
 Returns:-1 with errno set to EINTR

 1 ֻ�е�ִ����һ���źŴ�����򲢴��䷵��ʱ,pause�Ż᷵�ء�
 ******************************************************************************/
int pause(void);



#include <signal.h>

/*******************************************************************************
 function:���@setָ����źż�
 return: 0 if OK,-1 on error

 All applications have to call either @sigemptyset or @sigfillset once for each 
 signal set, before using the signal set.
 ******************************************************************************/
int sigemptyset(sigset_t *set);

/*
function:ʹ�źż�@set�������е��ź�
return: 0 if OK,-1 on error*/
int sigfillset(sigset_t *set);

/*
function:���ź�@signo��ӽ��źż�@set
return: 0 if OK,-1 on error*/
int sigaddset(sigset_t *set,int signo);

/*
function:���źż�@set��ɾ���ź�@signo
return: 0 if OK,-1 on error*/
int sigdelset(sigset_t *set,int signo);

/*Returns: 1 if true, 0 if false,-1 on error*/
int sigismember(const sigset_t *set,int signo);

#if 1
/*����źŵĸ���С��31�����������������ʵ������*/

#include  <signal.h>
#include  <errno.h>
/*<signal.h> usually defines NSIG to include signal number 0.*/
#define SIGBAD(signo) ((signo) <= 0 || (signo) >= NSIG)

#define sigemptyset(ptr) (*(ptr) = 0)

/*******************************************************************************
 Note that @sigfillset must return 0, in addition to setting all the bits on in 
 the signal set, so we use C's comma operator,which returns the value after the 
 comma as the value of the expression.
 ******************************************************************************/
#define sigfillset(ptr) (*(ptr) = ~(sigset_t)0, 0) /*~��λȡ��*/

int sigaddset(sigset_t *set, int signo)
{
    if (SIGBAD(signo)) 
	{
        errno = EINVAL;
        return(-1);
    }
	
    *set |= 1 << (signo - 1); /* turn bit on */
	
    return(0);
}

int sigdelset(sigset_t *set, int signo)
{
    if (SIGBAD(signo)) 
	{
        errno = EINVAL;
        return(-1);
    }
	
    *set &= ~(1 << (signo - 1)); /* turn bit off */
	
    return(0);
}

int sigismember(const sigset_t *set, int signo)
{
    if (SIGBAD(signo)) 
	{
        errno = EINVAL;
        return(-1);
    }
	
    return((*set & (1 << (signo - 1))) != 0);
}
#endif


#include <signal.h>
#define SIG_BLOCK   /*The new signal mask for the process is the union of its 
current signal mask and the signal set pointed to by @set.That is,@set contains 
the additional signals that we want to block.*/
#define SIG_UNBLOCK /*The new signal mask for the process is the intersection 
of its current signal mask and the complement of the signal set pointed to by @set.
That is,@set contains the signals that we want to unblock.*/
#define SIG_SETMASK /*The new signal mask for the process is replaced by the 
value of the signal set pointed to by @set*/

/*******************************************************************************
 @how : ָʾ����޸ĵ�ǰ�ź������� SIG_BLOCK SIG_UNBLOCK SIG_SETMASK
 @set : ���@how��ʹ��,@setΪ��ʱ,@how������
 @oset: ��@oset�Ƿǿ�ָ��,��ô���̵�ǰ���ź�������ͨ��@oset����
 returns: 0 if OK,-1 on error

 1 ����@sigprocmask��������κ�δ����,�����������ź�,����@sigprocmask����ǰ����
   �Ὣ����һ���źŵ��͸��Ľ���
 2 The @sigprocmask function is defined only for single-threaded processes.  
 ******************************************************************************/
int sigprocmask(int how,const sigset_t *restrict set,sigset_t *restrict oset);



#include <signal.h>
/*******************************************************************************
 function:ͨ��@set���ؽ����������ź�
 Returns: 0 if OK,-1 on error
 ******************************************************************************/
int sigpending(sigset_t *set);

#define SIG_ERR (void (*)())-1
#define SIG_DFL (void (*)())0
#define SIG_IGN (void (*)())1

/*������struct sigaction�ṹ��sa_flags�ֶο��ܵ�ֵ*/
#define SA_SIGINFO /*This option provides additional information to a signal 
handler: a pointer to a siginfo structure and a pointer to an identifier for the 
process context */


/*******************************************************************************
 @sa_mask:��һ���źż�������@sa_handler֮ǰ���뵽���̵��ź��������У������źŴ���
 �����з���ʱ�ٻظ�����ԭ�����ź������֡�The operating system includes the signal 
 being delivered in the signal mask when the handler is invoked. Hence, we 
 areguaranteed that whenever we are processing a given signal, another occurrence 
 of that same signal is blocked until we're finished processing the first occurrence. 

 @sa_sigaction:The @sa_sigaction field is an alternative signal handler used when 
 the SA_SIGINFO flag is used with sigaction.Implementations might use the same
 storage for both the @sa_sigaction field and the @sa_handler field, so applications
 can use only one of these fields at a time.
 ******************************************************************************/
struct sigaction 
{
    void  (*sa_handler)(int); /* addr of signal handler,or SIG_IGN, or SIG_DFL */
    sigset_t sa_mask;         /* additional signals to block */
    int  sa_flags;            /* signal options,SA_INTERRUPT ��*/
    void  (*sa_sigaction)(int, siginfo_t *, void *);/* alternate handler */
};

/*******************************************************************************
 The @siginfo structure contains information about why the signal was generated.
 An example of what it might look like is shown below.All POSIX.1-compliant
 implementations must include at least the @si_signo and @si_code members.
 Additionally,implementations that are XSI compliant contain at least the following
 fields:
 ******************************************************************************/
struct siginfo 
{
int  si_signo; /* signal number */
int  si_errno; /* if nonzero, errno value from errno.h */
int  si_code; /* additional info (depends on signal) */
pid_t  si_pid; /* sending process ID */
uid_t  si_uid; /* sending process real user ID */
void  *si_addr; /* address that caused the fault */
int  si_status; /* exit value or signal number */
union sigval si_value; /* application-specific value */
/* possibly other fields also */
};


/*******************************************************************************
 @signo: the signal number whose action we are examining or modifying.
 @act  : If the @act pointer is non-null, we are modifying the action. 
 @oact : If the @oact pointer is non-null, the system returns the previous action 
         for the signal through the @oact pointer.

 function:examine or modify (or both) the action associated with a particular signal.
 returns: 0 if OK,-1 on error

 1 sa_mask�ֶ�˵����һ���źż�,�ڵ��ø��źŲ�׽����֮ǰ,��һ�źż�Ҫ�ӵ����̵��ź�
   �������С����źŲ�׽��������ʱ,���̵������ָֻ���ԭ����ֵ
 2 ���źŲ�׽��������ʱ,ͬʱ����������ź�(@signo)
 3 ͬһ���źŶ�η���ͨ�����Ŷ�,Ҳ���ǽ��������ͨ��ֻ�����һ���źŲ�׽��������ʹ
   ���ڼ䷢���˺ܶ������źš�
 4 Once we install an action for a given signal, that action remains installed 
   until we explicitly change it by calling @sigaction.
 ******************************************************************************/
int sigaction(int signo,const struct sigaction *restrict act,struct sigaction *restrict oact);



#include <signal.h>
/************************************************************************************
 @sigmask:�����̵��ź�����������Ϊ��@sigmaskָ���ֵ��
 Returns:-1 with errno set to EINTR

 The signal mask of the process is set to the value pointed to by @sigmask. Then the 
 process is suspended until a signal is caught or until a signal occurs that terminates 
 the process. If a signal is caught and if the signal handler returns, then sigsuspend
 returns, and the signal mask of the process is set to its value before the call to 
 sigsuspend.Note that there is no successful return from this function. If it returns 
 to the caller, it always returns -1 with errno set to EINTR (indicating an interrupted 
 system call).
 
 sigsuspend������ԭ�Ӳ�������Ϊ��
(1) �����µ�mask������ǰ���̣�֮����̹���
(2) �յ��źţ��ָ�ԭ��mask��
(3) ���øý������õ��źŴ�������
(4) ���źŴ��������غ�sigsuspend���ء�
************************************************************************************/
int sigsuspend(const sigset_t *sigmask);


#include <setjmp.h>
/*******************************************************************************
 Returns: 0 if called directly,nonzero if returning from a call to @siglongjmp

 The only difference between these functions and the @setjmp and @longjmp functions 
 is that @sigsetjmp has an additional argument. If @savemask is nonzero, then 
 @sigsetjmp also saves the current signal mask of the process in env.When @siglongjmp 
 is called, if the env argument was saved by a call to @sigsetjmp with a nonzero 
 @savemask,then @siglongjmp restores the saved signal mask.
 ******************************************************************************/
int sigsetjmp(sigjmp_buf env,int savemask);

void siglongjmp(sigjmp_buf env,int val);



#include <stdlib.h>
/*******************************************************************************
 function: sends the SIGABRT signal to the caller.(Processes should not ignore 
           this signal.) 
 return:This function never returns
 ******************************************************************************/
void abort(void);


#include <unistd.h>
/*******************************************************************************
 Returns: 0 or number of unslept seconds

 This function causes the calling process to be suspended until either
 1 The amount of wall clock time specified by @seconds has elapsed.
 2 A signal is caught by the process and the signal handler returns.
 In case 1, the return value is 0. When sleep returns early because of some signal
 being caught (case 2), the return value is the number of unslept seconds (the requested
 time minus the actual time slept)

 @sleep������
 1 ���һ���������ȵ�����alarm(10); Ȼ���ֵ�����sleep(5);�ᷢ��ʲô
   The @sleep will return in 5 seconds (assuming that some other signal isn't 
   caught in the interim), but will another SIGALRM be generated 5 seconds later?
   These details depend on the implementation.
 ******************************************************************************/
unsigned int sleep(unsigned int seconds);



