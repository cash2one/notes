
/*
@mode:
If the mode argument is negative,fwide will try to make the specified stream byte oriented.
If the mode argument is positive,fwide will try to make the specified stream wide oriented.
If the mode argument is zero,fwide will not try to set the orientation, but will still return a value identifying the stream��s orientation.

Note thatfwidewill not change the orientation of a stream that is already oriented.
Also note that there is no error return.  Consider what would happen if the stream is
invalid.  The only recourse we have is to clear errnobeforecallingfwideand check
the value oferrnowhen we return.

Returns: positive if stream is wide oriented, negative if stream is byte oriented, or 0 if stream has no orientation*/
#include <stdio.h>
#include <wchar.h>
int fwide(FILE *fp,int mode);


/*
�������Ļ�������
@fp:
@buf:point to a buffer of length BUFSIZ( defined in<stdio.h>)

Returns: 0 if OK, non zero on error
Normally,the stream is then fully buffered, but some systems may set line buffering if the stream is associated
with a terminal device.To disable buffering, we set buf to NULL.
*/
void setbuf(FILE *restrict fp,char *restrict buf);

/*
@fp:
@buf:������ָ��
@mode:������ģʽ
@size:��������С

function:�������Ļ�������
return:0 if OK, non zero on error

mode argument:
_IOFBF fully buffered
_IOLBF line buffered
_IONBF unbuffered

������޻���ģʽ��@buf��@size��������
������л���ģʽ����@buf��NULL������Զ����仺������СΪBUFSIZ
*/
int setvbuf(FILE *restrict fp,char *restrict buf,int mode, size_t size);


/*
The fflush function causes any unwritten data for the stream to be passed to the
kernel. As a special case, if fp is NULL,fflush causes all output streams to be flushed.

Returns: 0 if OK,EOF on error*/
#include <stdio.h>
int fflush(FILE *fp);




/*

fopen:opens a specified file.
freopen:opens a specified file on a specified stream, closing the stream first if it is already open. If the stream previously 
    had an orientation,freopen clears it. This function is typically used to open a specified file as one of the predefined 
    streams: standardinput, standardoutput, or standarderror.
fdopen:takes an existing file descriptor,which we could obtain from the open,dup,dup2,fcntl,pipe,socket,socketpair,or accept
    functions,and associates a standard I/O stream with the descriptor.This function is often used with descriptors that are 
    returned by the functions that create pipes and network communication channels. Because these special types of files cannot 
    be opened with the standard I/O fopen function, we have to call the device-specific function to obtain a file descriptor,
    and then associate this descriptor with a standardI/O stream usingfdopen.
return: All three return file pointer if OK,NULL on error

Both fopen and freopen are part of ISO C;fdopen is part of POSIX.1, since ISO C doesn��t deal with file descriptors

---->����type

*/
#include <stdio.h>
FILE *fopen(const char *restrict pathname,const char *restrict type);
FILE *freopen(const char *restrict pathname,const char *restrict type,FILE *restrict fp);
FILE *fdopen(int fd,const char *type);



/*
Three functions allow us to read one character at a time.
The function getchar is defined to be equivalent to getc(stdin).The difference between getc and fgetc is that getc can be 
implemented as a macro, whereas fgetc cannot be implemented as a macro.  

All three return: next character if OK,EOF on end of file or error*/
#include <stdio.h>
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);

/*
Note that these functions return the same value whether an error occurs or the end
of file is reached. To distinguish between the two, we must call either ferror or feof.

Both return: nonzero(true) if condition is true, 0 (false) otherwise
*/
#include <stdio.h>
int ferror(FILE *fp);
int feof(FILE *fp);


/*
In most implementations, two flags are maintained for each stream in the FILE object:
An error flag An end-of-file flag
Both flags arecleared by calling clearerr.
*/
void clearerr(FILE *fp);


/*
    After reading from a stream, we can push back characters by calling ungetc
    The characters that arepushed back arereturned by subsequent reads on the stream in reverse  order  of  their  pushing. 
    The character that we push back does not have to be the same character that was read. We are notable to push back EOF.When we 
reach the end of file, however,we can push back a character.The next read will return that character,and the read after that 
will return EOF.
    When we push characters back with ungetc,they are not written back to the underlying file or device. Instead, they are kept 
incore in the standardI/O library's buffer for the stream.


Returns:c if OK,EOF on error */
#include <stdio.h>
int ungetc(intc,FILE *fp);


/*
putchar(c) is equivalent to putc(c, stdout),and putc can be implemented as a macro, whereas fputc cannot be implemented as a macro.

All three return:c if OK,EOF on error*/
#include <stdio.h>
int putc(int c,FILE *fp);
int fputc(int c,FILE *fp);
int putchar(int c);



/*Both specify the address of the buffef to read the line into. The gets function reads from standard input, whereas fgets reads from the specified stream.
fgets:һ�ζ���һ�У�����n-1���ַ�����n���ַ��Զ���NULL�����һ�ж���n-1���ַ������Է����ζ�ȡ����fgets���´ζ�ȡ����������С�
gets:���Ƽ�ʹ�ã�������ɻ��������������gets����ȡ���з���
Both return:buf if OK,NULL on end of file or erro*/
#include <stdio.h>
char *fgets(char *restrict buf,int n,FILE *restrict fp);
char *gets(char *buf);



/*
fputs: writes the null-terminated string to the specified stream.The null byte at the end is not written. 
puts:  writes the null-terminated string to the standardoutput, without writing the null byte. But puts then writes a newline character to the standard output.

Both return: non-negative value if OK,EOF on error*/
#include <stdio.h>
int fputs(const char *restrict str,FILE *restrict fp);
int puts(const char *str);


/*
�������ƣ�fileno����VC++6.0��Ϊ_fileno[1] ��
����ԭ�ͣ�int _fileno( FILE *stream );
�������ܣ�fileno()����ȡ�ò���streamָ�����ļ�����ʹ�õ��ļ�������
����ֵ��ĳ�����������ļ�������
ͷ�ļ���stdio.h
��غ�����open��fopen��fclose  
*/
int fileno( FILE *stream );

