#include<sys/epoll.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<mysql/mysql.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<stdlib.h>
#include<fcntl.h>

#define N 1000
#define LN 50
#define LOG_SUCCESS 1
#define PORT 7230
#define ONLINE 1
#define LISTENQ 50
#define OFF_LINE 0
#define NOT_ROOT 2
#define ROOT 3
#define BUFSIZE 20

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
#define EXIT 12 //tui chu,yong hu xia xian
int epfd ;

typedef struct user{

	int exist;
	int socket ;
	char nickname[LN] ;
	char name[LN] ;
	char pass[LN];
	char phonenum[LN];
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
	
	int cmd ;
	int isagree ;
	char msg[N];
	int r_a ;
	char nameto[LN];
	char namefrom[LN];
	int isroot ;
	char time[LN] ;
	
}msg_t;



void init(msg_t *root_user);

pthread_mutex_t mutex ;
void my_err(char * string ,int line);

void sock_init();
void client_pro(void* arg) ;
int login( msg_t *msg);
void sockaddr_init(struct sockaddr_in* serv_addr);
void setnonblocking(int* sock);
void recvdata(int fd);
void acceptconn(int srvfd);
void reg_account(msg_t msgs);
int add_file(msg_t msgs);
int is_exist(msg_t msgs);
int log_re(msg_t* msgs);//pan duan yong hu cun bu cun zai
int conn_fd ;
void print_log();
void read_file();
void mod_info(msg_t msgs);
void add_friend(msg_t msgs);
int is_friend(msg_t msgs);
const char* a_u_f = "alluserfile.txt";
//yong hu ming ming ming de wen jian shi ta men de si you xin xi wen jian
void add_friend(msg_t  msgs){

	if(msg.a_r == 0){

	FILE *fp ;
	if((fp = fopen(a_u_f , "rb+")) == NULL){
	
		strcpy(msgs.msg , "\n\t\tserver can't find client data\n");
		send(conn_fd ,&msgs , sizeof(msgs) ,0);

		return ;
	}
	
	else{
		msg_t temp ;
	
		int flag = 0 ;
		while(1){
		
			if(fread(&temp , sizeof(msg_t) , 1,fp)< 1){

				break ;		
			}
			else{
			
				if(!strcmp(msgs.nameto ,temp.name)){//dang ke hu qing qiu tian jia hao you de ren de zhang hao he wen jian zhong yi zhi shi
					
					flag =  1;
					if(is_friend( msgs) == 1){//ru jia de hao you yi zai lie biao
					
						strcpy(msgs.msg ,"\n\t\the friend has existed!\n");
					}
					
					if(send(temp.user.socket , &msg , sizeof(temp) , 0) < 0){
					
						printf("\n\t\twan dan...beng le...\n");
						return  ;
					}
				}
				
			}
		}
		if(flag == 0){//ru guo yong hu bu cun zai ze ti shi xin xi
		
			strcpy(msgs.msg ,"\n\t\tthe account not exist\n");
			if(send(temp.user.socket , &msg , sizeof(temp) , 0) < 0){
					
						printf("\n\t\twan dan...beng qiu...\n");
						return  ;
					}
				}
			}
	}
	else{//yan zheng guo de hua 
		
		
	}
}
int is_friend(msg_t msgs){//pan duan yong hu lie biao zhong you gai ren mei
	
	FILE * fp ;
	if(access(msgs.user.name ,0)){//yong yong hu ming ming ming wen jian 
	
		return 0 ;
	}
	else{
	
		fp = fopen(msgs.users.name , "rb");
		if(fp == NULL){
			prinf("\n\t\twa ta lie!\n")
			return  0 ;
		}
		msg_t temp ;

		while(1){
			
			if(fread(&temp ,sizeof(temp) , 1 , fp) < 1){
				
				break ;
			}
			if(!strcmp(temp.user.name , msg.nameto)){
			
				fclose(fp) ;
				return 1 ;
			}
		}
	
	}
	fclose(fp) ;

}
int is_exist(msg_t msgs){//pan duan yong hu cun bu cun zai

	FILE * fp ;
	fp = fopen(a_u_f,"rb+");
	if( fp == NULL){
		
		return 1;
	}
	msg_t temp ;
	while(1){
	
		if(fread(&temp ,sizeof(temp),1,fp )< 1){
		
			break ;
		}
		if(!strcmp(temp.user.name , msgs.user.name)){
			
			return 0 ;
		}
	}
	return 1 ;
}
void read_file(){//pan duan yong hu cun bu cun zai

	FILE * fp ;
	fp = fopen(a_u_f,"rb+");
	if( fp == NULL){
		
		return  ;
	}
	msg_t temp ;
	while(1){
	
		if(fread(&temp ,sizeof(temp),1,fp )< 1){
		
			break ;
		}

	}
	fclose(fp);
	return ;
}
int log_re(msg_t *msgs){//pan duan yong hu cun bu cun zai

	pthread_mutex_lock(&mutex);
	FILE * fp ;

	fp = fopen(a_u_f,"rb+");
	if( fp == NULL){
		
		return 0 ;
	}
	
	msg_t temp ;
	int flag = 0 ;
	while(1){
		
		if(fread(&temp ,sizeof(temp),1,fp )< 1){
			break ;
		}

		if(!strcmp(temp.user.name , msgs->user.name)&&!strcmp(temp.user.pass ,msgs->user.pass)){
			fpos_t pos ;
			flag = 1 ;
			msgs->user.isonline = 1 ;
			temp.user.isonline = 1 ;
			
			fgetpos(fp,&pos);
			fseek(fp ,-(int)(sizeof(temp)) ,SEEK_CUR);
			fwrite(&temp ,sizeof(temp) , 1, fp);
			fsetpos(fp, &pos);
			fclose(fp);
			return 1 ;
		}
	}
	fclose(fp);
	
	pthread_mutex_unlock(&mutex);

	msgs->user.isonline = 0 ;
	return 0 ;
}
int add_file(msg_t msgs){//pan duanzhu ce yong hu cun bu cun zai
	
	FILE* fp ;
	
	pthread_mutex_lock(&mutex);
	if(access(a_u_f , 0)){
	
		fp = fopen(a_u_f , "wb");
		if(fp == NULL){
			
			printf("\n\t\tCreate file failed.\n");
			return 0 ;
		}
		
		fwrite(&msgs , sizeof(msg_t) , 1, fp);

		fclose(fp);
		return 1 ;

	}
	else{
		if(!is_exist(msgs)){//yong hu cun zai de hua jiu fan hui 0
			
			printf("\n\t\tname_is_exist:%s\n",msgs.user.name);
			
			return 0;
		}
	
		fp = fopen(a_u_f ,"a+") ;
		if(fp == NULL){
			printf("\nom\n");
		
			return 0;
		}

		fwrite(&msgs , sizeof(msgs) ,1 ,fp) ;
		
		fclose(fp);
		pthread_mutex_unlock(&mutex);
	
		return 1 ;
	}
	
}
void setnonblocking(int *sock){

	int opts ;
	opts =fcntl(*sock , F_GETFL) ;
	if(opts < 0){
	
		perror("\n\t\tfcntl(sock,GETFL)");
		exit(1);
	}
	opts = opts |O_NONBLOCK ;
	if(fcntl(*sock,F_SETFL , opts) < 0){
		
		perror("fcntl(sock,SETFL,opts)");
		exit(0);
	}
}
void init(msg_t *root_user){
	
	strcpy((*root_user).user.name ,"changke");

	strcpy((*root_user).user.pass , "123");
	(*root_user).isroot = ROOT;
}
void reg_account(msg_t msgs){//zhu ce yong hu


	int flag = 0;
	
	if(add_file(msgs)){//yong hu zhu ce cheng gong
		
		msgs.user.exist = 1;
		if(send(conn_fd, &msgs, sizeof(msg_t), 0 )< 0){
	
		perror("\n\t\tsend\n");

	}
		
		printf("\n\t\tyong hu zhu ce cheng gong\n");
		
		return ;
		
	}
	
	else{
		
		msgs.user.exist = 0 ;
			

		if(send(conn_fd, &msgs, sizeof(msg_t), 0 )< 0){
	
			perror("\n\t\tsend\n");

			}
		}
	
}


