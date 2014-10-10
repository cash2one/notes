struct stat 
{
    mode_t  st_mode; /* file type & mode (permissions) */
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


/*

UNIX�¿�����ls -l �����������ļ���Ȩ�ޡ���ls�������õ��ı�ʾ���ĸ�ʽ�����������ģ�-rwxr-xr-x ��
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

��8-6λ��5-3λ��2-0λ�ֱ��ʾ�ļ������ߵ�Ȩ�ޣ�ͬ���û���Ȩ�ޣ������û���Ȩ�ޣ�����ʽΪrwx��
r��ʾ�ɶ������Զ����ļ�������
w��ʾ��д�������޸��ļ�������
x��ʾ��ִ�У��������������
û��Ȩ�޵�λ����-��ʾ

���һ���ļ���������SUID��SGIDλ����ֱ�����������߻�ͬ���û���Ȩ�޵Ŀ�ִ��λ�ϡ����磺
1��-rwsr-xr-x ��ʾSUID��������Ȩ���п�ִ��λ������
2��-rwSr--r-- ��ʾSUID�����ã���������Ȩ���п�ִ��λû�б�����
3��-rwxr-sr-x ��ʾSGID��ͬ���û�Ȩ���п�ִ��λ������
4��-rw-r-Sr-- ��ʾSGID�����ã���ͬ���û�Ȩ���п�ִ��λû�б���

��ʵ��UNIX��ʵ���У��ļ�Ȩ����12��������λ��ʾ�������λ���ϵ�ֵ��1����ʾ����Ӧ��Ȩ�ޣ�

11 10 9 8 7 6 5 4 3 2 1 0 
S G T r w x r w x r w x

��11λΪSUIDλ����10λΪSGIDλ����9λΪstickyλ����8-0λ��Ӧ�����������rwxλ��
11 10 9 8 7 6 5 4 3 2 1 0

�����-rwsr-xr-x��ֵΪ�� 1 0 0 1 1 1 1 0 1 1 0 1
      -rw-r-Sr--��ֵΪ�� 0 1 0 1 1 0 1 0 0 1 0 0

---->�û�ID
�û�ID�Ǹ�������
ʵ���û�ID(RUID), ������ϵͳ�б�ʶһ���û���˭�����û�ʹ���û���������ɹ���¼��һ��UNIXϵͳ���Ψһȷ��������RUID.
��Ч�û�ID(RUID), ����ϵͳ�����û���ϵͳ��Դ�ķ���Ȩ�ޣ�ͨ������µ���RUID��
�����û�ID(SUID)�����ڶ���Ȩ�޵Ŀ��š���RUID��EUID����һ���û��󶨲�ͬ�����Ǹ��ļ������Ǹ��û��󶨡�

���������е�ʱ����һЩ���ԣ����а��� ʵ���û�ID,ʵ����ID,��Ч�û�ID,��Ч��ID�ȡ� 
ʵ���û�ID��ʵ����ID��ʶ������˭��˭�������������,һ����2���ֶ��ڵ�½ʱ��������һ����½�Ự�ڼ䣬��Щֵ�����ϲ��ı䡣
����Ч�û�ID����Ч��ID������˽���������ʱ��Ȩ�ޡ��ں��ھ��������Ƿ����ļ���ȡȨ��ʱ���ǲ����˽��̵���Ч�û�ID�������жϵġ�
��һ������������ΪSUIDλʱ���ں˾�֪����������������ʱ��Ӧ����Ϊ���ļ���������������������򡣼��ó������е�ʱ����Ч�û�ID�Ǹó���������ߡ�
*/
/*
---->�ļ�����Ȩ��
u:��ʾ�û�(������)
g:��ʾ��
o:��ʾ����
*/
#define S_IRUSR /*user-read*/
#define S_IWUSR /*user-write*/
#define S_IXUSR /*user-execute*/
#define S_IRGRP /*group-read*/
#define S_IWGRP /*group-write*/
#define S_IXGRP /*group-execute*/
#define S_IROTH /*other-read*/
#define S_IWOTH /*other-write*/
#define S_IXOTH /*other-execute*/


