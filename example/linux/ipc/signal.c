#if 0
#include<signal.h>
#include<stdio.h>

void handler(int sig)
{
    printf("Receive signal:%u\n",sig);
}

int main()
{
    struct sigaction sa;
	int count;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGTERM,&sa,NULL);

	sigprocmask(&sa.sa_mask);

	while(1)
	{
	    sigsuspend(&sa.sa_mask);
		printf("loop\n");
	}

	return 0;
}
#endif

#include <signal.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <error.h>  
#include <string.h>  
  
void sig_handler(int signum)  
{  
    printf("catch SIGINT\n");  
}  
  
int main(int argc, char **argv)  
{  
    sigset_t block;  
    struct sigaction action, old_action;  
  
    /* ��װ�ź� */  
    action.sa_handler = sig_handler;  
    sigemptyset(&action.sa_mask);  
    action.sa_flags = 0;  
  
    sigaction(SIGINT, NULL, &old_action);  
    if (old_action.sa_handler != SIG_IGN) {  
        sigaction(SIGINT, &action, NULL);  
    }  
  
    /* �����ź� */  
    sigemptyset(&block);  
    sigaddset(&block, SIGINT);  
  
    printf("block SIGINT\n");  
    sigprocmask(SIG_BLOCK, &block, NULL);  
  
    printf("--> send SIGINT -->\n");  
    kill(getpid(), SIGINT);  
    printf("--> send SIGINT -->\n");  
    kill(getpid(), SIGINT);  
    sleep(1);  
  
    /* ����źź�, ֮ǰ�������źŽ�������, 
     * ��SIGINT�Ƿǿɿ��ź�, ֻ�����һ�� 
     */  
    printf("unblock SIGINT\n");  
    sigprocmask(SIG_UNBLOCK, &block, NULL);  
  
    sleep(2);  
  
    return 0;  
}  

