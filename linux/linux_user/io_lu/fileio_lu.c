
#include <fcntl.h>
/*******************************************************************************
 @path: 
    Ҫ�򿪻򴴽��ļ�������
 @oflag: O_RDWR
 @mode:  S_IEXEC
    ����ʱ�Ż��õ�������ָ���ļ��ķ���Ȩ��λ��access permission bits��
 @function:
    ��һ���ļ�(Ҳ�����ڴ����ļ�)
 @return: 
    file descriptor if OK,-1 on error

 1 open���ص��ļ�������һ������С��δ����������ֵ��
 2 @path�ļ�������ַ������� NAME_MAX
*******************************************************************************/
int open(const char *path,int oflag,... /* mode_t mode*/ );
int openat(int fd,const char *path,int oflag,... /* mode_tmode*/ );

/*******************************************************************************
Returns: file descriptor opened for write-only if OK,-1 on error

1 Note that this function is equivalent to open(path,O_WRONLY | O_CREAT | O_TRUNC,mode);
2 One deficiency with creat is that the file is opened only for writing. 
*******************************************************************************/
int creat(const char *path,mode_t mode);

#include <unistd.h>
/*******************************************************************************
function: An open file is closed by calling the close function.
Returns : 0 if OK,-1 on error

1 When a process terminates, all of its open files are closed automatically by 
  the kernel.  
*******************************************************************************/
int close(int fd);

#include <unistd.h>
#define SEEK_SET (0)
#define SEEK_CUR (1)
#define SEEK_END (2)
/******************************************************************************
@fd    :
@offset:
@whence:
SEEK_SET(0),the file's offset is set to @offset bytes from the beginning of the file.
SEEK_CUR(1),the file's offset is set to its current value plus the @offset. The @offset can be positive or negative.
SEEK_END(2),the file's offset is set to the size of the file plus the @offset. The @offset can be positive or negative.
function: ��һ���ļ���������ƫ����
returns : new file offset if OK,-1 on error
name    : lseek�е�l��ʾ������

@lseek only records the current file offset within the kernel��it does not cause
any I/O to take place. This offset is then used by the next read or write operation.
*******************************************************************************/
off_t lseek(int fd,off_t offset,int whence);

#include <unistd.h>
/******************************************************************************
@fd :���ĸ��ļ�(�Ѿ�����)
@buf:�Ѷ������ݷ������buf��
@nbytes:ϣ����ȡ���ݵĳ���

function:Data is read from an open file with the @read function.
Returns: number of bytes read, 0 if end of file,-1 on error

1 ����count�������ȡ���ֽ����������������ݱ����ڻ�����buf�У�ͬʱ�ļ��ĵ�ǰ��
  дλ������ơ�
2 �������ļ�ʱ���ڶ���count���ֽ�֮ǰ�ѵ����ļ�ĩβ�����磬���ļ�ĩβ����30����
  �ڶ������100���ֽڣ���read����30���´�read������0��
3 �����ı����׽��ֶ�������,һ��read���ܱ�֤����������һ�л�����,��������һ�п�
  ����Ҫ�Դ˵���read,����������Ƿ�����˻��з�
4 �������յ�FINʱ,����һ��EOF�����������е�read,�յ���read����EOF
5 POSIX.1 requires that read return -1 with errno set to EAGAIN if there is no 
  data to read from a nonblocking descriptor. 
******************************************************************************/
ssize_t read(int fd,void *buf,size_t nbytes);

/******************************************************************************
 @fd    : д�ĸ��ļ�(�Ѿ�����)
 @buf   : buf����Ҫд������
 @nbytes: д�����ݵĳ���
 funtion: Data is written to an open file with the @write function.
 Returns: number of bytes written if OK,-1 on error

 For a regular file, the write operation starts at the file's current offset. If 
 the O_APPEND option was specified when the file was opened, the file's offset 
 is set to the current end of file before each write operation. After a successful
 write, the file's offset is incremented by the number of bytes actually written.

 It is okay to write to a socket that has received a FIN, but it is an error to 
 write to a socket that has received an RST.

 What happens if the client ignores the error return from read and writes more 
 data to the server? This can happen, for example, if the client needs to perform 
 two writes to the server before reading anything back, with the first write 
 eliciting the RST.
 
 When a process writes to a socket that has received an RST, the SIGPIPE signal 
 is sent to the process. The default action of this signal is to terminate the 
 process, so the process must catch the signal to avoid being involuntarily 
 terminated.If the process either catches the signal and returns from the signal 
 handler, or ignores the signal, the write operation returns EPIPE.
 *****************************************************************************/
ssize_t write(int fd,const void *buf,size_t nbytes);

