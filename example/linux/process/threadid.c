//#include "apue.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx) %lu\n", s, (unsigned long)pid,
	  (unsigned long)tid, (unsigned long)tid,(unsigned long)ntid);
}

void *thr_fn(void *arg)
{
	printids("new thread: ");
	return((void *)0);
}

int main(void)
{
	int		err;
	printf("ntid1=%d\r\n",(unsigned long)ntid);

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	
	if (err != 0)
		printf("can't create thread");
	
	printids("main thread:");
	printf("\r\nntid2=%d",(unsigned long)ntid);
	printf("\r\nsize = %d %d",sizeof (pthread_t),sizeof(void *));
	
	sleep(1);
	exit(0);
}

/*
1 ���߳���Ҫ����,����������������Ƴ�,���������߳�����ǰ���������Ѿ���ֹ��
2 ���߳�û����ȫ�ֱ���ntid����߳�ID,������߳������̵߳���pthread_create����֮ǰ��������,��ô���߳̿�������δ����ʼ����ntid
*/
