#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
        int fd1,fd2,sd1,sd2;

        //passwd 파일 열기
        fd1 = open("/etc/passwd",O_RDONLY,0);
        printf("/etc/passwd's file descriptor = %d\n",fd1);


        //스트림형 소켁 개설
        sd1 = socket(PF_INET,SOCK_STREAM,0);
        printf("stream socket descriptor = %d\n",sd1);

        //데이터그램형 소켓 개설
        sd2 = socket(PF_INET,SOCK_DGRAM,0);
        printf("stream socket descriptor = %d\n",sd2);

        //host 파일 열기
        fd2 = open("/etc/hosts",O_RDONLY,0);
        printf("/etc/host's file descriptor = %d\n",fd2);

        close(fd2);
        close(sd2);
        close(fd1);
        close(sd1);

        return 0;
}
