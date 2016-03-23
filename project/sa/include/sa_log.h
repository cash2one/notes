/*-----------------------------------------------------------------------------------
 log: sa_log.c sa_log.h
 dep: sa_util.h   mkdirs
 ----------------------------------------------------------------------------------*/

#ifndef __SA_LOG_H__
#define __SA_LOG_H__

/*
 http://blog.csdn.net/shanzhizi/article/details/17844509

 ���׺������岿����ɣ��ֱ��Ǻ����BUF_SIZE���ṹ��log_st��log_init������log_debug������log_checksize������
 ���к����BUF_SIZE��������ÿ���������־����󳤶ȣ�
 �ṹ�������洢�û����󣬰����ļ�·�����ļ��������š������ļ�����С�������ʽ��־���ļ�������־�ȣ�
 log_init������������û�����¼�롢�ļ������ȹ��ܣ���mian�����Ŀ�ʼ����һ�μ��ɣ�
 log_debug�����Ĺ��ܸ�printf�����ƣ�����printf�����Ͻ��е����䣬ʵ�ֽ���־�������Ļ����д�뵽�ļ���
 ����Ҫ��ӡ��־�ĵط����øú�����
 log_checksize�������������־�ļ���С�Ƿ񳬹�����С���ƣ�����Ҫ����ʱ���߶����������
 ���һֱ�����ã�����־�ļ�������ָ��������С���ơ�
 */


#define BUF_SIZE 1024  

typedef struct _log_st log_st;  
struct _log_st  
{  
    char path[128];
    char name[128];  
    int fd;  
    int size;  
    int level;  
    int num;  
};  


log_st *log_init(char *log_path, char *logfile_name, int logfile_size);
void log_debug(log_st *log, const char *msg, ...);
void log_checksize(log_st *log);


#endif
