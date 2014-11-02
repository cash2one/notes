#define SIG_ERR (void (*)())-1
#define SIG_DFL (void (*)())0
#define SIG_IGN (void (*)())1

#include <signal.h>

/*******************************************************************************
 @signo:�źű��
 @func: �źŴ�������
         SIG_IGN ���Դ��ź�(SIGKILL��SIGSTOP���ܺ���)
         SIG_DFL ʹ��Ĭ�ϴ�����
 function: ���ź�@signoע�ᴦ����@func.
 Returns : previous disposition of signal if OK,SIG_ERR on error

 1 ���ı��źŵĴ���ʽ�Ͳ���ȷ����ǰ����ʽ
 ******************************************************************************/
void (*signal(int signo,void (*func)(int)))(int);


/*
@seconds:��
function:����@seconds������SIGALRM�ź�
Returns: 0 or number of seconds until previously set alarm

1 ÿ������ֻ������һ������,�������alarmʱ,��ǰ���õ����ӻ�û�г�ʱ,����@seconds�������ӵĳ�ʱʱ�䡣
  �ϴ����ӵĲ���ֵ��Ϊ���ε���alarm�ķ���ֵ
2 ����ϴ����ӻ�û��ʱ,���ұ��ε���@secondsΪ0,��ȡ����ǰ������,����ֵ��Ϊ���ε���alarm�ķ���ֵ
3 SIGALRM�źŵ�Ĭ�϶�������ֹ����

*/
#include <unistd.h>
unsigned int alarm(unsigned int seconds);

/*
function:�������ֱ������һ���ź�
Returns:-1with errno set to EINTR

1 ֻ�е�ִ����һ���źŴ�����򲢴��䷵��ʱ,pause�Ż᷵�ء�*/
#include <unistd.h>
int pause(void);



#include <signal.h>
/*
function:���@setָ����źż�
return: 0 if OK,-1 on error*/
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
int sigismember(const sigset_t *set,intsigno);



#include <signal.h>
/*
@how:ָʾ����޸ĵ�ǰ�ź�������
     SIG_BLOCK ��@setָ����źż����뵱ǰ���̵�������
     SIG_UNBLOCK
     SIG_SETMASK  �ѽ��̵��ź�����������Ϊ@setָ����źż�
@set:���@how��ʹ��,@setΪ��ʱ,@how������
@oset:��@oset�Ƿǿ�ָ��,��ô���̵�ǰ���ź�������ͨ��@oset����
Returns: 0 if OK,-1 on error

1 ����@sigprocmask��������κ�δ����,�����������ź�,����@sigprocmask����ǰ���ٻὫ����һ���źŵ��͸��Ľ���*/
int sigprocmask(int how,const sigset_t *restrict set,sigset_t *restrict oset);

#include <signal.h>
/*
function:ͨ��@set���ؽ����������ź�
Returns: 0 if OK,-1 on error*/
int sigpending(sigset_t *set);

struct sigaction 
{
    void  (*sa_handler)(int); /* addr of signal handler,or SIG_IGN, or SIG_DFL */
    sigset_t sa_mask; /* additional signals to block */
    int  sa_flags; /* signal options, Figure 10.16 */
    void  (*sa_sigaction)(int, siginfo_t *, void *);/* alternate handler */
};

#include <signal.h>
/*
@signo:the signal number whose action we are examining or modifying.
@act: If the @act pointer is non-null, we are modifying the action. 
@oact: If the @oact pointer is non-null, the system returns the previous action for the signal through the @oact pointer.

function:The @sigaction function allows us to examine or modify (or both) the action associated with a particular signal. 
Returns: 0 if OK,-1 on error

1 sa_mask�ֶ�˵����һ���źż�,�ڵ��ø��źŲ�׽����֮ǰ,��һ�źż�Ҫ�ӵ����̵��ź��������С����źŲ�׽��������ʱ,���̵������ָֻ���ԭ����ֵ
2 ���źŲ�׽��������ʱ,ͬʱ����������ź�(@signo)
3 ͬһ���źŶ�η���ͨ�����Ŷ�,Ҳ���ǽ��������ͨ��ֻ�����һ���źŲ�׽��������ʹ���ڼ䷢���˺ܶ������źš�
4 Once we install an action for a given signal, that action remains installed until we explicitly change it by calling @sigaction.*/
int sigaction(int signo,const struct sigaction *restrict act,struct sigaction *restrict oact);



#include <signal.h>
/*
@sigmask:�����̵��ź�����������Ϊ��@sigmaskָ���ֵ��
Returns:-1 with errno set to EINTR
sigsuspend������ԭ�Ӳ�������Ϊ��
(1) �����µ�mask������ǰ���̣�֮����̹���
(2) �յ��źţ��ָ�ԭ��mask��
(3) ���øý������õ��źŴ�������
(4) ���źŴ��������غ�sigsuspend���ء�*/
int sigsuspend(const sigset_t *sigmask);


#include <stdlib.h>
/*
function: sends the SIGABRT signal to the caller.(Processes should not ignore this signal.) 
return:This function never returns*/
void abort(void);


#include <unistd.h>
/*
Returns: 0 or number of unslept seconds

This function causes the calling process to be suspended until either
1.  The amount of wall clock time specified by @seconds has elapsed.
2.  A signal is caught by the process and the signal handler returns.
In case 1, the return value is 0. When sleep returns early because of some signal
being caught (case 2), the return value is the number of unslept seconds (the requested
time minus the actual time slept)*/
unsigned int sleep(unsigned int seconds);



