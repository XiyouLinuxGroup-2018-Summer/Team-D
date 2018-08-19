#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#define MAXSIZE 1024 
#define BACKLOG 10
#define  PORT 4057
int main(int argc ,char ** argv){

	int listenfd,connfd ;
	struct sockaddr_in servaddr ,cliaddr ;
	socklen_t len ;
	char message[MAXSIZE];
	if((listenfd = socket(AF_INET , SOCK_STREAM , 0)) == -1){//chuang jian tao jie zi 
		
		perror("socket");
		exit(1);
	}
	else{
		
		printf("socket create success\n");
	}

	bzero(&servaddr ,sizeof(servaddr));//qing kong duan kou
	
	servaddr.sin_family = AF_INET ;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	if(bind( listenfd, (struct sockaddr *)&servaddr , sizeof(struct sockaddr)) == -1){
				perror("bind");
				exit(1);
	}

	else{
	
		printf("bind succeed!\n");
	}
	if(listen(listenfd ,BACKLOG) == -1){
		
		perror("listen");
		exit(1);
	}
	else printf("server is listening\n");
	for(;;){
		
		printf("begain to chat....\n");
	
		len = sizeof(struct sockaddr);
		
		if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr,&len)) == -1){
		
			
			perror("accept");
			exit(1);
		}
		else {
			
			printf("hello server!\n");
			printf("client:%s:%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		}
		for( ; ; ){
		
			bzero(message , MAXSIZE);
			printf("Input :");
			scanf("%[^\n]",message);
	
			if(strncasecmp(message , "quit" , 4)){
				
				printf("end chat!\n");
				break ;
			}

			else{
			
				len = send(connfd , message , strlen(message), 0);
			}
			
			if(len < 0){
				
					printf("failed to send\n");
					break ;
				}
				bzero(message ,MAXSIZE);
				len = recv(connfd ,message , MAXSIZE ,0 );
				
				printf("%d\n",len);
		
				if(len > 0){
				
					printf("client:%s\n",message);
				}
			else if(len < 0){
						
					printf("connect client failed!\n");
					break ;
					}
		}
				close(connfd);
				printf("continue or quit?(Y/N)\n");
				bzero(message , MAXSIZE);
				fgets(message , MAXSIZE , stdin);
				if(!strncasecmp(message , "Y" , 1)){
					
					printf("server has exited!\n");
					break ;
					}
				/*
				close(connfd);
				printf("continue or quit?(Y/N)");
				bzero(message , MAXSIZE);
				fgets(message , MAXSIZE , stdin);
				if(!strncasecmp(message , "Y" , 1)){
					
					printf("server has exited!\n");
					break ;
					}*/
			}
		
	close(listenfd) ;
	return 0;
}
