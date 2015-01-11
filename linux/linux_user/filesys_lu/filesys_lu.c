#include <sys/stat.h>

/*******************************************************************************
 @pathname:�ļ���
 @buf     ;�����ļ��������Ϣ
 return   : 0 if OK,-1 on error
*******************************************************************************/
int stat(const char *restrict pathname,struct stat *restrict buf);

/*******************************************************************************  
 @buf    ;�����ļ��������Ϣ
 function:����������@fd��ȡ�ļ���Ϣ
 return  :0 if OK,-1 on error
*******************************************************************************/
int fstat(int fd,struct stat *buf);

/*******************************************************************************
 @pathname:�ļ���
 @buf     ;�����ļ��������Ϣ
 function :when the named file is asymbolic link, @lstat returns information about 
           the symbolic link, not the file referenced by the symbolic link.  
 return   :0 if OK,-1 on error
*******************************************************************************/
int lstat(const char *restrict pathname,struct stat *restrict buf);

/*return: 0 if OK,-1 on error*/
int fstatat(intfd,const char *restrict pathname, struct stat *restrict buf,int flag);



#include <unistd.h>
#define R_OK /*test for read permission*/
#define W_OK /*test for write permission*/
#define X_OK /*test for execute permission*/

/*******************************************************************************
 @mode : Ҫ�ж���ЩȨ�� R_OK ��
 return: 0 if OK, -1 on error
 ����  : �����ļ�@pathname��ʵ���û�ID���ж��ļ���Ȩ��
*******************************************************************************/
int access(const char *pathname, int mode);

/*return: 0 if OK, -1 on error*/
int faccessat(int fd, const char *pathname, int mode, int flag);

#include <sys/stat.h>

/*******************************************************************************
 @cmask : S_IWGRP�ȣ���������Ϊ1��λ�����ļ�mode�е���Ӧλ��һ�����ر�
 returns: previous file mode creation mask
*******************************************************************************/
mode_t umask(mode_t cmask);

#include <sys/stat.h>
#define S_ISUID /*set-user-ID on execution*/
#define S_ISGID /*set-group-ID on execution*/
#define S_ISVTX /*saved-text (sticky bit)*/
#define S_IRWXU /*read, write, and execute by user (owner)*/
#define S_IRUSR /*read by user (owner)*/
#define S_IWUSR /*write by user (owner)*/
#define S_IXUSR /*execute by user (owner)*/
#define S_IRWXG /*read, write, and execute by group*/
#define S_IRGRP /*read by group*/
#define S_IWGRP /*write by group*/
#define S_IXGRP /*execute by group*/
#define S_IRWXO /*read, write, and execute by other (world)*/
#define S_IROTH /*read by other (world)*/
#define S_IWOTH /*write by other (world)*/
#define S_IXOTH /*execute by other (world)*/

/*******************************************************************************
 function: �ı��ļ�@pathname������
 return  : 0 if OK, -1 on error

 ��ı��ļ���Ȩ��λ�����̵���Ч�û�ID��������ļ���������ID�����߽��̱�����г�
 ���û�Ȩ��
*******************************************************************************/
int chmod(const char *pathname, mode_t mode);

/*******************************************************************************
 function: �ı��ļ�@fd������
 return  : 0 if OK, -1 on error
*******************************************************************************/
int fchmod(int fd, mode_t mode);

/*return: 0 if OK, -1 on error*/
int fchmodat(int fd, const char *pathname, mode_t mode, int flag);
/*return: 0 if OK, -1 on error*/


#include <unistd.h>
/*******************************************************************************
 @owner  : -1��ʾ����
 @group  : -1��ʾ����
 function: �����ļ���������
 return  : 0 if OK, -1 on error
*******************************************************************************/
int chown(const char *pathname, uid_t owner, gid_t group);

/*return: 0 if OK, -1 on error*/
int fchown(int fd, uid_t owner, gid_t group);

/*return: 0 if OK, -1 on error*/
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group,int flag);

/*******************************************************************************
 @owner  : -1��ʾ����
 @group  : -1��ʾ����
 function: �����ļ���������
 return  : 0 if OK, -1 on error

 ����ļ��Ƿ�������@lchown���ķ������ӱ���������ߡ�
*******************************************************************************/
int lchown(const char *pathname, uid_t owner, gid_t group);



#include <unistd.h>
/*******************************************************************************
return: 0 if OK,-1 on error
These two functions truncate an existing file to @length bytes. If the previous 
size of the file was greater than length,the data beyond @length is no longer 
accessible. Otherwise, if the previous size was less than @length,the file size 
will increase and the data between the old end of file and the new end of file 
will read as 0 (i.e., a hole is probably created in the file).
*******************************************************************************/
int truncate(const char *pathname,off_t length);

/*return: 0 if OK,-1 on error*/
int ftruncate(int fd,off_t length);


#include <unistd.h>
/************************************************************************************
 @function:
    create a new directory entry, @newpath, that references the existing file 
    @existingpath. (hard link)
 @return: 
    0 if OK, -1 on error

 a file can have multiple directory entries pointing to its i-node. We can use either 
 the @link function or the @linkat function to create a link to an existing file.

 1 If the @newpath already exists, an error is returned
 2 Only the last component of the @newpath is created.The rest of the path must already 
   exist.
 3 ������Ŀ¼��������Ӽ���Ӧ���Ǹ�ԭ�Ӳ���
 4 �����ʵ��Ҫ��������·������ͬһ���ļ�ϵͳ��
 5 ���֧�ִ���ָ��Ŀ¼��Ӳ���ӣ�Ҳ�����ڳ����û����������������������ļ�ϵͳ��
   �γ�ѭ������˺ܶ��ļ�ϵͳ���������Ŀ¼��Ӳ����
************************************************************************************/
int link(const char *existingpath, const char *newpath);

/*******************************************************************************
 return: 0 if OK, -1 on error
*******************************************************************************/
int linkat(int efd, const char *existingpath, int nfd, const char *newpath,int flag);


/************************************************************************************
 @function: 
    remove the directory entry and decrement the link count of the file referenced by 
    @pathname. If there are other links to the file, the data in the file is still 
    accessible through the other links. The file is not changed if an error occurs.
 @return  :
    0 if OK, -1 on error

 1 @unlinkɾ��Ŀ¼�������@pathname�������ļ������Ӽ�����1
 2 Ϊ�˽�����ļ������ӣ�����԰�����Ŀ¼���Ŀ¼����д��ִ��Ȩ�ޡ�if the sticky bit 
   is set in this directory we must have write permission for the directory and meet 
   one of the following criteria:
   a) Own the file
   b) Own the directory
   c) Have superuser privileges
 3 ���@pathname�Ƿ������ӣ�@unlinkɾ���÷������ӣ�������ɾ���ɸ����������õ��ļ���
 4 The superuser can call @unlink with pathname specifying a directory if the file
   system supports it, but the function rmdir should be used instead to unlink a 
   directory
 5 Only when the link count reaches 0 can the contents of the file be deleted.One other 
   condition prevents the contents of a file from being deleted:as long as some process 
   has the file open, its contents will not be deleted.When a file is closed,the kernel 
   first checks the count  of the number of processes  that have the file open. If this 
   count has  reached 0, the kernel then  checks the link count; if it is 0, the file's 
   contents are deleted.
 ***********************************************************************************/
int unlink(const char *pathname);

/*return: 0 if OK, -1 on error*/
int unlinkat(int fd, const char *pathname, int flag);


#include <stdio.h>
/*******************************************************************************
 We can also unlink a file or a directory with the @remove function. For a file,
 @remove is identical to @unlink. For a directory, @remove is identical to @rmdir.

 returns: 0 if OK, -1 on error
*******************************************************************************/
int remove(const char *pathname);

#include <stdio.h>
/*******************************************************************************
 return: 0 if OK, -1 on error
*******************************************************************************/
int rename(const char *oldname, const char *newname);

/*return: 0 if OK, -1 on error*/
int renameat(int oldfd, const char *oldname, int newfd, const char *newname);


#include <unistd.h>
/*return: 0 if OK, -1 on error*/
int symlink(const char *actualpath, const char *sympath);

