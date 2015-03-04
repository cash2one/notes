#include <ev.h>    // a single header file is required
#include <stdio.h> // for puts

ev_io stdin_watcher;       /* every watcher type has its own typedef'd struct */
ev_timer timeout_watcher;  /* with the name ev_TYPE */

/*-----------------------------------------------------------------------------------
 all watcher callbacks have a similar signature. this callback is called when data is 
 readable on stdin

 notes01
    for one-shot events , one must manually stop the watcher . with its corresponding 
    stop function.
 notes02
    this causes all nested ev_run's to stop iterating
-----------------------------------------------------------------------------------*/
static void stdin_cb (EV_P_ ev_io *w, int revents)
{
    puts ("stdin ready");
    ev_io_stop (EV_A_ w);         /* notes01 */
    ev_break (EV_A_ EVBREAK_ALL); /* notes02 */
}

/* another callback, this time for a time-out */
static void timeout_cb (EV_P_ ev_timer *w, int revents)
{
    puts ("timeout");
    ev_break (EV_A_ EVBREAK_ONE);
}

/*-----------------------------------------------------------------------------------
 ����libev�����ĵ�������
 1 ��ȡev_loopʵ����ev_loop���������Ͽ��Կ�������������һ���¼�ѭ����Ҳ�����Ǻ������
   ����Ҫ��֯�ߡ�
 2 �����ͳ�ʼ��watcher��libev�ж�����һϵ�е�watcher��ÿ��watcher����һ���ض����¼���
   һ�����ͨ��ev_TYPE_init����������һ��watcherʵ����TYPE��ĳһ��watcher���ͣ��磺io, 
   timer�ȣ��������зֱ𴴽���io��timer����watcher����������Ӧ�Ļص�������������Ȥ��
   �¼������󣬶�Ӧ�Ļص��������ᱻ���á�
 3 ��watcherע�ᵽev_loop�С�һ�����ͨ��ev_TYPE_start��������ɡ�ע��ɹ���watcher
   ���loop���������ˣ���loop�м�⵽����Ȥ���¼����������֪ͨ��ص�watcher��
 4 �����¼�ѭ���� �������ev_run�������¼�ѭ�������󣬵�ǰ�߳�/���̽��ᱻ������ֱ��ѭ
   ������ֹ��
 5 ������������У��������ص������е�ev_break����������ֹѭ���ĵط�����5.5�볬ʱ���Ǳ�
   ׼�����������¼��������뵽��Ӧ�Ļص�������Ȼ�����ֹ�¼�ѭ�����˳�����

 notes01
    use the default event loop unless you have special needs
 notes02
    initialise an io watcher, then start it . this one will watch for stdin to become 
    readable.
 notes03
    initialise a timer watcher, then start it.simple non-repeating 5.5 second timeout
-----------------------------------------------------------------------------------*/
int main (void)
{
    struct ev_loop *loop = EV_DEFAULT;     /* notes01 */
	
    ev_io_init (&stdin_watcher, stdin_cb, /*STDIN_FILENO*/ 0, EV_READ);
    ev_io_start (loop, &stdin_watcher);   /* notes02 */
	
    ev_timer_init (&timeout_watcher, timeout_cb, 5.5, 0.);
    ev_timer_start (loop, &timeout_watcher);/* notes03 */
	
    ev_run(loop, 0); /* now wait for events to arrive */
    return 0;         /* break was called, so exit */
}

/*-----------------------------------------------------------------------------------
---- Makefile
LD_RUN_PATH=/usr/local/lib/
export LD_RUN_PATH

all:	
	gcc -LLIBDIR libev_eg01.c -lev
all2: # for cygwin	
	gcc -L/usr/local/lib/ libev_eg01.c -lev

---- setup libev
1 tar xzf libev-3.9.tar.gz
2 cd libev-3.9
3 ./configure --prefix=/usr //specify path,default is /usr/local
4 make
5 make install

---- reference
http://www.360doc.com/content/14/0814/09/12144668_401718271.shtml
-----------------------------------------------------------------------------------*/

