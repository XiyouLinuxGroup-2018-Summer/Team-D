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
#include"list.h"
#define N 10000
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
#define F_P  13
#define Msg 14
#define DEL_FRI 15
#define ALL_FRI 16
#define SEND 17

int epfd ;
typedef struct user{

	int exist;
	char nickname[LN] ;
	char name[LN] ;
	char pass[LN];
	char phonenum[LN];
	int isonline ;//是否在线
	int size ;//判断是否被禁言 0禁烟 1不禁
}user_t;

typedef struct cli_fri_group{//zai xain yong hu
	int sock ;

	char h_name[LN] ;//ben ren de ming zi

	char f_name[LN] ;//peng you de ming zi
	
	int f_status ;//peng you de xian shang zhuang tai ;

	char msg[N]; //yu peng you de liao tian ji lu 

	int size ;
	char time[LN]; //zui hou yi ci tong shi jian 

}cli_fri_group;

typedef struct node{//jian li shuan xiang lian biao bao cun yong hu xin xi

	cli_fri_group data ;
	struct node *next ,*prev ;
}cli_node;

cli_node *h;
typedef struct msg{

	user_t user ;
	int islogin ;
	
	int filesize ;
	char filename[LN];
	
	int cmd ;
	int isagree ;
	char msg[N];
	int a_f ;
	char nameto[LN];
	char namefrom[LN];
	int isroot ;
	char time[LN] ;
	
}msg_t;



void init(msg_t *root_user);
int find_pass(msg_t msgs);
pthread_mutex_t mutex ;
void my_err(char * string ,int line);

