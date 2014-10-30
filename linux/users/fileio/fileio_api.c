/*If the file exists and if it is successfully opened for either write-only or
read�Cwrite, truncate its length to 0.*/

#define O_APPEND /*Append to the end of file on each write.By default, 
"current file offset" is initialized to 0 when a file is opened, unless the 
O_APPEND option is specified.*/
#define O_CLOEXEC /*Set the FD_CLOEXEC file descriptor flag.*/
#define	O_CREAT  /*Create the file if it doesn��t exist. This option requires a
third argument to the open function (a fourth argument to the openat function)��
the mode,which specifies the access permission bits of the new file.*/
#define O_EXEC	  /* Open for execute only.*/
#define O_EXCL	/*Generate an error if O_CREAT is also specified and the file 
already exists. This test for whether the file already exists and the creation 
of the file if it doesn��t exist is an atomic operation. */
#define	O_NONBLOCK /*If path refers to a FIFO, a block special file, or a character
special file,this option sets the nonblocking mode for both the opening of the file 
and subsequent I/O.*/

#define O_RDONLY  /*Open for reading only.*/
#define O_WRONLY  /*Open for writing only.*/
#define O_RDWR /*Open for reading and writing.Most implementations define 
O_RDONLY as 0,O_WRONLY as 1, and O_RDWR as 2, for compatibility with older programs.*/
#define O_SEARCH  /*Open for search only (applies to directories).*/
#define	O_TRUNC /*If the file exists and if it is successfully opened for 
either write-only or read�Cwrite, truncate its length to 0.*/

/*
The purpose of theO_SEARCHconstant is to evaluate search permissions at the time
adirectory	is	opened. Further  operations  using	the  directory��s  file  descriptor  will
not  reevaluate  permission  to  search  the  directory.None  of  the  versions  of  the
operating systems covered in this book supportO_SEARCHyet.
One  and  only	one  of  the  previous	five  constants  must  be  specified. The  following
constants areoptional:
	 
O_DIRECTORYGenerate an error ifpathdoesn��t refer to a directory.
	
O_NOCTTY If pathrefers	to	a  terminal  device,  do  not  allocate  the  device  as  the
controlling  terminal  for	this  process.	Wetalk	about  controlling
terminals in Section 9.6.
O_NOFOLLOW Generate an error ifpathrefers to a symbolic link. We  discuss symbolic
links in Section 4.17.


In earlier releases of System V,theO_NDELAY(no delay) flag was introduced.	This
option	is	similar  to  theO_NONBLOCK(nonblocking)  option,  but  an  ambiguity  was
introduced in the return value from a read operation. The no-delay option causes a
read operation to return 0 if there is no data to be read from a pipe, FIFO, or device,
but  this  conflicts  with	a  return  value  of  0,  indicating  an  end  of  file. SVR4-based
systems  still	support  the  no-delay	option,  with  the	old  semantics,  but  new
applications should use the nonblocking option instead.

O_SYNC Have  eachwritewait	for  physical  I/O	to	complete,  including  I/O
necessary  to  update  file  attributes  modified  as  a  result  of  thewrite.
We	use this option in Section 3.14.


O_TTY_INIT When  opening  a  terminal  device  that  is  not  already  open,  set  the
nonstandardtermiosparameters to values that result in behavior that
conforms  to  the  Single  UNIX  Specification. We	discuss  the termios
structurewhen we discuss terminal I/O in Chapter 18.
The following two flags arealso optional. They arepart of the synchronized input and
output option of the Single UNIX Specification (and thus POSIX.1).
O_DSYNC Have eachwritewait for physical I/O to complete, but don��t wait for
file attributes to be updated if they don��t affect the ability to read the
data just written.
TheO_DSYNCandO_SYNCflags aresimilar,but subtly different.  TheO_DSYNCflag
affects a file��s attributes only when they need to be updated to reflect a change in the
file��s data (for example, update the file��s size to reflect moredata).  With theO_SYNC
flag, data and attributes arealways updated synchronously.When overwriting an
existing  part	of	a  file  opened  with  theO_DSYNCflag,	the  file  times  wouldn��t  be
updated synchronously.Incontrast, if we had opened the file with theO_SYNCflag,
everywriteto  the  file  would	update	the  file��s  times  beforethewritereturns,
regardless of whether we werewriting over existing bytes or appending to the file.
O_RSYNC Have eachreadoperation on the file descriptor wait until any pending
writes for the same portion of the file arecomplete.
Solaris 10 supports all three synchronization flags. Historically,FreeBSD (and thus
Mac OS X) have used theO_FSYNCflag, which has the same behavior asO_SYNC.
Because the two flags areequivalent, they define the flags to have the same value.
FreeBSD  8.0  doesn��t	support  theO_DSYNCorO_RSYNCflags.	Mac OS	X  doesn��t
support theO_RSYNCflag, but defines theO_DSYNCflag, treating it the same as the
O_SYNCflag.  Linux 3.2.0  supports	theO_DSYNCflag,  but  treats  theO_RSYNCflag
the same asO_SYNC
*/
#include <fcntl.h>
/*******************************************************************************
@path: Ҫ�򿪻򴴽��ļ�������
@oflag:
@mode: ����ʱ�Ż��õ�
function:��һ���ļ�(Ҳ�����ڴ����ļ�)
return: file descriptor if OK,-1 on error

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
******************************************************************************/
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
/*******************************************************************************
 ����ֵ:�ɹ������µ�������,ʧ�ܷ���-1
 ����:�����ļ�������@fd

 1 @dup���ص���������һ���ǵ�ǰ�����ļ��������е���С��ֵ
 2 ����������@fd����һ���ļ�����(file table entry)
 3 ����������ִ��ʱ�ر�(close-on-exec)��־������@dup�������
******************************************************************************/
int dup(int fd);