/*return: 0 if OK, -1 on error*/
int symlinkat(const char *actualpath, int fd, const char *sympath);

#include <unistd.h>
/*return: number of bytes read if OK, -1 on error*/
ssize_t readlink(const char* restrict pathname, char *restrict buf,size_t bufsize);

/*return: number of bytes read if OK, -1 on error*/
ssize_t readlinkat(int fd, const char* restrict pathname,char *restrict buf, size_t bufsize);

#include <sys/stat.h>
/*return: 0 if OK, -1 on error*/
int futimens(int fd, const struct timespec times[2]);

/*return: 0 if OK, -1 on error*/
int utimensat(int fd, const char *path, const struct timespec times[2],int flag);


#include <sys/time.h>
/*Returns: 0 if OK, -1 on error*/
int utimes(const char *pathname, const struct timeval times[2]);

#include <sys/stat.h>
/*******************************************************************************
 function: create a new, empty directory. The entries for dot and dot-dot are
           created automatically. 
 return  : 0 if OK, -1 on error
 *******************************************************************************/
int mkdir(const char *pathname, mode_t mode);


int mkdirat(int fd, const char *pathname, mode_t mode);


#include <unistd.h>
/*******************************************************************************
 function: An empty directory is deleted with the rmdir function. Recall that an 
           empty directory is one that contains entries only for dot and dot-dot.
 return  : 0 if OK, -1 on error
 
 If the link count of the directory becomes 0 with this call, and if no other 
 process has the directory open, then the space occupied by the directory is 
 freed. If one or more processes have the directory open when the link count 
 reaches 0, the last link is removed and the dot and dot-dot entries are removed 
 before this function returns.Additionally, no new files can be created in the 
 directory. The directory is not freed,however, until the last process closes it. 
 (Even though some other process has the directory open, it can��t be doing much 
 in the directory, as the directory had to be empty for the rmdir function to 
 succeed.)
 *******************************************************************************/
int rmdir(const char *pathname);



#include <dirent.h>


/*******************************************************************************
 The DIR structure is an internal structure used by these seven functions to 
 maintain information about the directory being read. The purpose of the DIR 
 structure is similar to that of the FILE structure maintained by the standard 
 I/O library, which we describe in Chapter 5.
*******************************************************************************/



/*return: pointer if OK, NULL on error*/
DIR *opendir(const char *pathname);

/*return: pointer if OK, NULL on error*/
DIR *fdopendir(int fd);

/*Returns: pointer if OK, NULL at end of directory or error*/
struct dirent *readdir(DIR *dp);

void rewinddir(DIR *dp);

/*Returns: 0 if OK, -1 on error*/
int closedir(DIR *dp);

/*Returns: current location in directory associated with dp*/
long telldir(DIR *dp);

void seekdir(DIR *dp, long loc);

#include <unistd.h>
/*******************************************************************************
 function: ���ĵ�ǰ����Ŀ¼Ϊ@pathname
 return  : 0 if OK, -1 on error
 ******************************************************************************/
int chdir(const char *pathname);

/*******************************************************************************
 function: ���ĵ�ǰ����Ŀ¼Ϊ@fd
 return: 0 if OK, -1 on error
 ******************************************************************************/
int fchdir(int fd);


#include <unistd.h>

/*******************************************************************************
 @buf   : ��ŵ�ǰ����Ŀ¼(�ݶ�·��)
 @size  : @buf�ĳ���
 returns: buf if OK, NULL on error
 
 pass to this function the address of a buffer, @buf, and its size (in bytes). 
 The buffer must be large enough to accommodate the absolute pathname plus a 
 terminating null byte, or else an error will be returned.

 What we need is a function that starts at the current working directory (dot) 
 and works its way up the directory hierarchy, using dot-dot to move up one 
 level. At each level, the function reads the directory entries until it finds 
 the name that corresponds to the i-node of the directory that it just came 
 from. Repeating this procedure until the root is encountered yields the entire
 absolute pathname of the current working directory. Fortunately, a function 
 already exists that does this work for us.
 ******************************************************************************/
char *getcwd(char *buf, size_t size);



