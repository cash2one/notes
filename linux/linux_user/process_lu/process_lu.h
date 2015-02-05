
//typedef int pid_t  /* linux */

/*-----------------------------------------------------------------------------------
 +------------------------+ high address
 | command-line arguments |
 | environment variables  |
 |------------------------|
 |          stack         |
 |                        |
 |                        |
 |          heap          |
 |------------------------|
 |          bbs           | initialized to zero bye exec
 |------------------------|
 |     initialized data   | read from program file by exec
 |------------------------|
 |          text          | read from program file by exec
 +------------------------+


       environ 
 +---------------------+
 | environment pointer | ----->  environment      environment    
 +---------------------+         list             strings
                                 +-------+
                                 | point | ----> HOME=/home/sar
                                 |-------|
                                 | point | ----> PATH=:/bin:/usr/bin
                                 |-------|
                                 | point | ----> SHELL=/bin/bash
                                 |-------|
                                 | point | ----> USER=sar
                                 |-------|
                                 | point | ----> LOGNAME=sar
                                 |-------|
                                 | NULL  |
                                 +-------+
                                 
main Function
    A C program starts execution with a function called @main . The prototype for the
    main function is
            int main(int argc,char *argv[]);
    where @argc is the number of command-line arguments, and @argv is an array of po-
    inters to the arguments.

    When a C program is executed by the kernel(by one of the exec functions), a spec-
    ial start-up routine is called before the main function is called. The executable 
    program file specifies this routine as the starting address for the program; this 
    is set up by the link editor when it is invoked by the C compiler. This start-up 
    routine takes values from the kernel (the command-line arguments and the environ-
    ment) and sets things up so that the main function is called as shown earlier.

Process Termination
    Thereare eight ways for a process to terminate. Normal termination occurs in five
    ways:
    1. Return from main
    2. Calling exit
    3. Calling _exit or _Exit
    4. Return of the last thread from its start routine 
    5. Calling pthread_exit from the last thread
    
    Abnormal termination occurs in three ways:
    6. Calling abort 
    7. Receipt of a signal 
    8. Response of the last thread to a cancellation request

    The start-up routine that we mentioned in the previous section is also written so 
    that if the main function returns, the exit function is called. If the start-up -
    routine were coded in C (it is often coded in assembly language) the call to main 
    could look like
            exit(main(argc, argv));
    Returning an integer value from the main function is equivalent to calling exit -
    with the same value. Thus exit(0);is the same as return(0);from the main function.
    
what happens if the parent terminates before the child
    the init process becomes the parent process of any process whose parent terminat-
    es. In such a case, we say that the process has been inherited by init. What nor-
    mally happens is that whenever  a process terminates, the kernel goes through all
    active processes to see whether the terminating process is the parent of any pro-
    cess that still exists. If so , the parent process ID of the surviving process is 
    changed to be 1 (the process ID of init). This way, we're guaranteed that every -
    process has a parent.
    
when a child terminates before its parent. 
    The kernel keeps a small amount of information for every terminating process , so 
    that the information is available when the parent of the terminating process cal-
    ls @wait or @waitpid. Minimally, this information consists of the process ID, the
    termination status of the process, and the amount of CPU time taken by the proce-
    ss. The kernel can discard all  the memory used by the process and close its open 
    files. In UNIX System terminology,a process that has terminated, but whose parent 
    has not yet waited for it, is called a zombie. The ps(1) command prints the state 
    of a zombie process as Z. 
    
What happens when a process that has been inherited by init terminates
    init is written so that whenever one of its children terminates,init calls one of 
    the wait functions to fetch the termination status.  By doing this, init prevents 
    the system from being clogged by zombies. When we say "one of init's children," -
    we mean either a process that init generates directly(such as getty) or a process 
    whose parent has terminated and has been subsequently inherited by init

Process Identifiers
    Every process has a unique process ID, a non-negative integer . Most UNIX systems 
    implement algorithms to delay reuse, however, so that newly created processes are 
    assigned IDs different from those used by processes that terminated recently.

    There are some special processes, but the details differ from implementation to -
    implementation. Process ID  0 is usually the scheduler process and is often known 
    as the swapper. No program on disk corresponds to this process , which is part of 
    the kernel and is known as a system process. Process ID 1 is usually the init pr-
    ocess and is invoked by the kernel at the end of the bootstrap procedure. The pr-
    ogram file for this process was /etc/init in older versions of the UNIX System a-
    nd is /sbin/init in newer versions. This process is responsible for bringing up a 
    UNIX system after the kernel has been bootstrapped. init usually reads the system
    -dependent initialization files (the /etc/rc* files or /etc/inittab and the files 
    in /etc/init.d) and brings the system to a certain state , such as multiuser. The 
    init process never dies. It is a normal user process, not a system process within 
    the kernel, like the swapper, although it does run with superuser privileges.

    Each UNIX System implementation has  its own set of kernel processes that provide
    operating system services. For example, on some virtual memory implementations of
    the UNIX System, process ID  2 is the pagedaemon. This process is responsible for
    supporting the paging of the virtual memory system.


---->�����˳�
�����������쳣��ֹʱ���ں˾����丸���̷���SIGCHLD�ź�(�첽�źţ�Ĭ�Ϻ���)��

---->��������(race conditions) 
a race condition occurs when multiple processes are trying to do something with 
shared data and the final outcome depends on the order in which the processes run. 

----> ����״̬
zombie
    The purpose of the zombie state is to maintain information about the child 
    for the parent to fetch at some later time. This information includes the 
    process ID of the child, its termination status, and information on the 
    resource utilization of the child (CPU time, memory, etc.). If a process 
    terminates, and that process has children in the zombie state, the parent 
    process ID of all the zombie children is set to 1 (the init process), which 
    will inherit the children and clean them up (i.e., init will wait for them, 
    which removes the zombie). Some Unix systems show the COMMAND column for a 
    zombie process as <defunct>.

    Obviously we do not want to leave zombies around. They take up space in the 
    kernel and eventually we can run out of processes. Whenever we fork children, 
    we must wait for them to prevent them from becoming zombies.


----> ����(zombie)���� �¶�����
unix�ṩ��һ�ֻ��ƿ��Ա�ֻ֤Ҫ��������֪���ӽ��̽���ʱ��״̬��Ϣ�� �Ϳ��Եõ���
���ֻ��ƾ���: ��ÿ�������˳���ʱ��,�ں��ͷŸý������е���Դ,�����򿪵��ļ�,ռ
�õ��ڴ�ȡ� ������ȻΪ�䱣��һ������Ϣ(�������̺�the process ID,�˳�״̬the 
termination status of the process,����ʱ��the amount of CPU time taken by the 
process��)��ֱ��������ͨ��wait / waitpid��ȡʱ���ͷš�

�¶����̣�һ���������˳���������һ�������ӽ��̻������У���ô��Щ�ӽ��̽���Ϊ
�¶����̡��¶����̽���init����(���̺�Ϊ1)������������init���̶��������״̬�ռ�
������

��ʬ���̣�һ������ʹ��fork�����ӽ��̣�����ӽ����˳����������̲�û�е���wait��
waitpid��ȡ�ӽ��̵�״̬��Ϣ����ô�ӽ��̵Ľ�����������Ȼ������ϵͳ�С����ֽ��̳�
֮Ϊ�������̡�


----> ������:
���������һЩ���̵����,���Ǳ˴�֮����ߴ��ڸ��ӡ��ֵܹ�ϵ�������ڹ��������������ϵ��
���̱ض�����һ�������飬Ҳֻ������һ�������顣 һ���������п��԰���������̡� ��������������ڴӱ�������ʼ�����������н�����ֹ���뿪���顣
----> �����������:
���������Ϊ�˷���Խ��̽��й�������Ҫ���һ��������Ҫͬʱ����100�����̡�
���û�����ĳ��ԭ��Ҫ��ֹ�������ʱ��Ҫ��û�н����飬����Ҫ�ֶ���һ����ȥɱ����100�����̣�
���ұ���Ҫ�ϸ��ս��̼丸���ֵܹ�ϵ˳�򣬷�������ҽ����������˽����飬
�Ϳ��Խ���100����������Ϊһ�������飬���ǹ���1����ţ�pgrp����
������ѡȡһ��������Ϊ�鳤��ͨ���ǡ����֡���ߵ��Ǹ���ͨ���ý��̵�IDҲ����Ϊ�������ID����
���ھͿ���ͨ��ɱ�����������飬���ر���100�����̣��������ϸ�����ġ�
----> �鳤����
�鳤���̱�ʶ: �������ID==�����ID
�鳤���̿��Դ���һ�������飬�����ý������еĽ��̣�Ȼ����ֹ
ֻҪ����������һ�����̴��ڣ�������ʹ��ڣ����鳤�����Ƿ���ֹ�޹�
������������: �����鴴�������һ�������뿪(��ֹ��ת�Ƶ���һ��������)
----> �Ự:
һ������������ļ���,��ʼ���û���¼,��ֹ���û��˳�.
����Linux�Ƕ��û�������ķ�ʱϵͳ�����Ա���Ҫ֧�ֶ���û�ͬʱʹ��һ������ϵͳ��
��һ���û���¼һ��ϵͳ���γ�һ�λỰ��ÿ���Ự����һ���Ự���죨leader�����������Ự�Ľ��̡�
һ���Ự�ɰ�����������飬��ֻ����һ��ǰ̨�����顣


gcc -static hello1.c                <---- prevent gcc from using shared libraries


