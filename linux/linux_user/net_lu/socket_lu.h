/*-----------------------------------------------------------------------------------
                   Datatypes required by the POSIX specification
 -----------------------------------------------------------------------------------
 Datatype    |                 Description                           |    Header   
 ------------|-------------------------------------------------------|------
 int8_t      | Signed 8-bit interger                                 | <sys/types.h>
 uint8_t     | Unsigned 8-bit interger                               | <sys/types.h>
 int16_t     | Signed 16-bit interger                                | <sys/types.h>
 uint16_t    | Unsigned 16-bit interger                              | <sys/types.h>
 int32_t     | Signed 32-bit interger                                | <sys/types.h>
 uint32_t    | Unsigned 32-bit interger                              | <sys/types.h>
 ------------|-------------------------------------------------------|--------------
 sa_family_t | Address family of socket address structure            | <sys/socket.h>
 socklet_t   | Length of socket address structure, normally uint32_t | <sys/socket.h>
 ------------|-------------------------------------------------------|----------------
 in_addr_t   | IPv4 address, normally uint32_t                       | <netinet/in.h>
 in_port_t   | TCP or UDP port, normally uint16_t                    | <netinet/in.h>
 ------------------------------------------------------------------------------------
 ----------------------------------------------------------------------------------*/

/* socklent_t   uint32_t */

#include<netinet/in.h>
typedef uint32_t in_addr_t;  /*  IPv4 address, normally uint32_t */


/*-----------------------------------------------------------------------------------
 Socket Address Structures
 Most socket functions require a pointer to a socket address structure as an argumen-
 t. Each supported protocol suite defines its own socket address structure. The names 
 of these structures begin with sockaddr_ and end with a unique suffix for each prot-
 ocol suite.
 ----------------------------------------------------------------------------------*/
 
#define INET_ADDRSTRLEN   16 /* for IPv4 dotted-decimal  <netinet/in.h>*/
#define INET6_ADDRSTRLEN  46 /* for IPv6 hex string  <netinet/in.h>*/

/*-----------------------------------------------------------------------------------
 An IPv4 socket address structure, commonly called an "Internet socket address struc-
 ture," is named sockaddr_in and is defined by including the <netinet/in.h> header.
 ------------------------------------------------------------------------------------
 @sin_len
     The length member, sin_len, was added with 4.3BSD-Reno, when support for the OSI 
     protocols was added (Figure 1.15). Before this release, the first member was   -
     sin_family, which was historically an unsigned short. Not all vendors support  a 
     length field for socket address structures and the POSIX specification does  not 
     require this member.
 @sin_family
 @sin_port
 @sin_addr
     The POSIX specification requires only three members in the structure:sin_family, 
     sin_addr, and sin_port. It is acceptable for a POSIX-compliant implementation to 
     define additional structure members, and this is normal for an Internet socket -
     address structure. Almost all implementations add the sin_zero member so that a-
     ll socket address structures are at least 16 bytes in size.
 @sin_zero
     The sin_zero member is unused, but we always set it to 0 when filling in one  of 
     these structures. Although most uses of the structure do not require that this -
     member be 0, when binding a non-wildcard IPv4 address, this member must be 0   -
     (pp. 731�C732 of TCPv2).

 Socket address structures are used only on a given host: The structure itself is not 
 communicated between different hosts, although certain fields (e.g., the IP  address 
 and port) are used for communication.    
 ----------------------------------------------------------------------------------*/
struct in_addr 
{
  in_addr_t   s_addr;           /* 32-bit IPv4 address network byte ordered */
};

struct sockaddr_in /* POSIX definition */
{
  uint8_t         sin_len;      /* length of structure (16) */
  sa_family_t     sin_family;   /* AF_INET */
  in_port_t       sin_port;     /* 16-bit TCP or UDP port number network byte ordered */
  struct in_addr  sin_addr;     /* 32-bit IPv4 address  network byte ordered */
  char            sin_zero[8];  /* unused */
};


#include <sys/socket.h>

/*-----------------------------------------------------------------------------------
 http://www.cnblogs.com/youxin/p/3965962.html

 windowsƽ̨��:
 ͷ�ļ���#include<ws2tcpip.h>

 linuxƽ̨�£�
 ��������ͷ�ļ����ж��壺
 1��#include <sys/socket.h>
 2��#include <unistd.h>


 ��ϸ���壺typedef int socklen_t;

 ���룺

 �κ������Ŀ���붨��socklen_t��int��ͬ�ĳߴ��С��������������BSD�׽��ֲ����䡣
 POSIX���ȷʵ���䶨��Ϊsize_t�����Ѿ������Ǵ�����˵������顣������Ϊsize_t�����Ƿ�
 �����ģ��ر���size_t��64λ����ϵͳ�ϣ����ٺ�int����ͬ���ĳߴ��С�����磬BSD�׽�
 �ֽӿ�ֻ���ܺ�int�ߴ��С��ֵ��������Σ�POSIX��֯�������һ���취������socklen_t��
 ���ͣ����Ǳ����ò���������͡�������������ȷʵ��ΪΪ������һ�������Ǳ���ģ�Ϊ��ĳЩ
 ���˷ѽ�����ɡ�
 ----------------------------------------------------------------------------------*/
