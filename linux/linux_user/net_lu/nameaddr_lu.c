#include <netdb.h>

struct hostent {
   char  *h_name;       /* official (canonical) name of host .��ʾ���������Ĺ淶��������www.google.com�Ĺ淶����ʵ��www.l.google.com��*/
   char **h_aliases;    /* pointer to array of pointers to alias names.
                              ��ʾ���������ı���.www.google.com����google���Լ��ı������е�ʱ���е����������кü���������
                              ��Щ����ʵ����Ϊ�������û������Ϊ�Լ�����վ��ȡ�����֡�*/
   int    h_addrtype;   /* host address type: AF_INET .��ʾ��������ip��ַ�����ͣ�������ipv4(AF_INET)������pv6(AF_INET6)*/
   int    h_length;     /* length of address: 4. ��ʾ��������ip��ַ�ĳ���*/
   char **h_addr_list;  /* ptr to array of ptrs with IPv4 addrs . ��ʾ����������ip��ַ��ע�⣬������������ֽ���洢�ġ�*/
};

#define HOST_NOT_FOUND
#define TRY_AGAIN
#define NO_RECOVERY
#define NO_DATA    /* specified name is valid, but it does not have an A record*/

/* 
  Returns: non-null pointer if OK,NULL on error with h_errno set
  
  1 it returns a pointer to a hostent structure that contains all the IPv4 addresses for the host. */
struct hostent *gethostbyname (const char *hostname);
	 
	 
#include <netdb.h>
/*@addr��ָ�������ֽ�˳���ַ��ָ�롣
  @len�� ��ַ�ĳ��ȣ���AF_INET���͵�ַ��Ϊ4��
  @type����ַ���ͣ�ӦΪAF_INET��
  @Returns: non-null pointer if OK, NULL on error with h_errno set */	  
struct hostent *gethostbyaddr (const char *addr, socklen_t len, int family);
	  
	  
#include <netdb.h>
struct servent {
  char   *s_name;      /* official service name */
  char  **s_aliases;   /* alias list */
  int     s_port;      /* port number, network-byte order */
  char   *s_proto;     /* protocol to use */
};
{
struct servent *sptr;

sptr = getservbyname("domain", "udp"); /* DNS using UDP */
sptr = getservbyname("ftp", "tcp");    /* FTP using TCP */
sptr = getservbyname("ftp", NULL);     /* FTP using TCP */
sptr = getservbyname("ftp", "udp");    /* this call will fail */
}
/*Returns: non-null pointer if OK, NULL on error */	   
struct servent *getservbyname (const char *servname, const char *protoname);
	   
	   
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*-----------------------------------------------------------------------------------
 Given @node and @service,which identify an Internet host and a service,@getaddrinfo 
 returns one or more addrinfo structures, each of which contains an Internet address 
 that can be specified in a call to @bind or @connect. The @getaddrinfo function co-
 mbines the functionality provided by the @gethostbyname and @getservbyname functions 
 into a single interface,but unlike the latter functions, @getaddrinfo() is reentrant 
 and allows programs to eliminate IPv4-versus-IPv6 dependencies.
 @node
     specifies either a numerical network address (for IPv4,numbers-and-dots notation 
     as supported by @inet_aton; for  IPv6, hexadecimal string format as supported by
     @inet_pton), or a network hostname, whose network addresses are looked up and r-
     esolved. If @hints.ai_flags contains the AI_NUMERICHOST flag,then node must be a 
     numerical network address. The AI_NUMERICHOST flag suppresses any potentially l-
     engthy network host address lookups.
 @service
    sets the port in each returned address structure. If this argument is a service 
    name, it is translated to the corresponding port number.This argument can also be 
    specified as a decimal number, which is simply converted to binary. If service is
    NULL, then the port number of the returned socket addresses will be left uniniti-
    alized. If AI_NUMERICSERV is specified in hints.ai_flags and service is not NULL, 
    then service must point to a string containing a numeric port number. This flag is 
    used to inhibit the invocation of a name resolution service in cases where it is 
    known not to be required.
    Either @node or @service, but not both, may be NULL.
 @hints
    Specifying @hints as NULL is equivalent to setting @ai_socktype and @ai_protocol 
    to 0; @ai_family to AF_UNSPEC; and ai_flags to (AI_V4MAPPED | AI_ADDRCONFIG).
    (POSIX specifies different defaults for ai_flags; see NOTES.)
 @res
    The @getaddrinfo function allocates and initializes a linked list of addrinfo st-
    ructures, one for each network address that matches @node and @service,subject to 
    any restrictions imposed by hints, and returns a pointer to the start of the list 
    in @res.  The items in the linked list are linked by the @ai_next field.

 1 ͨ�����������ڵ���@getaddrinfo֮ǰ��ai_flags����AI_PASSIVE������bind��������nodename
   ͨ��������ΪNULL������ͨ���ַ[::]��
 2 �ͻ��˵���getaddrinfoʱ��ai_flagsһ�㲻����AI_PASSIVE������������nodename�ͷ�����servname
  ����Ը���֮Ϊ�˿ڣ���Ӧ�ò�Ϊ�ա�
 3 ��Ȼ����ʹ������AI_PASSIVE��ȡ���ĵ�ַҲ���ǲ����Ա�bind���ܶ������ai_flagsֱ������Ϊ0��
   ��3����־λ�������ã����������ֻҪhostname��servname���õ�û������Ϳ�����ȷbind��   