#include <unistd.h>
/******************************************************************************
@fd    ��Ҫ��ȡ���ݵ��ļ�������
@buf   �����ݻ�����ָ�룬��Ŷ�ȡ����������
@count ����ȡ���ݵ��ֽ���
@offset����ȡ����ʼ��ַ��ƫ��������ȡ��ַ=�ļ���ʼ+offset��
����ֵ���ɹ������سɹ���ȡ���ݵ��ֽ�����ʧ�ܣ�����-1��

1 ִ�к��ļ�ƫ��ָ�벻��
2 �൱��˳�����lseek��read,���䶨λ�Ͷ�ȡ������ԭ�ӵġ�lseek��read֮��������ж�
  ����������⡣
******************************************************************************/
ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);

/*******************************************************************************
@fd    ��Ҫд�����ݵ��ļ�������
@buf   �����ݻ�����ָ�룬���Ҫд���ļ��е�����
@count ��д���ļ��е����ݵ��ֽ���
@offset��д���ַ=�ļ���ʼ+offset
����ֵ ���ɹ�������д�뵽�ļ��е��ֽ�����ʧ�ܣ�����-1��

1 ִ�к��ļ�ƫ��ָ�벻��
2 �൱��˳�����lseek��write,���䶨λ�Ͷ�ȡ������ԭ�ӵġ�lseek��read֮�������
  �жϿ���������⡣
******************************************************************************/
ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);



#include <unistd.h>
/*
 dup��dup2Ҳ�������ǳ����õĵ��ã����ǵ����ö�����������һ���ļ��������������Ǿ�������
 �ض�����̵�stdin��stdout��stderr��

*/
/************************************************************************************
 ����ֵ:
    �ɹ������µ�������,ʧ�ܷ���-1
 ����:
    �����ļ�������@fd�����ú���һ�����е������������ͻ᷵��һ���µ�������������µ���
    �����Ǵ��������������Ŀ���������ζ�ţ�����������������ͬһ��"�ļ���"��

 1 @dup���ص���������һ���ǵ�ǰ�����ļ��������е���С��ֵ
 2 ����������@fd����һ���ļ�����(file table entry)
 3 ����������ִ��ʱ�ر�(close-on-exec)��־������@dup�������
************************************************************************************/
int dup(int fd);

/************************************************************************************
 ����ֵ:
    �ɹ������µ�������,ʧ�ܷ���-1
 ����:
    �����ļ�������@fd,@fd2��ָ������������.dup2������dup�������ƣ���dup2�����������
    �߹涨һ����Ч��������Ŀ����������id��dup2�����ɹ�����ʱ��Ŀ����������dup2������
    �ڶ��������������Դ��������dup2�����ĵ�һ���������ĸ���Ʒ�����仰˵�������ļ���
    �������ڶ�ָ��ͬһ���ļ��������Ǻ�����һ������ָ����ļ���

 1 ���@fd2�Ѿ��򿪣����ȹرա�
 2 ���@fd==@fd2�����ر�@fd2��ֱ�ӷ���@fd2
 3 ����������@fd����һ���ļ�����(file table entry)
************************************************************************************/
int dup2(int fd,int fd2);
/*
Indeed, the call
dup(fd);
is equivalent to
fcntl(fd, F_DUPFD, 0);
Similarly, the call
dup2(fd, fd2);
is equivalent to
close(fd2);
fcntl(fd, F_DUPFD, fd2);
In this last case, the dup2 is not exactly the same as a close followed by an fcntl.
The differences are as follows:
1. dup2 is an atomic operation, whereas the alternate form involves two function
calls. It is possible in the latter case to have a signal catcher called between the
close and the fcntl that could modify the file descriptors. The same problem could 
occur if a different thread changes the file descriptors. 
2. There are some errno differences between dup2 and fcntl.*/

/******************************************************************************** 
  Traditional implementations of the UNIX System have a buffer cache or page 
cache in the kernel through which most disk I/O passes. When we write data to 
a file, the data is normally copied by the kernel into one of its buffers and 
queued for writing to disk at some later time. This is called delayed write. 
  The kernel eventually writes all the delayed-write blocks to disk, normally 
when it needs to reuse the buffer for some other disk block. To ensure consistency 
of the file system on disk with the contents of the buffer cache, the sync, 
fsync, and fdatasync functions are provided.

  The @sync function simply queues all the modified block buffers for writing and 
returns; it does not wait for the disk writes to take place.
  The function @sync is normally called periodically (usually every 30 seconds) 
from a system daemon, often called update.This guarantees regular flushing of 
the kernel's block buffers. The command sync(1) also calls the sync function.
  The function @fsync refers only to a single file, specified by the file descriptor
@fd, and waits for the disk writes to complete before returning. This function 
is used when an application, such as a database, needs to be sure that the modified 
blocks have been written to the disk.
  The @fdatasync function is similar to @fsync,but it affects only the data portions 
of a file. With @fsync,the file's attributes are also updated synchronously.

  Returns: 0 if OK,-1 on errors
*********************************************************************************/
#include <unistd.h>
int fsync(int fd);
int fdatasync(int fd);
void sync(void);

/*-----------------------------------------------------------------------------------
 @cmd: F_SETFL
    The @fcntl function is used for five different purposes.
    1 Duplicate an existing descriptor (cmd=F_DUPFD or F_DUPFD_CLOEXEC)
    2 Get/set file descriptor flags (cmd=F_GETFD or F_SETFD)
    3 Get/set file status flags (cmd=F_GETFL or F_SETFL)
    4 Get/set asynchronous I/O ownership (cmd=F_GETOWN or F_SETOWN)
    5 Get/setrecordlocks (cmd=F_GETLK,F_SETLK,or F_SETLKW)
 @fun:
   The @fcntl function can change the properties of a file that is already open.
@ret: 
   depends on @cmd if OK (see following),-1 on error
   The return value from @fcntl depends on the command. All commands return -1 on 
   an error or some other value if OK. The following four commands have special
   return values: F_DUPFD, F_GETFD, F_GETFL, and F_GETOWN. The first command returns 
   the new file descriptor, the next two return the corresponding flags, and the 
   final command returns a positive process ID or a negative process group ID.
-----------------------------------------------------------------------------------*/
#include <fcntl.h>
int fcntl(int fd,int cmd,... /* int arg */ );

/******************************************************************************\
                                 ��¼��
\******************************************************************************/

#define F_RDLCK /*a shared read lock*/
#define F_WRLCK /*an exclusive write lock*/
#define F_UNLCK /*unlocking a region*/


/*******************************************************************************
 The type of lock desired:F_RDLCK(a shared read lock),F_WRLCK(an exclusive write 
 lock), or F_UNLCK(unlocking a region)
 The starting byte offset of the region being locked or unlocked (l_start and
 l_whence)
 The size of the region in bytes (l_len)
 The ID (l_pid) of the  process	holding the lock that can block the current 
 process (returned by F_GETLK only)

 l_start:The two elements that specify the starting offset of the region aresimilar 
         to the last two arguments of the @lseek function.Locks can start and 
         extend beyond the current end of file, but cannot start or extend before 
         the beginning of the file.
 l_len  :If @l_len is 0, it means that the lock extends to the largest possible 
         offset of the file. This allows us to lock a region starting anywhere 
         in the file, up through and including any data that is appended to the 
         file. (We don't have to try to guess how many bytes might be appended 
         to the file.)
 To lock the entire file, we set @l_start and @l_whence to point to the beginning
 of the file and specify a length (l_len) of 0.(There are several ways to specify
 the beginning of the file, but most applications specify @l_start as 0 and
 @l_whence as SEEK_SET.)

 ---->ʹ�ù���
  We previously mentioned two types of locks: a shared read lock (l_type of
F_RDLCK) and an exclusive write lock (F_WRLCK). The basic rule is that any number 
of processes can have a shared read lock on a given byte, but only one process 
can have an exclusive write lock on a given byte. Furthermore, if there are one 
or more read locks on a byte, there can't be any write locks on that byte; if 
there is an exclusive write lock on a byte, there can��t be any read locks on 
that byte. 

---->����������ǿ������ Advisory versus Mandatory Locking
 ******************************************************************************/
struct flock 
{
    short l_type; /* F_RDLCK, F_WRLCK, or F_UNLCK */
    short l_whence; /* SEEK_SET, SEEK_CUR, or SEEK_END */
    off_t l_start; /* offset in bytes, relative to l_whence */
    off_t l_len; /* length, in bytes; 0 means lock to EOF */
    pid_t l_pid; /* returned with F_GETLK */
};

#define F_GETLK /*Determine whether the lock described by @flockptr is blocked
by some other lock. If a lock exists that would prevent ours from being created, 
the information on that existing lock overwrites the information pointed to by
@flockptr.If no lock exists that would prevent ours from being created, the
structure pointed to by @flockptr is left unchanged except for the l_type member,
which is set to F_UNLCK.*/
#define F_SETLK /*Set the lock described by @flockptr.If we are trying to obtain
a read lock(l_typeof F_RDLCK) or a write lock (l_typeof F_WRLCK) and the 
compatibility rule prevents the system from giving us the lock , @fcntl returns 
immediately with errno set to either EACCES or EAGAIN. This command is also used 
to clear the lock described by @flockptr(l_typeof F_UNLCK).*/
#define F_SETLKW /*This command is a blocking version of F_SETLK.(The W in the 
command name means wait.) If the requested read lock or write lock cannot be 
granted because another process currently has some part of the requested region  
locked, the calling process is put to sleep.The process wakes up either when the 
lock becomes available or when interrupted by a signal.*/