/*******************************************************************************
 ����ֵ:�ɹ������µ�������,ʧ�ܷ���-1
 ����:�����ļ�������@fd,@fd2��ָ������������

 1 ���@fd2�Ѿ��򿪣����ȹرա�
 2 ���@fd==@fd2�����ر�@fd2��ֱ�ӷ���@fd2
 3 ����������@fd����һ���ļ�����(file table entry)
******************************************************************************/
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

#define F_DUPFD  /*Duplicate the file descriptor @fd.The new file descriptor is 
returned as the value of the function. It is the lowest-numbered descriptor that 
is not already open, and that is greater than or equal to the third argument. 
The new descriptor shares the same file table entry as @fd. But the new descriptor 
has its own set of file descriptor flags, and its FD_CLOEXEC file descriptor 
flag is cleared. (This means that the descriptor is left open across an exec)*/
#define F_DUPFD_CLOEXEC /*Duplicate the file descriptor and set the FD_CLOEXEC 
file descriptor flag associated with the new descriptor.Returns the new file descriptor.*/
#define F_GETFD  /*Return the file descriptor flags for @fd as the value of the 
function. Currently,only one file descriptor flag is defined: the FD_CLOEXEC flag.*/
#define F_SETFD  /*Set the file descriptor flags for @fd.The new flag value is 
set from the third argument (taken as an integer).*/
#define F_GETFL /*Return the file status flags for fd as the value of the function. 
File status flag    Description
O_RDONLY            open for reading only
O_WRONLY            open for writing only
O_RDWR              open for reading and writing
O_EXEC              open for execute only
O_SEARCH            open directory for searching only
O_APPEND            append on each write
O_NONBLOCK          nonblocking mode
O_SYNC              wait for writes to complete (data and attributes)
O_DSYNC             wait for writes to complete (data only)
O_RSYNC             synchronize reads and writes
O_FSYNC             wait for writes to complete (FreeBSD and Mac OS X only)
O_ASYNC             asynchronous I/O (FreeBSD and Mac OS X only)

