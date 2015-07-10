/*-----------------------------------------------------------------------------------
 Signal Concepts
    A signal is a notification to a process that an event has occurred. Signals are -
    sometimes called software interrupts. Signals usually occur asynchronously. 
 generate a signal
     By one process to another process (or to itself)
     By the kernel to a process
 disposition          
     1 Catch the signal
       To do this, we tell the kernel to call a function of ours whenever the  signal 
       occurs. In our function, we can do whatever we want to handle the condition.
     2 Ignore the signal     
       We can ignore a signal by setting its disposition to SIG_IGN. The two  signals 
       SIGKILL and SIGSTOP cannot be ignored. The reason these two signals can't be -
       ignored is to provide the kernel and the superuser with a surefire way of eit-
       her killing or stopping any process. 
     3 Let the default action apply. 
	  We can set the default disposition for a signal by setting its disposition to -
	  SIG_DFL. The default is normally to terminate a process on receipt of a signal, 
	  with certain signals also generating a core image of the process in its current 
	  working directory. There are a few signals whose default disposition is to be -
	  ignored: SIGCHLD and SIGURG (sent on the arrival of out-of-band data) are two -
	  that we will encounter in this text.

�źŲ���������:
  1 ĳЩ�ض������������ն˲����źš�����Ctrl+Cͨ�������ж��ź�(SIGINT)
  2 Ӳ���쳣�����ź�
    These conditions are usually detected by the hardware,and the kernel is notified. 
    The kernel then generates the appropriate signal for the process that was running 
    at the time the condition occurred.For example,SIGSEGV is generated for a process 
    that executes an invalid memory reference.
  3 kill����
  4 �������
    Software conditions can generate signals when a process should be notified of various 
    events. These aren't hardware-generated conditions (as is the divideby-0 condition), 
    but software conditions. Examples are SIGURG (generated when out-of-band data arrives 
    over a network connection), SIGPIPE (generated when a process writes to a pipe that 
    has no reader), and SIGALRM (generated when an alarm clock set by the process expires).

Program Start-Up
    When a program is executed, the status of all signals is either default or ignore.
    Normally,all signals are set to their default action, unless the process that calls 
    exec is ignoring the signal. Specifically,the exec functions change the disposition 
    of any signals being caught to their default action and leave the status of all 
    other signals alone.(Naturally,asignal that is being caught by a process that calls 
    exec cannot be caught by the same function in the new program, since the address of 
    the signal catching function in the caller probably has no meaning in the new 
    program file that is executed.)

Process Creation
    When a process calls fork,the child inherits the parent's signal dispositions.Here,
    since the child starts off with a copy of the parent's memory image, the address of 
    a signal-catching function has meaning in the child.

һЩ����
  generated    ����
  delivered    �ݽ�
  pending      ����
  blocking     ����
  signal mask  �ź�����

  generated: 
  a signal is generated for a process (or sent to a process) when the event that causes 
  the signal occurs. The event could be a hardware exception (e.g., divide by 0), a 
  software condition (e.g., analarm timer expiring), a terminal-generated signal, or 
  a call to the kill function.When the signal is generated, the kernel usually sets a 
  flag of some form in the process table.

  delivered: 
  We say thata signal is delivered to a process when the action for a signal is taken.

  pending: 
  During the time between the generation of a signal and its delivery,the signal is said 
  to be pending.

  blocking:
  If a signal that is blocked is generated for a process, and if the action for that 
  signal is either the default action or to catch the signal, then the signal remains 
  pending for the process until the process either(a)unblocks the signal or(b)changes 
  the action to ignorethe signal.The system determines what to do with a blocked signal 
  when the signal is delivered, not when it's generated. This allows the process to 
  change the action for the signal before it's delivered. 
  ��ֹ����ֹ�źŵĵݽ�(delivery)��Ҳ����ʹ�������źŴ���pending״̬��

  signal mask: 
  Each process has a signal mask that defines the set of signals currently blocked from 
  delivery to that process. We can think of this mask as having one bit for each possible 
  signal.If the bit is on for a given signal,that signal is currently blocked.A process 
  can examine and change its current signal mask by calling @sigprocmask. Since it is 
  possible for the number of signals to exceed the number of bits in an integer,POSIX.1 
  defines a data type,called sigset_t,that holds a signal set.The signal mask,for example,
  is	stored in one of these	signal sets. 

�����ڼ䲻ֹ����һ�θ��źţ���δ���:
  POSIX.1 allows the system to deliver the signal either once or more than once.If the 
  system delivers the signal more than once, we say that the signals are queued. Most 
  UNIX systems,however,do not queue signals unless they support the real-time extensions 
  to POSIX.1. Instead, the UNIX kernel simply delivers the signal once.

ͬʱ��������źţ���δ���:
  POSIX.1 does not specify the order in which the signals are delivered to the process.
  The Rationale for POSIX.1 does suggest, however,that signals related to the current 
  state of the process be delivered before other signals. (SIGSEGV is one such signal.)

 ----> POSIX Signal Semantics
 We summarize the following points about signal handling on a POSIX-compliant system:
 1 Once a signal handler is installed, it remains installed. (Older systems removed -
   the signal handler each time it was executed.)
 2 While a signal handler is executing, the signal being delivered is blocked. Furth-
   ermore, any additional signals that were specified in the sa_mask signal set pass-
   ed to sigaction when the handler was installed are also blocked. 
 3 If a signal is generated one or more times while it is blocked, it is normally de-
   livered only one time after the signal is unblocked. That is, by default, Unix si-
   gnals are not queued. The POSIX real-time standard, 1003.1b, defines some reliable 
   signals that are queued.
 4 It is possible to selectively block and unblock a set of signals using the       -
   sigprocmask function. This lets us protect a critical region of code by preventing 
   certain signals from being caught while that region of code is executing.
*/
/******************************************************************************/