/*******************************************************************************
���ļ̳����ͷ�
1 when a process terminates, all its locks are released. whenever a descriptor is 
  closed, any locks on the file referenced by that descriptor for that process are 
  released. This means that if we make the calls
		fd1 = open(pathname, ...);
		read_lock(fd1, ...);
		fd2 = dup(fd1);
		close(fd2);
  after the close(fd2),the lock that was obtained on fd1 is released. The same 
  thing would happen if we replaced the dup with open, as in
		fd1 = open(pathname, ...);
		read_lock(fd1, ...);
		fd2 = open(pathname, ...)
		close(fd2);
  to open the same file on another descriptor.
 
2 Locks are never inherited by the child across a fork.This means that if a process
  obtains a lock and then calls fork,the child is considered another process with
  regard to the lock that was obtained by the parent. The child has to call @fcntl 
  to obtain its own locks on any descriptors that were inherited across the fork.
  This constraint makes sense because locks are meant to prevent multiple processes 
  from writing to the same file at the same time. If the child inherited locks 
  across a fork, both the parent and the child could write to the same file at 
  the same time.
3 Locks are inherited by a new program across an exec.Note, however,that if the
  close-on-exec flag is set for a file descriptor,all locks for the underlying 
  file are released when the descriptor is closed as part of an exec.
 ******************************************************************************/



#include <sys/select.h>
#include <sys/time.h>

#define FD_SETSIZE  /*@select�ĵ�һ������������������������ͨ����1024*/

struct timeval	
{
  long	 tv_sec;  /* seconds */
  long	 tv_usec; /* microseconds */
};

/*******************************************************************************
 @maxfdp1: ����������+1
 @readset: ����������������ΪNULL
 @readset: д��������������ΪNULL
 @readset: �쳣��������������ΪNULL
 @timeout: �ȴ�ʱ��
 function: 
    �����ں�
    1 ���ĵ�������
    2 ��������������Щ״̬�������Ƿ�ɶ����Ƿ��д�����������쳣״̬
    3 �ȴ�ʱ��
    ��select�����ں˸�������
    1 �Ѿ�׼���õ�����������
    2 ���ڶ���д���쳣������״̬�е�ÿһ������Щ�������Ѿ�׼���á�
      ʹ����Щ������Ϣ�Ϳ��Ե�����Ӧ��I/O��������ȷ��֪��������������
 Returns: 
    positive count of ready descriptors, 0 on timeout, �C1 on error
    
 There are three possible return values from @select.
 1 return -1 means that an error occurred. This can happen, for example, if a 
   signal is caught before any of the specified descriptors are ready.In this 
   case, none of the descriptor sets will be modified.
 2 return 0 means that no descriptors are ready.This happens if the time limit 
   expires before any of the descriptors are ready.When this happens,all the 
   descriptor sets will be zeroed out.
 3 A positive return value specifies the number of descriptors that are ready.
   This value is the sum of the descriptors ready in all three sets, so if the 
   same descriptor is ready to be read and written, it will be counted twice in 
   the return value. The only bits left on in the three descriptor sets are the 
   bits corresponding to the descriptors that are ready.
 ---->�ȴ���ʱ��
 1 ��Զ�ȴ�  timeout == NULL
 2 �ȴ�ָ����ʱ�� �����ʱ����timeoutָ��
 3 ���ȴ�  timeout�е�ʱ��Ϊ0
 The wait in the first two scenarios is normally interrupted if the process 
 catches a signal and returns from the signal handler.

 If we encounter the end of file on a descriptor, that descriptor is considered 
 readable by @select. We then call read and it returns 0��the way to signify end 
 of file on UNIX systems. 
 ---->׼����
 1 ���ڶ����������е�һ����������read���������������������������׼���õ�
 2 ����д���������е�һ����������write���������������������������׼���õ�
 3 ���쳣���������е�һ����������һ��δ���쳣״̬�������������׼���õġ�
   �쳣״̬����
   a �����������ϵ���Ĵ�������
   b �������ݰ�ģʽ��α�ն��Ϸ�����ĳЩ״̬��
 4 File descriptors for regular files always return ready for reading, writing, 
   and exception conditions.
 *******************************************************************************/
int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, 
const struct timeval *timeout);

#include <sys/select.h>
/*******************************************************************************
 @select uses descriptor sets, typically an array of integers, with each bit in 
 each integer corresponding to a descriptor. For example, using 32-bit integers, 
 the first element of the array corresponds to descriptors 0 through 31, the 
 second element of the array corresponds to descriptors 32 through 63, and so on. 
 All the implementation details are irrelevant to the application and are hidden 
 in the fd_set datatype and the following four macros:
 ******************************************************************************/
int  FD_ISSET(int fd,fd_set *fdset);
void FD_CLR(int fd,fd_set *fdset);
void FD_SET(int fd,fd_set *fdset);
void FD_ZERO(fd_set *fdset); 

/*******************************************************************************
 After declaring a descriptor set, we must zero the set using FD_ZERO.Wethen set
 bits in the set for each descriptor that we��reinterested in, as in
 ******************************************************************************/
