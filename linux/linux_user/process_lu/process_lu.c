/*========================= ���̵����� =========================
---->��������
�ں���exec����ִ��C����ʱ���ڵ���mainǰ�ȵ���һ��������������̡�
��������ȡ�������в����ͻ�������ֵ��Ȼ�����main��������main�������غ�����������������exit������

*/


/*========================= ���̵��˳� =========================
---->�����˳�
1 ����return����Ч��exit
2 ����exit
3 ����_exit��_Exit
---->�쳣�˳�
1 ����about���� 
2 �����յ�ĳ���źţ������ź�ʹ������ֹ�� 


Returning an integer value from the main function is equivalent to calling exitwith the same value. Thus
exit(0);is the same as return(0);from the main function.

*/

/*
function:With ISO C,a process can register at least 32 functions that are automatically called by
         exit.These are called exit handlers and are registered by calling the atexit function.
Returns: 0 if OK, nonzero on error

1 The exit function calls these functions in reverse order of their registration. Each function is called as many times as it was registered.*/
#include <stdlib.h>
int atexit(void (*func)(void));


#include<stdlib.h>

/*******************************************************************************
 @status:��Ϊ0����ʾ�쳣�˳�,0��ʾ�����˳�
 function:������ֹ����(Ҫ��ִ��һЩ���������Ȼ�󽫿���Ȩ�����ں�)

 1 exit()�����ڵ���exitϵͳ֮ǰҪ����ļ��Ĵ���������ļ�������������д���ļ���
 2 exit�����������ֹ�������(ͨ��atexitע��),Ȼ��ر����б�׼I/O���ȡ�
 3 exit��������_exit����֮�ϵ�һ����װ��������_exit�����ڵ���֮ǰ��ˢ������
 ******************************************************************************/
void exit(int status);

/*����ϴ��׼I/O��*/
void _Exit(int status);


/*******************************************************************************
1 _exit()ִ�к��������ظ��ںˣ���exit()Ҫ��ִ��һЩ���������Ȼ�󽫿���Ȩ�����ںˡ�
2 ����_exit����ʱ�����رս������е��ļ��������������ڴ��Լ�����һЩ�ں���������
  ������ˢ����(stdin, stdout, stderr ...).    
3 ����һЩ���ݣ���Ϊ�Ѿ�д�����ļ���ʵ������Ϊû�������ض������������ǻ�ֻ�Ǳ���
  �ڻ������ڣ���ʱ��_exit()����ֱ�ӽ����̹رգ������������ݾͻᶪʧ��
*******************************************************************************/
 
#include <unistd.h>    /* POSIX */ 
void _exit(int status); 


#include <unistd.h>

/*
@forkʱ���ӽ��̻���̸����̵�
 �򿪵��ļ�:�����ļ���(file table entry)
?Real user ID, real group ID, effective user ID, and effective group ID
?Supplementary group IDs
?Process group ID
?Session ID
?Controlling terminal
?The set-user-ID and set-group-ID flags
?Current working directory
?Root directory
?File mode creation mask
?Signal mask and dispositions
?The close-on-exec flag for any open file descriptors
?Environment
?Attached shared memory segments
?Memory mappings
?Resource limits

 The differences between the parent and child are:
 The return values from fork are different.
 The process IDs are different.
?The two processes have different parent process IDs: the parent process ID of the
child is the parent; the parent process ID of the parent doesn��t change.
?The  child��stms_utime, tms_stime, tms_cutime,andtms_cstimevalues
areset to 0 (these times arediscussed in Section 8.17).
?File locks set by the parent arenot inherited by the child.
?Pending alarms arecleared for the child.
?The set of pending signals for the child is set to the empty set*/
/*******************************************************************************
 Returns: 0 in child, process ID of child in parent,-1 on error
 1 The new process created by @fork is called the child process.This function is 
   called once but returns twice. �ӽ��̷���0�������̷����ӽ��̵Ľ���ID
 2 ���ӽ��̹������Σ��������Լ������ݶΡ��Ѻ�ջ�ռ䡣
 3 ���ӽ��̵�ִ��˳��ȡ���ڵ����㷨
 4 Modern implementations don't perform a complete copy of the parent's data, stack,
   and heap, since a @fork is often followed by an @exec. Instead, a technique 
   called copy-on-write (COW) is used. These regions are shared by the parent and 
   the child and have their protection changed by the kernel to read-only. If 
   either process tries to modify these regions, the kernel then makes a copy 
   of that piece of memory only, typically a "page" in a virtual memory system. 
 ******************************************************************************/