Unfortunately, the five access-mode flags��O_RDONLY, O_WRONLY,O_RDWR, O_EXEC, 
and O_SEARCH ��are not separate bits that can be tested. (As we mentioned 
earlier, the first three often have the values 0, 1,and 2, respectively, for 
historical reasons. Also, these five values are mutually exclusive; a file can 
have only one of them enabled.) Therefore, we must first use the O_ACCMODE mask 
to obtain the access-mode bits and then compare the result against any of the 
five values.*/
#define	O_ACCMODE /*<0003>����д�ļ�����ʱ������ȡ��flag�ĵ�2λ*/

#define F_SETFL /*Set the file status flags to the value of the third argument 
(taken as an integer). The only flags that can be changed are O_APPEND, O_NONBLOCK,
O_SYNC, O_DSYNC, O_RSYNC, O_FSYNC, and O_ASYNC.*/
#define F_GETOWN /*Get the process ID or process group ID currently receiving
the SIGIO and SIGURG signals.*/
#define F_SETOWN /*Set the process ID or process group ID to receive the SIGIO 
and SIGURG signals. A positive arg specifies a process ID. A negative arg implies 
a process group ID equal to the absolute value of arg.*/

/*********************************************************************************
function:The @fcntl function can change the properties of a file that is already open.
The @fcntl function is used for five different purposes.
1 Duplicate an existing descriptor (cmd=F_DUPFD or F_DUPFD_CLOEXEC)
2 Get/set file descriptor flags (cmd=F_GETFD or F_SETFD)
3 Get/set file status flags (cmd=F_GETFL or F_SETFL)
4 Get/set asynchronous I/O ownership (cmd=F_GETOWNorF_SETOWN)
5 Get/setrecordlocks (cmd=F_GETLK,F_SETLK,orF_SETLKW)
Returns: depends on cmd if OK (see following),-1 on error

The return value from @fcntl depends on the command. All commands return -1 on 
an error or some other value if OK. The following four commands have special
return values: F_DUPFD, F_GETFD, F_GETFL, and F_GETOWN. The first command returns 
the new file descriptor, the next two return the corresponding flags, and the 
final command returns a positive process ID or a negative process group ID.
**********************************************************************************/
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
 @cmd: F_GETLK, F_SETLK,or F_SETLKW.
 ******************************************************************************/
int fcntl(int fd,int cmd,struct flock *flockptr);

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

struct timeval	
{
  long	 tv_sec;  /* seconds */
  long	 tv_usec; /* microseconds */
};

/*
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
Returns: positive count of ready descriptors, 0 on timeout, �C1 on error
Ther eare three possible return values from @select.
1 return -1 means that an error occurred. This can happen, for example, if a signal is caught before any of the specified descriptors are ready.
  In this case, none of the descriptor sets will be modified.
2 return 0 means that no descriptors are ready.This happens if the time limit expires before any of the descriptors are ready.When this happens,
  all the descriptor sets will be zeroed out.
3 A positive return value specifies the number of descriptors that are ready.This value is the sum of the descriptors ready in all three sets, so 
  if the same descriptor is ready to be read and written, it will be counted twice in the return value. The only bits left on in the three descriptor  
  sets are the bits corresponding to the descriptors that are ready.
---->�ȴ���ʱ��
1 ��Զ�ȴ�  timeout == NULL
2 �ȴ�ָ����ʱ�� �����ʱ����timeoutָ��
3 ���ȴ�  timeout�е�ʱ��Ϊ0
The wait in the first two scenarios is normally interrupted if the process catches a signal and returns from the signal handler.
---->׼����
1 ���ڶ����������е�һ����������read���������������������������׼���õ�
2 ����д���������е�һ����������write���������������������������׼���õ�
3 ���쳣���������е�һ����������һ��δ���쳣״̬�������������׼���õġ��쳣״̬����
  a �����������ϵ���Ĵ�������
  b �������ݰ�ģʽ��α�ն��Ϸ�����ĳЩ״̬��
4 File descriptors for regular files always return ready for reading, writing, and exception conditions.
*/
int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);

 
#include <sys/select.h>
int FD_ISSET(int fd,fd_set *fdset);
void FD_CLR(int fd,fd_set *fdset);
void FD_SET(int fd,fd_set *fdset);
void FD_ZERO(fd_set *fdset); 
/*
After declaring a descriptor set, we must zerothe set usingFD_ZERO.Wethen set
bits in the set for each descriptor that we��reinterested in, as in
fd_set  rset;
int  fd;
FD_ZERO(&rset);
FD_SET(fd, &rset);
FD_SET(STDIN_FILENO, &rset);
On return from @select, we can test whether a given bit in the set is still on using @FD_ISSET:
if (FD_ISSET(fd, &rset)) {
.
}

*/

