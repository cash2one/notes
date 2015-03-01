
#include <sys/select.h>

#define FD_SETSIZE /* a constant in <sys/select.h> that specifies the maximum number 
of descriptors (often 1,024) */





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

/************************************************************************************
                             protocol family
*************************************************************************************
 AF_KEY
    It provides support for cryptographic security. Similar to the way that a routing 
    socket (AF_ROUTE) is an interface to the kernel's routing table,the key socket is 
    an interface into the kernel's key table.


 PF_INET
    ��Unix/Linuxϵͳ�У��ڲ�ͬ�İ汾����������΢С���.����BSD,��AF,����POSIX��PF.����
    �Ͻ���socketʱ��ָ��Э�飬Ӧ����PF_xxxx�����õ�ַʱӦ����AF_xxxx����ȻAF_INET��
    PF_INET��ֵ����ͬ�ģ�����Ҳ������̫������⡣

************************************************************************************/
#define AF_INET   /* ipv4 protocols */
#define PF_INET   /* */
#define AF_INET6  /* ipv6 protocols */
#define AF_LOCAL  /* unix domain protocols */
#define AF_ROUTE  /* routing sockets */
#define AF_KEY	  /* */

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
#include <sys/socket.h>	 
int socket(int domain, int type,int protocol);



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
int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
	 
	
/*******************************************************************************
 @sockfd:
 @myaddr:Ҫ��@sockfd�󶨵ĵ�ַ
 @addrlen:��ַ����
 function:The @bind function assigns a local protocol address to a socket.
 returns: 0 if OK,-1 on error

1 With TCP, calling @bind lets us specify a port number, an IP address, both, or 
  neither.A process can bind a specific IP address to its socket.The IP address 
  must belong to an interface on the host.
2 If a TCP client or server does not do this,the kernel chooses an ephemeral port 
  for the socket when either @connect or @listen is called.It is normal for a TCP 
  client to let the kernel choose an ephemeral port,unless the application requires 
  a reserved port , but it is rare for a TCP server to let the kernel choose an 
  ephemeral port, since servers are known by their well-known port.
3 For a TCP client, this assigns the source IP address that will be used for IP 
  datagrams sent on the socket.For a TCP server, this restricts the socket to 
  receive incoming client connections destined only to that IP address.
4 Normally, a TCP client does not bind an IP address to its socket. The kernel 
  chooses the source IP address when the socket is connected,based on the outgoing 
  interface that is used, which in turn is based on the route required to reach 
  the server.If a TCP server does not bind an IP address to its socket, the kernel 
  uses the destination IP address of the client's SYN as the server's source IP 
  address .
5 If we specify a port number of 0, the kernel chooses an ephemeral port when bind 
  is called. But if we specify a wildcard IP address,the kernel does not choose the 
  local IP address until either the socket is connected (TCP) or a datagram is sent 
  on the socket (UDP).
6 With IPv4, the wildcard address is specified by the constant INADDR_ANY, whose 
  value is normally 0.The system allocates and initializes the in6addr_any variable 
  to the constant IN6ADDR_ANY_INIT. 
*******************************************************************************/
int bind (int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
	  
	 
/*-----------------------------------------------------------------------------------
 @sockfd:
 @backlog: SOMAXCONN
    maximum number of connections the kernel should queue for this socket.
 @function
 @returns: 
    0 if OK, -1 on error
 
 This function is normally called after both the @socket and @bind functions and must 
 be called before calling the @accept function.

 When a socket is created by the @socket function, it is assumed to be an active soc-
 ket, that is, a client socket that will issue a connect. The @listen function conve-
 rts an unconnected socket into a passive socket, indicating that the kernel should -
 accept incoming connection requests directed to this socket. In terms of the TCP st-
 ate transition diagram,the call to @listen moves the socket from the CLOSED state to 
 the LISTEN state.

 for a given listening socket, the kernel maintains two queues:
 1 An incomplete connection queue, which contains an entry for each SYN that has arr-
   ived from a client for which the server is awaiting completion of the TCP three w-
   ay handshake. These sockets are in the SYN_RCVD state.
 2 A completed connection queue, which contains an entry for each client with whom t-
   he TCP three-way handshake has completed. These sockets are in the ESTABLISHED st-
   ate. When a SYN arrives from a client, TCP creates a new entry on the incomplete -
   queue and then responds with the second segment of the three-way handshake:the se-
   rver's SYN with an ACK of the client's SYN . This entry will remain on the incomp-
   lete queue until the third segment of the three-way handshake arrives(the client's 
   ACK of the server's SYN), or until the entry times out. If the three-way handshake 
   completes normally, the entry moves from the incomplete queue to the end of the c-
   ompleted queue. When the process calls @accept, the first entry on the completed -
   queue is returned to the process, or if the queue is empty , the process is put to 
   sleep until an entry is placed onto the completed queue.

 If the queues are full when a client SYN arrives, TCP ignores the arriving SYN; it -
 does not send an RST. This is because the condition is considered temporary, and the 
 client TCP will retransmit its SYN , hopefully finding room on the queue in the near 
 future.
-----------------------------------------------------------------------------------*/	  
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

 1 If accept is successful,its return value is a brand-new descriptor automatically 
   created by the kernel. This new descriptor refers to the TCP connection with 
   the client.
 2 When discussing @accept, we call the first argument to accept the listening 
   socket (the descriptor created by socket and then used as the first argument 
   to both @bind and @listen ) , and we call the return value from accept the 
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
 ******************************************************************************/
int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
 
/******************************************************************************
 Both return: 0 if OK, -1 on error
  
 These two functions return either the local protocol address associated with a 
 socket (getsockname) or the foreign protocol address associated with a socket 
 (getpeername).the final argument for both functions is a value-result argument. 
 That is, both functions fill in the socket address structure pointed to by 
 localaddr or peeraddr.

 These two functions are required for the following reasons:
 1 After connect successfully returns in a TCP client that does not call bind, 
   @getsockname returns the local IP address and local port number assigned to 
   the connection by the kernel.
 2 After calling @bind with a port number of 0 (telling the kernel to choose the 
   local port number), @getsockname returns the local port number that was assigned.
 3 @getsockname can be called to obtain the address family of a socket 
 4 In a TCP server that binds the wildcard IP address , once a connection is 
   established with a client (accept returns successfully), the server can call 
   @getsockname to obtain the local IP address assigned to the connection. The 
   socket descriptor argument in this call must be that of the connected socket, 
   and not the listening socket.
 ******************************************************************************/
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
   
  
/************************************************************************************
 @howto:SHUT_RD
Returns: 0 if OK, �C1 on error

 The normal way to terminate a network connection is to call the @close function.But,
 there are two limitations with @close that can be avoided with @shutdown:
 1 close decrements the descriptor's reference count and closes the socket only if the 
   count reaches 0. With shutdown, we can initiate TCP's normal connection termination 
   sequence(the four segments beginning with a FIN ),regardless of the reference count.
 2 close terminates both directions of data transfer, reading and writing. Since a TCP 
   connection is full-duplex, there are times when we want to tell the other end that 
   we have finished sending,even though that end might have more data to send us.
   
The three SHUT_xxx names are defined by the POSIX specification. Typical values for the @howto argument that you will encounter 
will be 0 (close the read half), 1 (close the write half), and 2 (close the read half and the write half).
************************************************************************************/
int shutdown(int sockfd, int howto);

/************************************************************************************
 @sockfd:
 @buff  :���յ����ݴ���������������
 @nbytes:ϣ�����յ��ֽ���
 @flag:
 @from:
   ������˭������,����ΪNULL,��ʾ��������Դ,��ʱaddrlenҲ��NULL.
   the protocol address of who sent the datagram. The number of bytes stored in this 
   socket address structure is also returned to the caller in the integer pointed to 
   by @addrlen. 
 @addrlen:
    If the from argument to @recvfrom is a null pointer, then the corresponding length 
    argument (addrlen) must also be a null pointer, and this indicates that we are not 
    interested in knowing the protocol address of who sent us data. 
 @return: number of bytes read if OK, �C1 on error

 Both @recvfrom and @sendto can be used with TCP, although there is normally no reason 
 to do so.

 1 ���Է���0,������ʾ�Զ˹رա�
************************************************************************************/
ssize_t recvfrom(int sockfd, void *buff, size_t nbytes, int flags, 
struct sockaddr *from, socklen_t *addrlen);

 
/************************************************************************************
 @sockfd:
 @buff  :���͵����ݶ��������������
 @nbytes:���͵��ֽ���������Ϊ0,��ʱ���͵�ֻ�б���ͷû��������.
 @flag:
 @to:
    The @to argument for @sendto is a socket address structure containing the protocol 
    address (e.g., IP address and port number) of where the data is to be sent. The 
    size of this socket address structure is specified by @addrlen.
 @addrlen:
 @return: number of bytes written if OK, �C1 on error

 Writing a datagram of length 0 is acceptable. In the case of UDP, this results in an 
 IP datagram containing an IP header(normally 20 bytes for IPv4 and 40 bytes for IPv6), 
 an 8-byte UDP header, and no data. This also means that a return value of 0 from 
 @recvfrom is acceptable for a datagram protocol: It does not mean that the peer has 
 closed the connection, as does a return value of 0 from read on a TCP socket. Since 
 UDP is connectionless, there is no such thing as closing a UDP connection.
 
 1 һ������UDP,Ҳ��������TCP(һ�㲻��)
 2 The client must specify the server's IP address and port number for the call to @sendto.
 3 a successful return from a UDP output operation only means there was room for the 
   resulting IP datagram on the interface output queue. 
************************************************************************************/
ssize_t sendto(int sockfd, const void *buff, size_t nbytes, int flags, 
const struct sockaddr *to, socklen_t addrlen);
 

/************************************************************************************
    flags              ˵��           recv      send
 MSG_DONTROUTE     �ƹ�·�ɱ����      n         y
 MSG_DONTWAIT	     ��������������      y         y
 MSG_OOB           ���ͻ���մ�������  y         y
 MSG_PEEK          ����������Ϣ        y         n
 MSG_WAITALL       �ȴ���������        y	        n 

 @flags
    ���flagsΪ0,���read,writeһ���Ĳ���.
 return: 
    number of bytes read or written if OK, �C1 on error 
************************************************************************************/
ssize_t recv(int sockfd, void *buff, size_t nbytes, int flags);
ssize_t send(int sockfd, const void *buff, size_t nbytes, int flags);


/*Both return: number of bytes read or written if OK, �C1 on error */
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);

