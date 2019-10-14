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
                int s,nbyte;
                struct sockaddr_in servaddr;
                char buf[MAXLINE+1];
				int addrlen = sizeof(servaddr);

                if(argc!=3){
                                printf("Usuage:%s ip_address\n",argv[0]);
                                exit(0);
                }

                if((s=socket(PF_INET,SOCK_DGRAM,0))<0){
								//SOCK_DGRAM 으로 변경
                                perror("socket fail");
                                exit(0);
                }

                bzero((char *)&servaddr,sizeof(servaddr));

                servaddr.sin_family = AF_INET;
                //inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
                servaddr.sin_addr.s_addr = inet_addr(argv[1]);
				servaddr.sin_port = htons(atoi(argv[2]));

                printf("입력");
                if(fgets(buf,MAXLINE,stdin)==NULL){
                        printf("fgets 실패");        
						exit(0);
                }

                //nbyte=strlen(buf);
				if(sendto(s,buf,strlen(buf),0,(struct sockaddr *)&servaddr,addrlen)<0){
						perror("sendto fail");
						exit(0);
				}

                //printf("수신:");
                if((nbyte = recvfrom(s,buf,MAXLINE,0,(struct sockaddr *)&servaddr,&addrlen))<0){
						perror("recvfrom fail");
						exit(0);
				}

                buf[nbyte]=0;
                printf("%s\n",buf);
                close(s);

                return 0;
}
