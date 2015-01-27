#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FIFO "/tmp/my_fifo"
/*-----------------------------------------------------------------------------------
 �������һ��FIFO�����ݣ����Ѷ��������ݴ�ӡ����׼�������������ַ���Q�������˳� 
-----------------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
    char buf_r[100];
    int fd;
    int nread;
	
    if((mkfifo(FIFO, O_CREAT) < 0) && (errno != EEXIST))
    {
        printf("mkfifo fail \r\n");
        exit(1);
    }
	
    printf("read data:\r\n");
    fd = open(FIFO, O_RDONLY, 0);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    while(1)
    {
        if((nread = read(fd, buf_r, 100)) == -1)
        {
            if(errno == EAGAIN) printf("no data \r\n");
        }

        if(buf_r[0]=='Q') break;

        buf_r[nread]=0;
        printf("date from fifo��%s\n", buf_r);
        sleep(1);
    }
}

