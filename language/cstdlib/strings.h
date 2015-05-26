/*-----------------------------------------------------------------------------------
<strings.h> ����C/C++�ı�׼ͷ�ļ���������string.h
http://blog.csdn.net/xin_yu_xin/article/details/38672137
strings.hͷ�ļ��Ǵ�BSDϵUNIXϵͳ�̳ж��������涨����һЩ�ַ�����������bzero�ȡ���Щ��
��������posix��׼��һ���֣�������POSIX.1-2001��׼���棬��Щ���������Ϊ��������������
�Ƽ�ʹ�á���POSIX.1-2008��׼���Ѿ�û����Щ�����ˡ�  
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 The strcasecmp() function performs a byte-by-byte comparison of the strings s1 and -
 s2, ignoring the case of the characters. It returns an integer less than , equal to, 
 or greater than zero if s1 is found, respectively, to be less than , to match, or be 
 greater than s2. The strncasecmp() function is similar , except it compares only the
 first n bytes of s1.

 http://man7.org/linux/man-pages/man3/strncasecmp.3.html
-----------------------------------------------------------------------------------*/
int strcasecmp (const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);


void bzero(void *, size_t); /* ��memset��� */

/*-----------------------------------------------------------------------------------
func:
    copies @n bytes from @src to @dest. The result is correct, even when both areas -
    overlap.This function is deprecated (marked as LEGACY in POSIX.1-2001):use memcpy 
    or memmove in new programs.
-----------------------------------------------------------------------------------*/
void bcopy(const void *src, void *dest, size_t n);