#include <sys/select.h>
#include <signal.h>
#include <time.h>
 
struct timespec {
  time_t tv_sec;       /* seconds */
  long   tv_nsec;      /* nanoseconds */
};


/*
When @pselect is called, it replaces the signal mask of the process with an @sigmask set (i.e., zeromask) and then checks 
the descriptors, possibly going to sleep. But when @pselect returns, the signal mask of the process is reset to its value 
before pselect was called (i.e., SIGINT is blocked).

Returns: count of ready descriptors, 0 on timeout,-1 on error*/
int pselect(int maxfdp1,fd_set *restrict readfds,fd_set *restrict writefds,fd_set *restrict exceptfds,
             const struct timespec *restrict tsptr,const sigset_t *restrict sigmask);




#include <poll.h>
#define POLLIN       /*��ͨ�����ȼ������ݿɶ�*/
#define POLLRDNORM   /*��ͨ���ݿɶ�*/
#define POLLRDBAND   /*���ȼ������ݿɶ�*/
#define POLLPRI      /*�����ȼ����ݿɶ�*/
#define POLLOUT      /*��ͨ���ݿ�д*/
#define POLLWRNORM   /*��ͨ���ݿ�д*/
#define POLLWRBAND   /*���ȼ������ݿ�д*/
#define POLLERR      /*��������*/
#define POLLHUP      /*��������*/
#define POLLNVAL     /*�����ֲ���һ���򿪵��ļ�*/

#define INFTIM       /*��һ����ֵ poll�ĵ���������,��ʾ��Զ�ȴ�*/

struct pollfd 
{
    int  fd; /* file descriptor to check, or <0 to ignore */
    short  events; /* events of interest on fd */
    short  revents;  /* events that occurred on fd */
};

/*
@fdarray: ÿ������Ԫ��ָ��һ������������Լ����������ĵ�״̬��
@nfds:����Ԫ�صĸ���
@timeout: INFTIM��Զ�ȴ� 0���ȴ� ����0�ȴ�ָ����ʱ��
Returns: count of ready descriptors, 0 on timeout,-1 on error*/
int poll(struct pollfd fdarray[], nfds_t nfds,int timeout);


#include <sys/mman.h>
#define PROT_READ   /*Region can be read.*/
#define PROT_WRITE  /*Region can be written.*/
#define PROT_EXEC   /*Region can be executed.*/
#define PROT_NONE   /*Region cannot be accessed.*/
#define MAP_FIXED   /*����ֵ�������@addr*/
#define MAP_SHARED	/*�洢�����൱�ڶԸ��ļ���write.MAP_SHARED��MAP_PRIVATE����ָ��һ����������ͬʱָ����*/
#define MAP_PRIVATE /*��ӳ�����Ĵ洢�������´�����ӳ���ļ���һ��˽�и�����*/

