#include<unistd.h>

/*-----------------------------------------------------------------------------------
 @fd:
    Two file descriptors are returned through the fd argument: fd[0] is open for re-
    ading, and fd[1] is open for writing.
 @returns: 
    0 if OK,-1 on error

 �������: 
 EMFILE �����������ļ������������
 ENFILE ϵͳ�����ļ����������á�
 EFAULT ���� filedes �����ַ���Ϸ���

1 Historically, they have been half duplex (i.e., data flows in only one direction). 
  Some systems now provide full-duplex pipes, but for maximum portability, we should 
  never assume that this is the case.
 2 Pipes can be used only between processes that have a common ancestor. Normally, a 
   pipe is created by a process, that process calls fork, and the pipe is used betw-
   een the parent and the child
-----------------------------------------------------------------------------------*/
int pipe(int fd[2]);


#include <stdio.h>
/*-----------------------------------------------------------------------------------
 @cmd:
    Ҫִ�е�����,�� ps ls
 @type:�򿪷�ʽ
    "r":�ļ�ָ�����ӵ�@cmd�ı�׼���
    "w":�ļ�ָ�����ӵ�@cmd�ı�׼����
 @function:
    creating a pipe, forking a child, closing the unused ends of the pipe, executing 
    a shell to run the command, and waiting for the command to terminate.
 @returns: 
    file pointer if OK, NULL on error

 The function @popen does a @fork and @exec to execute the @cmd and returns a stand-
 ard I/O file pointer. If @type is "r" , the file pointer is connected to the stand-
 ard output of @cmd. If @type is "w" , the file pointer is connected to the standar-
 d input of @cmd.

 1 ʹ��popen()�����Ĺܵ�����ʹ��pclose()�ر�
 2 �ܵ����������ķ������ɵڶ�������@type���Ƶġ��˲���������r����w���ֱ�������д��
   ������ͬʱΪ����д��
 3 ��Linux ϵͳ�£��ܵ������Բ���@type�е�һ���ַ�����ķ�ʽ�򿪡����ԣ�������ڲ���
   @type��д��rw���ܵ������Զ��ķ�ʽ�򿪡�
-----------------------------------------------------------------------------------*/
FILE *popen(const char *cmd,const char *type);

/*-----------------------------------------------------------------------------------
 @func:
    closes the standard I/O stream, waits for  the command to terminate, and  returns 
    the termination status of the shell.
 @returns: 
    termination status of @cmd, or -1 on error. If the shell cannot be  executed, the 
    termination status returned by @pclose is as if the shell had executed exit(127).
-----------------------------------------------------------------------------------*/
int pclose(FILE *fp);




#include <sys/stat.h>
/*-----------------------------------------------------------------------------------
 @func
    �ú����ĵ�һ��������һ����ͨ��·������Ҳ���Ǵ�����FIFO�����֡��ڶ������������
    ͨ�ļ���open()�����е�mode ������ͬ�� ���mkfifo�ĵ�һ��������һ���Ѿ����ڵ�·��
    ��ʱ���᷵��EEXIST��������һ����͵ĵ��ô������Ȼ����Ƿ񷵻ظô������ȷʵ
    ���ظô�����ôֻҪ���ô�FIFO�ĺ����Ϳ����ˡ�һ���ļ���I/O��������������FIFO��
    ��close��read��write�ȵȡ�
 @return: 
    0 if OK,-1 on error

 mkfifo�����Ѿ�����ָ��O_CREAT | O_EXCL,Ҳ����˵,Ҫô����һ���µ�FIFO��Ҫô����EEXIST
 ����(�ļ��Ѿ�����)
-----------------------------------------------------------------------------------*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);

