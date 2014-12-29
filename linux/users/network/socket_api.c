#include <arpa/inet.h>

/*
function:converts the C character string pointed to by @strptr into its 32-bit binary network byte ordered value, 
         which is stored through the pointer @addrptr.
Returns: 1 if string was valid, 0 on error*/
int inet_aton(const char *strptr, struct in_addr *addrptr);
 

/*Returns: 32-bit binary network byte ordered IPv4 address; INADDR_NONE(0xffffffff) if error*/
in_addr_t inet_addr(const char *strptr);
 

/*Returns: pointer to dotted-decimal string
The inet_ntoa function converts a 32-bit binary network byte ordered IPv4 address into its corresponding dotted-decimal string. 
The string pointed to by the return value of the function resides in static memory. This means the function is not reentrant*/ 
char *inet_ntoa(struct in_addr inaddr);
 

/*
@family:AF_INET or AF_INET6
Returns: 1 if OK, 0 if input not a valid presentation format, -1 on error

1 If family is not supported, both functions return an error with errno set to EAFNOSUPPORT
2 The letters "p" and "n" stand for presentation and numeric. The presentation format for an address is often an ASCII string 
  and the numeric format is the binary value that goes into a socket address structure.

*/  
int inet_pton(int family, const char *strptr, void *addrptr);
  
 
/*
@family :��ַ���� AF_INET or AF_INET6
@addrptr:�����ַָ�����һ����ַ��ֵ,�����ֵת�����ַ���
@strptr :����ת����Ľ��,������NULL.
@len    :������strptr�Ĵ�С��������������������̫С�޷��洢��ַ��ֵ���򷵻�һ����ָ�룬����errno��ΪENOSPC
  
Returns: pointer to result if OK, NULL on error

ʵ��
struct sockaddr_in   addr;
inet_ntop(AF_INET, &addr.sin_addr, str, sizeof(str));

struct sockaddr_in6   addr6;
inet_ntop(AF_INET6, &addr6.sin6_addr, str, sizeof(str));*/ 
 const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
  
 
#define INET_ADDRSTRLEN       16       /* for IPv4 dotted-decimal */
#define INET6_ADDRSTRLEN      46       /* for IPv6 hex string */

/****************************** protocol family *******************************/
#define AF_INET   /* ipv4 protocols */
#define AF_INET6  /* ipv6 protocols */
#define AF_LOCAL  /* unix domain protocols */
#define AF_ROUTE  /* routing sockets */
#define AF_KEY	  /* It provides support for cryptographic security. Similar to 
the way that a routing socket (AF_ROUTE) is an interface to the kernel's routing 
table, the key socket is an interface into the kernel's key table. */

/******************************** socket type *********************************/
#define SOCK_STREAM /*stream socket TCP Э��,�������ṩ��˳���,�ɿ�,˫��,������
�ӵı�����. */
#define SOCK_DGRAM /*datagram socket UDPЭ��,����ֻ���ṩ������,���ɿ�,�����ӵ�
ͨ��.*/
#define SOCK_SEQPACKET /*sequenced packet socket*/
#define SOCK_RAW /*raw socket*/
#define SOCK_PACKET	/* Linux supports a new socket type, SOCK_PACKET, that provides 
access to the datalink */

/****************************** socket protocol *******************************/
#define IPPROTO_TCP   /* TCP transport protocol */
#define IPPROTO_UDP   /* UDP transport protocol */
#define IPPROTO_SCTP  /* SCTP transport protocol */

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

