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
	   
	   
int getaddrinfo( const char *hostname, const char *service, 
	                const struct addrinfo *hints, struct addrinfo **result );