typedef int socklen_t;


/*-----------------------------------------------------------------------------------
	  The generic socket address structure: sockaddr.  <sys/socket.h>
 ----------------------------------------------------------------------------------*/
struct sockaddr 
{
  uint8_t      sa_len;
  sa_family_t  sa_family;    /* address family: AF_xxx value */
  char         sa_data[14];  /* protocol-specific address */
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

/*-----------------------------------------------------------------------------------
                               Socket Options
 -----------------------------------------------------------------------------------
 SO_RCVTIMEO SO_SNDTIMEO 
     These two socket options allow us to place a timeout on socket receives and sen-
     ds. Notice that the argument to the two sockopt functions is a pointer to a tim-
     eval structure. This lets us specify the timeouts in seconds and microseconds. -
     We disable a timeout by setting its value to 0 seconds and 0 microseconds.  Both 
     timeouts are disabled by default. The receive timeout affects the five input fu-
     nctions: read, readv, recdv, recvfrom, and recvmsg. The send timeout affects the 
     five output functions: write, writev, send, sendto, and sendmsg. 
 SO_ERROR
    When an error occurs on a socket, the protocol module in a Berkeley-derived kernel 
    sets a variable named @so_error for that socket to one of the standard Unix Exxx 
    values. This is called the pending error for the socket.The process can then obtain 
    the value of so_error by fetching the SO_ERROR socket option. The integer value 
    returned by getsockopt is the pending error for the socket. The value of so_error 
    is then reset to 0 by the kernel
 SO_LINGER    struct linger
 ----------------------------------------------------------------------------------*/
#define SO_RCVTIMEO  /* struct timeval */
#define SO_SNDTIMEO 
#define SO_REUSEADDR /* �������ñ��ص�ַ tcp_udp_serv*/
#define SO_LINGER
#define SO_ERROR  /* eg:connect_nonb */

/*-----------------------------------------------------------------------------------
There are two basic types of options: binary options that enable or disable a certain 
feature (flags), and options that fetch and return specific values that we can either 
set or examine (values). The column labeled "Flag" specifies if the option is a flag 
option. When calling getsockopt for these flag options, *optval is an integer. The 
value returned in *optval is zero if the option is disabled, or nonzero if the option 
is enabled. Similarly,setsockopt requires a nonzero *optval to turn the option on,and 
a zero value to turn the option off. If the "Flag" column does not contain a "?," then 
the option is used to pass a value of the specified datatype between the user process 
and the system.

ѡ�����ơ���������������˵���������������������������������������������� 
======================================================================== 
������������������������SOL_SOCKET 
------------------------------------------------------------------------ 
SO_BROADCAST�����������������͹㲥���ݡ�����������������������int 
SO_DEBUG����������������������ԡ�������������������������������int 
SO_DONTROUTE������������������·�ɡ�����������������������������int 
SO_ERROR��������������������׽��ִ��󡡡�����������������������int 
SO_KEEPALIVE�������������������ӡ�������������������������������int 
SO_LINGER�������������� �ӳٹر����ӡ���������������������������struct linger 
SO_OOBINLINE�������������������ݷ�������������������������������int 
SO_RCVBUF�������������� ���ջ�������С��������������������������int 
SO_SNDBUF�������������� ���ͻ�������С��������������������������int 
SO_RCVLOWAT������������ ���ջ��������ޡ�������������������������int 
SO_SNDLOWAT������������ ���ͻ��������ޡ�������������������������int 
SO_RCVTIMEO������������ ���ճ�ʱ��������������������������������struct timeval 
SO_SNDTIMEO������������ ���ͳ�ʱ��������������������������������struct timeval 
SO_REUSERADDR���������� �������ñ��ص�ַ�Ͷ˿ڡ�����������������int 
SO_TYPE���������������� ����׽������͡�������������������������int 
SO_BSDCOMPAT��������������BSDϵͳ���ݡ������������������������� int 
========================================================================
������������������������IPPROTO_IP 
------------------------------------------------------------------------
IP_HDRINCL�������������������ݰ��а���IP�ײ���������������������int 
IP_OPTINOS��������������IP�ײ�ѡ�����������������������������int 
IP_TOS�������������������������� 
IP_TTL����������������������ʱ�䡡������������������������������int 
========================================================================
������������������������IPPRO_TCP 
------------------------------------------------------------------------
TCP_MAXSEG��������������TCP������ݶεĴ�С�������������������� int 
TCP_NODELAY������������ ��ʹ��Nagle�㷨������������������������ int 
========================================================================


 ----------------------------------------------------------------------------------*/









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

#define SOMAXCONN /* @listen @backlog*/

/*-----------------------------------------------------------------------------------
                 Protocol family constants for socket function
 ------------------------------------------------------------------------------------
 AF_KEY
    It provides support for cryptographic security. Similar to the way that a routing 
    socket (AF_ROUTE) is an interface to the kernel's routing table,the key socket is 
    an interface into the kernel's key table.
 PF_INET
    ��Unix/Linuxϵͳ�У��ڲ�ͬ�İ汾����������΢С���.����BSD,��AF,����POSIX��PF.����
    �Ͻ���socketʱ��ָ��Э�飬Ӧ����PF_xxxx�����õ�ַʱӦ����AF_xxxx����ȻAF_INET��
    PF_INET��ֵ����ͬ�ģ�����Ҳ������̫������⡣
 ----------------------------------------------------------------------------------*/
#define AF_INET   /* ipv4 protocols */
#define PF_INET   /* */
#define AF_INET6  /* ipv6 protocols */
#define AF_LOCAL  /* unix domain protocols */
#define AF_ROUTE  /* routing sockets */
#define AF_KEY	  /* Key socket*/

/*-----------------------------------------------------------------------------------
				 type of socket for socket function
 ------------------------------------------------------------------------------------
 @SOCK_STREAM
     stream socket TCP Э��,�������ṩ��˳���,�ɿ�,˫��,�������ӵı�����. 
 @SOCK_DGRAM
     datagram socket UDPЭ��,����ֻ���ṩ������,���ɿ�,�����ӵ�ͨ��.
 @SOCK_PACKET
     Linux supports a new socket type, SOCK_PACKET, that provides access to the data-
     link.
 ----------------------------------------------------------------------------------*/
#define SOCK_STREAM    /* */
#define SOCK_DGRAM     /* */
#define SOCK_SEQPACKET /* sequenced packet socket */
#define SOCK_RAW       /* raw socket */
#define SOCK_PACKET	   /* */

/****************************** socket protocol *******************************/
#define IPPROTO_TCP   /* TCP transport protocol */
#define IPPROTO_UDP   /* UDP transport protocol */
#define IPPROTO_SCTP  /* SCTP transport protocol */

/**************************** @connect error type ****************************/
#define ETIMEDOUT
#define ECONNREFUSED
#define EHOSTUNREACH
#define ENETUNREACH 

/********************************* @shutdown @howto *********************************/
#define SHUT_RD /* The read half of the connection is closed�� No more data can be 
received on the socket and any data currently in the socket receive buffer is discarded. 
The process can no longer issue any of the read functions on the socket.Any data received 
after this call for a TCP socket is acknowledged and then silently discarded.*/
#define SHUT_WR /* The write half of the connection is closed�� In the case of TCP,
this is called a half-close.Any data currently in the socket send buffer will be sent, 
followed by TCP's normal connection termination sequence.As we mentioned earlier,this 
closing of the write half is done regardless of whether or not the socket descriptor's 
reference count is currently greater than 0. The process can no longer issue any of the 
write functions on the socket.*/
#define SHUT_RDWR /* The read half and the write half of the connection are both closed
This is equivalent to calling shutdown twice: first with SHUT_RD and then with SHUT_WR.*/


/*******************************************************************************
                | AF_INET  | AF_INET6 | AF_LOCAL | AF_ROUTE | AF_KEY |
 ---------------|----------|----------|----------|----------|--------|
 SOCK_STREAM    | tcp|sctp | tcp|sctp |    yes   |          |        |
 ---------------|----------|----------|----------|----------|--------|
 SOCK_DGRAM     |    udp   |   udp    |    yes   |          |        |
 ---------------|----------|----------|----------|----------|--------| 
 SOCK_SEQPACKET |   sctp   |   sctp   |    yes   |          |        |
 ---------------|----------|----------|----------|----------|--------| 
 SOCK_RAW       |   ipv4   |   ipv6   |          |    yes   |   yes  |
 ---------------|----------|----------|----------|----------|--------|
 Figure 4.5 Combinations of @family and @type for the @socket function
       
 Not all combinations of @socket @family and @type are valid.Figure 4.5 shows the 
 valid combinations, along with the actual protocols that are valid for each pair. 
 The boxes marked "Yes" are valid but do not have handy acronyms. The blank boxes 
 are not supported.    
 ******************************************************************************/

 
#include <sys/select.h>
 
#define FD_SETSIZE /* a constant in <sys/select.h> that specifies the maximum number 
 of descriptors (often 1,024) */


