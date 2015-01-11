struct stat 
{
    mode_t  st_mode; /* file type & mode (permissions) ��ͨ�ļ� Ŀ¼�ļ��� */
    ino_t  st_ino; /* i-node number (serial number) */
    dev_t  st_dev; /* device number (file system) */
    dev_t  st_rdev; /* device number for special files */
    nlink_t  st_nlink; /* number of links */
    uid_t  st_uid; /* user ID of owner */
    gid_t  st_gid; /* group ID of owner */
    off_t  st_size; /* size in bytes, for regular files */
    struct timespec st_atim; /* time of last access */
    struct timespec st_mtim; /* time of last modification */
    struct timespec st_ctim; /* time of last file status change */
    blksize_t  st_blksize; /* best I/O block size */
    blkcnt_t  st_blocks; /* number of disk blocks allocated */
};


/*******************************************************************************
 The dirent structure defined in <dirent.h> is implementation dependent.
 Implementations define the structure to contain at least the following two members:
 *******************************************************************************/
struct dirent
{
    ino_t d_ino; /* i-node number */
    char d_name[]; /* null-terminated filename */
}

/*DIR �ṹ���ԭ��Ϊ��struct_dirstream
  ��linuxϵͳ�У�*/
typedef struct __dirstream DIR;
struct __dirstream
{
    void *__fd; /* `struct hurd_fd' pointer for descriptor.   */
    char *__data; /* Directory block.   */
    int __entry_data; /* Entry number `__data' corresponds to.   */
    char *__ptr; /* Current pointer into the block.   */
    int __entry_ptr; /* Entry number `__ptr' corresponds to.   */
    size_t __allocation; /* Space allocated for the block.   */
    size_t __size; /* Total valid data in the block.   */
    __libc_lock_define (, __lock) /* Mutex lock for this structure.   */
};


/*st_modeҲ�������ļ��ķ���Ȩ��λ,������9����λȨ��λ*/
#define S_IRUSR /*user-read*/
#define S_IWUSR /*user-write*/
#define S_IXUSR /*user-execute*/
#define S_IRGRP /*group-read*/
#define S_IWGRP /*group-write*/
#define S_IXGRP /*group-execute*/
#define S_IROTH /*other-read*/
#define S_IWOTH /*other-write*/
#define S_IXOTH /*other-execute*/

/*���º�Ĳ�����stat�ṹ�е�st_mode*/
#define S_ISREG()  /*regular file*/
#define S_ISDIR()  /*directory file*/
#define S_ISCHR()  /*character special file*/
#define S_ISBLK()  /*block special file*/
#define S_ISFIFO() /*pipe or FIFO*/
#define S_ISLNK()  /*symbolic link*/
#define S_ISSOCK() /*socket*/

/*���º�Ĳ�����stat�ṹ��ָ��*/
#define S_TYPEISMQ()  /*message queue*/
#define S_TYPEISSEM() /*semaphore*/
#define S_TYPEISSHM() /*shared memory object*/

/*the set-user-ID bit and the set-group-ID bit are contained in the file's 
st_mode value. These two bits can be tested against the constants S_ISUID and
S_ISGID, respectively.*/
#define S_ISUID
#define S_ISGID


