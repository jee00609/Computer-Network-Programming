#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 511

int main(int argc,char *argv[]){
		struct sockaddr_in servaddr,cliaddr;
		//int listen_sock,accp_sock; 사용하지 않는다.
		//int addrlen = sizeof(cliaddr);
		int nbyte;
		int s,addrlen = sizeof(struct sockaddr);//추가 된다.
		char buf[MAXLINE+1];

		if(argc!=2){
				printf("Usuage:%s port\n",argv[0]);
				exit(0);
		}

		if((s = socket(PF_INET,SOCK_DGRAM,0))<0){
				//SOCK_DRAM 으로 변경된다.
				perror("socket fail");
				exit(0);
		}

		//servaddr 을 '\0'으로 초기화
		bzero((char *)&servaddr,addrlen);
		bzero((char *)&cliaddr,addrlen);

		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(atoi(argv[1]));

		if(bind(s,(struct sockaddr *)&servaddr,addrlen)<0){
				perror("bind fail");
				exit(0);
		}

		//interative 에코 서비스 수행
		while(1){
				puts("Server : Waiting Request.");
				
				//accp_sock = accept(listen_sock,(struct sockaddr *)&cliaddr,&addrlen);
				nbyte = recvfrom(s,buf,MAXLINE,0,(struct sockaddr *)&cliaddr,&addrlen);	
				
				if(nbyte < 0){
						perror("recvfrom fail");
						exit(1);
				}

				buf[nbyte]=0;

				printf("%d byte recv:%s\n",nbyte,buf);
				
				if(sendto(s,buf,nbyte,0,(struct sockaddr *)&cliaddr,addrlen)<0){
						perror("sendto fail");
						exit(1);
				}
				puts("sendto complete");
		}

}
