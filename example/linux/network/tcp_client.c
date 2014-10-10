#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"



void str_cli_v3(FILE *fp, int sockfd)
{
    int     maxfdp1, stdineof;
    fd_set  rset;
    char    buf[MAXLINE];
    int     n;
    stdineof = 0;
    FD_ZERO(&rset);
	
    for ( ; ; ) 
	{
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
		
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
		
        if(select(maxfdp1, &rset, NULL, NULL, NULL) < 0)
		{
			printf("tcp client select error\r\n");
		}

        if (FD_ISSET(sockfd, &rset)) /* socket is readable */
		{  
            if ( (n = read(sockfd, buf, MAXLINE)) == 0) 
			{
                if (stdineof == 1)
                    return;       /* normal termination */
                else
                    printf("str_cli: server terminated prematurely");
            }
			else if(n < 0)
			{
			    printf("\r\ntcp client error read 1");
			}
			
            if(n != write(fileno(stdout), buf, n))
				printf("\r\ntcp client error write 1");
        }
		
        if (FD_ISSET(fileno(fp), &rset))  /* input is readable */
		{ 
            if ( (n = read(fileno(fp), buf, MAXLINE)) == 0) 
			{
			    /*����EOF�������˳�,����Ϊ��ʱ���׽�������ܻ�������û�ж�ȡ*/
                stdineof = 1;
                if(shutdown(sockfd, SHUT_WR) < 0)
					printf("\r\ntcp client error shutdown");  /* send FIN */
				
                FD_CLR(fileno(fp), &rset);
                continue;
            }
			else if(n < 0)
			{
			    printf("\r\ntcp client error read 2 ");
			}
			
            if(n != write(fileno(stdout), buf, n))
				printf("\r\ntcp client error write 2 ");
        }
    }
}



/*
�ڱ�׼������׽�����select�ɶ�����
��׼����:���ݻ�EOF
�׽���  :RST ���� FIN
Three conditions are handled with the socket:
1 If the peer TCP sends data, the socket becomes readable and read returns greater than 0 (i.e., the number of bytes of data).
2 If the peer TCP sends a FIN (the peer process terminates), the socket becomes readable and read returns 0 (EOF).
3 If the peer TCP sends an RST (the peer host has crashed and rebooted), the socket becomes readable, read returns �C1, 
  and errno contains the specific error code.
*/
void str_cli_v2(FILE *fp, int sockfd)
{
     int     maxfdp1;
	 int     ready_nums;
     fd_set  rset;
     char    sendline[MAXLINE], recvline[MAXLINE];

     FD_ZERO(&rset);
     for ( ; ; )  
	 {
         FD_SET(fileno(fp), &rset);
         FD_SET(sockfd, &rset);
         maxfdp1 = max(fileno(fp), sockfd)  +  1;
		 
         ready_nums = select(maxfdp1,  &rset,  NULL,  NULL,  NULL);

		 if(ready_nums < 0)
		 {
		     printf("tcp client select error\r\n");
			 //return;
		 }

         if (FD_ISSET(sockfd,  &rset))  /* socket is readable */
		 {  
             if (x_readline(sockfd, recvline, MAXLINE) == 0)
                 printf("str_cli: server terminated prematurely");
			 
			 if (fputs(recvline, stdout) == EOF)
		         printf("\r\ntcp client error: str_cli -> fputs");
         }

         if (FD_ISSET(fileno(fp), &rset)) /*  input is readable */ 
		 { 
		     /*����ط��и�����:������EOFʱ,�����˳���,����ʱ�����׽����ﻹ������û�ж�.*/
             if (fgets(sendline, MAXLINE, fp) == NULL)
                 return;          /* all done */
			 
			 if(strlen(sendline) != x_writen(sockfd, sendline, strlen(sendline)))
			    printf("\r\ntcp client error:str_cli -> x_writen");
         }
     }
}

/*V1�汾�и�����:���׽����Ϸ��������ʱ��,�ͻ��˿���������fgets����*/
void str_cli_v1(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];	
	char	*read_string = NULL;

    do
    {
        /*������ֹ1:���ͻ��˼���EOF,fgets����NULL,��ͻ��˵���exit�˳�*/
	    read_string = fgets(sendline, MAXLINE, fp);

	    if( read_string == NULL && ferror(fp))
		    printf("\r\ntcp client error:str_cli -> fgets");

		if(NULL != read_string)
		{

		    /*����������쳣��ֹ,����һ��FIN.�ͻ����յ�FIN�󷵻�ack.��ʱ�ͻ��˿���������fgets,������ַ���,�ߵ�����
			  ����write����������,�����Ϣ���Է���ȥ��ΪTCPֻ�ر���һ��.�������յ���Ϣ��,������ǰ�򿪵��Ǹ��׽��ֵ�
			  �����Ѿ���ֹ,������Ӧһ��RST(��һ��д����RST,�ڶ���д����SIGPIPE�ź�,д����EPIPE����).Ȼ���ͻ����̿���
			  �����RST,��Ϊ���ڵ���write����������readline,�������������FIN����,����readline��������0(EOF)*/
			if(strlen(sendline) != x_writen(sockfd, sendline, strlen(sendline)))
			    printf("\r\ntcp client error:str_cli -> x_writen");

		    if (x_readline(sockfd, recvline, MAXLINE) == 0)
			    printf("tcp client error:str_cli server terminated prematurely");

			if (fputs(recvline, stdout) == EOF)
				printf("\r\ntcp client error: str_cli -> fputs");
		}
    }while(NULL != read_string);

    #if 0
	while (Fgets(sendline, MAXLINE, fp) != NULL) 
	{

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
	}
	#endif
}


/*./cli.exe 192.168.1.101*/
int main(int argc, char **argv)
{
	int					sockfd;
	int                 ret = 0;
	struct sockaddr_in	servaddr;

	if (argc != 2)
	{
		printf("usage: tcpcli <IPaddress>");
		return 1;
	}

	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	
	if(sockfd < 0)
	{
	    printf("tcp client error socket fail %d",sockfd);
		return 1;
	}

	memset(&servaddr,0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    /*�ͻ���connect������������,�յ�ack�󷵻�(�ڶ�������),��������Ҫ���������ֲŷ���*/
	ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		printf("tcp client error connect fail %d",ret);
		return 1;
	}

	str_cli_v3(stdin, sockfd);		/* do it all */
	
	/*������ֹ 2:exit�رմ򿪵�������,���ر��׽���ʱ,�ͻ��˷���һ��FIN��������,�յ���������ack��,TCPǰ�벿�ֹر�
	  ���˷������׽��ִ���CLOSE_WAIT״̬,�ͻ����׽��ִ���FIN_WAIT_2״̬*/

    /*close decrements the descriptor's reference count and closes the socket only if the count reaches 0. 
	  close terminates both directions of data transfer, reading and writing. */
	exit(0);
}

