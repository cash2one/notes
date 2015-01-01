/*******************************************************************************
---->FILE
When we open a stream, the standard I/O function @fopen returns a pointer to a 
FILE object. This object is normally a structure that contains all the information
required by the standard I/O library to manage the stream: the file descriptor 
used for actual I/O, a pointer to a buffer for the stream, the size of the buffer,
acount of the number of characters currently in the buffer, an error flag, and 
the like.
To reference the stream, we pass its FILE pointer as an argument to each standard
I/O  function.

---->����FILE����
�ļ�I/O��������ļ��������ģ���׼I/O��Χ����(stream)���еġ�
When we open or create a file with the standardI/O library, we say that we have 
associated a stream with the file.

---->�����ļ�������
�ļ�������:
���������fd��ʾ����fd������open��pipe��dup��dup2��creat�ȵ��÷��صĽ������linux
ϵͳ�У��豸Ҳ�����ļ�����ʽ���ڣ�Ҫ�Ը��豸���в����ͱ����ȴ�����ļ��������
�ļ��ͻᣬ�ͻ�������ļ������������Ǹ���С��������������һ������ֵ��ָ���ں�Ϊÿ
һ��������ά���ĸý��̴��ļ��ļ�¼���ļ����������ŵ㣺����POSIX��׼�����Linux
��UNIXϵͳ���ö������������ļ���������ȱ�㣺������ֲ��UNIX�����ϵͳ��ȥ��Ҳ��ֱ�ۡ�
fdֻ��һ������.

�ļ�ָ��:
C������ʹ�õ����ļ�ָ��������ļ���������ΪI/O�ľ��."�ļ�ָ��(file pointer)"ָ
������û����е�һ������ΪFILE�ṹ�����ݽṹ��FILE�ṹ����һ����������һ���ļ���
����ֵ.���ļ�������ֵ���ļ����������е�һ������.��ĳ��������˵�ļ�ָ����Ǿ����
�����

---->���Ķ��� stream's orientation
A stream's orientation determines whether the characters that are read and written 
are single byte or multibyte. Initially,when a stream is created, it has no 
orientation. If a multibyte I/O function (see<wchar.h>) is used on a stream 
without orientation, the stream's orientation is set to wide oriented. If a byte 
I/O function is used on a stream without  orientation, the stream's orientation 
is set to byte oriented.Only two functions can change the orientation once set. 
The freopen function  will clear a stream��s orientation; the fwide function can 
be used to set a stream's orientation.
*/

/*����Ĭ�ϴ򿪵���
Three streams are predefined and automatically available to a process: standard 
input, standard output, and standard error.These streams refer to the same files 
as the file descriptors STDIN_FILENO, STDOUT_FILENO,and STDERR_FILENO,respectively.
These three standard I/O streams are referenced through the predefined file 
pointers stdin, stdout,and stderr. The file pointers are defined in the<stdio.h> 
header.
*/
#define stdin  /*Standard input  ��׼����*/
#define stdout /*Standard output ��׼���*/
#define stderr /*Standard error  ��׼����*/

/*
---->����
The goal of the buffering provided by the standardI/O library is to use the minimum
number of read and write calls. Also, this library tries to do its buffering 
automatically for each I/O stream, obviating the need for the application to
worry about it.

---->�������͵Ļ���
1 ȫ���� Fully buffered �����ļ�����
  In this case, actual I/O takes place when the standard I/O buffer is filled. 
Files residing on disk are normally fully buffered by the standard I/O library.
The buffer used is usually obtained by one of the standard I/O functions calling 
@malloc the first time I/O is performed on a stream.
  The term flush describes the writing of a standardI/O buffer.A buffer can be 
flushed automatically by the standard I/O routines, such as when a buffer fills, 
or we can call the function @fflush to flush a stream. Unfortunately, in the UNIX
environment,flush means two different things. In terms of the standard I/O library,
it means writing out the contents of a buffer,which may be partially filled. In 
terms of the terminal driver,such as the @tcflush function,it means to discard 
the data that's already stored in a buffer.

2 �л��� Line buffered �ն���ʾ����
  д��һ��֮��Ž���ʵ�ʵ�I/O�����������еĳ����ǹ̶��ģ�д����(��ʱ���ܻ�û��һ
  �еĽ���)Ҳ����I/O������
  
3 �������� Unbuffered
  The standardI/O library does not buffer the	characters. If we write 15  
  characters with the standardI/O @fputs function, for example, we expect 
  these 15 characters to be output as soon as possible, probably with the
  @write function.
  
  The standard error stream, for example, is normally unbuffered so that any 
error messages are displayed as quickly as possible, regardless of whether they
contain a newline.

---->ISO C requires the following buffering characteristics:
1 Standard input and standard output are fully buffered, if and only if they do 
  not refer to an interactive device.
2 Standard error is never fully buffered.

  This, however,doesn't tell us whether standard input and standard output are
unbuffered or line buffered if they refer to an interactive device and whether 
standard error should be unbuffered or line buffered. Most implementations 
default  to  the following types of buffering:
1 Standarderror is always unbuffered.
2 All other streams are line buffered if they refer to a terminal device; 
  otherwise,they are fully buffered.
  The four platforms discussed in this book follow these conventions for 
  standard I/O buffering:standard error is unbuffered, streams open to terminal 
  devices areline buffered, and all other streams are fully buffered.

----> ��δ���
Be aware that if we allocate a standardI/O buffer as an automatic variable within a
function, we have to close the stream beforereturning from the function. (We��ll discuss
this point further in Section 7.8.) Also, some implementations use part of the buffer for
internal  bookkeeping,  so  the  actual  number  of  bytes  of  data  that  can  be  stored  in  the
buffer can be less thansize.Ingeneral, we should let the system choose the buffer size
and  automatically  allocate  the  buffer.When  we  do  this,  the  standardI/O  library
automatically releases the buffer when we close the stream.

********************************************************************************
---->�ļ�ʹ�÷�ʽ
�ļ�ʹ�÷�ʽ��r,w,a,t,b��+�����ַ�ƴ�ɣ����ַ��ĺ����ǣ�
r : read ��
w : write д
a : append ׷��
t : text �ı��ļ�����ʡ�Բ�д
b : binary �������ļ�
+ : ����д

���á�r����һ���ļ�ʱ�����ļ������Ѿ����ڣ���ֻ�ܴӸ��ļ�������
�á�w���򿪵��ļ�ֻ������ļ�д�롣���򿪵��ļ������ڣ�����ָ�����ļ����������ļ���
���򿪵��ļ��Ѿ����ڣ��򽫸��ļ�ɾȥ���ؽ�һ�����ļ���
��Ҫ��һ���Ѵ��ڵ��ļ�׷���µ���Ϣ��ֻ���á�a����ʽ���ļ�������ʱ���ļ������Ǵ�
�ڵģ����򽫻����
��һ���ı��ļ������ڴ�ʱ��Ҫ��ASCII��ת���ɶ������룬�����ļ����ı���ʽд�����ʱ��
ҲҪ�Ѷ�������ת����ASCII�룬����ı��ļ��Ķ�дҪ���ѽ϶��ת��ʱ�䡣�Զ������ļ�
�Ķ�д����������ת����

