#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>


int  globvar=6;/*external variable in initialized data */
char  buf[] = "a write to stdout\n";

int main(void)
{
    int  var; /* automatic variable on the stack */
    pid_t  pid;
    var = 88;
	
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        printf("write error");
	
    printf("before fork "); 

    //printf("before fork \n");
	
    if ((pid = fork()) < 0) 
	{
        printf("fork error");
    }
	else if (pid == 0) 
	{ /* child */
        globvar++;  /* modify variables */
        var++;
    }
	else 
    {
        sleep(2);  /* parent */
    }
	
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
    exit(0);
}

/*******************************************************************************
write:��������
printf:��׼I/O������壬�����׼������ӵ��ն��豸���������л���ģ���������ȫ����ġ�

printf("before fork\n");
1 ������ն�ʱ(��ʱprintf���л����)
  ����ǰ�Ѿ�ˢ�»������������ӽ��̲������"before fork"
2 ������ļ�(��ʱprintf��ȫ�����)
  ��Ȼ��\n�����ڴ�ʱ��ȫ����ģ������ӽ���Ҳ�������




*/

/*
printf("before fork\n");��������

$ ./a.exe
a write to stdout
before fork
pid = 5928, glob = 7, var = 89
pid = 6832, glob = 6, var = 88


$ ./a.exe >out.txt
$ cat out.txt
a write to stdout
before fork
pid = 2160, glob = 7, var = 89
before fork
pid = 840, glob = 6, var = 88

*/
