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
    puts ("timeout\n");
	
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
3 ./configure --prefix=/usr     //specify path,default is /usr/local
4 make
5 make install

---- reference
http://www.360doc.com/content/14/0814/09/12144668_401718271.shtml
-----------------------------------------------------------------------------------*/


/*

linux-iu5j:/home/xyx/srccode/libev/libev-4.19 # make install                                                                        
make[1]: Entering directory `/home/xyx/srccode/libev/libev-4.19'                                                                    
 /bin/mkdir -p '/usr/lib'                                                                                                           
 /bin/sh ./libtool   --mode=install /usr/bin/install -c   libev.la '/usr/lib'                                                       
libtool: install: /usr/bin/install -c .libs/libev.so.4.0.0 /usr/lib/libev.so.4.0.0                                                  
libtool: install: (cd /usr/lib && { ln -s -f libev.so.4.0.0 libev.so.4 || { rm -f libev.so.4 && ln -s libev.so.4.0.0 libev.so.4; }; 
})                                                                                                                                  
libtool: install: (cd /usr/lib && { ln -s -f libev.so.4.0.0 libev.so || { rm -f libev.so && ln -s libev.so.4.0.0 libev.so; }; })    
libtool: install: /usr/bin/install -c .libs/libev.lai /usr/lib/libev.la                                                             
libtool: install: /usr/bin/install -c .libs/libev.a /usr/lib/libev.a                                                                
libtool: install: chmod 644 /usr/lib/libev.a                                                                                        
libtool: install: ranlib /usr/lib/libev.a                                                                                           
libtool: finish: PATH="/home/xyx/bin:/usr/local/bin:/usr/bin:/sbin:/usr/sbin:/bin:/usr/bin/X11:/usr/X11R6/bin:/usr/games:/usr/lib/mi
t/bin:/usr/lib/mit/sbin:/sbin" ldconfig -n /usr/lib                                                                                 
----------------------------------------------------------------------                                                              
Libraries have been installed in:                                                                                                   
   /usr/lib                                                                                                                         
                                                                                                                                    
If you ever happen to want to link against installed libraries                                                                      
in a given directory, LIBDIR, you must either use libtool, and                                                                      
specify the full pathname of the library, or use the `-LLIBDIR'                                                                     
flag during linking and do at least one of the following:                                                                           
   - add LIBDIR to the `LD_LIBRARY_PATH' environment variable                                                                       
     during execution                                                                                                               
   - add LIBDIR to the `LD_RUN_PATH' environment variable                                                                           
     during linking                                                                                                                 
   - use the `-Wl,-rpath -Wl,LIBDIR' linker flag                                                                                    
   - have your system administrator add LIBDIR to `/etc/ld.so.conf'                                                                 
                                                                                                                                    
See any operating system documentation about shared libraries for                                                                   
more information, such as the ld(1) and ld.so(8) manual pages.                                                                      
----------------------------------------------------------------------                                                              
 /bin/mkdir -p '/usr/include'                                                                                                       
 /usr/bin/install -c -m 644 ev.h ev++.h event.h '/usr/include'                                                                      
 /bin/mkdir -p '/usr/share/man/man3'                                                                                                
 /usr/bin/install -c -m 644 ev.3 '/usr/share/man/man3'                                                                              
make[1]: Leaving directory `/home/xyx/srccode/libev/libev-4.19'




*/