void fd_set_example()
{
	fd_set	rset;
	int  fd;
	
	FD_ZERO(&rset); 		 /* initialize the set: all bits off */
	FD_SET(1, &rset);		 /* turn on bit for fd 1 */
	FD_SET(4, &rset);		 /* turn on bit for fd 4 */
	FD_SET(5, &rset);		 /* turn on bit for fd 5 */
	FD_SET(STDIN_FILENO, &rset);

	if (FD_ISSET(fd, &rset)) {
	}
}

#include <sys/select.h>
#include <signal.h>
#include <time.h>
 
struct timespec {
  time_t tv_sec;       /* seconds */
  long   tv_nsec;      /* nanoseconds ���� */
};

/*******************************************************************************
 When @pselect is called, it replaces the signal mask of the process with an 
 @sigmask set (i.e., zeromask) and then checks the descriptors, possibly going 
 to sleep. But when @pselect returns, the signal mask of the process is reset 
 to its value before @pselect was called (i.e., SIGINT is blocked).

 Returns: count of ready descriptors, 0 on timeout,-1 on error
 ******************************************************************************/
int pselect(int maxfdp1,fd_set *restrict readfds,fd_set *restrict writefds,fd_set *restrict exceptfds,
const struct timespec *restrict tsptr,const sigset_t *restrict sigmask);



#include <poll.h>

/********** Input events and returned revents for poll ***********/
#define POLLIN       /*��ͨ�����ȼ������ݿɶ� */
#define POLLRDNORM   /*��ͨ���ݿɶ�*/
#define POLLRDBAND   /*���ȼ������ݿɶ�*/
#define POLLPRI      /*�����ȼ����ݿɶ�*/

#define POLLOUT      /*��ͨ���ݿ�д*/
#define POLLWRNORM   /*��ͨ���ݿ�д*/
#define POLLWRBAND   /*���ȼ������ݿ�д*/

#define POLLERR      /*�������󣬲�����Ϊ@events*/
#define POLLHUP      /*�������𣬲�����Ϊ@events*/
#define POLLNVAL     /*�����ֲ���һ���򿪵��ļ���������Ϊ@events*/

#define INFTIM       /*��һ����ֵ @poll�ĵ���������,��ʾ��Զ�ȴ�*/

/*******************************************************************************
 To tell the kernel which events we're interested in for each descriptor, we have
 to set the @events member of each array element to one or more of the values in 
 Figure 14.17. On return, the @revents member is set by the kernel, thereby 
 specifying which events have occurred for each descriptor. 
 ******************************************************************************/
struct pollfd 
{
    int  fd; /* file descriptor to check, or <0 to ignore */
    short  events; /* events of interest on fd POLLIN��ֵ*/
    short  revents;  /* events that occurred on fd */
};

/************************************************************************************
 @fdarray: 
    a pointer to the first element of an array of structures.Each element of the array 
    is a pollfd structure that specifies the conditions to be tested for a given 
    descriptor, fd.
 @nfds   : 
    The number of elements in the array of structures is specified by the nfds argument.
 
 @timeout: INFTIM��Զ�ȴ� 0���ȴ� ����0�ȴ�ָ����ʱ��
 @returns: 
    The return value from @poll is �C1 if an error occurred, 0 if no descriptors are 
    ready before the timer expires,otherwise it is the number of descriptors that have 
    a nonzero @revents member.

 With regard to TCP and UDP sockets, the following conditions cause @poll to return 
 the specified revent. Unfortunately, POSIX leaves many holes (i.e., optional ways 
 to return the same condition) in its definition of poll.
 1 All regular TCP data and all UDP data is considered normal.
 2 TCP's out-of-band data is considered priority band.
 3 When the read half of a TCP connection is closed (e.g., a FIN is received), this 
   is also considered normal data and a subsequent read operation will return 0.
 4 The presence of an error for a TCP connection can be considered either normal data 
   or an error (POLLERR). In either case, a subsequent read will return �C1 with errno 
   set to the appropriate value. This handles conditions such as the receipt of an RST 
   or a timeout.
 5 The availability of a new connection on a listening socket can be considered either 
   normal data or priority data. Most implementations consider this normal data.
 6 The completion of a nonblocking connect is considered to make a socket writable.
************************************************************************************/
int poll(struct pollfd fdarray[], nfds_t nfds,int timeout);



#include <sys/epoll.h> 