/*******************************************************************************
 @domain: AF_INET��
    Э����,Ҳ��Э��������ȷ��ͨ�ŵ����ԣ�������ַ��ʽ.We note that you may 
    encounter AF_UNIX (the historical Unix name)instead of AF_LOCAL (the POSIX 
    name).You may also encounter the corresponding PF_xxx constant as the first 
    argument to socket.
 @type: SOCK_STREAM�� 
    �׽������� 
 @protocol: IPPROTO_TCP��
    Э������ 0��ʾѡ��domain��type��ϵ�ϵͳĬ��ֵ��When multiple protocols are 
    supported for the same @domain and socket @type,we can use the @protocol 
    argument to select a particular protocol.The default protocol for a SOCK_STREAM 
    socket in the AF_INET communication domain is TCP(Transmission Control Protocol).
    The default protocol for a SOCK_DGRAM socket in the AF_INET communication domain  
    is UDP(User Datagram  Protocol).
 return:
    �ɹ�ʱ�����ļ�������(�е�Ҳ��Ϊ�׽���������),ʧ��ʱ����-1,��errno��֪������
    ����ϸ���.On success, the socket function returns a small non-negative 
    integer value, similar to a file descriptor. We call this a socket descriptor, 
    or a sockfd.
 AF_xxx Versus PF_xxx
    The "AF_" prefix stands for "address family" and the "PF_" prefix stands for 
    "protocol family." Historically, the intent was that a single protocol family 
    might support multiple address families and that the PF_ value was used to 
    create the socket and the AF_ value was used in socket address structures. 
    But in actuality, a protocol family supporting multiple address families has 
    never been supported and the <sys/socket.h> header defines the PF_ value for 
    a given protocol to be equal to the AF_ value for that protocol. While there 
    is no guarantee that this equality between the two will always be true, should 
    anyone change this for existing protocols, lots of existing code would break. 
    To conform to existing coding practice, we use only the AF_ constants in this 
    text, although you may encounter the PF_ value, mainly in calls to socket.
 ******************************************************************************/
int socket(int domain, int type,int protocol);

/**************************** @connect error type ****************************/
#define ETIMEDOUT
#define ECONNREFUSED
#define EHOSTUNREACH
#define ENETUNREACH 