/*return: number of bytes read or written if OK, �C1 on error */  
ssize_t sendmsg(int sockfd, struct msghdr *msg, int flags);




/************************************************************************************
 @function:
    The normal Unix close function is also used to close a socket and terminate a TCP 
    connection.
 @returns: 
    0 if OK, -1 on error

 The default action of close with a TCP socket is to mark the socket as closed and 
 return to the process immediately.The socket descriptor is no longer usable by the 
 process:It cannot be used as an argument to read or write.But,TCP will try to send 
 any data that is already queued to be sent to the other end, and after this occurs, 
 the normal TCP connection termination sequence takes place . we will describe the 
 SO_LINGER socket option, which lets us change this default action with a TCP socket.
 ***********************************************************************************/
#include <unistd.h>  
int close (int sockfd);
  





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





#include <sys/socket.h>


#include <sys/socket.h>





/************************************************************************************
 @sockfd 
    must refer to an open socket descriptor. 
 @level  SOL_SOCKET
    specifies the code in the system that interprets the option: the general socket 
    code or some protocol-specific code (e.g., IPv4, IPv6, TCP, or SCTP).
 @optname  SO_LINGER
    �������׽���ѡ��ʱ���������ѡ��λ�ڵĲ�(@level)��ѡ�������(@optname)��Ϊ�˲���
    �׽��ֲ��ѡ�Ӧ�ý����ֵָ��ΪSOL_SOCKET��Ϊ�˲����������ѡ�����ѡ��ĺ�
    ��Э��ű�����������磬Ϊ�˱�ʾһ��ѡ����TCPЭ���������Ӧ���趨ΪЭ�� ��TCP��
 @optval 
    is a pointer to a variable from which the new value of the option is fetched by 
    @setsockopt,or into which the current value of the option is stored by @getsockopt. 
 @optlen    
    The size of this variable is specified by the final argument, as a value for 
    @setsockopt and as a value-result for getsockopt.

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
************************************************************************************/
  