/*-----------------------------------------------------------------------------------
 epoll is a Linux kernel system call,a scalable I/O event notification mechanism,first 
 introduced in Linux kernel 2.5.44. It is meant to replace the older POSIX select(2) 
 and poll(2) system calls,to achieve better performance in more demanding applications, 
 where the number of watched file descriptors is large (unlike the older system calls, 
 which operate in O(n) time, epoll operates in O(1) time).epoll is similar to FreeBSD's 
 kqueue, in that it operates on a configurable kernel object, exposed to user space as 
 a file descriptor of its own.

 EPOLL�¼�������ģ�� Level Triggered (LT) �� Edge Triggered (ET)��

 LT(level triggered��ˮƽ����ģʽ)
    ��ȱʡ�Ĺ�����ʽ������ͬʱ֧�� block �� non-block socket�������������У��ں˸�����
    һ���ļ��������Ƿ�����ˣ�Ȼ������Զ����������fd����IO����������㲻���κβ�����
    �ں˻��ǻ����֪ͨ��ģ����ԣ�����ģʽ��̳����������ҪСһ�㡣

 ET(edge-triggered����Ե����ģʽ)
    �Ǹ��ٹ�����ʽ��ֻ֧��no-block socket��������ģʽ�£�����������δ������Ϊ����ʱ��
    �ں�ͨ��epoll�����㡣Ȼ�����������֪���ļ��������Ѿ����������Ҳ�����Ϊ�Ǹ��ļ�
    ���������͸���ľ���֪ͨ���ȵ��´����µ����ݽ�����ʱ��Ż��ٴγ��������¼��� 
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 @size:
    The @size argument specifies the number of file descriptors that we expect to mo-
    nitor via the epoll instance. This argument is not an upper limit, but rather a -
    hint to the kernel about how to initially dimension internal data structures. Si-
    nce  Linux 2.6.8, the size argument is unused.
 @flags: 0 or EPOLL_CLOEXEC
    If flags is 0,then,other than the fact that the obsolete size argument is dropped, 
    epoll_create1() is the same as epoll_create().The following value can be included 
    in flags to obtain different behavior:EPOLL_CLOEXEC
 @func
    The epoll_create() system call creates a new epoll instance whose interest list -
    is initially empty.
 @ret
    Returns file descriptor on success, or �C1 on error

 As its function result,epoll_create() returns a file descriptor referring to the new
 epoll instance. This file descriptor is used to refer to the epoll instance in other 
 epoll system calls. When the file descriptor is no longer required, it should be cl-
 osed in the usual way, using close(). When all file descriptors referring to an epo-
 ll instance are closed, the instance is destroyed and its associated resources are -
 released back to the system. ( Multiple file descriptors may refer to the same epoll 
 instance as a consequence of calls to fork() or descriptor duplication using dup() -
 or similar.)

 Starting with kernel 2.6.27, Linux supports a new system call, epoll_create1(). Thi-
 s system call performs the same task as epoll_create(), but drops the obsolete @size 
 argument and adds a @flags argument that can be used to modify the behavior of the -
 system call. One flag is currently supported: EPOLL_CLOEXEC, which causes the kernel 
 to enable the close-on-exec flag (FD_CLOEXEC) for the new file descriptor. This flag 
 is useful for the same reasons as the open() O_CLOEXEC flag. 
-----------------------------------------------------------------------------------*/
int epoll_create(int size);
int epoll_create1(int flags);


/*-----------------------------------------------------------------------------------
 @epfd: 
 @op    EPOLL_CTL_ADD
    The @op argument specifies the operation to be performed
 @fd    
    The @fd argument identifies which of the file descriptors in the interest list is 
    to have its settings modified.  This argument can be a file descriptor for a pipe, 
    FIFO, socket, POSIX message queue, inotify instance, terminal, device, or even a-
    nother epoll descriptor (i.e., we can build a kind of hierarchy of monitored des-
    criptors). However, @fd can't be a file descriptor for a regular file or a direc-
    tory (the error EPERM results).
 @event 
 @func
    The epoll_ctl() system call modifies the interest list of the epoll instance ref-
    erred to by the file descriptor @epfd.
 @ret
    Returns 0 on success, or �C1 on error
-----------------------------------------------------------------------------------*/
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *ev);

/* Using epoll_create() and epoll_ctl() */
void epoll_eg01(int fd)
{
    int epfd;
    struct epoll_event ev;
    epfd = epoll_create(5);
    if (epfd == -1)
        errExit("epoll_create");
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, ev) == -1)
        errExit("epoll_ctl");
}


/*-----------------------------------------------------------------------------------
 @evlist @maxevents
    The information about ready file descriptors is returned in the array of epoll_event
    structures pointed to by @evlist. The @evlist array is allocated by the caller, -
    and the number of elements it contains is specified in @maxevents.
    Each item in the array @evlist returns information about a single ready file des-
    criptor. The  @events subfield returns a mask of the events that have occurred on
    this descriptor. The @data subfield returns whatever value was specified in ev.data
    when we registered interest in this file descriptor using  epoll_ctl(). Note that 
    the @data field provides the only mechanism for finding out the number of the fi-
    le descriptor associated with this event. Thus, when we make the epoll_ctl() call 
    that places a file descriptor in the interest list, we should either set ev.data.fd 
    to the file descriptor number or set ev.data.ptr to point to a structure that co-
    ntains the file descriptor number.
 @timeout
    If @timeout equals �C1, block until an event occurs for one of the file descript-
    ors in the interest list for @epfd or until a signal is caught.
    If @timeout equals 0, perform a nonblocking check to see which events are curren-
    tly available on the file descriptors in the interest list for @epfd.
    If timeout is greater than 0, block for up to @timeout milliseconds, until an ev-
    ent occurs on one of the file descriptors in the interest list for @epfd, or unt-
    il a signal is caught.
 @func
    The epoll_wait() system call returns information about ready file descriptors from
    the epoll instance referred to by the file descriptor @epfd. A single epoll_wait() 
    call can return information about multiple ready file descriptors.
 @ret
   	Returns number of ready file descriptors, 0 on timeout, or �C1 on error
-----------------------------------------------------------------------------------*/
int epoll_wait(int epfd, struct epoll_event *evlist, int maxevents, int timeout);


