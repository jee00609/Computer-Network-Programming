#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

#define MAXLINE 127

int main(int argc, char *argv[]) {
        struct hostent *hp;
        struct sockaddr_in servaddr;
        int s, nbyte;
        char buf[MAXLINE+1];

        if(argc != 3) {
                printf("Usage : %s hostname, port number\n", argv[0]);
                exit(0);
        }

        if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
                perror("socket fail");
                exit(0);
        }

        hp = gethostbyname(argv[1]);

        //에코 서버의 소켓주소 구조체 작성[FOR 문 쓰지말고!]
        bzero((char *)&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, hp->h_aliases[0], &servaddr.sin_addr);
        servaddr.sin_port = htons(atoi(argv[2]));

        printf("Server IP: %s\n", inet_ntoa(*(struct in_addr *)hp->h_addr_list[0]));

        // 연결요청
        if(connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
                perror("connect fail");
                exit(0);
        }

        printf("입력 : ");
        if(fgets(buf, sizeof(buf), stdin) == NULL)
                exit(0);
        nbyte = strlen(buf);

        if(write(s, buf, nbyte) < 0) {
                printf("write error\n");
                exit(0);
        }

        printf("수신 : ");
        if((nbyte = read(s, buf, MAXLINE)) < 0) {
                perror("read fail");
                exit(0);
        }

        buf[nbyte] = 0;
        printf("%s", buf);
        close(s);
        return 0;
}
