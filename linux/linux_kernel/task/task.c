

struct task_struct

struct pid   /*�ں˶�PID���ڲ���ʾ*/
struct upid  /*�ض������ռ�ɼ�����Ϣ*/

pid_hash 
attach_pid
task_pid
pid_nr_ns
pid_vnr    /*���ظ�ID�����������ռ��������ľֲ�PID*/
pid_nr     /*��ȡ��init���̿�����ȫ��PID*/
task_pid_nr_ns

find_pid_ns  /*�ɾֲ�����PID�͹����������ռ���pidʵ��(����PID���ں˱�ʾ)*/
find_task_by_pid_ns

alloc_pidmap /*����PID*/
free_pidmap  /*�ͷ�PID*/
alloc_pid    /*ÿ�������ռ�����һ���ֲ�PID*/


/*pid hash*/
pidhash_init
pid_hashfn
attach_pid
alloc_pid
find_pid_ns

alloc_pidmap






/*

init_tss  init_task.c
INIT_TSS

---->�����̸߳���
����:����+��Դ

---->�û�̬�ͺ���̬
�û�̬:����ͨ�������û�̬,ֻ�ܷ������������.��������ϵͳ���ݻ�����Ҫ�л�������̬.
�û�̬�л�������̬
1 ͨ��ϵͳ����  �����л�
2 �жϴ���      �����л�  ��Ȼ�жϵ��½����л�������̬�����жϵ�ִ��ͨ���ͽ����޹�.��ǰ����Ҳ��������жϵ�����.

---->�ں���ռ
1 ��ͨ�������ǿ��ܱ���ռ�������Ǳ�����������ռ.
2 ϵͳ���ں���̬�����ڴ���ϵͳ����,��ô���������޷���ռ,���жϿ�����ֹϵͳ����.

---->��ʬ����

---->����ID��
�߳�ID:
  ÿ���߳�Ӧ�����Լ���ID�������߳�ID����linux kernel�У�ÿһ��thread����һ��task_struct���ýṹ�е�pid��Ա�����߳�ID����POSIX��׼�У�������pthread_self
  ����ȡ�߳�ID��linux kernel������gettid��ϵͳ��������ȡ�����ߵ��߳�ID����linux kernel�У��������£�
            asmlinkage long sys_gettid(void)
            {
                   return current->pid;
            }
  POSIX�涨�߳�ID��������������Ψһ�ģ�������linux kernel��ʵ���У�thread ID��ȫϵͳΨһ�ģ���Ȼ�����ǵ�����ֲ�ԣ�Application software��Ӧ�ü�����һ�㡣
  
TGID:�߳���ID
    ���̵߳Ľ����е�һ���̣߳����̣߳�group leader����pid����tgid��֮�󣬸��߳����е��̶߳����Լ���pid�����ǹ���tgid��Ҳ���Ǵ�ͳ�����ϵĽ���ID��

PID:�����ܻ����һ�������������������ռ���Ψһ�ر�ʶ����,�ú����Ϊ����ID��,���PID.
    ��������һ�����߶��thread��ɣ�POSIX�涨���threadҪ����һ������ID����
    ���̵߳Ľ����е�һ���̣߳����̣߳�group leader����pid����tgid��֮�󣬸��߳����е��̶߳����Լ���pid�����ǹ���tgid��Ҳ���Ǵ�ͳ�����ϵĽ���ID��
    ϵͳ������getpid(sys_getpid)��������ȡһ�����̵�process ID��
    asmlinkage long sys_getpid(void)
    {
       return current->tgid;
    }
������ID:
    ÿ����������һ�������飬ÿ����������һ��Leader���̣�Ҳ���ǽ���ID���ڽ�����ID���Ǹ����̡�
    ���������������ڣ������������ڿ�ʼ�ڽ�����leader���������飬�����ڽ������ڵ����һ�������뿪������

SID :�ỰID
    �ͽ������ڽ��������ƣ�ÿ�������鶼����һ��session��ÿ��session��һ��Leader���̣�Ҳ���Ǵ���session���Ǹ����̣�
    session leader��ID�͵��ڸ�session��ID��Session�����������û���¼���


ĳЩ�����ж��PID,�����Կ����ý��̵������ռ�,����Ϊ�����һ��PID


---->�����ռ�
�����ռ�:�����������⻯

struct nsproxy         ͨ������ṹ�����
CLONE_NEWUTS           �ȱ�ʾ������ʾ�Ƿ񴴽��µ�uts�������ռ�
struct task_struct->nsproxy ����ָ����������������ռ�
init_nsproxy           ���ȫ�ֱ��������˳�ʼ��ȫ�������ռ�

UTS�����ռ�
struct uts_namespace   ����ṹ
init_uts_ns            ��ʼ��Ϣ
copy_utsname           ����ust�����ռ�,fork�ǵ���

�û������ռ�
struct user_namespace  ����ṹ
clone_user_ns          �����û������ռ�

PID�����ռ�
struct pid_namespace   ����ṹ
struct pid             �ں˶�pid���ڲ���ʾ
struct upid            �ض��������ռ��пɼ�����Ϣ

pid_hash               pidhash_init�г�ʼ��
attach_pid

task_pid_nr_ns        �ɽ��̺������������ռ��þֲ�ID
  task_pid            �ɽ��̻�û��task_struct������pid
  pid_nr_ns           ��pid�������ռ��þֲ�ID
pid_vnr              ���ظ�ID�����������ռ��������ľֲ�PID
pid_nr               ��ȡ��init���̿�����ȫ��PID

find_task_by_pid_type_ns  �ɾֲ�ID�Ͷ�Ӧ�������ռ��ö�Ԫ�������task_struct
  find_pid_ns             �ɾֲ�����PID�͹����������ռ�(�û��ռ��pid��ʾ)���pidʵ��(pid���ں˱�ʾ)
  pid_task
  
find_task_by_pid_ns       ͨ������PID�������������ռ���task_structʵ��  
  find_task_by_pid_type_ns
  
find_task_by_vpid         ͨ���ֲ�pid���ҽ���
find_task_by_pid          ͨ��ȫ��pid���ҽ���

alloc_pid



---->���̴���
�û�̬API    fork vfork clone
libc��       fork vfork clone
               system_call            128���жϴ��û�̬�л����ں�̬,����ϵͳ���ô������
      sys_fork sys_clone sys_vfork    ����ϵͳ���úŵ��ö�Ӧ�ķ������� ϵͳ���ú���linux/include/asm-i386/unistd.h�ж���
               do_fork


long do_fork(unsigned long clone_flags,     ��͵�һ���ֽ�Ϊ�ӽ��̽���ʱ���͸������̵��źŴ��룬ͨ��ΪSIGCHLD��ʣ��������ֽ����Ǹ���clone��־�����
	        unsigned long stack_start,     �ӽ����û�̬��ջ�ĵ�ַ
	        struct pt_regs *regs,          ָ��pt_regs�ṹ���ָ�롣��ϵͳ����ϵͳ���ã����û����̴��û�̬�л����ں�̬ʱ���ýṹ�屣��ͨ�üĴ����е�ֵ������������ں�̬�Ķ�ջ��
	        unsigned long stack_size,      δ��ʹ�ã�ͨ������ֵΪ0
	        int __user *parent_tidptr,     ���������û�̬��pid�ĵ�ַ���ò�����CLONE_PARENT_SETTID��־���趨ʱ������
	        int __user *child_tidptr)      �ӽ������û�̬��pid�ĵ�ַ���ò�����CLONE_CHILD_SETTID��־���趨ʱ������
do_fork
  copy_process
    ��־���
    dup_task_struct
    copy_flags
    sched_fork  ��ʼ���������
    copy_thread �����ӽ��̵ļĴ�����ʼֵ�������ں˶�ջλ��
    attach_pid  ��pid���뵽hlist



kernel_thread   �����ں��߳�


execve