/*
********************************************************************************
---->Ŀ¼�Ķ�ȡ
  Directories can be read by anyone who has access permission to read the 
directory. But only the kernel can write to a directory, to preserve file system 
sanity. the write permission bits and execute permission bits for a directory
determine if we can create new files in the directory and remove files from the
directory �� they don't specify if we can write to the directory itself.
  The actual format of a directory depends on the UNIX System implementation and
the design of the file system. Earlier systems, such as Version 7, had a simple 
structure:each directory entry was 16 bytes, with 14 bytes for the filename and 
2 bytes for the i-node number. When longer filenames were added to 4.2BSD, each 
entry became variable length, which means that any program that reads a directory 
is now system dependent. To simplify the process of reading a directory, a set of 
directory routines were developed and are part of POSIX.1. Many implementations 
prevent applications from using the read function to access the contents of 
directories, thereby further isolating applications from the implementation-specific 
details of directory formats.
********************************************************************************
�ļ�����
1 ��ͨ�ļ�(regular file)  
2 Ŀ¼�ļ�(directory file) 
  �����ļ������������ļ��������Լ�ָ������Щ�ļ��й���Ϣ��ָ�롣
3 �������ļ�(block special file)
  �����ļ������ṩ���豸(�������)������ķ��ʣ�ÿ�η��ʹ̶�����Ϊ��λ����
4 �ַ������ļ�(character special file)
  �����ļ������ṩ���豸��������ķ��ʣ�ÿ�η��ʳ��ȿɱ䡣
5 FIFO
6 �׽���(socket)
7 ��������(symbolic link)
  



********************************************************************************
UNIX�¿�����ls -l �����������ļ���Ȩ�ޡ���ls�������õ��ı�ʾ���ĸ�ʽ�����������ģ�
-rwxr-xr-x ��

���ֱ�ʾ����һ����ʮλ��
9 8 7 6 5 4 3 2 1 0 
- r w x r - x r - x

��9λ��ʾ�ļ�����,����Ϊp��d��l��s��c��b��-��
p��ʾ�����ܵ��ļ� 
d��ʾĿ¼�ļ� 
l��ʾ���������ļ� 
-��ʾ��ͨ�ļ� 
s��ʾsocket�ļ� 
c��ʾ�ַ��豸�ļ� 
b��ʾ���豸�ļ�

��8-6λ��5-3λ��2-0λ�ֱ��ʾ�ļ������ߵ�Ȩ�ޣ�ͬ���û���Ȩ�ޣ������û���Ȩ�ޣ���
��ʽΪ rwx
r��ʾ�ɶ������Զ����ļ�������
w��ʾ��д�������޸��ļ�������
x��ʾ��ִ�У��������������
û��Ȩ�޵�λ����-��ʾ

���һ���ļ���������SUID��SGIDλ����ֱ�����������߻�ͬ���û���Ȩ�޵Ŀ�ִ��λ�ϡ�
���磺
1��-rwsr-xr-x ��ʾSUID��������Ȩ���п�ִ��λ������
2��-rwSr--r-- ��ʾSUID�����ã���������Ȩ���п�ִ��λû�б�����
3��-rwxr-sr-x ��ʾSGID��ͬ���û�Ȩ���п�ִ��λ������
4��-rw-r-Sr-- ��ʾSGID�����ã���ͬ���û�Ȩ���п�ִ��λû�б�����

��ʵ��UNIX��ʵ���У��ļ�Ȩ����12��������λ��ʾ�������λ���ϵ�ֵ��1����ʾ����Ӧ��
Ȩ�ޣ�
11  10  9  8 7 6  5 4 3  2 1 0 
 S   G  T  r w x  r w x  r w x

��11λΪSUIDλ����10λΪSGIDλ����9λΪstickyλ����8-0λ��Ӧ�����������rwxλ��
11 10 9 8 7 6 5 4 3 2 1 0

�����-rwsr-xr-x��ֵΪ�� 1 0 0 1 1 1 1 0 1 1 0 1
      -rw-r-Sr--��ֵΪ�� 0 1 0 1 1 0 1 0 0 1 0 0

---->�û�ID �û�ID�Ǹ�������
ʵ���û�ID(RUID):������ϵͳ�б�ʶһ���û���˭�����û�ʹ���û���������ɹ���¼
                 ��һ��UNIXϵͳ���Ψһȷ��������RUID.
��Ч�û�ID(RUID):����ϵͳ�����û���ϵͳ��Դ�ķ���Ȩ�ޣ�ͨ������µ���RUID��
�����û�ID(SUID):
  When we execute a program file, the effective user ID of the process is usually 
the real user ID, and the effective group ID is usually the real group ID. 
However, we can also set a special flag in the file��s mode word (st_mode) that 
says:"When this file is executed, set the effective user ID of the process to 
be the owner of the file (st_uid)." Similarly, we can set another bit in the 
file's mode word that causes the effective group ID to be the group owner of 
the file (st_gid). These two bits in the file��s mode word are called the 
set-user-ID bit and the set-group-ID bit.
  For example, if the owner of the file is the superuser and if the file's 
set-user-ID bit is set, then while that program file is running as a process, 
it has superuser privileges. This happens regardless of the real user ID of 
the process that executes the file. 


ʵ����ID
��Ч��ID
������ID
������ID

���������е�ʱ����һЩ���ԣ����а���ʵ���û�ID,ʵ����ID,��Ч�û�ID,��Ч��ID�ȡ�
ʵ���û�ID��ʵ����ID��ʶ������˭��˭�������������,һ����2���ֶ��ڵ�½ʱ��������
һ����½�Ự�ڼ䣬��Щֵ�����ϲ��ı䡣����Ч�û�ID����Ч��ID������˽���������ʱ
��Ȩ�ޡ��ں��ھ��������Ƿ����ļ���ȡȨ��ʱ���ǲ����˽��̵���Ч�û�ID�������жϵġ�
��һ������������ΪSUIDλʱ���ں˾�֪����������������ʱ��Ӧ����Ϊ���ļ�������
��������������򡣼��ó������е�ʱ����Ч�û�ID�Ǹó���������ߡ�


---->�ļ�����Ȩ��
u:��ʾ�û�(������)
g:��ʾ��
o:��ʾ����

********************************************************************************__
1 ���ļ������������͵��ļ�ʱ�������а�����ÿһ��Ŀ¼��Ӧ�þ���ִ��Ȩ�ޡ������
  Ϊʲô����Ŀ¼��ִ��Ȩ��λ������Ϊ����λ��ԭ�򡣶���Ŀ¼����Ȩ�������Ŀ¼����
  ���ڸ�Ŀ¼�������ļ������б�Ŀ¼��ִ��Ȩ��ʹ���ǿ���ͨ����Ŀ¼(Ҳ����������
  Ŀ¼��Ѱ��һ���ض����ļ���)��
  ����Ϊ�˴��ļ�/usr/include/stdio.h����Ҫ��Ŀ¼/��/usr��/usr/iinclude����ִ��
  Ȩ�ޡ�Ȼ����Ҫ���жԸ��ļ�������ʵ�Ȩ�ޣ���ȡ�����Ժ���ģʽ����(��д��)��
2 The read permission for a file determines whether we can open an existing file 
  for reading: the O_RDONLY and O_RDWR flags for the open function.
3 The write permission for a file determines whether we can open an existing file 
  for writing: the O_WRONLY and O_RDWR flags for the open function.
4 We must have write permission for a file to specify the O_TRUNC flag in the 
  open function.
5 We cannot create a new file in a directory unless we have write permission and
  execute permission in the directory.
6 To delete an existing file, we need write permission and execute permission in 
  the directory containing the file. We do not need read permission or write 
  permission for the file itself.
7 Execute permission for a file must be on if we want to execute the file using 
  any of the seven exec functions. The file also has to be a regular file.

  ����ÿ�δ򿪡�������ɾ��һ���ļ�ʱ���ں˾ͽ����ļ�����Ȩ�޲��ԣ����ֲ��Կ�����
���ļ���������(st_uid��st_gid)�����̵���ЧID(��Ч�û�ID����Ч��ID)�Լ����̵ĸ���
��ID(��֧�ֵĻ�)������������ID���ļ������ʣ���������ЧID�͸�����ID���ǽ��̵�����
�ں˽��еĲ�����:
1 If the effective user ID of the process is 0 (the superuser), access is allowed. 
  This gives the superuser free rein throughout the entire file system.
2 If the effective user ID of the process equals the owner ID of the file (i.e., 
  the process owns the file), access is allowed if the appropriate user access
  permission bit is set. Otherwise, permission is denied. By appropriate access
  permission bit, we mean that if the process is opening the file for reading, 
  the user-read bit must be on. If the process is opening the file for writing, 
  the user-write bit must be on. If the process is executing the file, the 
  user-execute bit must be on.
3 If the effective group ID of the process or one of the supplementary group IDs 
  of the process equals the group ID of the file, access is allowed if the 
  appropriate group access permission bit is set. Otherwise, permission is denied.
4 If the appropriate other access permission bit is set, access is allowed.
  Otherwise, permission is denied.
  
  These four steps are tried in sequence. Note that if the process owns the file
(step 2), access is granted or denied based only on the user access permissions; 
the group permissions are never looked at. Similarly, if the process does not 
own the file but belongs to an appropriate group, access is granted or denied 
based only on the group access permissions; the other permissions are not looked at.

********************************************************************************
���ļ���Ȩ��
  The user ID of a new file is set to the effective user ID of the process. 
POSIX.1 allows an implementation to choose one of the following options to 
determine the group ID of a new file:
1 The group ID of a new file can be the effective group ID of the process.
2 The group ID of a new file can be the group ID of the directory in which 
  the file is being created.
  
  Using the second option��inheriting the directory's group ID��assures us that
all files and directories created in that directory will have the same group ID 
as the directory. This group ownership of files and directories will then 
propagate down the hierarchy from that point. This is used in the Linux directory
/var/mail, for example.

********************************************************************************
---->i�ڵ�
ÿһ���´������ļ�����һ��Inode(�������),ÿ���ļ�����һ��Ωһ��inode��
i�ڵ��д����:�ļ��������ߡ��ļ��������顢�ļ���С���ļ����ݿ������ϵ�λ�õ���Ϣ


---->Ŀ¼��
Ŀ¼�������������: i�ڵ�ź��ļ���

********************************************************************************
---->�ļ�������ʱ���ֶ�
Field     Description                           Example       ls(1) option
st_atim   last-access time of file data         read          -u
st_mtim   last-modification time of file data   write         default
st_ctim   last-change time of i-node status     chmod,chown   -c


*************************************************************************************
Ӳ���ӵĶ���
    Linux �ļ�ϵͳ����Ҫ���ص�֮һ�������ļ����ӡ������Ƕ��ļ������ã��������������ļ�
    ���ļ�ϵͳ�жദ���������������� Linux �У����ӿ�����ͬԭʼ�ļ�һ�����Դ������ӿ�
    ������ͨ���ļ�һ����ִ�С��༭�ͷ��ʡ���ϵͳ�е�����Ӧ�ó�����ԣ����Ӿ���������Ӧ
    ��ԭʼ�ļ�������ͨ�����Ӷ��ļ����б༭ʱ�����༭��ʵ������ԭʼ�ļ������Ӳ��Ǹ�����
    ���������͵����ӣ�Ӳ���Ӻͷ�������(������)��Ӳ����ֻ������ͬһ�ļ�ϵͳ�е��ļ�����
    ���õ����ļ����ļ�ϵͳ�е���������(Ҳ��Ϊ inode)�������ƶ���ɾ��ԭʼ�ļ�ʱ��Ӳ����
    ���ᱻ�ƻ�����Ϊ�������õ����ļ����������ݶ������ļ����ļ��ṹ�е�λ�á�Ӳ���ӵ���
    ������Ҫ�û��з���ԭʼ�ļ���Ȩ�ޣ�Ҳ������ʾԭʼ�ļ���λ�ã������������ļ��İ�ȫ��
    �����ɾ�����ļ�����Ӧ��Ӳ���ӣ���ô����ļ���Ȼ�ᱣ����ֱ�����ж��������ö���ɾ����
Ӳ�����������ӵ�����
    ��Linux���ļ�ϵͳ�У������ڴ��̷����е��ļ�������ʲô���Ͷ���������һ����ţ���Ϊ
    �����ڵ��inode �������ӣ���ʵ�����½���һ���ļ�������ļ�����ר������ָ�����ļ�
    �ģ��Ǿͺ�windows �µĿ�ݷ�ʽ���Ǹ��ļ��кܽӽ�����ζ���������Ӳ�������һ���µ���
    ����������ļ������þ���ר��ָ��ĳ���ļ��ģ�ɾ������������ļ����Ǿ͵��ڲ���Ҫ���
    ���ӣ���ԭ���Ĵ��ڵ�ʵ��ԭ�ļ�û���κι�ϵ����ɾ��ԭ�����ļ�������Ӧ�������Ӳ�����
    ��cat�Ǹ��������ļ�������ʾ��û�и��ļ���Ŀ¼����
    Ӳ�����ǲ��Ὠ��inode�ģ���ֻ�����ļ�ԭ����inode link count��������1���ѣ�Ҳ���Ӳ
    �����ǲ����Կ�Խ�ļ�ϵͳ�ġ��෴���������ӻ����½���һ��inode����Ȼinode�Ľṹ����
    ���Ĳ�һ������ֻ��һ��ָ��Դ�ļ����ַ�����Ϣ��һ��ɾ��Դ�ļ�����ô�����ӽ���ú���
    ���塣��Ӳ����ɾ����ʱ��ϵͳ���û���inode link count����ֵ����������ڵ���1����
    ôinode���ᱻ���ա�����ļ������ݲ��ᱻɾ����
    Ӳ����ʵ������Ϊ�ļ���һ�������������ļ���ԭ�ļ�ʵ������ͬһ���ļ�������ͨ��ls -i��
    �鿴һ�£��������ļ���inode����ͬһ����˵��������ͬһ���ļ����������ӽ�������һ��ָ
    �򣬼������ļ��ڵ�������ָ��ԭ�ļ���ָ�룬�����������ļ���
    �����ӿ��Կ��ļ�ϵͳ��Ӳ���Ӳ����ԣ������ӿ��Զ�һ�������ڵ��ļ���(filename)��������
    ����Ȼ��ʱ�����vi����������ļ���linux���Զ��½�һ���ļ���Ϊfilename���ļ���,Ӳ����
    �����ԣ����ļ�������ڣ�inode������ڣ��������ӿ��Զ�Ŀ¼�������ӣ�Ӳ���Ӳ����ԡ�����
    ���Ӷ�����ͨ������ ln ��������ln Ĭ�ϴ�������Ӳ���ӡ�ʹ�� -s ���ؿ��Դ��������ӡ�

