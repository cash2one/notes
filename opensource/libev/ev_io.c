/************************************************************************************
 ev_io����Ҫʹ�����Ǽ�������Ӧָ���ļ�����fd�ϵĶ�д�¼�����fd�ļ�����������Ҫί�и���
 ���io������ɡ�libev��Ŀǰ�Ƚ����е�io�ⶼ�ṩ��֧�֣��磺select, epoll�Լ�windows��
 iocp�ȡ�������libevʹ����Adaptorģʽ��ͨ��ͳһ������������˵ײ�io���ϸ�ڡ� ��loop��
 ʼ����ʱ��loop_init������������ý�����ָ��󶨵��ײ��io�⺯����Ӧ����������ϡ���
 �ԣ������߿��Ժܷ���İѴ����л�����ͬ�ĵײ�ʵ���ϡ� ��صĺ����У�backend_modify����
 �ײ��ע��fd�¼����磺epoll��epoll_ctl��backend_poll�� ��ײ����ѯfd���Ƿ��и���Ȥ��
 �¼��������磺epoll��epoll_wait��������ʵ�ֵĴ��������ev_LIB.c�п����� LIB��io�����
 �֣��磺ev_epoll.c��ev_win32.c�ȡ�

 +-----------------------------------------+
 |              Hight Level Codes          |
 +-----------------------------------------+
                         /|\
                          |
                          |
 +----------------------------------------------+
 |         backend_modify     |   backend_poll  |    Adaptor Layer      
 +----------------------------------------------+
                         /|\
                          |
                          |
 +-------------------------------------------------------+
 | ev_select | ev_poll | ev_epoll | ev_kqueue | ev_win32 |    Adaptor Implement
 +-------------------------------------------------------+
*************************************************************************************

 ev_io�Ľṹ
    EV_WATCHER_LIST��EV_WATCHER�ṹ������ڵ�ṹ��fd�Ǽ������ļ���������events�Ǹ���
    Ȥ���¼��� ev_io������������һ���𣬱����ļ����������ܽ����һ���ˡ�ev_io��ʵ����
    �洢��loop->anfds�Ľṹ�С�anfds�Ľṹ����ͼ��ʾ��
            ANFD
          +--------+      ev_io linked list
          |  head  |----> w0 ----> w1 ----> w2
          |--------|
          | events |
          |--------|
          |  ...   |
          +--------+
             /|\
 loop->anfds  |
    +-----+   |  
    | fd0 |----  
    +-----+     
    | fd1 |       
    +-----+       
    | ... |       
    +-----+
    | fdn |
    +-----+
 anfds��ʵ��һ�����飬��ʹ��fd��Ϊ�±꣬�����е�Ԫ����һ��ANFD�Ľṹ��ANFD��һ��ά��
 fd��Ϣ�Ľṹ�塣���У�events��¼�˵�ǰfd�ϸ���Ȥ���¼��ļ�¼��head��watcher�б��ͷ
 ָ�룬����б���������fd��ע���watcher�б���fd�Ĵ�С������anfds��������anfds��
 ������Ӧ����չ��

ev_io�Ĳ���
    ��ǰ��Ľ�������֪����Ҫͨ��libev������fd�ϵ��¼�����Ҫ�Ȳ���һ��ev_io��libev��
    loop�С�ev_io�Ĳ����������װ��ev_io_start�����С��������ʣ�libev���Ȼ����fd��
    ����Ӧ��watcher�б�������watcher���뵽�б��С��������������fd_change��������
    fd���뵽loop->fdchanges�С�fdchanges��һ���򵥵����飬 ��¼���ǵ�ǰע���¼��з�
    ���ı��fd������Ϊֹ����ev_io�Ĳ�����ɣ���������в���ʱ����۶���O(1)�� 
ev_io��ѡȡ
    ǰ�������Ѿ���libev��loop�в�����һ��ev_io����ôlibev����ô�����ev_ioע�ᵽ�ײ�
    io����Ӧ�ײ��io�¼����أ� ��ev_run�����п��Կ�����ev_io��ѡȡ��fd_reify��
    backend_poll��������������ɡ� 
    fd_reify�����Ĺ�����Ҫ�Ǳ���fdchanges������Ӧ�б��watcher��events�ֶκϲ���ANFD
    �ṹ��events�ֶΡ�ANFD������µ�events��ԭ��������events��һ�£����ʾ�����fd��
    �������¼��������˱仯����Ҫ��fd���¼�����ͨ��backend_modifyע�ᵽ�ײ��io�⡣ 
    ��ѭ���ĺ��棬������backend_poll�����fd���Ƿ���ע����¼�������������¼�����
    ����ͨ��fd_event����������fd��Ӧ��watcher�б��Ƚ�ÿ��watcher�ϵ�events�ֶ��뷢
    �����¼�eventֵ���ҳ�������watcher��ӵ�pendings�С�
    �����Щpendings�е�watcher����ѭ������ǰ����ev_invoke_pending��ͳһ������
ev_io���Ƴ�
    ev_io���Ƴ���ev_io_stop����ɡ����ȣ����ȼ���watcher�Ƿ���pendings�б��У����
    �ǣ����ȴ�pendings��ɾ����watcher��pendings��һ�����飬libev�е�����һ����������
    ��Ԫ��������ά���ġ�ɾ�������е�һ��Ԫ�أ�ֻҪ������ĩβ��Ԫ���滻����ɾ����Ԫ��
    ������Ԫ��������һ�Ϳ����ˣ�������ʱ�临�Ӷ���O(1) �� 
    ����������ͨ��fd�ҵ�watcher�б�����ɾ�����watcher�����������Ҫ�����б��ҵ���
    ɾ����watcher������ƽ��ʱ�临�Ӷ���O(n)������n��ע����fd�ϵ�watcher������ һ����
    ����������̫��
    Ȼ���ǰ�watcher��active��־λ��λ��������ȫ��active��watcher������
    ����ǰ�fd���뵽fdchanges�У���Ϊ�Ƴ�һ��watcher�����ܻ�ı�fd�ϸ���Ȥ���¼�����
    ��Ҫ����һ��ѭ�������¼����fd�ϵ��¼����ϡ�
*/

#define ev_init(ev,cb_) do {			\
  ((ev_watcher *)(void *)(ev))->active  =	\
  ((ev_watcher *)(void *)(ev))->pending = 0;	\
  ev_set_priority ((ev), 0);			\
  ev_set_cb ((ev), cb_);			\
} while (0)


int x_ev_io_init(ev_io *ev,void *cb,int fd,int events)
{
	ev->active   = 0;
	ev->pending  = 0;
	ev->priority = 0;
	ev->cb       = cb;
	ev->fd       = fd; 
	ev->events   = (events) | EV__IOFDSET;
}

/*-----------------------------------------------------------------------------------
 notes01
    �ǶԺ��� ��ev_verify"�ĵ��ã���ôev_verify�Ǹ�ʲô���أ����ĵ��Ļ���This can be 
    used to catch bugs inside libev itself��������������Ļ�������ȥ���Libev���ڲ�
    ���ݽṹ���жϸ��߽�ֵ�Ƿ�����������ʱ��assert����
-----------------------------------------------------------------------------------*/
void x_ev_io_start (ev_loop *loop, ev_io *w)
{
    int fd = w->fd;

    if (expect_false (ev_is_active (w)))
        return;

    assert (("libev: ev_io_start called with negative fd", fd >= 0));
    assert (("libev: ev_io_start called with illegal event mask", !(w->events & ~(EV__IOFDSET | EV_READ | EV_WRITE))));

    EV_FREQUENT_CHECK; /* notes01 */

    ev_start (loop, (W)w, 1);
    array_needsize (ANFD, anfds, anfdmax, fd + 1, array_init_zero);
    wlist_add (&anfds[fd].head, (WL)w);

    /* common bug, apparently */
    assert (("libev: ev_io_start called with corrupted watcher", ((WL)w)->next != (WL)w));

    fd_change (EV_A_ fd, w->events & EV__IOFDSET | EV_ANFD_REIFY);
    w->events &= ~EV__IOFDSET;

    EV_FREQUENT_CHECK;
}

