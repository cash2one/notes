
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

/*
 Unix domain socket address structure, which is defined by including the <sys/un.h> 
 header.
 
 POSIX renames the Unix domain protocols as "local IPC," to remove the dependence on 
 the Unix OS. The historical constant AF_UNIX becomes AF_LOCAL.Nevertheless,we still 
 use the term "Unix domain" as that has become its de facto name, regardless of the 
 underlying OS. Also, even with POSIX  attempting to make these OS-independent, the 
 socket address structure still retains the _un suffix!
 
 @sun_path
    The pathname stored in the sun_path array must be null-terminated.The unspecified 
    address is indicated by a null string as the pathname, that is, a structure with 
    sun_path[0] equal to 0. This is the Unix domain equivalent of the IPv4 INADDR_ANY 
    constant and the IPv6 IN6ADDR_ANY_INIT constant.
*/
#include <sys/un.h>
struct sockaddr_un {
  sa_family_t sun_family;     /* AF_LOCAL */
  char        sun_path[104];  /* null-terminated pathname */
};

#define SUN_LEN /* is provided and it takes a pointer to a sockaddr_un structure and 
returns the length of the structure,including the number of non-null bytes in the pathname.*/ 

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

#include <sys/socket.h>
/*
 @l_onoff @l_linger
    If @l_onoff is 0, the option is turned off. The value of @l_linger is ignored and 
    the previously discussed TCP default applies: @close returns immediately.
    If @l_onoff is nonzero and @l_linger is zero, TCP aborts the connection when it is 
    closed.That is,TCP discards any data still remaining in the socket send buffer and 
    sends an RST to the peer,not the normal four-packet connection termination sequence.

    If @l_onoff is nonzero and @l_linger is nonzero, then the kernel will linger when 
    the socket is closed . That is, if there is any data still remaining in the socket 
    send buffer,the process is put to sleep until either: (i) all the data is sent and 
    acknowledged by the peer TCP,or (ii) the linger time expires.If the socket has been 
    set to nonblocking, it will not wait for the close to complete, even if the linger 
    time is nonzero. 
    When using this feature of the SO_LINGER option,it is important for the application 
    to check the return value from close, because if the linger time expires before the 
    remaining data is sent and acknowledged,close returns EWOULDBLOCK and any remaining 
    data in the send buffer is discarded.
*/
struct linger {      
    int l_onoff;  //0=off, nonzero=on(����)      
    int l_linger; //linger time(�ӳ�ʱ��)
};

/*
 SO_ERROR
    When an error occurs on a socket, the protocol module in a Berkeley-derived kernel 
    sets a variable named @so_error for that socket to one of the standard Unix Exxx 
    values. This is called the pending error for the socket.The process can then obtain 
    the value of so_error by fetching the SO_ERROR socket option. The integer value 
    returned by getsockopt is the pending error for the socket. The value of so_error 
    is then reset to 0 by the kernel
 SO_LINGER    struct linger
*/
#define SO_RCVTIMEO  /* ���ճ�ʱ struct timeval */
#define SO_REUSEADDR /* �������ñ��ص�ַ tcp_udp_serv*/
#define SO_LINGER
#define SO_ERROR  /* eg:connect_nonb */
/*-----------------------------------------------------------------------------------
                     @send @recv @flags
-------------------------------------------------------------------------------------
 MSG_DONTROUTE:
    ��send����ʹ�õı�־.�����־����IPЭ��.Ŀ�������ڱ�����������,û�б�Ҫ����·�ɱ�
    �����־һ����������Ϻ�·�ɳ�������.
 MSG_OOB:
    ��ʾ���Խ��պͷ��ʹ��������.���ڴ������������Ժ����͵�.
MSG_PEEK:
    ��recv������ʹ�ñ�־,��ʾֻ�Ǵ�ϵͳ�������ж�ȡ����,�������ϵͳ������������.����
    �´ζ���ʱ��,��Ȼ��һ��������.һ�����ж�����̶�д����ʱ����ʹ�������־.
MSG_WAITALL
    ��recv������ʹ�ñ�־,��ʾ�ȵ����е���Ϣ����ʱ�ŷ���.ʹ�������־��ʱ��recv��һֱ��
    ��,ֱ��ָ������������,�����Ƿ����˴���. 
    1)��������ָ�����ֽ�ʱ,������������.����ֵ����len 
    2)���������ļ��Ľ�βʱ,������������.����ֵС��len 
    3) ��������������ʱ,����-1,�����ô���Ϊ��Ӧ�Ĵ����(errno)
*/
#define MSG_DONTROUTE
#define MSG_DONTWAIT
#define MSG_PEEK
#define MSG_WAITALL

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

*************************************************************************************
                            Unix Domain Protocols
*************************************************************************************
The Unix domain protocols are not an actual protocol suite, but a way of performing 
client/server communication on a single host using the same API that is used for clients 
and servers on different hosts. The Unix domain protocols are an alternative to the 
interprocess communication (IPC) methods described in Volume 2 of this series, when 
the client and server are on the same host. Details on the actual implementation of 
Unix domain sockets in a Berkeley-derived kernel are provided in part 3 of TCPv3.

Two types of sockets are provided in the Unix domain: stream sockets (similar to TCP) 
and datagram sockets (similar to UDP). Even though a raw socket is also provided, its 
semantics have never been documented, it is not used by any  program that the authors 
are aware of, and it is not defined by POSIX.

The protocol addresses used to identify clients and servers in the Unix domain are 
pathnames within the normal filesystem. Recall that IPv4 uses a combination of 32-bit 
addresses and 16-bit port numbers for its protocol addresses, and IPv6 uses a combination 
of 128-bit addresses and 16-bit port numbers for its protocol addresses. These pathnames 
are not normal Unix files: We cannot read from or write to these files except from a 
program that has associated the pathname with a Unix domain socket.

*/

#define INADDR_ANY