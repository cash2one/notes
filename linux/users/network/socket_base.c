
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
---->�׽��ֵ�ַ
ÿ��Э���嶼�������Լ����׽��ֵ�ַ�ṹ��

ipv4�׽��ֵ�ַ�ṹ,Ҳ��Ϊ�����׽��ֵ�ַ�ṹ struct sockaddr_in
ͨ���׽��ֵ�ַ�ṹ 

�׽�����ͨ�Ŷ˵�ĳ��󣬷����׽�����Ҫʹ���׽���������(���ļ�����������)�� 
�׽�����������UNIXϵͳ�����ļ�������ʵ�ֵġ�

