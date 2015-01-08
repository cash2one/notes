
/* socklent_t   uint32_t */

#include<netinet/in.h>

struct sockaddr {          /*ͨ���׽��ֵ�ַ�ṹ*/
  uint8_t      sa_len;
  sa_family_t  sa_family;    /* address family: AF_xxx value */
  char         sa_data[14];  /* protocol-specific address */
};


struct in_addr {
  in_addr_t   s_addr;           /* 32-bit IPv4 address network byte ordered */
};

struct sockaddr_in {         /*ipv4�׽��ֵ�ַ�ṹ*/
  uint8_t         sin_len;      /* length of structure (16) */
  sa_family_t     sin_family;   /* AF_INET */
  in_port_t       sin_port;     /* 16-bit TCP or UDP port number network byte ordered */
  struct in_addr  sin_addr;     /* 32-bit IPv4 address  network byte ordered */
  char            sin_zero[8];  /* unused */
};


/************************************************************************************
 @msg_name @msg_namelen
    The @msg_name and @msg_namelen members are used when the socket is not connected 
    (e.g., an unconnected UDP socket).They are similar to the fifth and sixth arguments 
    to @recvfrom and @sendto: @msg_name points to a socket address structure in which 
    the caller stores the destination's protocol address for @sendmsg, or in which 
    @recvmsg stores the sender's protocol address. If a protocol address does not need 
    to be specified (e.g., a TCP socket or a connected UDP socket), @msg_name should 
    be set to a null pointer. @msg_namelen is a value for @sendmsg, but a value-result 
    for @recvmsg.
 @msg_iov  @msg_iovlen
    The @msg_iov and @msg_iovlen members specify the array of input or output buffers 
    (the array of iovec structures),similar to the second and third arguments for @readv 
    or @writev. 
 @msg_control  @msg_controllen
    The @msg_control and @msg_controllen members specify the location and size of the 
    optional ancillary data. msg_controllen is a value-result argument for @recvmsg. 
************************************************************************************/
struct msghdr {
void		 *msg_name; 	   /* protocol address */
socklen_t	  msg_namelen;	   /* size of protocol address */
struct iovec *msg_iov;		   /* scatter/gather array */
int 		  msg_iovlen;	   /* # elements in msg_iov */
void		 *msg_control;	   /* ancillary data (cmsghdr struct) */
socklen_t	  msg_controllen;  /* length of ancillary data */
int 		  msg_flags;	   /* flags returned by recvmsg() */
};

/*----------------------------------- @getsockopt @level --------------------------*/
#define SOL_SOCKET /* �����׽ӿ� */
#define IPPROTO_IP
#define IPPRO_TCP
/*----------------------------------- @getsockopt @optname ------------------------*/
#define SO_RCVTIMEO  /* ���ճ�ʱ struct timeval */
#define SO_REUSEADDR /* �������ñ��ص�ַ tcp_udp_serv*/
#define SO_LINGER

/*----------------------------------- @recv @flags ------------------------*/
#define MSG_DONTROUTE
#define MSG_DONTWAIT

/*
---->�׽��ֵ�ַ
ÿ��Э���嶼�������Լ����׽��ֵ�ַ�ṹ��

ipv4�׽��ֵ�ַ�ṹ,Ҳ��Ϊ�����׽��ֵ�ַ�ṹ struct sockaddr_in
ͨ���׽��ֵ�ַ�ṹ 

�׽�����ͨ�Ŷ˵�ĳ��󣬷����׽�����Ҫʹ���׽���������(���ļ�����������)�� 
�׽�����������UNIXϵͳ�����ļ�������ʵ�ֵġ�


---->ԭʼ�׽���
ԭʼ�׽��ֿ��Զ�д�ں�û�д����IP���ݰ��������׽��֣�����TCP����ֻ�ܶ�ȡTCPЭ�����
�ݣ����ݰ��׽���ֻ�ܶ�ȡUDPЭ������ݡ���ˣ����Ҫ��������Э�鷢�����ݱ���ʹ��ԭʼ
�׽��֡�

ԭʼ�׽����ṩtcp��udp�׽��ֲ��ṩ��������������
1 ��дicmpv4��igmpv4��icmpv6�ȷ���
2 ��д�ں˲�������Э���ֶε�ipv4���ݱ�
3 ����ipv4ͷ��

ԭʼ�׽��ֵ�ʹ�ó���
1 ������;��̽��Ӧ��
2 �������ݰ������Ӧ��
3 ������;�Ĵ���Ӧ��

