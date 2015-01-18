#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


/*
 ���ļ�"log.txt"(û���򴴽�)������ȡ�ļ�������oldfd������dup2����������Ϊoldfd��1��
 ��ᵼ���������´򿪵��ļ��������滻����1������ļ�����������stdout����Ϊ��׼�����
 ����idΪ1�����κ�д��stdout�Ķ��������ڶ�����Ϊд����Ϊ"log.txt"���ļ��С���Ҫע���
 �ǣ�dup2�����ڸ�����oldfd֮�󣬻���������رգ�������ص��½��򿪵��ļ�����������Ϊ
 �ļ�������1����Ҳָ������
*/
int dup2_eg01()
{
	int oldfd;
	oldfd = open("log.txt", (O_RDWR | O_CREAT), 0644 );
	if(oldfd < 0){
		printf("open fail!\r\n");
		return -1;
	}
	dup2( oldfd, 1 ); /* stdout */
	close( oldfd );
	printf("abcd\r\n"); /* output to file "log.txt"*/
	return 0;
}

int dup2_eg02()
{
    int pfds[2]; /* 0:read 1:write*/
	pid_t pid;
	int nbytes;
	char buf[1000] = {0};

    if ( pipe(pfds) < 0 ) {
        printf("pipe error \r\n");
		return -1;
    }
	pid = fork();
	if(pid < 0){
		printf("fork error \r\n");
	}
/*
 �ӽ��̹رձ�׼������ѹܵ���д�˸��Ƶ���׼������൱��ԭ���������׼�������������Ҫ
 д��ܵ��������̶�ȡ�ܵ�������ݣ������������ӽ���ִ������ls -l �����д��ܵ�������
 �̶�ȡ��
*/	
    if ( pid == 0 ) {

        close(1); /* STDOUT_FILENO */
        dup2( pfds[1], 1 );
        close( pfds[0] );
        if(execlp( "ls", "ls", "-l", NULL ) < 0){
			printf("execlp error");
			exit(0);
        }
    } else {
        #if 0
        close(0);
        dup2( pfds[0], 0 ); /* STDIN_FILENO */
        close( pfds[1] );
		//if (waitpid(pid, NULL, 0) < 0) {
            //printf("wait error\r\n");
        //}
		execlp( "wc", "wc", "-l", NULL );
        return 0;
		#else
		while(1) {
			close( pfds[1] );
		    nbytes = read(pfds[0],buf,sizeof(buf));
			if(nbytes <= 0){
				printf("father read %d bytes\r\n",nbytes);
				break;
			}
			printf("----> father read %d bytes:\r\n",nbytes);
			printf(buf);
		}	
		#endif
    }
}

int main()
{
    dup2_eg02();
}

/*
 http://hi.baidu.com/flikecn/item/e82e14bef06e8a412aebe38a

 3 CGI��dup2
 д��CGI������˶�������������ʹ��post�����ύ������ʱ��CGI�������Ǵӱ�׼

����stdin, д������д����׼���stdout(c��������printf����)������������������

�⣬printf�����Ӧ�����ն���ʾ��ԭ��CGI����ʹ��dup2������STDOUT_FINLENO(���

����unitstd.h���壬Ϊ��)����ļ��������ض����������׽��֡�

dup2(connfd, STDOUT_FILENO)����ʵ��������漰���˹ܵ������Ǳ��ĵ��ص�

���һ����˵����һ������Ĭ�ϵ��ļ���������(STDOUT_FILENO)�Ǻͱ�׼���stdout��

�����ģ������ں˶��ԣ����д򿪵��ļ���ͨ���ļ����������ã����ں˲���֪������

����(����stdin��stdout)������printf���������stdout���������д�����ļ�����

�������档�����ļ�������0������2���׼���롢��׼�������׼����������������

ֻ��shell�Լ��ܶ�Ӧ�ó���Ĺ����������ں��޹ء�

���������ͼ����˵������:(ps: ��Ȼ������ͼ��ϵ�����ǻ������������)

printf ��> stdout ��> STDOUT_FILENO(1) ��> �ն�(tty)

printf������������ն��豸���ļ���������ָ��ǰ���ն˿�����ô��⣺

STDOUT_FILENO = open("/dev/tty", O_RDWR);

ʹ��dup2֮��STDOUT_FILENO����ָ���ն��豸��������ָ��connfd, ����printf��

������д����connfd���ǲ��Ǻ�������:)

4. �����CGI�����fork�ӽ����л�ԭSTDOUT_FILENO

������ܿ��������л������ģ�����֪���ܶ��˿��ܸо��е㸴�ӣ�����ʵ

���ӵ��������һ����С����ļ��ϡ�����Ū���ÿ��С�����OK�ˣ���������

˵����STDOUT_FILENO���ض�����connfd�׽��֣�����ʱ�����ǿ�������CGI����

�е��ú�̨�ű�ִ�У�����Щ�ű����������һЩ���������������֪��fork֮��

�ӽ��̼̳��˸����̵������ļ���������������Щ�ű����������������������Ը

������ն��豸�����Ǻ�connfd������ˣ������Ȼ��������ҳ���������ô���

�ָ�STDOUT_FILENO���ն˹����أ�

����������dup2֮ǰ����ԭ�е��ļ���������Ȼ��ָ���

����ʵ�����£�

savefd = dup(STDOUT_FILENO);���savefd��ʱָ���ն�

dup2(connfd, STDOUT_FILENO);   STDOUT_FILENO(1) ������ָ��connfd

..... ����һЩ����

dup2(savefd, STDOUT_FILENO); STDOUT_FILENO(1)���ָ�ָ��savefd


���ź�CGI�����޷�ʹ�����ַ���������Ϊdup2��Щ������CGI��������ɵģ�������

web server��ʵ�ֵģ��޸�web server�����Ǹ������⡣

����2: ׷����Դ���򿪵�ǰ�ն˻ָ�STDOUT_FILENO��

���������ڵ���ͼ����STDOUT_FILENO����κ��ն˹����ģ���������ͷ��һ�鲻����

�ˣ�������ʵ�����£�

ttyfd = open("/dev/tty", O_RDWR);

dup2(ttyfd, STDOUT_FILENO);

close(ttyfd);

/dev/tty�ǳ����������ڵ��նˣ������Ӧ��ͨ��һ�ַ�����á�ʵ��֤�����ַ���

�ǿ��еģ��������ܸо���Щ���ף���֪��Ϊʲô������һЩǱ�ڵ����⻹û���֡�

Ŀǰ�Ҿ��뵽�����ַ���������֪������ʲô�õ��뷨�����еĻ�ϣ��������:)


������β�ˣ�һ���Ϲ���д��û�뵽д������Сʱ��д�꣬�þ�û��дԭ���ˣ�����ʰ

����ǰ������ĸо�:)


*/