/*
@addr:ӳ��洢������ʼ��ַ,0��ʾ��ϵͳ�Զ�ѡ��ҳ�߽����
@len: ӳ����ֽ���
@prot:ӳ�����ı���Ҫ��(��λ��)
      PROT_READ Region can be read.
      PROT_WRITE Region can be written.
      PROT_EXEC Region can be executed.
      PROT_NONE Region cannot be accessed.
@flag:ӳ��洢��������
      MAP_FIXED   ����ֵ�������@addr
      MAP_SHARED  �洢�����൱�ڶԸ��ļ���write.MAP_SHARED��MAP_PRIVATE����ָ��һ����������ͬʱָ����
      MAP_PRIVATE ��ӳ�����Ĵ洢�������´�����ӳ���ļ���һ��˽�и�����
@fd:  ��ӳ���ļ���������,ӳ���ļ�ǰҪ�򿪸��ļ�
@off: Ҫӳ���ֽ����ļ��е���ʼƫ����
Returns: starting address of mapped region if OK,MAP_FAILED on error*/
void *mmap(void *addr,size_t len,int prot,int flag,int fd,off_t off);





#include <sys/mman.h>
/*
function:We can change the permissions on an existing mapping by calling @mprotect
Returns: 0 if OK,-1 on error*/
int mprotect(void *addr,size_t len,int prot);



#include <sys/mman.h>
/*
flags: MS_ASYNC       MS_ASYNC��MS_SYNC����ָ��һ��
       MS_SYNC        �ȴ���ϴ���
       MS_INVALIDATE
function:�޸ĳ�ϴ���ļ��С�
Returns: 0 if OK,-1 on error*/
int msync(void *addr,size_t len,int flags);


#include <sys/mman.h>
/*
function:���ӳ��
Returns: 0 if OK,-1 on error

Amemory-mapped region is automatically unmapped when the process terminates
or  we  can  unmap  a  region  directly  by  calling  themunmapfunction.  Closing the  file
descriptor used when we mapped the region does not unmap the region.
Themunmapfunction  does  not  affect  the  object  that  was  mapped��that  is,  the  call  to
munmapdoes not cause the contents of the mapped region to be written to the disk file.
The updating of the disk file for aMAP_SHAREDregion happens automatically by the
kernel��s virtual memory algorithm sometime after we storeinto the memory-mapped
region.  Modifications to  memory  in  aMAP_PRIVATEregion  arediscarded  when  the
region is unmapped.*/
int munmap(void *addr,size_t len);



include <sys/socket.h>
	/*return: number of bytes read or written if OK, �C1 on error */
 
ssize_t recv(int sockfd, void *buff, size_t nbytes, int flags);
 
/*return: number of bytes read or written if OK, �C1 on error */
ssize_t send(int sockfd, const void *buff, size_t nbytes, int flags);
 

#include <sys/uio.h>
struct iovec {
  void   *iov_base;   /* starting address of buffer */
  size_t  iov_len;    /* size of buffer */
};

/* return: number of bytes read or written, �C1 on error */ 
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);

/*@iov:�ṹ������ָ��
  return: number of bytes read or written, �C1 on error */
ssize_t writev(int filedes, const struct iovec *iov, int iovcnt);
 
 
#include <sys/socket.h>
struct msghdr {
void		 *msg_name; 	   /* protocol address */
socklen_t	  msg_namelen;	   /* size of protocol address */
struct iovec *msg_iov;		   /* scatter/gather array */
int 		  msg_iovlen;	   /* # elements in msg_iov */
void		 *msg_control;	   /* ancillary data (cmsghdr struct) */
socklen_t	  msg_controllen;  /* length of ancillary data */
int 		  msg_flags;	   /* flags returned by recvmsg() */
};

  /*Both return: number of bytes read or written if OK, �C1 on error */
 ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);

/*return: number of bytes read or written if OK, �C1 on error */  
ssize_t sendmsg(int sockfd, struct msghdr *msg, int flags);
 

/*




*/