pid_t fork(void);

/*******************************************************************************
 vfork���ڴ���һ���½��̣������½��̵�Ŀ����execһ���½��̡�vfork��֤�ӽ�������
 �У��ڵ���exec��_exit֮ǰ�븸���������ǹ����,��������exec��_exit֮�󸸽��̲�
 ���ܱ��������С�
 ******************************************************************************/
pid_t vfork(void);



#include <unistd.h>
pid_t getpid(void);/*Returns: process ID of calling process*/
pid_t getppid(void);/*Returns: parent process ID of calling process*/
uid_t getuid(void);/*Returns: real user ID of calling process*/
uid_t geteuid(void);/*Returns: effective user ID of calling process*/
gid_t getgid(void);/*Returns: real group ID of calling process*/
gid_t getegid(void);/*Returns: effective group ID of calling process*/


#include <sys/wait.h>

/*���wait waitpid��ֹ״̬�ĺ� ���̿���:������ֹ ��ĳ���ź�ɱ�� ����ҵ����ֹͣ*/
#define WEXITSTATUS(status) /*WExitStatus to fetch the low-order 8 bits of the 
argument that the child passed to exit,_exit,or_Exit*/
#define WTERMSIG(status)  /*wtermsig to fetch the signal number that caused the 
termination.*/
#define WSTOPSIG(status)  /*Wstopsig to fetch the signal number that caused the 
child to stop*/
#define WIFEXITED(status)   /*WIFexited ������ֹ��Ϊ�档������ֹʱ����ִ��
WEXITSTATUS()*/
#define WIFSIGNALED(status) /*WIFsignaled �쳣��ֹ��Ϊ��(����һ����������ź�)��
��ʱ���Ե���WTERMSIG()��ȡ�ӽ�����ֹ���źű��*/
#define WIFSTOPPED(status)  /*WIFstopped True if status was returned for a child 
that is currently stopped.��ʱ���Ե���WSTOPSIG()��ȡʹ�ӽ�����ͣ���źű��*/
#define WIFCONTINUED(status) /* True if status was returned for a child that has 
been continued after a job control stop (XSI option; waitpid only).*/



/*******************************************************************************
 @statloc:���ؽ��̵��˳�״̬(���Դ�NULL)������ĳЩλ��ʾ�˳�״̬(��������)������
          λ��ָʾ�źű��(�쳣����)
 return: process ID(�˳�����) if OK, 0 (see later), or -1 on error
 1 ��������ӽ��̶��������У�����������һ����ֹwait�ͷ��ء�
 2 �����û���κ��ӽ��̣������������ء�����Ψһ�ĳ���ԭ��
 ******************************************************************************/
pid_t wait(int *statloc);