#include <sys/mman.h>
/* @mmmap @prot */
#define PROT_READ   /* Region can be read. */
#define PROT_WRITE  /* Region can be written. */
#define PROT_EXEC   /* Region can be executed. */
#define PROT_NONE   /* Region cannot be accessed. */
/* @mmmap @flag */
#define MAP_FIXED   /* ����ֵ�������@addr MAP_SHARED��MAP_PRIVATE����ָ��һ����������ͬʱָ����*/
#define MAP_SHARED	/* �洢�����൱�ڶԸ��ļ���write.*/
#define MAP_PRIVATE /* ��ӳ�����Ĵ洢�������´�����ӳ���ļ���һ��˽�и�����*/

/*-----------------------------------------------------------------------------------
 @addr:
    ӳ��洢������ʼ��ַ,0��ʾ��ϵͳ�Զ�ѡ��ҳ�߽����
 @len: 
    ӳ����ֽ���
 @prot:
    ӳ�����ı���Ҫ��(��λ��)
    PROT_READ Region can be read.
    PROT_WRITE Region can be written.
    PROT_EXEC Region can be executed.
    PROT_NONE Region cannot be accessed.
 @flag: MAP_FIXED
    Either the MAP_SHARED or the MAP_PRIVATE flag must be specified , optionally ORed 
    with  MAP_FIXED. If MAP_PRIVATE is specified, then modifications to the mapped d-
    ata by the calling process are visible only to that process and do not change the 
    underlying object (either a file object or a shared memory object). If MAP_SHARED 
    is specified, modifications to the mapped data by the calling process are visible  
    to all processes that are sharing the object, and these changes do modify the un-
    derlying object. 
 @fd:  
    ��ӳ���ļ���������,ӳ���ļ�ǰҪ�򿪸��ļ�
 @off: 
    Ҫӳ���ֽ����ļ��е���ʼƫ����
 @Returns: 
    starting address of mapped region if OK,MAP_FAILED on error

 One way to share memory between a parent and child is	to call map with MAP_SHARED 
 before calling fork. Posix.1 then guarantees that memory mappings in the parent are 
 retained in the child. Furthermore, changes made by the parent are visible to the c-
 hild and vice versa.

 After map returns success, the @fd argument can be closed. This has no effect on the 
 mapping that was established by @mmap. 

 Trying to map a descriptor that refers to a terminal or a socket, for example, gene-
 rates an error return from map. These types of  descriptors must be accessed using -
 read and write (or variants thereof ). 
 
 Another use of map is to provide shared memory between unrelated processes . In this 
 case, the actual contents of the file become the initial contents of the memory that 
 is shared, and any changes made by the processes to this shared memory are then cop-
 ied back to the file (providing filesystem persistence).This assumes that MAP_SHARED 
 is specified, which is required to share the memory between processes. 

 low memory      return value of @mmap        
 |                   |
\|/                 \|/
 +-----------------------------------------------+
 |                   |                 |         |       address space of process
 +-----------------------------------------------+
                     |                 |
                     |                 |
                    \|/               \|/
 +-------------------------------------------+
 |   @offset         |      @len       |     |      file referenced by descriptor @fd
 +-------------------------------------------+

 example: mmap_eg_sharemem()
-----------------------------------------------------------------------------------*/
void *mmap(void *addr,size_t len,int prot,int flag,int fd,off_t off);

/*-----------------------------------------------------------------------------------
 @function:
    To remove a mapping from the address space of the process, we call @munmap. 
 @Returns: 
    0 if OK,-1 on error

 A memory-mapped region is automatically unmapped when the process terminates or we -
 can unmap a region directly by calling the @munmap function. The @munmap function d-
 oes not affect the object that was mapped, that is, the call to @munmap does not ca-
 use the contents of the mapped region to be written to the disk file.The updating of 
 the disk file for a  MAP_SHARED region happens automatically by the kernel's virtual 
 memory algorithm sometime after we store into the memory-mapped region.Modifications 
 to memory in a MAP_PRIVATE region are discarded when the region is unmapped.
-----------------------------------------------------------------------------------*/
int munmap(void *addr,size_t len);