/* return: 0 if OK,�C1 on error */ 
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
 
/* return: 0 if OK,�C1 on error
   example: dg_cli_timeout3 */ 
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
 
/*
����ʹ�����£� 
1.closesocket��һ�㲻�������رն�����TIME_WAIT�Ĺ��̣�����������ø�socket�� 
BOOL bReuseaddr=TRUE; 
setsockopt(s,SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(BOOL));

2. ���Ҫ�Ѿ���������״̬��soket�ڵ���closesocket��ǿ�ƹرգ������� TIME_WAIT�Ĺ��̣� 
BOOL bDontLinger = FALSE; 
setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));

3.��send(),recv()��������ʱ��������״����ԭ�򣬷��ղ���Ԥ�ڽ���,�������շ�ʱ�ޣ� 
int nNetTimeout=1000;//1�� 
//����ʱ�� 
setsockopt(socket��SOL_S0CKET,SO_SNDTIMEO��(char *)&nNetTimeout,sizeof(int)); 
//����ʱ�� setsockopt(socket��SOL_S0CKET,SO_RCVTIMEO��(char *)&nNetTimeout,sizeof(int)); 

 
4.��send()��ʱ�򣬷��ص���ʵ�ʷ��ͳ�ȥ���ֽ�(ͬ��)���͵�socket���������ֽ� (�첽);ϵͳĬ�ϵ�״̬���ͺͽ���һ��Ϊ8688�ֽ�(ԼΪ8.5K)�� 
��ʵ�ʵĹ����з������ݺͽ����������Ƚϴ󣬿�������socket����������������send(),recv()���ϵ�ѭ���շ��� 
// ���ջ����� 
int nRecvBuf=32*1024; 
//����Ϊ32K 
setsockopt(s,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int)); 
//���ͻ����� int nSendBuf=32*1024;//����Ϊ32K 
setsockopt(s,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
 
5. ����ڷ������ݵ�ʱ��ϣ����������ϵͳ��������socket�������Ŀ�����Ӱ���������ܣ� 
int nZero=0; 
setsockopt(socket��SOL_S0CKET,SO_SNDBUF��(char *)&nZero,sizeof(nZero));
 
6.ͬ����recv()�����������(Ĭ������ǽ�socket�����������ݿ�����ϵͳ������)�� 
int nZero=0; 
setsockopt(socket��SOL_S0CKET,SO_RCVBUF��(char *)&nZero,sizeof(int));
 
7.һ���ڷ���UDP���ݱ���ʱ��ϣ����socket���͵����ݾ��й㲥���ԣ� 
BOOL bBroadcast=TRUE; 
setsockopt(s,SOL_SOCKET,SO_BROADCAST,(const char*)&bBroadcast,sizeof(BOOL));
 
8.��client���ӷ����������У�������ڷ�����ģʽ�µ�socket��connect()�Ĺ����п�������connect()��ʱ,ֱ��accpet()������(����������ֻ���ڷ������Ĺ����������������ã��������ĺ������������ò���) 
BOOL bConditionalAccept=TRUE; 
setsockopt(s,SOL_SOCKET,SO_CONDITIONAL_ACCEPT,(const char*)&bConditionalAccept,sizeof(BOOL));
 
9.����ڷ������ݵĹ�����(send()û����ɣ���������û����)��������closesocket(),��ǰ����һ���ȡ�Ĵ�ʩ��"���ݹر�"shutdown(s,SD_BOTH),���������ǿ϶���ʧ�ˣ���������ó����������Ӧ�õ�Ҫ��(����û��������ݷ��ͳ�ȥ���ڹر�socket)�� 
struct linger 
{ 
u_short l_onoff; 
u_short l_linger; 
}; 
linger m_sLinger; 
m_sLinger.l_onoff=1;//(��closesocket()����,���ǻ�������û������ϵ�ʱ��������) ���m_sLinger.l_onoff=0;���ܺ�2.)������ͬ; 
m_sLinger.l_linger=5; //(��������ʱ��Ϊ5��) 
setsockopt(s,SOL_SOCKET,SO_LINGER,(const char*)&m_sLinger,sizeof(linger));

*/
 

