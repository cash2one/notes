/*

sysfs��ʼ��
sysfs_init






struct task_struct {
    int link_count; 
    int total_link_count;
    struct fs_struct *fs;
    struct files_struct *files;
    struct nsproxy *nsproxy;
}
struct file_system_type ����һ���ļ�ϵͳ
struct vfsmount         ÿ��װ�ص��ļ�ϵͳ����Ӧһ��vfsmount�ṹ��ʵ��
super_block             ������


expand_fdtable

register_filesystem   ע���ļ�ϵͳ,file_systems�������

��װ
namespace.c/SYSCALL_DEFINE5