-----------------------------------------------------------------------------------*/	   
int getaddrinfo(const char *node, const char *service,const struct addrinfo *hints,
                   struct addrinfo **res);	   
void freeaddrinfo(struct addrinfo *res);
const char *gai_strerror(int errcode);



#define AF_UNSPEC

/*---------------- struct addrinfo @ai_flags 
AI_PASSIVE
   ���˱�־��λʱ����ʾ�����߽���bind()����������ʹ�÷��صĵ�ַ�ṹ�����˱�־����λʱ
   ����ʾ����connect()����������ʹ�á���@nodeΪNULL���Ҵ˱�־��λ���򷵻صĵ�ַ����ͨ
   ���ַ�����@nodeΪNULL���Ҵ˱�־����λ���򷵻صĵ�ַ���ǻػ���ַ��
AI_CANONNAME   
   ���˱�־��λʱ���ں��������صĵ�һ��addrinfo�ṹ�е�@ai_cannoname��Ա�У�Ӧ�ð���һ
   ���Կ��ַ���β���ַ������ַ����������ǽڵ�������������
AI_NUMERICHOST   
   ���˱�־��λʱ���˱�־��ʾ�����еĽڵ���������һ�����ֵ�ַ�ַ�����
*/
#define AI_PASSIVE 
#define AI_CANONNAME 
#define AI_NUMERICHOST


/*-----------------------------------------------------------------------------------
 http://man7.org/linux/man-pages/man3/getaddrinfo.3.html

 @ai_family: AF_INET AF_INET6 AF_UNSPEC
    This field specifies the desired address family for the returned addresses. Valid 
    values for this field include AF_INET and AF_INET6. The value AF_UNSPEC indicates 
    that @getaddrinfo() should return socket addresses for any address family (either 
    IPv4 or IPv6, for example) that can be used with node and service.
 @ai_socktype: SOCK_STREAM SOCK_DGRAM 
    This field specifies the preferred socket type,for example SOCK_STREAM or SOCK_DGRAM. 
    Specifying 0 in this field indicates that socket addresses of any type can be ret-
    urned by @getaddrinfo().
 @ai_protocol: IPPROTO_IP IPPROTO_IPV4 IPPROTO_IPV6 IPPROTO_UDP IPPROTO_TCP
    This field specifies the protocol for the returned socket addresses. Specifying 0 
    in this field indicates that socket addresses with any protocol can be returned by
    @getaddrinfo().
 @ai_flags: AI_PASSIVE AI_CANONNAME AI_NUMERICHOST
    This field specifies additional options, described below. Multiple flags are spec-
    ified by bitwise OR-ing them together.
*/
struct addrinfo {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    size_t ai_addrlen;        //must be zero or a null pointer
    char* ai_canonname;       //must be zero or a null pointer
    struct sockaddr* ai_addr; //must be zero or a null pointer
    struct addrinfo* ai_next; //must be zero or a null pointer
};