#define WUNTRACED
/*******************************************************************************
 @pid: pid == -1 �ȴ������ӽ���
       pid > 0   �ȴ������ID��pid��ȵ��ӽ���
       pid == 0  �ȴ�����ID���ڽ�����ID�������ӽ���
       pid < -1  �ȴ�����ID����pid����ֵ�������ӽ���
 @statloc:���ؽ��̵��˳�״̬
 @options:����Ϊ 0 �������"|"�������������������ʹ��,�� WNOHANG | WUNTRACED
      0         �ȴ�
      WNOHANG   ��pidָ�����ӽ���û�н�������waitpid()��������0�������Եȴ�������
                �����򷵻ظ��ӽ��̵�ID��
      WUNTRACED ���ӽ��̽�����ͣ״̬�������Ϸ��أ����ӽ��̵Ľ���״̬��������ᡣ
                WIFSTOPPED(status)��ȷ������ֵ�Ƿ��Ӧ��һ����ͣ�ӽ��̡�
                
 return: process ID if OK, 0 (see later), or -1 on error

 1 ���ָ���Ľ��̻�����鲻���ڣ����߲���pidָ���Ľ��̲��ǵ��ý��̵��ӽ����򶼽�����
 ******************************************************************************/
pid_t waitpid(pid_t pid,int *statloc,int options);


#include <sys/wait.h>
#define P_PID /*Wait for a particular process: id contains the process ID of the 
child to wait for.*/
#define P_PGID /*Wait for any child process in a particular process group: id 
contains the process group ID of the children to wait for.*/
#define P_ALL /*Wait for any child process: id is ignored*/

#define WCONTINUED /*Wait for a process that has previously stopped and has been 
continued, and whose status has not yet been reported.*/
#define WEXITED /*Wait for processes that have exited.*/

#define WNOHANG /* (WithNoHang) Return immediately instead of blocking if there 
is no child exit status available.*/

#define WNOWAIT /*Don't destroy the child exit status. The child's exit status 
can be retrieved by a subsequent call to wait, waitid, or waitpid.*/
#define WSTOPPED /*Wait for a process that has stopped and whose status has not 
yet been reported*/

/*******************************************************************************
 @idtype : ����@id�����ͣ�P_PID P_PGID P_ALL
 @id     :
 @infop  : 
 @options: WCONTINUED WEXITED WNOHANG  WNOWAIT WSTOPPED
 Returns: 0 if OK, -1 on error
 ******************************************************************************/
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
/*return: process ID if OK, 0, or -1 on error*/
pid_t wait3(int *statloc,int options,struct rusage *rusage);

/*return: process ID if OK, 0, or -1 on error*/
pid_t wait4(pid_t pid,int *statloc,int options,struct rusage *rusage);


#include <unistd.h>
/*
We��ve mentioned that the process ID does not change after an exec,but the new
program inherits additional properties from the calling process:
?Process ID and parent process ID
?Real user ID and real group ID
?Supplementary group IDs
?Process group ID
?Session ID
?Controlling terminal
?Time left until alarm clock
?Current working directory
?Root directory
?File mode creation mask
?File locks
?Process signal mask
?Pending signals
?Resource limits
?Nice value (on XSI-conformant systems; see Section 8.16)
?Values fortms_utime,tms_stime,tms_cutime,andtms_cstime

l:list  v:vector  
p: means that the function takes a filename argument and uses the PATH environment variable to find the executable file.
l: means that the function takes a list of arguments and is mutually exclusive with the letter v, 
v: means that it takes an argv[] vector.
e: means that the function takes an envp[] array instead of using the current environment.

@filename:If filename contains a slash /, it is taken as a pathname.Otherwise, the executable file is searched for 
          in the directories specified by the PATH environment variable

All seven return:-1 on error, no return on success


The process ID does not change across an exec,because a new process is not created; exec merely replaces the current process
��its text, data, heap,  and  stack segments �� with a brand-new program from disk.*/
int execl(const char *pathname,const char *arg0,... /* (char *)0 */ );
int execv(const char *pathname,char *const argv[]);
int execle(const char *pathname,const char *arg0,.../* (char *)0, char *const envp[] */ );
int execve(const char *pathname,char *const argv[], char *const envp[]);

/*If either execlp or execvp finds an executable file using one of the path prefixes,but the file isn't a machine executable 
  that was generated by the link editor,the function assumes that the file is a shell script and tries to invoke /bin/sh with 
  the filenameas input to the shell.*/