int login(msg_t* msg){//deng lu 
	if(log_re(msg) == 1){
		
		msg->user.isonline = 1 ;
		return 1 ;
	}

	
	return 0 ;

}

void* user_process(void *arg){//接受到用户消息，用线程指向此函数
	
	


	int ret ;
	msg_t msg ; 

	bzero(&msg , sizeof(msg_t));
	while(1){
	
		ret = recv(conn_fd ,&msg, sizeof(msg_t),0);//fu wu qi jie shou xin xi
		printf("\n\t\tname:%s\n",msg.user.name);

		if(ret == -1){
			
			my_err("\n\t\trecv",__LINE__);

			}
		if(ret == 0){
		
			printf("\n\t\t客户端%d下线\n",conn_fd);
			pthread_exit(0);
	
			}

			printf("\n\t\tServer read a client\n ");
			printf("\n\t\t-------------------------------------------\n");
	
		
		
			switch(msg.cmd){
		
					case 1:
						if(login(&msg) == 1){
						
							msg.user.isonline = 1;
							if(mod_info())
							if(send(conn_fd, &msg ,sizeof(msg_t),0) < 0){
							
								printf("\n\t\tsend info failed!\n");
								exit(0);
						}
						
					}
					else{
					
						send(conn_fd , &msg , sizeof(msg_t) , 0);
						pthread_exit(0);
					}
					break ;
				case 0:
					reg_account(msg);
				
					break ;
				case 2:
					add_friend(msg);
					break ;
				case 3:
					break ;
				case 4:
					break ;
				case 5:
					break ;
				case 6:
					break ;
				case 7:
					break ;
				case 8:
					break ;

		}
	}
}


