struct iovec {
  void   *iov_base;   /* starting address of buffer */
  size_t  iov_len;    /* size of buffer */
};

#define IOV_MAX  /* 1024 */




/*
---->��������I/O unbuffered I/O
���׼I/O�����,���ﲻ������ָÿ��read��write�������ں��е�һ��ϵͳ����.
��Щ���������I/O����ISO C����ɲ���,��������POSIX.1����ɲ���.

---->�ļ�������
A file descriptor is a non-negative integer. To the kernel, all open files are 
referred to by file descriptors. 
file descriptor 0 STDIN_FILENO  with the standard input of a process, 
file descriptor 1 STDOUT_FILENO with the standard output 
file descriptor 2 STDERR_FILENO with the standard error.

---->��ǰ�ļ�ƫ���� current file offset
ÿ���򿪵��ļ�����һ������������ĵ�ǰ�ļ�ƫ����,ͨ����һ���Ǹ�����,���Զ�����
�ļ���ʼ��������ֽ�����ͨ��,�ļ��ĵ�ǰƫ����Ӧ����һ���Ǹ�����,����,ĳЩ�豸Ҳ
����������ƫ��������������ͨ�ļ�������ƫ���������ǷǸ�ֵ��

---->��������
ͨ����һ���������飬����ÿ�������е�ÿһ��bitλ��Ӧһ����������
����ʹ��32λ����������ĵ�һ��Ԫ�ض�Ӧ��������0~31���ڶ���Ԫ�ض�Ӧ��������32~63���Դ����ơ�
fd_set
void FD_ZERO(fd_set *fdset);         clear all bits in fdset
void FD_SET(int fd, fd_set *fdset);  turn on the bit for fd in fdset
void FD_CLR(int fd, fd_set *fdset);  turn off the bit for fd in fdset
int FD_ISSET(int fd, fd_set *fdset); is the bit for fd on in fdset
 
---->current file offset
ͨ����һ���Ǹ����������Զ������ļ���ʼ��������ֽ�����

---->�ļ����� file sharing
The kernel uses three data structures to represent an open file, and the relationships
among them determine the effect one process has on another with regard to file sharing.
1 entry in the process table
  �ڽ��̱��м�¼��ÿ�����̴򿪵��ļ���ÿ���ļ�ռһ����������м�¼�����ļ���������ָ���ļ����ָ��
  (a)  The file descriptor flags (close-on-exec)
  (b)  A pointer to a file table entry
2 file table
  The kernel maintains a file table for all open files. Each file table entry contains
  (a) The file status flags for the  file, such as read, write, append, sync, and nonblocking;
  (b) The current file offset
  (c) A pointer to the v-node table entry for the file
3 v-node
  Each open file (or device) has a v-node structurethat contains information 
  about the type of file and pointers to functions that operate on the file. 
  v-node also contains the i-node for the file. This information is read from
  disk when the file is opened, so that all the pertinent information about the
  file is readily available. For example, the i-node contains the owner of the 
  file, the size of the file, pointers to wherethe actual data blocks for the 
  file are located on disk, and so on.


  
+-----------------------------------------------+
|              process table entry              |   ���̱�  ��¼ÿ�����̴򿪵��ļ�
|------------------------------------------------
|    fd0   | file descriptor flags  |   pointer |   file descriptor flags �� pointer ��Ϊһ������
|------------------------------------------------
|    fd1   | file descriptor flags  |   pointer |   file descriptor flags  
|------------------------------------------------  
|    fd2   | file descriptor flags  |   pointer |   pointerָ�� �ļ���(file table entry)
|------------------------------------------------ 
|    ...   | file descriptor flags  |   pointer |  
+-----------------------------------------------+  

+----------------------+
|   file table entry   |    �ļ���(file table entry) ����ÿ���򿪵��ļ���Ӧһ���ļ���
+----------------------+
|   file status flags  |    ���������̴�ͬһ���ļ���ÿ�����̶����Լ����ļ��� 
|-----------------------
|  current file offset |
|-----------------------  
|    v-node pointer    |
+----------------------+  


+----------------------+
|  v-node table entry  |    v�ڵ� ����ÿ���򿪵��ļ���Ӧһ��
+----------------------+
|  v-node information  |    ���������̴�ͬһ���ļ�������һ��v�ڵ�
|-----------------------
|         v_data       |
+----------------------+  

It is possible for more than one file descriptor entry to point to the same 
file table entry, as we'll see when we discuss the dup function. This also 
happens after a fork when the parent and the child share the same file table 
entry for each open descriptor 

Given these data structures, we now need to be more specific about what happens
with certain operations that we've already described.
1 After each writeis complete, the current file offset in the file table entry 
  is incremented by the number of bytes written. If this causes the current 
  file offset to exceed the current file size, the current file size in the 
  i-node table entry is set to the current file offset .
2 If a file is opened with the O_APPEND flag, a corresponding flag is set in 
  the file status flags of the file table entry.Each time a write is performed 
  for a file with this append flag set, the current file offset in the file 
  table entry is first set to the current file size from the i-node table entry.
  This forces every write to be appended to the current end of file.
3 If a file is positioned to its current end of file using lseek,all that happens 
  is the current file offset in the file table entry is set to the current file 
  size from the i-node table entry.(Note that this is not the same as if the file 
  was opened with the O_APPEND flag)
4 The lseek function modifies only the current file offset in the file table entry.
  No I/O takes place.


----> atomic operations
In general, the term atomic operation refers to an operation that might be composed
of multiple steps. If the operation is performed atomically, either all the steps are
performed (on success) or none are performed (on failure). It must not be possible for
only a subset of the steps to be performed. 

Assume that two independent processes, A and B, are appending to the same file.Each has opened the file but without the O_APPEND flag.
Each process has its own file table entry,but they sharea single v-node table entry.Assume that process A does the lseek and that this 
sets the current offset for the file for process A to byte offset 1,500 (the current end of file). Then the kernel switches processes, 
and B continues running. Process B then does the lseek,which sets the current offset for the file for process B to byte offset 1,500 
also (the current end of file). Then B calls write,which increments B's current file offset for the file to 1,600. Because the file��s 
size has been extended, the kernel also updates the current file size in the v-node to 1,600. Then the kernel switches processes and A 
resumes. When A calls write,the data is written starting at the current file offset for A, which is byte offset 1,500. This overwrites 
the data that B wrote to the file.

---->����
Traditional implementations of the UNIX System have a buffer cache or page cache in the kernel through which most disk I/O passes. 
When we write data to a file, the data is normally copied by the kernel into one of its buffers and queued for writing to disk at
some later time. This is called delayed write. The kernel eventually writes all the delayed-write blocks to disk, normally when it
needs to reuse the buffer for some other disk block. To ensure consistency of the file system on disk with the contents of the buffer 
cache, the sync, fsync,and fdatasync functions are provided.

---->I/O��·ת�� I/O multiplexing
�ȹ���һ���й����������б�,Ȼ�����һ������,ֱ����Щ�������е�һ���Ѿ�׼���ý���I/Oʱ,�ú����ŷ���.�ڷ���ʱ�����߽�����Щ�������Ѿ�׼���ÿ��Խ���I/O

---->�洢ӳ��I/O 
ʹһ�������ļ���洢�ռ��е�һ����������ӳ��.���ӻ�������ȡ���ݾ��൱�ڶ�ȡ�ļ��е���Ӧ�ֽڡ������ݴ��뻺��������Ӧ�ֽھ��Զ���д���ļ���
�����Ϳ����ڲ�ʹ��read��write�������ִ��I/O��
fork֮���ӽ��̼̳д洢ӳ����

---->Interruptibility of select and poll
When the automatic restarting of interrupted system calls was introduced with
4.2BSD(Section 10.5), the @select function was never restarted. This 
characteristic continues with most systems even if the SA_RESTART option is 
specified. But under SVR4, if SA_RESTART was specified, even @select and @poll 
were automatically restarted. To prevent this from catching us when we port 
software to systems derived from SVR4,we'll always use the signal_intr 
function (Figure 10.19) if the signal could interrupt a call to @select or @poll