int execlp(const char *filename,const char *arg0,... /* (char *)0 */ );
int execvp(const char *filename,char *const argv[]);
int fexecve(int fd,char *const argv[], char *const envp[]);

#include <unistd.h>
/*
function:
return: 0 if OK,-1 on error

---->�޸Ĺ���
1 �����̾��г����û�Ȩ�ޣ���setuid������ʵ���û�ID����Ч�û�ID,�Լ�����������û�ID����Ϊuid
2 If the process does not have superuser privileges, but uid equals either the real user ID or the saved set-user-ID,
  setuid sets only the effective user ID to uid. The real user ID and the saved set-user-ID are not changed.
3 If neither of these two conditions is true,errno is set to EPERM and -1 is returned.

We can make a few statements about the three user IDs that the kernel maintains.
1 Only a superuser process can change the real user ID. Normally,the real user ID is set by the login(1) program when we log in and never changes. 
  Because login is a superuser process, it sets all three user IDs when it call ssetuid.
2 The effective user ID is set by the exec functions only if the set-user-ID bit is set for the program file. 
  If the set-user-ID bit is not set, the exec functions leave the effective user ID as its current value. 
  We can call setuid at any time to set the effective user ID to either the real user ID or the saved set-user-ID.  
  Naturally, we can��t set the effective user ID to any random value.
3 The saved set-user-ID is copied from the effective user ID by exec.If the file��s set-user-ID bit is set, this copy is saved after exec stores 
  the effective user ID from the file's user ID.*/
int setuid(uid_t uid);
int setgid(gid_t gid);



#include <unistd.h>
/*Returns: process group ID of calling process*/
pid_t getpgrp(void);

/*
  returns: process group ID if OK,-1 on error

  1 getpgid(0)==getpgrp()*/
pid_t getpgid(pid_t pid);

/*
  function:A process joins an existing process group or creates a new process group by calling @setpgid
  Returns: 0 if OK,-1 on error

  1 �ѽ���@pid�Ľ�����ID���ó�@pgid,���@pid==@pgid,�����@pid��ɽ������鳤.
  2 if @pid==0  ʹ�õ����ߵĽ���ID
  3 if @pgid==0 �����@pid�Ľ���ID��Ϊ������ID
  4 һ������ֻ��Ϊ�Լ��������ӽ������ý�����ID
  5 �ӽ��̵���execϵ�к�����,�����鲻�ܸı�*/
int setpgid(pid_t pid,pid_t pgid);

/*
function:A process establishes a new session by calling the @setsid function.
returns: process group ID if OK,-1 on error

1 ������øú����Ľ������鳤����,�������س���.
2 ��������鳤����,��@setsid����һ���»Ự.
2.1 The process becomes the session leader of this new session. (A session leader is
    the process that creates a session.) The process is the only process in this new session.
2.2 The process becomes the process group leader of a new process group. The new
    process group ID is the process ID of the calling process.
2.3 The process has no controlling terminal. If the process had a controlling terminal before calling
    @setsid,that association is broken.*/
pid_t setsid(void);

/*
returns: session leader's process group ID if OK,-1 on error
1 If @pid is 0, @getsid returns the process group ID of the calling process's session leader.
2 For security reasons, some implementations may restrict the calling process from obtaining the 
  process group ID of the session leader if @pid doesn't belong to the same session as the caller.*/
pid_t getsid(pid_t pid);





#include <setjmp.h>
/*******************************************************************************
 @env: һ���Ǹ�ȫ�ֱ������洢ջ��Ϣ����������@longjmpʱ�����ָ�ջ��
 Returns: 0 if called directly,nonzero if returning from a call to @longjmp
 ******************************************************************************/
int setjmp(jmp_buf env);

/*******************************************************************************
 @env:����@setjmpʱʹ�õ�@env
 @val:��@setjmp���ص�ֵ����α������0
 ******************************************************************************/
void longjmp(jmp_buf env,int val);