/************************************************************************************
 ��������ź�����ҵ�����ź�
 Except for SIGCHLD,most application programs don't handle these signals

 There are some interactions between the job-control signals. When any of the four
 stop  signals (SIGTSTP, SIGSTOP, SIGTTIN,or SIGTTOU) is generated for a process,
 any pending SIGCONT signal for that process is discarded. Similarly,when the
 SIGCONT signal is generated for a process, any pending stop signals for that same
 process are discarded.
 Note that the default action for SIGCON Tis to continue the process, if it is stopped;
 otherwise, the signal is ignored. Normally, we don't have to do anything with this
 signal. When SIGCONT is generated for a process that is stopped, the process is
 continued, even if the signal is blocked or ignored.

 SIGCHLD 
     Child process has stopped or terminated. sent by the kernel whenever a process -
     terminates, to the parent of the terminating process.
 SIGHUP
    This signal is sent to the controlling process (session leader) associated with 
    a controlling terminal if a disconnect is detected by the terminal interface.
 SIGIO
    This signal indicates an asynchronous I/O event.The default depends on the system. 
    Under System V,SIGIO is identical to SIGPOLL,so its default action is to terminate 
    the process.Under BSD, the default is to ignore the signal.Linux 3.2.0 and Solaris 
    10 define SIGIO  to be  the same value as  SIGPOLL, so the default  behavior is to 
    terminate the process. On FreeBSD 8.0 and Mac OS X 10.6.8,the default is to ignore 
    the signal.

 
 ***********************************************************************************/

#define SIGABRT /*This signal is generated by calling the abort function. The process 
terminates abnormally.*/
#define SIGCHLD
#define SIGCONT /*Continue process, if stopped.When we tell the shell to resume 
a job in the foreground or background, the shell sends all the processes in the 
job the SIGCONT signal.*/

#define SIGSTOP /*Stop signal (can't be caught or ignored).*/
#define SIGTSTP /*Interactive stop signal. ����������ַ�(ͨ����ctrl+z)ʱ�ź�
���͵�ǰ̨����������н���*/
#define SIGTTIN /*Read from controlling terminal by background process group member.*/
#define SIGTTOU /*Write to controlling terminal by a background process group member.
if SIGTTIN or SIGTTOU is delivered to a process, the process is stopped by default, and
the job-control shell recognizes this and notifies us.*/
#define SIGHUP 
#define SIGINT /*This signal is generated by the terminal driver when we press 
the interrupt key (often DELETE or Control-C). This signal is  sent to all processes 
in the foreground process group. This signal is often used to terminate a runaway
program, especially when it's generating a lot of unwanted output on the screen.*/
#define SIGIO 
#define SIGUSR1 /*This is a user-defined signal, for use in application programs.*/
#define SIGUSR2 /*This is another user-defined signal,similar to SIGUSR1,for use 
in application programs.*/
#define SIGBUS /*This signal indicates an implementation-defined  hardware fault.
Implementations usually generate this signal on certain types of memory faults
�������ӳ������ĳ������,���ڷ���ʱ��һ����ʵ�����Ѿ������ڣ������SIGBUS�ź�*/
#define SIGSEGV /*the process has made an invalid memory reference (which is 
usually a sign that the program has a bug, such as dereferencing an uninitialized 
pointer).The name SEGV stands for "segmentation violation."*/

#define SIGPIPE /*If we write to a pipeline but the reader has terminated,SIGPIPE 
is generated.This signal is also generated when a process writes to a socket of 
type SOCK_STREAM that is no longer connected.*/

#define SIGTERM /*This is the termination signal sent by the kill(1) command by 
default.Because it can be caught by applications, using SIGTERM gives programs
a chance to terminate gracefully by cleaning up before exiting  (in contrast to 
SIGKILL,which can't be caught or ignored).*/

