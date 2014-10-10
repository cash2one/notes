#include<errno.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

static void sig_int(int);

int main(void)
{
	sigset_t  newmask, oldmask, waitmask;
	
	print_mask("program start: ");
	
	if (signal(SIGINT, sig_int) == SIG_ERR)
	    printf("signal(SIGINT) error");
	
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	
	/*Block SIGINT and save current signal mask.*/
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	    printf("SIG_BLOCK error");
	
	/*Critical region of code.*/
	
	print_mask("in critical region: ");
	
	/*Pause, allowing all signals except SIGUSR1.*/
	if (sigsuspend(&waitmask) != -1)
	    printf("sigsuspend error");
	
	print_mask("after return from sigsuspend: ");
	
	/*Reset signal mask which unblocks SIGINT*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	    printf("SIG_SETMASK error");
	
	/*And continue processing ...*/
	print_mask("program exit: ");
	exit(0);
}

static void sig_int(int signo)
{
    print_mask("\nin sig_int: ");
}

/*
�ڵ���sigsuspend֮ǰֻ��SIGINT������������sigsuspend���ź������ּ�����ʱ�滻��SIGUSR1����ʱ���Ե���SIGINT��
��SIGINT������ȥִ��sig_int��ע�⣺��sig_int�����in sig_int: SIGINT SIGUSR1 ������Ϊ����ϵͳ���Զ������ڱ����͵��źż��������ּ���
(���ڵ��͵��ź�Ҳ��δ���źţ��ᱻ��ӵ��ź��������У�����sig_int���أ�sigsuspendҲ�����أ���ʱ�����־���SIGINT��
*/

/*
program start:
in critical region: SIGINT
^C
in sig_int: SIGINT SIGUSR1
after return from sigsuspend: SIGINT
program exit:

*/
