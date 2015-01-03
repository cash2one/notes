#include<errno.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

static void sig_int(int);


int sigsuspend_eg_error()
{
	sigset_t newmask, oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	
	/* block SIGINT and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
	    printf("SIG_BLOCK error");
	}
	
	/* ����Ĵ��벻���ܵ�SIGINT��Ӱ�죬���������SIGINT�źţ�������*/
	
	/* restore signal mask, which unblocks SIGINT */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
	    printf("SIG_SETMASK error");
	}
	
/* ��������﷢��SIGINT�źţ�pause���ܾ͵Ȳ���SIGINT(���ʱ��û�е���pasue)��To correct 
 this problem, we need a way to both restore the signal mask and put the process to sleep 
 in a single atomic operation. This feature is provided by the @sigsuspend function.*/

    pause(); /* wait for signal to occur */
	
	/* continue processing */

}

int sigsuspend_eg(void)
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

/*******************************************************************************
 �ڵ���sigsuspend֮ǰֻ��SIGINT������������sigsuspend���ź������ּ�����ʱ�滻��
 SIGUSR1����ʱ���Ե���SIGINT����SIGINT������ȥִ��sig_int��ע�⣺��sig_int�����
 in sig_int: SIGINT SIGUSR1 ������Ϊ����ϵͳ���Զ������ڱ����͵��źż��������ּ���
 (���ڵ��͵��ź�Ҳ��δ���źţ��ᱻ��ӵ��ź��������У�����sig_int���أ�sigsuspendҲ
 �����أ���ʱ�����־���SIGINT��
*/

/*
program start:
in critical region: SIGINT
^C
in sig_int: SIGINT SIGUSR1
after return from sigsuspend: SIGINT
program exit:

*/

volatile sig_atomic_t quitflag; /* set nonzero by signal handler */

static void sig_int(int signo) /* one signal handler for SIGINT and SIGQUIT */
{
    if (signo == SIGINT)
        printf("\ninterrupt\n");
    else if (signo == SIGQUIT)
        quitflag = 1; /* set flag for main loop */
}


/************************************************************************************
 wait for a signal handler to set a global variable.we catch both the interrupt signal 
 and the quit signal,but want to wake up the main routine only when the quit signal is 
 caught.
************************************************************************************/
int sigsuspend_eg02(void)
{
	sigset_t newmask, oldmask, zeromask;
	
	if (signal(SIGINT, sig_int) == SIG_ERR)
	    printf("signal(SIGINT) error");
	
	if (signal(SIGQUIT, sig_int) == SIG_ERR)
        printf("signal(SIGQUIT) error");
	
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	
	/* Block SIGQUIT and save current signal mask. */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	    printf("SIG_BLOCK error");
	
	while (quitflag == 0)
	    sigsuspend(&zeromask);
	
	/* SIGQUIT has been caught and is now blocked; do whatever. */
	quitflag = 0;
	
	/* Reset signal mask which unblocks SIGQUIT. */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	    printf("SIG_SETMASK error");
	
	exit(0);
}

