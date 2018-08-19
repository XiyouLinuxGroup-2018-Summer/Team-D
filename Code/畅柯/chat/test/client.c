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
#define A_F 2 //tian jia hao you 添加好友
#define A_G 3 // chuang jian qun//创建群聊
#define I_F 4 // yao qing hao you jin qun邀请好友金群
#define K_P 5 //ti ren踢人
#define N_T 6 //jin yan禁烟
#define A_A 7 //tian jia guan li yuan 添加管理元
#define S_L 8 //si liao饲料
#define O_F 9//li xian xiao xi离线消息
#define H_M 10 // liao tian ji lu聊天记录
#define S_F 11 //chuan shu wen jian文件传输
#define EXIT 12//xia xian

int main_menu();
typedef struct user{
	
	int exist ;
	int socket ;
	char nickname[LN] ;
	char name[LN] ;
	char pass[LN];
	char phonenum[LN];//电话号码
	int isonline ;//是否在线
	int flag ;//判断是否被禁言 0禁烟 1不禁
	
}user_t;

typedef struct cli_fri_group{//hao you lie biao shu ju jie gou 

	char h_name[LN] ;//ben ren de ming zi

	char f_name[LN] ;//peng you de ming zi
	
	int f_status ;//peng you de xian shang zhuang tai ;

	char msg[N]; //yu peng you de liao tian ji lu 

	char time[N]; //zui hou yi ci tong shi jian 

}cli_fri_group;
typedef struct msg{
	
	cli_fri_group client_info ;
	user_t user ;
	int islogin ;

	int cmd ;//给服务器下命令的
	int isagree ;
//	『1.登陆 2.注册 』
	char msg[N] ;//消息内容
	int r_a ;
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
void do_cmd(int cmd);
int conn_fd ;
void recv_pack(void * arg);
void add_friends();
void is_agree(msg_t msgs);
void is_agree(msg_t msgs){

	int ch ;
	
	printf("\n\t\t>>> [0]N   >>> [1]Y\n");	
	printf("\n\t\tInput you choice:")
	scanf("%d",&ch);
}
void add_friends(){//tian jia hao you

	msg_t msgs ;	
	
	memset(&msgs, 0, sizeof(msg_t));

	while(1){
		system("clear");
		printf("\n\t\tInput user you want to account('e'or'E' to return) :");
		
		scanf("%[^\n]",msgs.nameto);

		while('\n'!=getchar());
		
		if(strlen(msgs.nameto) < 8){
			printf("\n\t\tinvalid account num,try again\n");
			
			continue ;
	
		}
		msgs.r_a = 0 ;
		msgs.isagree = 0 ;
		msgs.user.socket = conn_fd ;

		msgs.cmd = A_F ;
		
		
		strcpy(msgs.msg , "request to add you as his friend ,are you agree ?\n") ;
		
		if(send(conn_fd , &msgs , sizeof(msg_t) , 0) < 0){
		
			strcpy(msgs.msg,"\n\t\tsend error \n");
		
		}
	
	}
}
void do_cmd(int cmd){//zhi xing ge zhong ming ling
	

	msg_t msgs ;
	memset(&msgs , 0 , sizeof(msg_t));
	switch(cmd){//wei le kuai dian hui jia xian man zu ji ben xu qiu ji ke

		case A_F:
			add_friends();
			break ;
		case A_G:
			break ;
		case I_F:
			break ;
		case S_L:
			break ;
		case O_F:
			break ;
		case H_M:
			break ;
		case S_F:
			break ;
		case EXIT :
//			exit_p();
			break ;
	
	}
	return  ;

}

void recv_pack(void* arg){//jie shou fu wu qi duan de bao

	msg_t  msgs ;
	int ret ;
	while(1){
		if((ret = recv(conn_fd ,&msgs ,sizeof(msg_t) , 0)) <0){
			
			perror("\n\t\trecv\n");
			return ;
		}

		else{
			switch(msgs.cmd){
		
				case A_F://tian jia hao you
					printf("\n\t\t%s\n",msgs.msg);
					is_agree(msgs);
					printf("\n\t\tPress [Enter] to return......\n");
					break ;
				case A_G:// chuang jian qun liao
					break ;
				case I_F://yao qing hao you 

					break ;
		
				case S_L://si liao
					break ;
				
				case O_F://li xian xiao xi
					break ;

				case H_M://liao tian ji lu
					break ;
				
				case S_F://fa song wen jian
					break ;
				case EXIT ://tui chu 
				/*	msgs.user.socket =conn_fd ;
					msgs.cmd = 12 ;
					if(send(conn_fd ,&msgs ,sizeof(msg_t), 0) < 0 ){
					
						printf("\n\t\tserver not response !\n");
						continue ;
					}*/
					exit(0);
			}
		}
	}
}

void my_err(char * string , int line){//提示错误信息

	printf("%d:",line);
	perror(string);
	exit(1);
}
void * recv_msg(void * conn_fd){//jie shou xiao xi,bing fan jui ti shi xin xi
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
			
		int ret ;
		if((ret =recv(conn_fd ,&users ,sizeof(msg_t) , 0)) < 0){
				
				perror("\n\t\trecv\n");
				return 0 ;
			}
			else if( ret == 0){
				
				printf("\n\t\tserver cut down !\n");
				return 0 ;
			}
	
			if(users.user.isonline == 1){
				return 1 ;
			}
			else{

			

				return 0;
			}

		}
			
	
	
}
int re_account(){//yong hu shen qing zhang hao

	msg_t msg ;
	bzero(&msg, sizeof(msg_t));
	while(1){
	

		printf("\n\t\tInput nickname:");
		
		scanf("%[^\n]",msg.user.nickname);
		
		while('\n'!=getchar());
		
		printf("\n\t\tInput account number:");

		scanf("%[^\n]",msg.user.name);
		while('\n' != getchar()) ;

		printf("\n\t\tInput phone number:");
		
		scanf("%[^\n]",msg.user.phonenum);
		
		while('\n' != getchar());

	
		
		char temp[N] ;
		while(1){
			printf("\n\t\tInput password:");

			scanf("%[^\n]",msg.user.pass);
			while('\n' !=getchar());

			printf("\n\t\tresure your paasword:");
			scanf("%[^\n]",temp);
			
			while('\n' != getchar());
			if(!strcmp(temp , msg.user.pass)){
			
				break ;
			}
			else{
			
				printf("\n\t\ttwice pass is different!try again\n");
				continue ;
			}
		}
		msg.user.socket = conn_fd ;
		msg.cmd = 0 ;
		msg.user.exist = 0 ;
		int n ;
		if((n = send(conn_fd ,&msg ,sizeof(msg_t),0)) < 0){
		
			perror("\n\t\tsend");
			return 0 ;
		}
		
		int ret ;
	if((ret = recv(conn_fd , &msg ,sizeof(msg_t) , 0)) < 0){
			
			printf("\n\t\tret = %d\n ",ret);
			if(ret == 0){
			
				printf("\n\t\tyong hu xia xian!\n");
				return 0;
			}
		
		}
	if(msg.user.exist == 1 ){
		printf("\n\t\tregist an account.press[enter]key to return ...\n");

		while('\n'!=getchar());
		return 1 ;
		
		}
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
			if(!print_log())return 0;
		
		
	//		pthread_t thid1 ;

	///		pthread_create( &thid1 , NULL ,(void*)&recv_pack ,NULL );

	//		pthread_join(&thid1 , NULL);
			while(1){

				if(!main_menu())break ;
			}

		
		}
	
}