void sock_init(int *serv_fd);
void client_pro(void* arg) ;
int login( msg_t *msg);
void send_f(msg_t msgs);
void send_file(msg_t msgs);
void print_list(cli_node * h);
void sockaddr_init(struct sockaddr_in* serv_addr);
void setnonblocking(int* sock);
void recvdata(int fd);
void acceptconn(int srvfd);
void get_name(char *name);
void offline_msg(msg_t msgs);
void reg_account(msg_t msgs);
int add_file(msg_t msgs);
int is_exist(char *h_name,const char*pathname);
int log_re(msg_t* msgs);//pan duan yong hu cun bu cun zai
int conn_fd ;
void get_time(char *  str);
void print_log();
void read_file();
void answer_request(msg_t msgs);
void* user_process(void*arg);
int mod_pass(msg_t msgs);
void add_friends(msg_t msgs);
int is_friend(msg_t msgs);
void del_namefile(msg_t msgs ,char * namefrom , char * name_del);
void del_fri(msg_t msgs);
void person_talk(msg_t msgs);
void all_fri(msg_t msg);
void add_userfile(msg_t msgs);
FILE* file_open (char *filename);
msg_t find_info(char *names);
const char* a_u_f = "alluserfile";
void chan_name(char * name2 ,char* name1) ;
void s_file(msg_t msgs);
void s_file(msg_t msgs){

	cli_node * p;
	p = h->next ;
	while(p != h){

		if(!strcmp(p->data.h_name ,msgs.nameto)){
		
			send(p->data.sock ,&msgs ,sizeof(msgs) ,0);
		}
		p = p->next ;
	}
}
void get_time(char * str){
	
	time_t t ;
	t= time(&t);
	strcpy(str , ctime(&t));
}
void chan_name(char *name2 ,char *name1){
	
	char name3[N];
	strcpy(name3 ,name1);
	strcpy(name1,name2);
	strcpy(name2,name3);

}
void all_fri(msg_t msgs){
	char friends[N];

	if(access(msgs.namefrom ,0)){
	
		strcpy(msgs.msg,"你暂时还没加好友,快去加好友吧！\n");
		
		send(conn_fd ,&msgs, sizeof(msgs) ,0);

		return  ;
	}
	FILE *fp ;
	
	fp =fopen(msgs.namefrom,"rb");
	if(fp == NULL){
		printf("\n\t\t这儿错了\n");
		return  ;
	}
	msg_t temp;
	memset(&temp , 0 ,sizeof(temp));
	
	strcpy(msgs.msg , "\n\t\tfriends online:\n\t\t");
	strcpy(friends , "\n\t\tfriends offline:\n\t\t");

	while(1){
	
		if(fread(&temp ,sizeof(temp) ,1 ,fp) < 1){
			break ;
		}
		cli_node *p ;
		p = h->next ;
		int flag = 0 ;
		strcat(temp.user.name,"\n\t\t");
		while(p != h){//遍历在线用户链表
			if(!strcmp(p->data.h_name ,temp.user.name)){
				
				flag = 1;
				strcat(msgs.msg ,temp.user.name);
			}
				p = p->next ;
		}

		if(flag == 0){
			strcat(friends , temp.user.name);
		}

	}
	fclose(fp);

	strcat(msgs.msg ,friends);

	send(conn_fd ,&msgs , sizeof(msgs),0);
	
}
FILE* file_open(char* filename){//新建文件或是向文件中加内容
	
	FILE *fp ;
	if(access(filename ,0)){
		fp = fopen(filename ,"wb");
		if(fp == NULL){
			printf("这儿file_open");
			return NULL ;
		}
	}
	else{
		fp = fopen(filename ,"ab+") ;
		if(fp == NULL){
		
			printf("我一下就找到你了。。。\n");
			return NULL ;
		}
	}
	return fp ;
	
}
void del_fri(msg_t msgs){//zuo dao hao you hu shan

	del_namefile(msgs , msgs.namefrom,msgs.nameto);

	del_namefile(msgs, msgs.nameto, msgs.namefrom) ;
}
void del_namefile(msg_t msgs,char *namefrom, char * name_del){
	char *tempfile= "temp" ;
	if(access(namefrom ,0)){
	
		printf("\n\t\t这破服务器把信息弄丢了!!!!\n");
		return ;
	}
	FILE* fp ;
	fp = fopen(namefrom ,"rb+") ;

	if(fp == NULL){
	
		printf("\n\n数据库打不开\n");
		return ;
	}

	
	FILE* fp1 ;
	fp1 = fopen(tempfile,"wb");
	if(fp1 == NULL){
		
		printf("\n\t\t文件打开失败\n");
		return ;
	}
	msg_t temp ;
	int flag ;
	while(1){
		if(fread(&temp , sizeof(temp), 0 , fp)< 1){
			break ;
		}
		printf("\n====%s====\n",temp.user.name);

		if(!strcmp(temp.user.name , name_del)){
			
			flag = 1 ;
			continue ;
		}
		fwrite(&temp ,sizeof(temp),1,fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove(namefrom);
	rename(tempfile , namefrom);
	if(!strcmp(msgs.nameto , name_del)){
		
		if(flag == 0){
			strcpy(msgs.msg ,"\n\t\t这个人不在你的好友列表中\n");
			printf("\n----%s----\n",msgs.msg);
			send(conn_fd , &msgs , sizeof(msgs) ,0);
			return ;
		}
	
		strcpy(msgs.msg,"\n\t\t这个人已被删除\n");
		send(conn_fd ,&msgs,sizeof(msgs),0);
	}


}

void offline_msg(msg_t msgs){
	
	FILE *fp ;
	pthread_mutex_lock;
	fp =fopen(msgs.nameto,"rb+") ;

	if(fp == NULL){
		printf("\n\t\t服务器出错！\n");
		pthread_mutex_unlock(&mutex);
		return ;
	}
	msg_t temp ;
	while(1){
	
		if(fread(&temp , sizeof(temp), 1, fp) < 1){
			break ;
		}
		if(!strcmp(msgs.namefrom ,temp.user.name)){
			
			strcat(msgs.msg , ":\n\t\t");
			strcat(temp.msg ,msgs.msg);
			fpos_t pos ;
			fgetpos(fp , &pos);
			fseek(fp ,-(int)sizeof(temp), SEEK_CUR);
			fwrite(&temp ,sizeof(temp) , 1,fp);
			pthread_mutex_unlock(&mutex);
			fclose(fp);
			return ;
		}

	}
	printf("\n\t\t出错了吧，死锁住了\n");
}
msg_t find_info(char * names){
	
	FILE* fp ;
	msg_t msgs ,temp;
	memset(&msgs , 0,sizeof(msgs));
	memset(&temp , 0,sizeof(temp));
	if(access(a_u_f , 0)){
	
		printf("怎么可能没有信息find_info\n");
	}
	 fp = fopen(a_u_f , "rb");
	 if(fp == NULL)
	 {
	 
	 	printf("\n\t\t打不开文件!find_info\n");
		
	 }
	 int flag = 0 ;
	 while(1){
	 
	 	if(fread(&msgs ,sizeof(msgs) , 1 ,fp) < 1){
			break ;
		}
		if(!strcmp(msgs.user.name , names)){
			flag = 1 ;
			temp = msgs ;
			fclose(fp);
			return temp ;
		}
	 }
	 
	 if(flag == 0){
	 
	 	printf("这个人的信息丢失了，这服务器写的好烂....+_+\n");
	 }
	 return msgs ;
}

void add_userfile(msg_t msgs){//将互加好友成功的两个人互相保存到私人数据库

	FILE *fp ,*fp1;
	msg_t msg1 ;
	fp = file_open(msgs.nameto) ;
	
	msg1 = find_info(msgs.namefrom);

	fwrite(&msg1 , sizeof(msg_t) , 1 , fp);
	
	fclose(fp) ;
	
	fp1 = file_open(msgs.namefrom);
	
	msg1 = find_info(msgs.nameto);
	
	fwrite(&msg1 ,sizeof(msg_t) , 1,fp);


	fclose(fp1);
	printf("就这破服务器竟然保存成功了...\n");

}
void answer_request(msg_t msgs){

	if(msgs.isagree == 6){
		
		//bao cun zai hao you lie biao  wen jian...
	}
	send(conn_fd ,&msgs , sizeof(msgs), 0);
}
void send_file(msg_t msgs){
	
	
	if(!is_exist(msgs.user.name,a_u_f)){//yong hu cun zai de hua jiu fan hui 0
	
		strcpy(msgs.msg ,"好友列表中不存在这个人\n");
	
		send(conn_fd ,&msgs ,sizeof(msgs), 0);
		return  ;
	}
	
	cli_node* p ;
	
	p = h->next ;
	while(p != h){
		
		if(!strcmp(p->data.h_name ,msgs.nameto){
			pthread_mutex_lock(&mutex);
			p->data.size = msgs.filesize ;
			pthread_mutex_unlock(&mutex);
			send(p->data.sock , &msgs, sizeof(msg_t),0);
			return ;
		}
		p = p->next ;
	}

	strcpy(msgs.msg , "好友不在线，还不能实现离线发文件");
	send(conn_fd , &msgs ,sizeof(msgs) , 0);
	return ;

}
void person_talk(msg_t msgs){
	

	if(is_exist(msgs.nameto,msgs.namefrom)){//服务器先在他的好友列表信息中查看这个人存不存在
	
		strcpy(msgs.msg ,"好友列表中不存在这个人\n");
	
		send(conn_fd ,&msgs ,sizeof(msgs), 0);
		return  ;
	}

	cli_node* p ;
	p = h->next ;
	

	while(p != h ){
	
		if(!strcmp(p->data.h_name ,msgs.nameto)){
			msgs.user.exist = 1 ;
			send(p->data.sock , &msgs ,sizeof(msgs) , 0);
			return ;

		}
		p = p->next ;
	}

	get_time(msgs.time);
	strcat(msgs.msg ,msgs.namefrom);
	strcat(msgs.msg ,"  ");
	strcat(msgs.msg ,msgs.time);
	strcat(msgs.time ,"  ");
	strcat(msgs.msg ,"\n\t\t");
	offline_msg(msgs);//保存离线消息
	
	strcpy(msgs.msg , "\n\t\t好友不在线，消息已发出\n");
	send(conn_fd ,&msgs ,sizeof(msgs) , 0);


}
int find_pass(msg_t msgs){

		mod_pass(msgs)	;
	
}
int mod_pass(msg_t msgs){
	
	
	
	pthread_mutex_lock(&mutex);

	FILE *fp ;
	if(access( a_u_f , 0)){
	
		strcpy(msgs.msg , "\n\t\tno user in server\n");
		send(conn_fd , &msgs ,sizeof(conn_fd) , 0) ;
		pthread_mutex_unlock(&mutex);
		return  0;
	}

	fp = fopen(a_u_f , "rb+") ;
	if(fp == NULL){
		printf("\n\t\tzhe er cuo le !\n");
		return 0;
	}
	msg_t temp ;
	while(1){
		if(fread(&temp , sizeof(msg_t) , 1 , fp) < 1){
			break ;
		}
		if(!strcmp(temp.user.name , msgs.user.name)&& !strcmp(temp.user.phonenum, msgs.user.phonenum)){
			strcpy(temp.user.pass , msgs.user.pass);
			fpos_t pos ;
			fgetpos(fp ,&pos) ;
			
			fseek(fp ,-(int)(sizeof(temp)) ,SEEK_CUR);
			
			fwrite(&temp ,sizeof(temp) , 1, fp);
			fsetpos(fp, &pos);
			fclose(fp);

			strcpy(msgs.msg , "\n\t\treset password succeed!\n");

			send(conn_fd , &msgs ,sizeof(msg_t) , 0) ;
		
			pthread_mutex_unlock(&mutex) ;
			return 1 ;
		}
	}
	printf("\n\t\tuser:\n");
	strcpy(msgs.msg , "\n\t\tno this user!\n");

	send(conn_fd , &msgs ,sizeof(msg_t) , 0) ;

	pthread_mutex_unlock(&mutex);
	return 0;

}

void get_name(char *name){//huo qu xing ming
	
	cli_node * p ;
	p =h->next ;
	while(p!=h){
		
		if(p->data.sock == conn_fd){
			
			strcpy(name , p->data.h_name) ;
			break  ;
		
		}

		p = p->next ;
	}

}

void add_friends(msg_t msgs){

		
		printf("\n\t\tmsgs.namefrom:%s  msgs.nameto:%s\n",msgs.namefrom ,msgs.nameto);
		
		cli_node * p ;
	
		p = h->next ;

		
		while(p != h){	

			printf("\n\t\tmsgs.nameto:%s ,msgs.namefrom:%s\n",msgs.nameto,msgs.namefrom);
			if(!strcmp(msgs.nameto ,p->data.h_name)){//qing qiu fang qing qiu tian jia hao you
				
				if(msgs.isagree == 6){
				
					add_userfile(msgs);
				}
				send(p->data.sock ,&msgs ,sizeof(msgs) , 0 );//jiang tao jie zi fa gei xiang ying yong 		
				break ;

			}
		
			p = p->next ;

		}	
}
int is_friend(msg_t msgs){//pan duan yong hu lie biao zhong you gai ren mei
	
	return 1;
}
int is_exist(char * h_name ,const char *pathname){//pan duan yong hu cun bu cun zai

	FILE * fp ;
	fp = fopen(pathname,"rb");
	if( fp == NULL){
		
		return 1;
	}
	msg_t temp ;
	while(1){
		if(fread(&temp ,sizeof(temp),1,fp )< 1){
		
			break ;
		}
		printf("\n\t\thello:%s",temp.user.name);
		if(!strcmp(temp.user.name , h_name)){
			fclose(fp);
			return 0 ;
		}
	}
	fclose(fp);
	return 1 ;
}
void read_file(){//pan duan yong hu cun bu cun zai

	FILE * fp ;
	fp = fopen(a_u_f,"rb+");
	if(access(a_u_f ,0)){
		return ;
	}
	if( fp == NULL){
		printf("\nwa ta le!\n");
		return  ;
	}
	msg_t temp ;
	while(1){
	
		if(fread(&temp ,sizeof(temp),1,fp )< 1){
		
			break ;
		}
		printf("\n\t\tname:%s pass:%s\n",temp.user.name,temp.user.pass);

	}
	fclose(fp);
	return ;
}
int log_re(msg_t *msgs){
	printf("\n\t\t----------------\n");
	read_file();
	printf("\n\t\t-------------------\n");
	if(access(a_u_f , 0)){
	
		strcpy(msgs->msg ,"\n\t\tfile not exist!\n");

		return 0 ;
	}
	pthread_mutex_lock(&mutex);
	FILE * fp ;
	
	fp = fopen(a_u_f,"rb+");
	if( fp == NULL){
		pthread_mutex_unlock(&mutex);
		return 0 ;
	}
	
	msg_t temp ;
	int flag = 0 ;
	printf("\n\t\t%s %s\n",msgs->user.name ,msgs->user.pass);
	while(1){
		
		if(fread(&temp ,sizeof(temp),1,fp )< 1){
			pthread_mutex_unlock(&mutex);
			break ;
		}
		if(!strcmp(temp.user.name , msgs->user.name)&&!strcmp(temp.user.pass ,msgs->user.pass)){
			strcpy(msgs->user.nickname , temp.user.nickname);
			printf("\n\t\thhhhh\n");
			fpos_t pos ;
			flag = 1 ;
			msgs->user.isonline = 1 ;
			
			msgs->islogin = 1 ;
			temp.user.isonline = 1 ;
		
			
			fgetpos(fp,&pos);
			fseek(fp ,-(int)(sizeof(temp)) ,SEEK_CUR);
			fwrite(&temp ,sizeof(temp) , 1, fp);
			fsetpos(fp, &pos);
			fclose(fp);
			pthread_mutex_unlock(&mutex);

			return 1 ;
		}
	}
	fclose(fp);
	
	pthread_mutex_unlock(&mutex);

	msgs->user.isonline = 0 ;
	strcpy(msgs->msg , "\n\t\tno the user or password error!\n");
//	pthread_mutex_unlock(&mutex);
	return 0 ;
}
int add_file(msg_t msgs){//pan duanzhu ce yong hu cun bu cun zai
	read_file();

	FILE* fp ;
	
	pthread_mutex_lock(&mutex);
	if(access(a_u_f , 0)){
	
		fp = fopen(a_u_f , "wb");
		if(fp == NULL){
			
			printf("\n\t\tCreate file failed.\n");
			pthread_mutex_unlock(&mutex);
			return 0 ;
		}
		printf("\n\t\t%s\n",msgs.user.name);
		fwrite(&msgs , sizeof(msg_t) , 1, fp);

		fclose(fp);
		pthread_mutex_unlock(&mutex);
		return 1 ;

	}//de
	else{
		if(!is_exist(msgs.user.name,a_u_f)){//yong hu cun zai de hua jiu fan hui 0
			
			strcpy(msgs.msg ,"\n\t\tthe account exist!\n");
			pthread_mutex_unlock(&mutex);
			return 0;
		}
	
		fp = fopen(a_u_f ,"a+") ;
		if(fp == NULL){
			printf("\nom\n");
			pthread_mutex_unlock(&mutex);
			return 0;
		}
		printf("hellop\n");
		fwrite(&msgs , sizeof(msgs) ,1 ,fp) ;
		
		fclose(fp);
		pthread_mutex_unlock(&mutex);
		printf("hekll\n");
		return 1 ;
	}
	
}
//socket
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

void reg_account(msg_t msgs){//zhu ce yong hu

	printf("\n\t\t%s\n",msgs.user.name);
	int flag = 0;
	
	if(add_file(msgs)){//yong hu zhu ce cheng gong
		
		msgs.user.exist = 1;
		strcpy(msgs.msg , "\n\t\tregist an account!\n");
		if(send(conn_fd, &msgs, sizeof(msg_t), 0 )< 0){
	
		perror("\n\t\tsend\n");
			}
	}
	else{
	
		msgs.user.exist = 0 ;
		strcpy(msgs.msg , "\n\t\tregist account failed!it maybe you input an exist user info!\n");
		send(conn_fd, &msgs, sizeof(msg_t), 0 );
	}
		
		printf("\n\t\tyong hu zhu ce cheng gong\n");
		
		return ;
		
	
	
}


int login(msg_t* msgs){//deng lu 
	printf("de\n");
//	printf("tao jie zi wen ti:%d\n",msg->user.socket);
	if(log_re(msgs) == 1){
		strcpy(msgs->msg,"\n\t\tlog succeed!\n");
		msgs->user.isonline = 1 ;
		return 1 ;
	}
	else{

		msgs->user.isonline = 0;
		return 0 ;
	}

	
	return 0 ;

}

void print_list(cli_node * h){

	cli_node *p ;
	p = h->next ;
	while(p!=h){
		printf("\n\t\t()%s()\n",p->data.h_name);
		p = p->next ;
	}
	

}
void* user_process(void *arg){//接受到用户消息，用线程指向此函数
	
	int ret ;
	msg_t msg ; 
	pthread_mutex_lock(&mutex);
	
	cli_node *p ;
	
	p = (cli_node *)malloc(sizeof(cli_node)) ;

	p->data.sock = conn_fd ;
	pthread_mutex_unlock(&mutex);
	List_AddTail(h , p);

	pthread_mutex_unlock(&mutex);
	print_list(h);
	
	bzero(&msg , sizeof(msg_t));
	while(1){
	
		ret = recv(conn_fd, &msg, sizeof(msg_t),0);//fu wu qi jie shou xin xi
		


		if(ret == -1){
			
			my_err("\n\t\trecv",__LINE__);

			}
		if(ret == 0){
		

			printf("\n\t\t客户端%d下线\n",conn_fd);

			pthread_mutex_lock(&mutex);//zuo ji lu
			
			cli_node * p ;
			p = h->next ;

			while(p->next !=h){
		
			
				if(p->data.sock == conn_fd){
				
					List_DelNode(p) ;
					break ;
				}
				p = p->next ;
			}

			pthread_mutex_unlock(&mutex);
			pthread_exit(0) ;
	
			}

	
		
		
	
			printf("\n\t\tuser account: %d,gong_neng_qing_qiu_shu:%d\n",conn_fd, msg.cmd);

			switch(msg.cmd){
		
					case 1:
					//
						if(login(&msg) == 1){
							msg.islogin = 1;
							msg.user.isonline = 1 ;
							msg.user.exist = 1 ;
							if(send(conn_fd, &msg ,sizeof(msg),0) < 0){
							
								printf("\n\t\tsend info failed!\n");

								exit(0);
						}
							pthread_mutex_lock(&mutex);//jia  suo bao cun yong hu zhang hao
							cli_node * temp ;
							temp = h ->next ;

							while(temp != h){//yong hu deng lu hou jiang yuong hu ming bao cun zai lian biao zhong
								printf("\n\t\t(%s)\n",temp->data.h_name);
								if(temp ->data.sock == conn_fd){

									printf("\n\t\t****%s***\n",msg.user.name);
								
									strcpy(temp->data.h_name , msg.user.name) ;
									break ;
								}
								temp = temp->next ;
							}
							
						
						pthread_mutex_unlock(&mutex);
						
					}
					else{
						send(conn_fd , &msg , sizeof(msg_t) , 0);

					}
					break ;
				case 13:
					find_pass(msg);
					break;
				case 0:
					reg_account(msg);
				
					break ;
				case 2:
					
					add_friends(msg);

					break ;
				case 11:
					send_file(msg);

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
					person_talk(msg);
					break ;
				case DEL_FRI:
					del_fri(msg);
					break ;
				case Msg:
					answer_request(msg);
					break ;
				case ALL_FRI:
					all_fri(msg);
					break ;
				case SEND:

					send_f(msg);

					break ; 
		}
	}
}

void send_f(msg_t msgs){
	
	cli_node * p ;

	p = h->next ;
	int flag = 
	while(p != h){
		
		if(!strcmp(p->data.h_name ,msgs.nameto)){

			msgs.isagree = 1;

			send(p->data.sock , &msgs ,sizeof(msgs) , 0);
			return  ;
		}

	}

	strcpy(msgs.msg."对方突然掉线，传输文件出错!按1退出...\n");
	send(conn_fd , &msgs , sizeof(msgs) , 0);
	return ;
}
int main(){

	List_Init(h , cli_node);

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
				printf("\n\t\tconnect from client %s,%d\n",str,conn_fd);
				
				ev.data.fd = conn_fd ;
				ev.events = EPOLLIN | EPOLLET ;
				epoll_ctl(epfd , EPOLL_CTL_ADD ,conn_fd, &ev);//加入到事件列表

			}
			
			else if(events[i].events&EPOLLIN){//如果shi已连接事件,从内核读取数据到用户缓冲区
				
				
				if((serv_fd == events[i].data.fd) < 0){
					continue ;
				}
				
				

				pthread_t thid ;
				pthread_create(&thid, NULL, (void*)user_process, NULL);
				pthread_detach(thid);
				//int ret ;
			}
		}
	} 
	List_Free(h ,cli_node)
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
