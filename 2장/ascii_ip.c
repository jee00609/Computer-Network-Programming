#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>

int main(int argc,char *argv[]){
	struct in_addr inaddr;
	char buf[20];

	if(argc<2){
		printf("사용법 :%sIP 주소 (dotted decimal)\n",argv[0]);
		exit(0);
	}

	printf("입력한 dotted decimal IP 주소(DOTTED DECIMAL)\n",argv[1]);

	inet_pton(AF_INET,argv[1],&inaddr.s_addr);
	printf("inet_pton(%s)=0x%X\n",argv[1],inaddr.s_addr);

	inet_ntop(AF_INET,&inaddr.s_addr,buf,sizeof(buf));
	printf("inet_ntop(0x%X)=%s\n",inaddr.s_addr,buf);

	return 0;
}