int main(){

//	connect_mysql();
	pthread_mutex_init(&mutex,NULL);
	
	int serv_fd ;

	socklen_t cli_len ;
	
	sock_init(&serv_fd);
	
	struct sockaddr_in  serv_addr ;
	
	sockaddr_init( &serv_addr);

	if(bind( serv_fd , (struct sockaddr *)&serv_addr , sizeof(struct sockaddr_in)) < 0){
		
		my_err("\n\t\tbind" , __LINE__);
	}	
	printf("\n\t\tbind success!\n");
	
	if( listen(serv_fd , LISTENQ) < 0){
		printf("{}");
		my_err("\n\t\tlisten",__LINE__ );
	}


	
		

	int i = 0;
	
	int epfd ;
	msg_t msg ;
	struct sockaddr_in cli_addr ;
	epfd = epoll_create(200);
	printf("\n\t\tlistening......\n");
	
	struct epoll_event ev , events[BUFSIZE] ;
	
	setnonblocking(&serv_fd) ;//将用于监听的套接子设置为非阻塞方式
	
	ev.data.fd = serv_fd ;
	//向epoll申明事件类型	
	ev.events = EPOLLIN|EPOLLET ;
	//向epoll注册事件
	epoll_ctl(epfd , EPOLL_CTL_ADD ,serv_fd ,&ev) ;
	while(1){
	             
		
        

		int count = epoll_wait(epfd , events , 20 ,1000);

			
		for(i = 0 ; i < count ; i++ ){
		
			if(events[i].data.fd == serv_fd ){
			//监听事件
				conn_fd = accept(serv_fd , (struct sockaddr *)&cli_addr ,&cli_len);
				if(conn_fd < 0){
				
					perror("\n\t\taccept\n");
					exit(1) ;
				}

			

				char *str = inet_ntoa(cli_addr.sin_addr) ;
				printf("\n\t\tconnect from client %s\n",str);
				ev.data.fd = conn_fd ;
				ev.events = EPOLLIN | EPOLLET ;
				epoll_ctl(epfd , EPOLL_CTL_ADD ,conn_fd, &ev);//加入到事件列表

			}
			
			else if(events[i].events&EPOLLIN){//如果时已连接事件,从内核读取数据到用户缓冲区
				
				
				if((serv_fd == events[i].data.fd) < 0){
					continue ;
				}
				
				

				pthread_t thid ;
				pthread_create(&thid , NULL ,(void*)user_process ,NULL);
				int ret ;


			}
		}
	} 
	close(serv_fd) ;
	close(epfd);
	pthread_mutex_destroy(&mutex) ;
	return 0 ;
	
}



void my_err(char * string , int line){//提示错误信息

	printf("%d:",line);
	perror(string);
}



void sock_init(int * serv_fd){//初始化套接字
		
	*serv_fd = socket(AF_INET , SOCK_STREAM , 0);
	if(*serv_fd < 0){

		my_err("\n\t\tsocket",__LINE__ ) ;
	}

	int optval = 1 ;
	 if(setsockopt( *serv_fd , SOL_SOCKET , SO_REUSEADDR , (void *)&optval , sizeof(int)) < 0){
	 
	 	my_err("\n\t\tsetsockopt" , __LINE__);
	 }
}
void sockaddr_init(struct sockaddr_in* serv_addr){//初始化服务器端口结构
		
	memset(serv_addr , 0 , sizeof(struct sockaddr_in));
	(*serv_addr).sin_family = AF_INET ;
	(*serv_addr).sin_port = htons(PORT);
	(*serv_addr).sin_addr.s_addr = htonl(INADDR_ANY) ;

}