#define MS_ASYNC	   
#define MS_SYNC 
#define MS_INVALIDATE

/*-----------------------------------------------------------------------------------
 @addr @len
    The @addr and @len arguments normally refer to the entire memory-mapped region of  
    memory, although subsets of this region can also be specified. 
 @flags: MS_ASYNC	MS_SYNC 	MS_INVALIDATE
    One of the two constants MS_ASYNC and MS_SYNC must be specified, but not both.The 
    difference in these two is that MS_ASYNC returns once the write operations are q-
    ueued by the kernel , whereas MS_SYNC returns only after the write operations are 
    complete. If MS_INVALIDATE is also specified, all in-memory copies of the file d-
    ata that are inconsistent with the file data are invalidated. Subsequent referen-
    ces will obtain data from the file. 
 @Returns: 
    0 if OK,-1 on error		

 the kernel's virtual memory algorithm keeps the memory-mapped file (typically on di-
 sk) synchronized with the memory-mapped region in memory, assuming a MAP_SHARED seg-
 ment. That is, if we modify a location in memory that is memory-mapped to a file, t-
 hen at some time later the kernel will update the file accordingly. But sometimes, -
 we want to make certain  that the file on disk corresponds to what is in the memory-
 mapped region, and we call @msync to perform this synchronization. 
-----------------------------------------------------------------------------------*/
int msync(void *addr,size_t len,int flags);


/*-----------------------------------------------------------------------------------
function:We can change the permissions on an existing mapping by calling @mprotect
Returns: 0 if OK,-1 on error
-----------------------------------------------------------------------------------*/
int mprotect(void *addr,size_t len,int prot);




 

#include <sys/uio.h>

/************************************************************************************
 read()��write()ϵͳ����ÿ�����ļ��ͽ��̵ĵ�ַ�ռ�֮�䴫��һ�����������ݡ����ǣ�Ӧ����
 ʱҲ��Ҫ����ɢ���ڴ�ദ�ط�����������д���ļ��У����߷�֮������������£����Ҫ����
 ���ж�һƬ���������������̵Ĳ�ͬ����ʹ��read()��Ҫôһ�ν����Ƕ���һ���ϴ�Ļ�����
 �У�Ȼ�����Ƿֳ����ɲ��ָ��Ƶ���ͬ������Ҫô����read()���ɴη��������Ƕ�����ͬ��
 ��ͬ��������뽫�����в�ͬ��������ݿ�������д���ļ���Ҳ����������ƵĴ���

 UNIX�ṩ����������������readv()��writev()������ֻ��һ��ϵͳ���þͿ���ʵ�����ļ��ͽ���
 �Ķ��������֮�䴫�����ݣ�����˶��ϵͳ���û������ݵĿ�����readv()��Ϊɢ����������
 �ļ����������������ݿ�����ڴ��ɢ�Ļ������С�writev()��Ϊ�ۼ�д�����ռ��ڴ��з�ɢ��
 ���ɻ������е�����д���ļ������������С�

 ����@fildes���ļ������֡�@iov��һ���ṹ���飬����ÿ��Ԫ��ָ���洢���е�һ����������
 ����@iovcntָ������@iov��Ԫ�ظ�����Ԫ�ظ������಻����IOV_MAX��Linux�ж���IOV_MAX��ֵ
 Ϊ1024��

 readv()��fildesָ���ļ��е����ݰ�iov[0]��iov[1]��...��iov[iovcnt�C1]�涨��˳��ͳ�
 �ȣ���ɢ�ض�������ָ���Ĵ洢��ַ�С�readv()�ķ���ֵ�Ƕ�������ֽ��������û�����ݿ�
 �����������ļ�β���䷵��ֵΪ0��

 ��������������������Ҫ����д��ĳ������ʱ��ֻ����iov����ĸ���Ԫ�ذ��������и�������
 �ĵ�ַ���䳤�ȣ�Ȼ��iov������Ԫ�ظ�����Ϊ�������ݸ�writev()����Щ���ݱ��һ��д����
************************************************************************************/

/* return: number of bytes read or written, �C1 on error */ 
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);

/*@iov:�ṹ������ָ��
  return: number of bytes read or written, �C1 on error */
ssize_t writev(int filedes, const struct iovec *iov, int iovcnt);
 

/************************************************************************************
 @request
    We can divide the  requests  related to  networking  into six categories: Socket 
    operations; File operations; Interface operations; ARP cache operations; Routing 
    table operations; STREAMS system
 @third argument
    The  third argument is always  a pointer, but the type of pointer depends on the 
    request.
 
 @returns: -1 on error, something else if OK
 
************************************************************************************/
#include <unistd.h> /* System V */
#include <sys/ioctl.h> /* BSD and Linux */
int ioctl(int fd, int request, ...);
	


