#include <ev.h>    // a single header file is required
#include <stdio.h> 
#include <stdlib.h>


static void timeout_cb01 (struct ev_loop *loop, ev_timer *w, int revents)
{
    puts ("timeout\n");
	
    ev_break (loop, EVBREAK_ONE);
}

int timer_libev_eg01 (void)
{
    struct ev_loop *loop = EV_DEFAULT;
	ev_timer timer;
	
    ev_timer_init (&timer, timeout_cb01, 1.5, 0.);
    ev_timer_start (loop, &timer);
	
    ev_run(loop, 0);
	
    return 0;
}

static void timeout_cb02 (struct ev_loop *loop, ev_timer *w, int revents)
{
     //.. ten seconds without any activity
     
	 puts ("timeout02\n");
}

int timer_libev_eg02()
{
	struct ev_loop *loop = EV_DEFAULT; 

	ev_timer mytimer;
	ev_timer_init (&mytimer, timeout_cb02, 0., 2.); /* note, only repeat used */
	ev_timer_again (loop,&mytimer); /* start timer */
	ev_run (loop, 0);
	
	// and in some piece of code that gets executed on any "activity":
	// reset the timeout to start ticking again at 10 seconds
	printf("break from ev_run\n");
	ev_timer_again (loop,&mytimer);

	return 0;

}

int main(int argc, char *argv[])
{
    int tflag = 0;
	
    if(1 == argc) {
		return timer_libev_eg01();
    } else if(2 == argc) {
		tflag = atoi(argv[1]);
		if(1 == tflag) {
			return timer_libev_eg01();
		} else if(2 == tflag) {
			return timer_libev_eg02();
		} else {
		    printf("inpara error01\n");
			return 0;
		}
	} else {
	   printf("inpara error\n");
	   return 0;
	}
}

/*
ev_timer_init
ev_timer_set
ev_timer_again 
ev_timer_remaining

ev_tstamp repeat [read-write]


ev_timer - relative and optionally repeating timeouts
    Timer watchers are simple relative timers that generate an event after a given t-
    ime, and optionally repeating in regular intervals after that.

    The timers are based on real time, that is, if you register an event that times -
    out after an hour and you reset your system clock to January last year, it will -
    still time out after (roughly) one hour. "Roughly" because detecting time jumps -
    is hard, and some inaccuracies are unavoidable ( the monotonic clock option helps 
    a lot here).

    The callback is guaranteed to be invoked only after its timeout has passed (not -
    at, so on systems with very low-resolution clocks this might introduce a small d-
    elay). If multiple timers become ready during the same loop iteration then the o-
    nes with earlier time-out values are invoked before ones of the same priority wi-
    th later time-out values (but this is no longer true when a callback calls ev_run 
    recursively).




1.������ʱ�������

��ʱ���ڳ����п������̶�����tick������Ҳ������һ���ԵĶ�ʱ������Libev���붨ʱ�����ƵĻ��и������¼�watcher���䱾�ʶ���һ���ģ�ֻ����ʱ��ļ��㷽�������в�ͬ���������Լ���һ���¼�����Ķѡ����ڶ�ʱ���¼������ǰ���֮ǰ˵��˳���ev_init��ʼ����

1.1��ʱ��������ĳ�ʼ��

��ʱ����ʼ��ʹ�� ev_init(&timer_w,timer_action);,������̺�֮ǰ��IO���ƣ���Ҫ�������û����active��pending��priority�Լ����������ص�����cb��

1.2���ö�ʱ��������Ĵ�������

ͨ�� ev_timer_set(&timer_w,2,0);�������ö�ʱ����2���Ӻ󱻴����������������������0����һ������0��������nʱ����ô�ڵ�һ�δ�����2��󣩣�ÿ��n����ٴδ�����ʱ���¼���

��Ϊһ���궨�� do { ((ev_watcher_time *)(ev))->at = (after_); (ev)->repeat = (repeat_); } while (0) Ҳ�������������ඨʱ��watcher�ġ�at��Ϊ�����¼����Լ��ظ�������repeat����

1.3����ʱ��ע�ᵽ�¼���������

ev_timer_start(main_loop,&timer_w);�Ὣ��ʱ�������ע�ᵽ�¼��������ϡ������� ev_at (w) += mn_now; �õ�δ����ʱ�䣬�����ŵ�ʱ�����Ķѡ�timers������ΪȨ�ء�Ȼ��ͨ��֮ǰ˵���ġ�ev_start���޸�������loop��״̬�����������ֿ����˶�̬��С�������ˡ�Libev�Ķѵ��ڴ����Ҳ��ͨ�������Ĺ�ϵ�ġ���������ѵ�ʵ�֣�����Ȥ�Ŀ�����ϸ����ʵ�֡�����Ĳ������ǽ����ʱ��Ȩ�طŵ����к��ʵ�λ�á�����ѵ�Ԫ�ĽṹΪ��

typedef struct {
    ev_tstamp at;
    WT w;
} ANHE;
��ʵ�ʾ���һ��ʱ��at�Ϲ�һ���Ŷ�ʱ��watcher��list������ʱʱ������ִ����Щ��ʱ��watcher�ϵĴ����ص�������

1.4��ʱ��������Ĵ���

�������һ���¼�������ѭ��������δ���ʱ��������ġ�����������Ȼ�׿������Ĳ��֣�
ֻ�Ҷ�ʱ����صĿ����ڡ�/ calculate blocking time /�������棬���ǿ�������blocking ti-
me��ʱ����ȣ�
    if (timercnt) {
        ev_tstamp to = ANHE_at (timers [HEAP0]) - mn_now;
        if (waittime > to) waittime = to;
    }
����ж�ʱ������ô�ʹӶ�ʱ���ѣ�һ����С�ѣ�timers��ȡ�öѶ�����С��һ��ʱ�䡣������
��֤�������ʱ��ǰ���Դ�backend_poll�г�����������ִ��timers_reify����pengding�Ķ�
ʱ����

��timers_reify������ȡ��С�ѵĶѶ���������ϵ�ANHE.atС�ڵ�ǰʱ�䣬��ʾ�ö�ʱ��watcher
��ʱ�ˣ���ô����ѹ��һ�������У�������ʵ��ִ��pendings��ά�����϶�Ӧ���ȼ��ϵ�watcher
�Ǵ�β��ͷ����ģ������������һ��������ʱ���Ⱥ�δ��µ�һ���м�����loop->rfeeds�С�Ȼ
�����������ev_invoke_pending���뵽pendings��ά�����С�������ִ��pending�¼��Ĵ�����
����ʱ��Ϳ��Ա�֤��ʱ�俿ǰ�Ķ�ʱ������ִ�С����� feed_reverse�� feed_reverse_done����
����ʱ�Ķ�ʱ�����뵽loop->rfeeds�ݴ������Լ����ݴ������е�pending��watcher���뵽pengdings
����Ĳ�������pending��watcher���뵽pendings���飬�����Ĳ����ͺ�֮ǰ��һ���ˡ�������ִ
����Ӧ�Ļص�������

��������л��ж϶�ʱ���� w->repeat ��ֵ�������Ϊ0����ô�����øö�ʱ����ʱ�䣬������ѹ
�������ȷ��λ�ã�������ָ����ʱ������ֻᱻִ�С������Ϊ0����ô����ev_timer_stop�ر�
�ö�ʱ���� ������ͨ��clear_pending��pendings�����м�¼�ĸ�watcher�ϵĻص�����Ϊһ����ִ
���κζ������ƶ�����

�ܽ�һ�¶�ʱ��������backend_poll֮ǰͨ����ʱ���Ѷ��ĳ�ʱʱ�䣬��֤blocking��ʱ�䲻����
����Ķ�ʱ��ʱ�䣬��backend_poll���غ󣬴Ӷ�ʱ������ȡ�ó�ʱ��watcher���뵽pendings��
ά�����У��Ӷ��ں��������п���ִ������ע��Ĵ���������Ȼ��Ӷ�ʱ���������ɾ���ö�ʱ��
�������ú�ev_start��Ӧ��ev_stop�޸�������loop��״̬����loop->activecnt����һ��������
watcher��active���㡣

���������Ե��¼��������ͬ���Ĵ�����̡�ֻ�ǽ�timers_reify������periodics_reify������
������������¼������������������ƶ�ʱ�������Ƿ�repeat���жϲ������ж��Ƿ����µ���ʱ
�䣬�����Ƿ��ظ����߼�����Щ���´���Ƚ�������⣬���ﲻ��׸������

*/
