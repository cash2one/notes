/*-----------------------------------------------------------------------------------
 @which_clock��������
    CLOCK_REALTIME:ϵͳʵʱʱ��,��ϵͳʵʱʱ��ı���ı�,����UTC1970-1-1 0:0:0��ʼ��
    ʱ,�м�ʱ�����ϵͳʱ�䱻�û��ó�����,���Ӧ��ʱ����Ӧ�ı�
    CLOCK_MONOTONIC:��ϵͳ������һ����ʼ��ʱ,����ϵͳʱ�䱻�û��ı��Ӱ��
    CLOCK_PROCESS_CPUTIME_ID:�����̵���ǰ����ϵͳCPU���ѵ�ʱ��
    CLOCK_THREAD_CPUTIME_ID:���̵߳���ǰ����ϵͳCPU���ѵ�ʱ��

 ��Ӧ��ϵͳ����
 long sys_clock_gettime (clockid_t which_clock, struct timespec *tp);

 example: clock_gettime_eg01()
-----------------------------------------------------------------------------------*/
long clock_gettime (clockid_t which_clock, struct timespec *tp);