int main_menu(){
	
	int ch ;
	do{
		system("clear");
		printf("\n\t\t---------------------------------------------\n");
		printf("\n\t\t\t\t>>>  [2] add friends\n");
		printf("\n\t\t\t\t>>>  [3] add group\n");
		printf("\n\t\t\t\t>>>  [4] invite friends\n");
		printf("\n\t\t\t\t>>>  [8] personal talk\n");
		printf("\n\t\t\t\t>>>  [9] offline msg\n");
		printf("\n\t\t\t\t>>>  [10] histroy msg\n");
		printf("\n\t\t\t\t>>>  [11] send file\n");
		printf("\n\t\t---------------------------------------------\n");
		printf("\n\t\tInput you choice(0 return):");
	
		scanf("%d",&ch);
		while('\n' !=getchar());
		do_cmd(ch);
		
	}while(ch != 0);
	return 0 ;

}

int print_log(){//打印初始登陆

	char choice ;
	
	do{
		system("clear") ;
		printf("\n\t\t-------------------------------------------------\n");
		printf("\n\t\t\t\t>>> [L] user login\n");
		
		printf("\n\t\t\t\t>>> [R] register an accunt\n");
		
		printf("\n\t\t\t\t>>> [Q] quit\n");

		printf("\n\t\t-------------------------------------------------\n");

		printf("\n\t\tInput your choice :");
	
		choice = getchar();
		while('\n' != getchar());

		switch(choice){
			
			case 'l':
			case 'L':
				if(log_in() == 1){
					system("clear");
					printf("\n\t\tlog success!press [enter]key to return .....\n");
					while('\n' != getchar());
					return 1;
				}
			
			
				else  printf("\n\t\tlog failed!press [Enter]to continue.....\n");
				while('\n' != getchar());
				break ;
			case 'R':
			case 'r':
				if(re_account()== 1){
					
					printf("\n\t\tpress[enter]key to log......\n");
					while('\n' !=getchar());
					break ;
				}
				
				while('\n' != getchar());
				break ;
		}
	}while(choice != 'q'&&choice != 'Q');

	return 0 ;
}

