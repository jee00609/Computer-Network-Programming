#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 511

char *EXIT_STRING = "exit";
int recv_and_print(int sd,struct sockaddr_in* servaddr); //인자를 추가하여 FORK 로 인해 보내지 못했던 주소값 전달할 수 있게 변형
int input_and_send (int sd,struct sockaddr_in* servaddr);//위 주석과 동일

int flag = 0;//전역 FLAG 값 => 한번이라도 RECEIVE 할 시 0에서 1로 올림

int main(int argc,char *argv[]){
                struct sockaddr_in servaddr,cliaddr;
                int nbyte;
                int s;
				int addrlen = sizeof(struct sockaddr);//추가 된다.
                char buf[MAXLINE+1];
				pid_t pid;

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

                puts("서버가 클라이언트를 기다리고 있습니다.");
                //listen(s,1);

				recv_and_print(s,&cliaddr);

				//printf("nbyte : %d\n",nbyte);
				if((pid=fork())>0)
						input_and_send(s,&cliaddr);
				else if(pid == 0)
						recv_and_print(s,&cliaddr);
				close(s);
				
				return 0;

}
//키보드 입력받고 상대에게 메시지 전달
int input_and_send(int sd,struct sockaddr_in* servaddr){
        char buf[MAXLINE+1];
        int nbyte;
		int addrlen = sizeof(struct sockaddr_in);

        while(fgets(buf,sizeof(buf),stdin) != NULL){
                nbyte = strlen(buf);
                write(sd,buf,strlen(buf));
				if(sendto(sd,buf,strlen(buf),0,(struct sockaddr *)servaddr,addrlen)<0){
					perror("send to fail");
					exit(1);
				}

                if(strstr(buf,EXIT_STRING) != NULL){
                        puts("Good Bye");
                        close(sd);
                        exit(0);
                }
        }
        return 0;
}

//상대로부터 메시지 수신 후 화면 출력
int recv_and_print(int sd,struct sockaddr_in* servaddr){
        char buf[MAXLINE+1];
        int nbyte;
		int addrlen = sizeof(struct sockaddr_in);
        while(1){
                if((nbyte = recvfrom(sd,buf,MAXLINE,0,(struct sockaddr*)servaddr,&addrlen))<0){
                        perror("read fail");
                        close(sd);
                        exit(0);
                }
                buf[nbyte]=0;

                if(strstr(buf,EXIT_STRING)!=NULL)
                                break;
                printf("%s",buf);


				if(flag==0){
						flag=1;
						break;
				}
        }
        return 0;
}
