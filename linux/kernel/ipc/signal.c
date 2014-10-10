typedef void __signalfn_t(int);
typedef __signalfn_t __user *__sighandler_t;


struct sigaction {
	__sighandler_t sa_handler;  /* ����ָ�� */
	unsigned long sa_flags;
	__sigrestore_t sa_restorer;
	sigset_t sa_mask;		    /* ÿ�����ش���һ���źţ�Ϊ1��ʾ�������ź� 0��ʾ������*/
};

/*
���̽ṹ�����й��źŵı���
struct task_struct {
struct signal_struct *signal;
struct sighand_struct *sighand;
sigset_t blocked, real_blocked;
sigset_t saved_sigmask;		
struct sigpending pending;
}


sigset_t

sigaction   ��һ���ź����ô�����
sigsuspend  �ȴ�һ���ź�
sigemptyset ������ʼ���źż���set,��set ����Ϊ��.


