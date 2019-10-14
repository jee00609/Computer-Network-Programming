#include <stdio.h>
int main(){
		char s1[30];
		char s2[30];
		char s3[30];
		char s4[30];

		printf("학과는?\n");
		scanf("%s",s1);

		printf("학년은?\n");
		scanf("%s",s2);

		printf("학번은?\n");
		scanf("%s",s3);

		printf("이름은?\n");
		scanf("%s",s4);

		int i=0;
		for(i=0;i<5;i++)
				printf("학과:%s 학년:%s 학번:%s 이름:%s\n",s1,s2,s3,s4);

		return 0;
}
