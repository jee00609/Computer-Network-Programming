#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>

#define MAXLINE 511

int main(int argc,char *argv[]){
		int s,nbyte;
		struct sockaddr_in servaddr,cliaddr;
		int addrlen = sizeof(struct sockaddr);
		char buf[MAXLINE+1];

		struct hostent *hp;
		struct in_addr in;
		int i;
		char buf2[20];

		if(argc!=2){
				printf("Usuage:%s host_name\n",argv[0]);
				exit(0);
		}

		hp = gethostbyname(argv[1]);
		if(hp==NULL){
				printf("gethostbyname fail");
				exit(0);
		}

		
		
		for(i=0;hp->h_addr_list[i];i++){
				memcpy(&in.s_addr,hp->h_addr_list[i],sizeof(in.s_addr));
				inet_ntop(AF_INET,&in,buf2,sizeof(buf2));
		}
		

		//buf2=hp->h_addr_list[0];

		if((s=socket(PF_INET,SOCK_DGRAM,0))<0){
				perror("socket fail");
				exit(0);
		}

		bzero((char *)&servaddr,addrlen);
		//bzero((char *)&cliaddr,addrlen);

		servaddr.sin_family = AF_INET;
		//inet_pton(AF_INET,buf2,&servaddr.sin_addr);
		servaddr.sin_addr.s_addr = inet_addr(buf2);
		
		servaddr.sin_port = htons(13);

		/*
		while(1){
				nbyte = recvfrom(s,buf,MAXLINE,0,(struct sockaddr *)&cliaddr,&addrlen);

				if(nbyte<0){
						perror("receive fail");
						exit(1);
				}

				buf[nbyte]=0;
				printf("%s",buf);

				if(sendto(s,buf,nbyte,0,(struct sockaddr *)&cliaddr,addrlen)<0){
						perror("sendto fail");
						exit(1);
				}

		}
		*/


		if(sendto(s,buf,strlen(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
				perror("sendto fail");
				exit(0);
		}

		if((nbyte = recvfrom(s,buf,MAXLINE,0,(struct sockaddr *)&servaddr,&addrlen))<0){
				perror("recvfrom fail");
				exit(0);
		}
		
		
		buf[nbyte]=0;
		printf("%s",buf);
		close(s);
		
		return 0;
}