/*******************************************************************************
 @sockfd: 
   is a socket descriptor returned by the @socket function. 
 @servaddr: 
   The socket address structure must contain the IP address and port number of 
   the server. 
 @servlen: 
   The second and third arguments are a pointer to a socket address structure 
   and its size 
 function:
   The connect function is used by a TCP client to establish a connection with 
   a TCP server.
 returns:
   0 if OK, -1 on error

 1 The client does not have to call @bind before calling connect: the kernel 
   will choose both an ephemeral port and the source IP address if necessary.
 2 In the case of a TCP socket, the @connect function initiates TCP's three-way 
   handshake.The function returns only when the connection is established or an 
   error occurs
 3 each time connect fails, we must close the socket descriptor and call socket 
   again.
 4 �ͻ���connect������������,�յ�ack�󷵻�(�ڶ�������),��������Ҫ���������ֲŷ���
 5 When @connect is interrupted by a caught signal and is not automatically 
   restarted.If this function returns EINTR, we cannot call it again, as doing 
   so will return an immediate error.

There are several different error returns possible.
1 If the client TCP receives no response to its SYN segment, ETIMEDOUT is returned. 
  4.4BSD, for example, sends one SYN when connect is called, another 6 seconds 
  later, and another 24 seconds later. If no response is received after a total 
  of 75 seconds, the error is returned.Some systems provide administrative control 
  over this timeout;
2 If the server's response to the client's SYN is a reset (RST), this indicates 
  that no process is waiting for connections on the server host at the port 
  specified (i.e., the server process is probably not running). This is a hard 
  error and the error ECONNREFUSED is returned to the client as soon as the RST 
  is received.An RST is a type of TCP segment that is sent by TCP when something 
  is wrong. Three conditions that generate an RST are: when a SYN arrives for a 
  port that has no listening server (what we just described), when TCP wants to 
  abort an existing connection, and when TCP receives a segment for a connection 
  that does not exist. (TCPv1 [pp. 246�C250] contains additional information.)
3 If the client's SYN elicits an ICMP "destination unreachable" from some 
  intermediate router, this is considered a soft error. The client kernel saves 
  the message but keeps sending SYNs with the same time between each SYN as in 
  the first scenario. If no response is received after some fixed amount of time 
  (75 seconds for 4.4BSD), the saved ICMP error is returned to the process as 
  either EHOSTUNREACH or ENETUNREACH. It is also possible that the remote system 
  is not reachable by any route in the local system's forwarding table, or that 
  the connect call returns without waiting at all.
*******************************************************************************/
#include <sys/socket.h>	 
int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
	 
	
/*******************************************************************************
 @sockfd:
 @myaddr:Ҫ��@sockfd�󶨵ĵ�ַ
 @addrlen:��ַ����
 function:The @bind function assigns a local protocol address to a socket.
 returns: 0 if OK,-1 on error

1 With TCP, calling @bind lets us specify a port number, an IP address, both, or neither.
  A process can bind a specific IP address to its socket. The IP address must belong to an interface on the host.
2 If a TCP client or server does not do this, the kernel chooses an ephemeral port for the socket when either @connect or @listen is called. 
  It is normal for a TCP client to let the kernel choose an ephemeral port, unless the application requires a reserved port , but it is rare 
  for a TCP server to let the kernel choose an ephemeral port, since servers are known by their well-known port.
3 For a TCP client, this assigns the source IP address that will be used for IP datagrams sent on the socket. 
  For a TCP server, this restricts the socket to receive incoming client connections destined only to that IP address.
4 Normally, a TCP client does not bind an IP address to its socket. The kernel chooses the source IP address when the socket is connected,
  based on the outgoing interface that is used, which in turn is based on the route required to reach the server .
  If a TCP server does not bind an IP address to its socket, the kernel uses the destination IP address of the client's SYN as the server's source IP address .
5 If we specify a port number of 0, the kernel chooses an ephemeral port when bind is called. But if we specify a wildcard IP address, 
  the kernel does not choose the local IP address until either the socket is connected (TCP) or a datagram is sent on the socket (UDP).
6 With IPv4, the wildcard address is specified by the constant INADDR_ANY, whose value is normally 0. 
  The system allocates and initializes the in6addr_any variable to the constant IN6ADDR_ANY_INIT. 
*/	 
#include <sys/socket.h>
int bind (int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
	  
	 
/*
@sockfd:
@backlog:maximum number of connections the kernel should queue for this socket
function:TCP����������
Returns: 0 if OK, -1 on error

When a socket is created by the socket function, it is assumed to be an active socket, that is, a client socket that will issue 
a connect. The listen function converts an unconnected socket into a passive socket, indicating that the kernel should accept 
incoming connection requests directed to this socket. In terms of the TCP state transition diagram , the call to listen moves 
the socket from the CLOSED state to the LISTEN state.

for a given listening socket, the kernel maintains two queues:
a) An incomplete connection queue, which contains an entry for each SYN that has arrived from a client for which the server is 
   awaiting completion of the TCP three-way handshake. These sockets are in the SYN_RCVD state .
b) A completed connection queue, which contains an entry for each client with whom the TCP three-way handshake has completed. 
   These sockets are in the ESTABLISHED state .
   ���������յ�SYN����δ��ɶ��н�����Ŀ����������SYN+ACK�����յ�ACK�󣬸���Ŀת�Ƶ���ɶ��У�accept�ܹ����ء�

*/	  
#include <sys/socket.h>
int listen (int sockfd, int backlog);
	      
/*******************************************************************************
 @cliaddr:
   The @cliaddr and @addrlen arguments are used to return the protocol address 
   of the connected peer process (the client). 
 @addrlen:
   Before the call, we set the integer value referenced by *@addrlen to the size 
   of the socket address structure pointed to by cliaddr;on return, this integer 
   value contains the actual number of bytes stored by the kernel in the socket 
   address structure.
 function:
   @accept is called by a TCP server to return the next completed connection from 
   the front of the completed connection queue. If the completed connection queue 
   is empty, the process is put to sleep (assuming the default of a blocking socket).
 returns: 
   non-negative descriptor if OK, -1 on error

 1 If accept is successful, its return value is a brand-new descriptor automatically 
   created by the kernel.This new descriptor refers to the TCP connection with 
   the client.
 2 When discussing @accept, we call the first argument to @accept the listening 
   socket (the descriptor created by socket and then used as the first argument 
   to both @bind and @listen), and we call the return value from accept the 
   connected socket.
 3 A given server normally creates only one listening socket, which then exists 
   for the lifetime of the server.The kernel creates one connected socket for 
   each client connection that is accepted (i.e., for which the TCP three-way 
   handshake completes). When the server is finished serving a given client, the 
   connected socket is closed.
 4 ������acceptҪ������������ɲŷ��ء�
 5 signal was caught by the parent(�����ӽ�����ֹ) while the parent was blocked 
   in a slow system call (accept), the kernel causes the accept to return an error 
   of EINTR (interrupted system call). 
*******************************************************************************/
#include <sys/socket.h>
int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
 

/*
function:The normal Unix close function is also used to close a socket and terminate a TCP connection.
Returns: 0 if OK, -1 on error

The default action of close with a TCP socket is to mark the socket as closed and return to the process immediately. 
The socket descriptor is no longer usable by the process: It cannot be used as an argument to read or write. 
But, TCP will try to send any data that is already queued to be sent to the other end, and after this occurs, 
the normal TCP connection termination sequence takes place .*/
#include <unistd.h>  
int close (int sockfd);
  
/*Both return: 0 if OK, -1 on error
1 These two functions return either the local protocol address associated with a socket (getsockname) or 
  the foreign protocol address associated with a socket (getpeername).
2 the final argument for both functions is a value-result argument. That is, both functions fill in the 
  socket address structure pointed to by localaddr or peeraddr.
*/
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
  
 
  
  




/*
If how is SHUT_RD,then reading from the socket is disabled. If how is SHUT_WR,then we can��t use the socket for transmitting data. 
We  can use SHUT_RDWR to disable both data transmission and reception.*/
#include <sys/socket.h>
int shutdown(int sockfd,int how);


/*
�����ĸ�ת��������,h ����host, n ���� network.s ����short l ����long 
��һ�������������ǽ��������ϵ�long����ת��Ϊ�����ϵ�long. ������������������Ҳ���.
*/
unsigned long  int htonl(unsigned long  int hostlong);
unsigned short int htons(unisgned short int hostshort);
unsigned long  int ntohl(unsigned long  int netlong);
unsigned short int ntohs(unsigned short int netshort);

#include <sys/socket.h>

/*
@sockfd:
@buff  :���յ����ݴ���������������
@nbytes:ϣ�����յ��ֽ���
@flag:
@from:������˭������,����ΪNULL,��ʾ��������Դ,��ʱaddrlenҲ��NULL.
@addrlen:Ŀ�ĵص�ַ����

return: number of bytes read if OK, �C1 on error

1 ���Է���0,������ʾ�Զ˹رա�*/
ssize_t recvfrom(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);

 
/*
@sockfd:
@buff  :���͵����ݶ��������������
@nbytes:���͵��ֽ���������Ϊ0,��ʱ���͵�ֻ�б���ͷû��������.
@flag:
@to:Ŀ�ĵ�
@addrlen:Ŀ�ĵص�ַ����
return: number of bytes written if OK, �C1 on error

1 һ������UDP,Ҳ��������TCP(һ�㲻��)
2 The client must specify the server's IP address and port number for the call to @sendto.*/
ssize_t sendto(int sockfd, const void *buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen);
 

 


#include <sys/socket.h>

#define SHUT_RD
#define SHUT_WR
#define SHUT_RDWR
/*
@howto:SHUT_RD   �رն��벿,�׽��ֻ������е�����������,���ԶԶ˵����ݶ���ȷ��,Ȼ����Ȼ������
       SHUT_WR   �ر�д�벿(��ʹ���ü�����Ϊ0),�׽��ֻ����������ݽ�������,���tcp������ֹ����,
       SHUT_RDWR The read half and the write half of the connection are both closed�� 
                 This is equivalent to calling shutdown twice: first with SHUT_RD and then with SHUT_WR. 
Returns: 0 if OK, �C1 on error


The three SHUT_xxx names are defined by the POSIX specification. Typical values for the @howto argument that you will encounter 
will be 0 (close the read half), 1 (close the write half), and 2 (close the read half and the write half).
*/
int shutdown(int sockfd, int howto);
 

 
#include <poll.h>
struct pollfd {
  int     fd;       /* descriptor to check */
  short   events;   /* events of interest on fd */
  short   revents;  /* events that occurred on fd */
};

int poll (struct pollfd *fdarray, unsigned long nfds, int timeout);
  

#include <sys/socket.h>
#define SOL_SOCKET /*�����׽ӿ�*/
  #define SO_REUSEADDR /*�������ñ��ص�ַ*/
  #define SO_RCVTIMEO  /*���ճ�ʱ struct timeval */
  
/*@sockfd:�򿪵��׽���������
  @level : ָ��ѡ����������
           SOL_SOCKET: �����׽ӿ�
           IPPROTO_IP: IPv4�׽ӿ�
           IPPROTO_IPV6: IPv6�׽ӿ�
           IPPROTO_TCP: TCP�׽ӿ�
  @iptname:
  @optval:�����׽��ֵ�ǰ��ѡ��ֵ
  @iptlen:
  return: 0 if OK,�C1 on error*/ 
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
 
/*@sockfd:�򿪵��׽���������
  @level
  @iptname:
  @optval:����׽��ִ����õ���ֵ
  @iptlen:
return: 0 if OK,�C1 on error*/ 
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
 

 

