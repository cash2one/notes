
//http://www.cnblogs.com/Anker/p/3438480.html
/*intptr_t�ڲ�ͬ��ƽ̨�ǲ�һ����,ʼ�����ַλ����ͬ,���������ŵ�ַ,����ַ.*/
/* Types for `void *' pointers.  */
#if __WORDSIZE == 64
# ifndef __intptr_t_defined
typedef long int		intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned long int	uintptr_t;
#else
# ifndef __intptr_t_defined
typedef int			intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned int		uintptr_t;
#endif
