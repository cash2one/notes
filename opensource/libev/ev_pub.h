



union ev_any_watcher
{
  struct ev_watcher w;
  struct ev_watcher_list wl;    
  struct ev_io io;
  struct ev_timer timer;
  struct ev_periodic periodic;
  struct ev_signal signal;
  struct ev_child child;
  struct ev_stat stat;
  struct ev_idle idle;
  struct ev_prepare prepare;
  struct ev_check check;
  struct ev_fork fork;
  struct ev_cleanup cleanup;
  struct ev_embed embed;
  struct ev_async async;
};




/* �ź�watcher */
typedef struct ev_signal
{
    int active; 
    int pending;
    int priority;
    void *data; 
    void (*cb)(struct ev_loop *loop, struct ev_signal *w, int revents);
    struct ev_watcher_list *next;

    int signum; /* ���signum�������������µ����г�Ա ����ʾ���ǽ��յ����źţ��Ͷ�ʱ���е�at���� */
} ev_signal;


