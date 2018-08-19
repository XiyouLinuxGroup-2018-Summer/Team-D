#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define MAXSIZE 1024
#define PORT 4057
#define BACKLOG 10
int main(int argc ,char ** argv){

	int sockfd ;
	struct sockaddr_in servaddr;
	socklen_t len ;
	char message[MAXSIZE];
	if((sockfd = socket(AF_INET ,SOCK_STREAM , 0) )== -1){
	
		perror("socket");
		exit(1);
	}

	else printf("socket create success!\n");

	bzero(&servaddr , sizeof(servaddr));

	servaddr.sin_family = AF_INET ;
	
	servaddr.sin_port = htons(PORT);
	
	inet_aton(argv[1],&servaddr.sin_addr);
	int ret;
	if((ret = connect(sockfd , (struct sockaddr *)&servaddr,  sizeof(struct sockaddr))) == -1){
	
		perror("connect");
		exit(1);
	}
	else{
		printf("connect sucess!\n");
	}
	for( ; ;){
				
	len = recv(sockfd , message , MAXSIZE , 0) ;
	printf("*%d*\n",len);
	printf("%s",message);
	if(len > 0){
			
		printf("server:%s\n",message);
		}
	else{
				
				if(len < 0){
				
					printf("get message failed!\n");
				}
				else{
				//	printf("*hello*\n");
				}
			}
			bzero(message ,MAXSIZE);
			
			printf("input:");
			
			scanf("%[^\n]",message);
			
			
			if(!strncasecmp(message , "quit" , 4)){
			
				printf("request end chat!\n");
				break ;
			}
			else len = send(sockfd , message , strlen(message), 0);

			if(len < 0){
			
				printf("failed to send message!\n");
				break ;
			}
		}

		close(sockfd);
		return 0 ;
}
