
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<mysql/mysql.h>
#include<errno.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#define N 1000
#define PORT 7230
#define LN 50
#define LOG_SUCCESS 1
#define ONLINE 1
#define OFF_LINE 0
#define NOT_ROOT 2
#define ROOT 3

typedef struct user{
	
	int id ;
	int exist ;
	int socket ;
	char nickname[LN] ;
	char name[LN] ;
	char pass[LN];
	char phonenum[LN];//电话号码
	int isonline ;//是否在线
	int flag ;//判断是否被禁言 0禁烟 1不禁
	
}user_t;
typedef struct msg{
	
	user_t user ;
	int islogin ;

	int cmd ;//给服务器下命令的
//	『1.登陆 2.注册 』
	char msg[N] ;//消息内容
	char nameto[LN];//发送对象姓名
	char namefrom[LN];//发送人姓名
	int isroot;//是否为群主
	char time[LN];
}msg_t;

int print_log();
void sock_init(int * conn_fd);
void ny_err(char* string ,int line);
int log_in();
int re_account();
int conn_fd ;
//void * recv_pack();
void my_err(char * string , int line){//提示错误信息

	printf("%d:",line);
	perror(string);
	exit(1);
}
/*
void * recv_pack(){

	msg_t msg ;
	int ret ;

	if((ret = recv(conn_fd , &msg ,sizeof(msg) , 0)) < 0){
	
			printf("\n\t\tjie shou xian xi chu cuo!\n");
	}
	if(ret > 0){
	
		
	
	}
}*/
void * recv_msg(void * conn_fd){
	int con ;
	msg_t msg ;
	bzero(&msg ,sizeof(msg));
	if(recv(con , &msg ,sizeof(msg) , 0) < 0){
	
		perror("\n\t\trecv\n");
		return ;
	}

	if(msg.cmd == 0 || msg.user.exist == 1){
	
		printf("\n\t\tregist success!\n");
		return ;
	}

	
}
int log_in(){
	
	msg_t users ;

	bzero(&users , sizeof(msg_t));
	
	while(1){
	
		printf("\n\t\tInput account name :");
	
		scanf("%[^\n]",users.user.name);
	
		while('\n'!=getchar()) ;
		printf("\n\t\tInput account password :");
		
		scanf("%[^\n]",users.user.pass);
		
		while('\n'!=getchar());
		
		users.islogin = 0 ;
		
		users.cmd = 1;

		users.user.socket = conn_fd ;

		if(send(conn_fd , &users ,sizeof(msg_t),0) < 0){
			
			perror("\n\t\tsend\n");
			return  0;
		}
		
//		pthread_t thid ;
		//pthread_create( &thid , NULL , (void *)&recv_pack , NULL);
			
			int ret ;
			if((ret =recv(conn_fd ,&users ,sizeof(msg_t) , 0)) < 0){
				
				perror("\n\t\trecv\n");
				return 0 ;
			}
			else if( ret == 0){
				
				printf("\n\t\tserver offline !\n");
				return 0 ;
			}

			else if(users.user.isonline == 1){
				
			printf("\n\t\tret = %d\n",ret);
				return 1 ;
			}
			printf("*name:%s",user.user.name);
			getchar();
		}
			
	}
	
}
int re_account(){

	msg_t msg ;
	bzero(&msg, sizeof(msg_t));
	while(1){
	

		printf("\n\t\tInput nickname:") ;
		
		scanf("%[^\n]",msg.user.nickname);
		
		while('\n'!=getchar());
		
		printf("\n\t\tInput account number:");
		scanf("%[^\n]",msg.user.name);
		while('\n' != getchar()) ;
		printf("\n\t\tInput account number:");
		
		scanf("%[^\n]",msg.user.phonenum);
		
		while('\n' != getchar());

	
		printf("\n\t\tInput password:");
		
		scanf("%[^\n]",msg.user.pass);
		while('\n'!= getchar());
		msg.user.socket = conn_fd ;
		msg.cmd = 0 ;
		msg.user.exist = 0 ;
		int n ;
		if((n = send(conn_fd ,&msg ,sizeof(msg_t),0)) < 0){
		
			perror("\n\t\tsend");
			return 0 ;
		}
		
	
		printf("\n\t\tregist an account.\n");
		
		return 1;
	
	}
	
}
void sock_init(int * conn_fd){//初始化套接字
		
	*conn_fd = socket(AF_INET , SOCK_STREAM , 0);
	if(*conn_fd < 0){

		my_err("socket",__LINE__ ) ;
	}
}
int main(int argc , char ** argv){


	char  choice ;
	char * ip = "127.0.0.1";
	struct sockaddr_in serv_addr ;
	memset(&serv_addr , 0 , sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_INET ;
	
	serv_addr.sin_port = htons(7230);


	inet_aton("127.0.0.1",&serv_addr.sin_addr) ;
//	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	
	sock_init(&conn_fd);
//向服务器发送连接请求
	
	
	if(connect(conn_fd , (struct sockaddr *)&serv_addr , sizeof(struct sockaddr_in)) < 0){
	
			my_err("connect" , __LINE__);
		}
		printf("\n\t\tConnect server succeess!\n");
	
		while(1){
			if(print_log() == 0){
	
			return 0 ;
			}
	
	
		
		pthread_t thid1 ;

		pthread_create( &thid1 , NULL ,(void*)&recv ,NULL );

		pthread_join(&thid1 , NULL);
		
		}
	}
}

int print_log(){//打印初始登陆

	char choice ;
	
	do{
		system("clear") ;
		printf("\n\t\t>>> [L] user login\n");
		printf("\n\t\t>>> [R] register an accunt\n");
		printf("\n\t\t>>> [Q] quit\n");
		printf("\n\t\tInput your choice :");
	
		choice = getchar();
		while('\n' != getchar());

		switch(choice){
			
			case 'l':
			case 'L':
				if(log_in() == 1){
				
					return 1 ;
				}

				break ;
			case 'R':
			case 'r':
				if(re_account()== 1){
					
					printf("\n\t\tyou can log in!\n");
					continue ;
				}
				printf("\n\t\tPress [enter]key to continue....\n");
				while('\n' != getchar());
				break ;
		}
	}while(choice !='q'||choice != 'Q');

	return 0 ;
}

