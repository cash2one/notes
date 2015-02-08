

/* invoked when fd is either EV_READable or EV_WRITEable */
/* revent EV_READ, EV_WRITE */
/*-----------------------------------------------------------------------------------
 @active: 
     ��ʾ��ǰwatcher�Ƿ񱻼��ev_TYPE_start���ú���λ��ev_TYPE_stop���ú�λ��
 @pending: 
    ��ʾ��ǰwatcher���¼��������ȴ�����pending��ֵ��ʵ���ǵ�ǰwatcher��pendings����
    �е��±ꣻ
 @priority: 
    �ǵ�ǰwatcher�����ȼ���
 @data: 
    ��������ָ�룬������watcher��Я��������������ݣ�
 @cb��
    ���¼�������Ļص��������塣

 �����watcher���ڴ˻�������Ӷ�������ԡ� �����߿��Ը�����Ҫ��ѡ���ض����͵�watcher��
 ����ʵ�������г�ʼ����Ȼ��ʵ��ע�ᵽloop�м��ɡ�libev�ж��������������͵�watcher��
 ÿ��watcher������ĳһ�ض���������⣨�磺io, timer, signal�ȣ���������ev.h�п�����
 Щwatcher�Ķ��塣
-----------------------------------------------------------------------------------*/
typedef struct ev_io
{
	int active; /* private */		  
	int pending; /* private */			  
	int priority; /* private */		  
	void *data; /* rw */				  
	void (*cb)(struct ev_loop *loop, struct ev_io *w, int revents); /* private */
    int fd;     /* fd�Ǽ������ļ������� */
    int events; /* events�Ǹ���Ȥ���¼���  */
} ev_io;

