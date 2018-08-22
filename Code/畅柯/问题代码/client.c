#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<sys/socket.h>
#include<mysql/mysql.h>
#include<errno.h>
#include<time.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include"list.h"
#include<sys/stat.h>
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
#define EXITs 12//xia xian
#define F_P  13
#define Msg   14
#define DEL_FRI 15
#define ALL_FRI 16
#define FILE_MSG 17
#define SEND 18 
void fflushs();
int s_flag = 1;
char name[LN];
int l_j(char * str ,int len);
int main_menu();
int c_q();
typedef struct user{
	
	int exist ;
	char nickname[LN] ;
	char name[LN] ;
	char pass[LN];
	char phonenum[LN];//电话号码
	int isonline ;//是否在线
	int flag ;//判断是否被禁言 0禁烟 1不禁
	
}user_t;

typedef struct cli_fri_group{//hao you lie biao shu ju jie gou

	int sock ;
	int isonline ;//pan duan yong hu shi fou zai xian
	char h_name[LN] ;//ben ren de ming zi

	char f_name[LN] ;//peng you de ming zi
	

	char msg[N]; //yu peng you de liao tian ji lu 
	int size ;

	char time[N]; //zui hou yi ci tong shi jian 
	

}cli_fri_group ;

typedef struct cli_group_node{//lian biao shu ju jie gou lian 
	
	cli_fri_group data ;

	struct cli_fri_node* next ,*prev ;

}cli_node ;
pthread_mutex_t mutex ;
//cli_node * h ;//ji lu zai xian yong hu
//List_Init(h , cli_node) ;

typedef struct msgbox{
	
	char namefrom[LN] ;
	char msg[LN] ;
	int filesize ;

}Box;
Box box ;
int chat = 0;
 
typedef struct msg{
	
	user_t user ;//yong hu xin xi
	int islogin ;//pan fuan yong hu zai xian yu fou
	int filesize ;
	char filename[LN];

	int cmd ;//给服务器下命令的
	int isagree ;//pan duan shi fou tong yi
//	『1.登陆 2.注册 』
	char msg[N] ;//消息内容
	int a_f ;//yan zheng shi fou qing qiu guo 
	char nameto[LN];//发送对象姓名
	char namefrom[LN];//发送人姓名
	int isroot;//是否为群主
	char time[LN];
}msg_t;
//name
char n_y ;
void chan_name(char *name2 ,char *name1);

void personal_talk();
int print_log();
void sock_init(int * conn_fd);
void ny_err(char* string ,int line);
int log_in();
int re_account();
void file_msg();
void do_cmd(int cmd);
int conn_fd ;
void del_fri();
void s(int sig);
void recv_pack(void * arg);
void si_liao(msg_t msgs);
void add_friends();
void is_agree(msg_t msgs);
int find_pass();
void get_time(char * str);
void save_msg(msg_t msgs);
void s_file(msg_t msgs);
int file_size(char * name);

void off_linemsg();
void send_file();

void msg_center() ;
void all_fri();
void sending();	
int S = 2 ;
char f_name[LN];
void sending(){


	msg_t msgs ;
	
	int num ,t;
	int sum = 0 ;
	char pathname[LN] ;
	printf("\n\t\tinput the file you want to send:");
	scanf("%[^\n]",pathname);
	while('\n'!=getchar());
	num = file_size(pathname);
	int fd ;
	fd = open(pathname ,O_RDONLY,0777);
	memset(msgs.msg ,sizeof(msgs.msg ),0);
	
	strcpy(msgs.filename ,pathname);
	strcpy(msgs.nameto , f_name);
	strcpy(msgs.namefrom ,name);
	msgs.cmd = 17 ;
	while(1){
		
		t = read(fd ,msgs.msg , S);
		sum = sum + t ;
		send(conn_fd ,&msgs ,sizeof(msgs),0);
		memset(msgs.msg ,sizeof(msgs.msg ),0);
		if(sum >= num){
			break ;
		}
	}
	close(fd);
	printf("\n\t\t传输完毕!按回车退出....\n");
	while('\n'!=getchar());
}
void msg_center(){//xiao xi zhong xin
	system("clear");
	msg_t msgs ;
	char ch ;
	
	if(strlen(box.namefrom) == 0){

		printf("\n\t\tno request now!\n");
		return ;
	}
	printf("\n\t\t%s %s",box.namefrom , box.msg);
	printf("\n\t\tInput you choice(y/n):");
	ch = getchar();

	while('\n' !=getchar());
	
	strcpy(msgs.namefrom , name) ;
	
	strcpy(msgs.nameto, box.namefrom);

	if(ch == 'n'){
		
		msgs.isagree = 1 ;
	
		printf("\n\t\tyou refuse %s request!!!\n",box.namefrom);

		strcpy(msgs.msg , "\n\t\trefuse your request!\n");
		printf("\n\n你拒绝了这个人的请求...+_+");
	}
	if(ch =='y'){
		msgs.isagree = 6 ;
		strcpy(msgs.msg ,"同意了你的请求，现在你们是好友了！");
		printf("\n\t\t成功添加对方为好友！");
	}
	msgs.cmd = 2 ;
	send(conn_fd , &msgs ,sizeof(msgs) , 0);
	memset(&box, 0 , sizeof(Box));
	printf("按回车返回...\n");
	while('\n' !=getchar());
}

int file_size(char * name){

	int size ;
	struct stat file ;
	stat(name , &file);
		
	size = file.st_size ;
	 
	return size ;
}
void file_msg(){
	msg_t msgs ;
	bzero(&msgs ,0);
	strcpy(msgs.nameto , box.namefrom);
	strcpy(msgs.namefrom ,name);
	char ch ;
	printf("\n\t\t%s %s(y/n)",box.msg);
	
	ch = getchar();
	
	while('\n'!=getchar());
	if(ch == 'n'){
		msgs.isagree = 1 ; 
		strcpy(msgs.msg ,"\n\t\t拒绝了你的请求....+_+, 按1返回...\n");
		send(conn_fd ,&msgs ,sizeof(msg_t),0);
	}
	else{
		msgs.isagree = 6 ;
		msgs.cmd = 11 ;
		strcpy(msgs.msg ,"\n\t\t按18开始传文件.....\n");
		send(conn_fd ,&msgs ,sizeof(msg_t) , 0);
	
	}
	

}
void send_file(){//send file

	char name[LN],filename[LN];
	msg_t msgs ;
	
	strcpy(msgs.namefrom ,name);
	printf("\n\t\tinput send person:");
	
	scanf("%[^\n]" , msgs.nameto) ;
	while('\n' !=getchar());
	
	bzero(&f_name ,0);
	pthread_mutex_lock(&mutex);

	strcpy(f_name ,msgs.nameto);

	pthread_mutex_unlock(&mutex);
	 msgs.filesize = S ;
	

	strcpy(msgs.namefrom , name);

	strcpy(msgs.msg , "request to send file ,are you agree?\n");
	
	msgs.cmd = 11 ;
	msgs.isagree = 0 ;
	
	send(conn_fd ,&msgs , sizeof(msgs) ,0 );	
	
	return ;
}
void all_fri(){

	msg_t msgs ;
	memset(&msgs ,0 ,sizeof(msgs));

	strcpy(msgs.namefrom, name);
	
	msgs.cmd = 16 ;

	send(conn_fd , &msgs ,sizeof(msgs) , 0);
	
}
void off_linemsg(){

	system("clear");
	
	FILE *fp ;
	msg_t msgs ;
	
	if(access(name , 0)){
	
		printf("\n\t\tno off line msg.....+_+....\n");
		return ;
	
	}

	fp =fopen(name , "rb") ;

	if(fp == NULL){
	
		printf("\n\t\t du quxiao xi chu cuo!\n");
		fclose(fp);
		return ;
	}
	cli_node * p ;

	
	while(1){

		if(fread(&msgs , sizeof(msgs), 1, fp) < 1){
			
			break ;
		}

		printf("\n\t\t%s:%s\n",msgs.namefrom , msgs.msg);
	}
	
	while('\n' != getchar());
	fclose(fp);

	return ;

	
	
	
}
void get_time(char * str){
	
	time_t t ;
	t= time(&t);
	strcpy(str , ctime(&t));
}
void s(int sig){

	s_flag = 1 ;
}
void personal_talk(){
		
		s_flag = 1;
		msg_t  msgs ;
		memset(&msgs , 0 ,sizeof(msgs));
		
		system("clear");
		chat = 1 ;

		if(msgs.isagree == 0){//0 ci jiao liu
		
			msgs.isagree = 1 ;
	
			printf("\n\n\t\tInput you the person account you want to talk(press [Enter+ctl+C]to return):\n");
		
			scanf("%[^\n]",msgs.nameto);
			
			while('\n' != getchar()) ;
			system("clear");

		}
		
		while(s_flag){//yi jing jiao liu guo
		
			strcpy(msgs.namefrom,name);
			signal(SIGINT , s);
			printf("\n\t\tInput:");
		
			scanf("%[^\n]",msgs.msg);
	
			while('\n' != getchar());

			msgs.cmd = 8 ;
			
			get_time(msgs.time);

			send(conn_fd ,&msgs, sizeof(msgs) ,0);
			
	}
		chat = 0 ;
		msgs.isagree = 0 ;
		s_flag = 1;
		signal(SIGINT ,SIG_DFL);

}


void save_msg(msg_t msgs){//sha bi cao zuo ,can le......!!!!qiao dai ma qiao cheng shen jing bing.....

	FILE *fp ;
	if(access(msgs.nameto , 0)){
		if((fp = fopen(msgs.nameto ,"wb")) == NULL){
			printf("\n\t\tda bu kai wen jian......+_+\n");
			return ;
		}
		fwrite(&msgs ,sizeof(msgs) ,1, fp);

		fclose(fp);
		return ;
	}

	fp =fopen(msgs.nameto , "a");

	if(fp == NULL){
		printf("\n\t\tda bu kai wen jian ....+_+\n");
		return ;
	}
	
	fwrite(&msgs, sizeof(msgs), 1 , fp);
	fclose(fp);
	return ;
}
	
void si_liao(msg_t  msgs){

	
	if(msgs.isagree == 1){
		
		printf("\n%s:%s\n",msgs.namefrom,msgs.msg);

	}
	
}
void is_agree(msg_t msgs){


	int ch ;
	
	printf("\n\t\t>>> [0]N   >>> [1]Y\n");	

	printf("\n\t\tInput you choice:");

	scanf("%d",&ch);
	while('\n' !=getchar());

	if(ch == 1){
		
		printf("\n\t\tyou are friends,and began to chat....\n");
		
		chan_name(msgs.nameto ,msgs.namefrom);

		strcpy(msgs.msg ,"agree your request!\n\t\t");

		msgs.a_f = 1;

		msgs.isagree = 1 ;

		send(conn_fd ,&msgs, sizeof(msg_t), 0);
	}
	else{
		chan_name(msgs.nameto ,msgs.namefrom) ;
		strcpy(msgs.msg,"\n\t\trefuse your add friends request \n");//jiang ju jue hao you qing qiu fa guo qu
		msgs.isagree = 0 ;
		msgs.a_f = 1 ;
		send(conn_fd ,&msgs ,sizeof(msg_t) , 0) ;
	}
}
void fflushs(){//shu xin huan chong 	qu

	while('\n' !=getchar());

}
int l_j(char * str ,int len){//pan duan zi fu changt du

	return (strlen(str))< len ?0:1 ;
}
int c_q(){

	char ch;
	printf("\n\t\t[C] continue    [q]quit\n") ;
	printf("\n\t\tInput you choice:") ;
	ch =getchar();
	while('\n'  != getchar());
	if(ch == 'c'|| ch =='C'){
		
		return 1 ;
		}
	return 0 ;
}
int find_pass(){

	msg_t msgs ;
	memset(&msgs, 0, sizeof(msg_t));
	char ch ;

	while(1){
		
		system("clear");
		printf("\n\t\tInput your account:") ;
		scanf("%[^\n]" , msgs.user.name) ;
		fflushs();
		if(l_j(msgs.user.name , 8) == 0){
			printf("\n\t\tname is too short! \n");
			if(c_q() == 0)return 0 ;
			continue ;
		}
		printf("\n\t\tInput your phonenum:  ");
		scanf("%[^\n]",msgs.user.phonenum);
		while('\n' != getchar()) ;
		if(!l_j(msgs.user.phonenum , 11)){

			printf("\n\t\tphonenum is error!\n");
			if(c_q() == 0)return 0 ;
			continue ;
		}
		printf("\n\t\treset your password:");

		
		scanf("%[^\n]",msgs.user.pass) ;
		while('\n' !=getchar());
		if(!l_j(msgs.user.pass , 6)){
			
			printf("\n\t\tpassword is too short!\n");
			if (c_q() == 0)return 0;
			continue ;
		}
		break ;
	}
	msgs.cmd = 13 ;
	
	send(conn_fd ,&msgs , sizeof(msgs) ,0);
	return 1 ;

}


void chan_name(char *name2 ,char *name1){
	char names[N];
	strcpy(names ,name1);
	strcpy(name1,name2);
	strcpy(name2,names);
}//name
void add_group(){
/*	
	printf("input you group name:");
	scanf()
*/
}
void add_friends(){//tian jia hao you

		msg_t msgs ;	
	

		memset(&msgs, 0, sizeof(msg_t));

	while(1){

		system("clear");
		
		printf("\n\t\t输入你想要加的人('e'or'E' to return) :");
		
		scanf("%[^\n]",msgs.nameto);

		while('\n'!=getchar());
		
		if(strlen(msgs.nameto) < 8){
			printf("\n\t\t无效用户名\n");

			continue ;
	
		}

		msgs.isagree = 0 ;
		
		msgs.cmd = 2;


		printf("msgs.namefrom:%s\n",name);
		strcpy(msgs.namefrom , name) ;
		printf("\n\t\t%s\n",msgs.namefrom);
	
		strcpy(msgs.msg , "请求加你为好友，你是否同意？\n") ;
		printf("\n\t\t***%s  %s****\n",msgs.namefrom,msgs.nameto);
	
		//while('\n'!=getchar());
		if(send(conn_fd, &msgs, sizeof(msgs), 0) < 0){
		
			strcpy(msgs.msg,"\n\t\tsend error \n");
		//	continue;
		
		}
		
		printf("\n\t\t发送人：%s    发送给：%s\n",msgs.namefrom ,msgs.nameto);
	//	while('\n'!=getchar());
	//	break ;
	}
		
}
void do_cmd(int cmd){//zhi xing ge zhong ming ling
	
	switch(cmd){//wei le kuai dian hui jia xian man zu ji ben xu qiu ji ke

		case A_F:
			add_friends();
	//		system("clear");
			break ;
		case A_G:
			add_group();
			break ;
		case I_F:
			break ;
		case S_L:
			personal_talk();//jin ru liao tian
			break ;
		case O_F:
			off_linemsg();
			while('\n' != getchar());
			break ;
		case H_M:
			break ;
		case S_F:
			send_file();
			break ;
		case EXITs :
			break ;
		case DEL_FRI:
			del_fri();
			break ;
		case Msg:
			msg_center();
			break ;
		case ALL_FRI:
			all_fri();
			break ;
		case FILE_MSG:
			file_msg();
			break ;
		case SEND :
			sending();
			break ;


	
	}
	return  ;

}
void del_fri(){	

	
	msg_t msgs ;


	memset(&msgs , 0 ,sizeof(msgs) );
	strcpy(msgs.namefrom , name);
	char ch ;

	printf("\n\t\t请输入要删除的好友姓名:");
	
	scanf("%[^\n]",&(msgs.nameto));

	
	while('\n'!=getchar());
	msgs.cmd = 15 ;
	printf("\n\t\t你确定删除这个好友!!!!?(y/n)\n");

	ch = getchar();
	while('\n' != getchar());
	if(ch == 'n'){
	
		return ;
	}

	else{
	
		printf("\n\t\t请求已发送,按回车键退出....\n");
		while('\n' != getchar());
		send(conn_fd ,&msgs , sizeof(msgs) , 0);
		
	}
	
}
void recv_pack(void* arg){//jie shou fu wu qi duan de bao

	msg_t  msgs ;
	int fd ;
	int i ;
	int ret ;
	while(1){
		if((ret = recv(conn_fd ,&msgs ,sizeof(msg_t) , 0)) < 0){
			
			perror("\n\t\trecv\n");
			return ;
		}
		
		else{
			switch(msgs.cmd){
		
				case A_F://tian jia hao you
					if(msgs.isagree == 0){
					
					system("clear");
					printf("\n\t\t有验证消息, 按14去消息中心查看....+_+\n");
					
					pthread_mutex_lock(&mutex);
	//memset			
					strcpy(box.namefrom , msgs.namefrom);
					
					strcpy(box.msg ,msgs.msg) ;

					pthread_mutex_unlock(&mutex);
					
							
					}
					else if(msgs.isagree == 1){
						
						system("clear");

						printf("\n\t\t%s %s \n",msgs.namefrom ,msgs.msg);
				

					}
					else{
					
						printf("%s",msgs.msg);

					}
					break ;
				case A_G:// chuang jian qun liao
					break ;
				case I_F://yao qing hao you 
					
					break ;
		
				case S_L://si liao
					if(chat == 0){

						system("clear");
						printf("\n\t\tyou have personal msg +_+ , input you choice :");
						
						while('\n' != getchar());

					 	save_msg(msgs);
					}
					else{
					
						si_liao(msgs);
					}
					break ;
				case DEL_FRI:
					system("clear");
					printf("\n\t\t%s %s",msgs.nameto,msgs.msg);
					
					printf("\n\t\t请按1返回......\n");

					while('\n' != getchar());
					break ;
				case O_F://li xian xiao xi

					break ;

				case H_M://liao tian ji lu
					
					break ;
				
				case S_F://fa song wen jian
					if(msgs.isagree == 0){
					
						pthread_mutex_lock(&mutex);
						
						strcpy(box.namefrom , msgs.namefrom) ;
						
						strcpy(box.msg ,msgs.msg) ;

						pthread_mutex_unlock(&mutex);
						
						printf("\n\t\t%s请求发文件，按17进入验证界面...");
						
					}

					break ;
				case EXITs ://tui chu 
					break ;
				case ALL_FRI:
					system("clear");
					printf("\n\t\t所有好友信息如下所示:\n");
					
					printf("\n\t\t%s\n",msgs.msg);
					
					printf("\n\t\t按1退出......\n");
					
					while('\n'!=getchar());
					break ;
				case FILE_MSG:
				
					i = 0 ;
					fd =open(msgs.filename,O_WRONLY , 0777);
					
					break ;

			}
		}
	}
}

void my_err(char * string , int line){//提示错误信息

	printf("%d:",line);
	perror(string);
	exit(1);
}

int log_in(){//yong hu deng lu
	
	msg_t users ;

	bzero(&users , sizeof(msg_t));
	
	
	while(1){
		int ch ;
		printf("\n\t\tInput account name :");
	
		scanf("%[^\n]",users.user.name);
	
		while('\n'!=getchar()) ;
		if(strlen(users.user.name) < 8){
		
			printf("\n\t\tthe account is to short\n");
			printf("\n\t\t[0]exit ,[1]continue");
			printf("\n\t\tinput you choice:");
			scanf("%d",&ch);
			while('\n' !=getchar());
			if(ch == 0)return 0 ;
			continue ;
		}
		
		printf("\n\t\tInput account password :");
		
		scanf("%[^\n]",users.user.pass);
		
		while('\n'!=getchar());
	
		if(strlen(users.user.pass) < 8){
		
			printf("\n\t\tthe account is to short\n");
			printf("\n\t\t[0]exit ,[1]continue\n");
			printf("\n\t\tinput you choice:");
			scanf("%d",&ch);
			while('\n' !=getchar());
			if(ch == 0)return 0 ;
			continue ;
		}
		break ;
	}
		
		users.cmd = 1;


		if(send(conn_fd , &users ,sizeof(msg_t),0) < 0){
			
			perror("\n\t\tsend\n");
			return  0;
		}
			
			
	return 1 ;
	
}
int re_account(){//yong hu shen qing zhang hao
	
	
	msg_t msg ;
	char ch ;
	bzero(&msg, sizeof(msg_t));
	

	while(1){
			system("clear");
		printf("\n\t\tInput nickname:");
		
		scanf("%[^\n]",msg.user.nickname);
		
		while('\n'!=getchar());
	
			
			printf("\n\t\tInput account number:");

			scanf("%[^\n]",msg.user.name);
			while('\n' != getchar()) ;
	
			if(strlen(msg.user.name) < 8){
		
				printf("\n\t\tuser name is to short\n");
				printf("\n\t\t[0]exit ,[1]continue\n");
				printf("\n\t\tinput you choice:");
				scanf("%d",&ch);
				while('\n' !=getchar());
				if(ch == 0)return 0 ;
				continue ;
		}
		printf("\n\t\tInput phone number:");
		
		scanf("%[^\n]",msg.user.phonenum);
		
		while('\n' != getchar());

		if(strlen(msg.user.phonenum) != 11){
		
			printf("\n\t\tthe pthonenum is to short\n");
			printf("\n\t\t[0]exit ,[1]continue\n");
			printf("\n\t\tinput you choice:");
			scanf("%d",&ch);
			while('\n' !=getchar());
			if(ch == 0)return 0 ;
			continue ;
	
		}
		break ;
		}
		char temp[LN];
		while(1){
			printf("\n\t\tInput password:");

			scanf("%[^\n]",msg.user.pass);
			while('\n' !=getchar());
			if(l_j(msg.user.pass , 8) == 0){
				if(c_q() == 1)continue ;
				else return 0 ;
			}
			printf("\n\t\tresure your pasword:");
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
		msg.cmd = 0 ;
		msg.user.exist = 0 ;
		msg.islogin = 0 ;
		int n ;
		if((n = send(conn_fd ,&msg ,sizeof(msg_t),0)) < 0){
		
			perror("\n\t\tsend");
			return 0 ;
		}
		return 1 ;
}

void sock_init(int * conn_fd){//初始化套接字
		
	*conn_fd = socket(AF_INET , SOCK_STREAM , 0);
	if(*conn_fd < 0){

		my_err("socket",__LINE__ ) ;
	}
}

int main(int argc , char ** argv){

	pthread_mutex_init(&mutex, NULL);

	
	char  choice ;
	char * ip = "127.0.0.1";
	struct sockaddr_in serv_addr ;
	memset(&serv_addr , 0 , sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_INET ;
	
	serv_addr.sin_port = htons(7230);


	inet_aton("127.0.0.1",&serv_addr.sin_addr) ;

	
	sock_init(&conn_fd);
//向服务器发送连接请求
	
	
	if(connect(conn_fd , (struct sockaddr *)&serv_addr , sizeof(struct sockaddr_in)) < 0){
	
			my_err("connect" , __LINE__);
		}
		printf("\n\t\tConnect server succeess!\n");
	
		msg_t msgs ;
		while(1){
				
				int s ;
			
				s = print_log();
	
				if(s == 0){
				
					continue ;	
				}
				
				recv(conn_fd , &msgs , sizeof(msg_t) , 0);
				
				printf("%s",msgs.msg);
				if(s == 3){
				

					printf("\n\t\tpress [enter]to return.....\n");
					
					while('\n' != getchar());
					continue ;

				}
				printf("\n\t\tname:%s status:%d,msg:%s\n",msgs.user.name,msgs.islogin,msgs.msg);
				while('\n'!= getchar());
				if(msgs.islogin == 1){
					
					printf("%s",msgs.msg);
					printf("\n\t\tpress [enter] go to main menu....\n");
					
					while('\n' != getchar());

					break ;
				}
				else{
					
					if(msgs.user.exist == 1 && s == 2){
						
						printf("\n\t\tyou have register an account ,press [enter] to log in....\n");
						
						while('\n' != getchar());
						continue ;
					}
					else if(msgs.user.exist == 0 && s == 2){
						
						printf("%s" , msgs.msg) ;
						printf("\n\t\tpress [enter] to try again ....\n");
						while('\n' !=getchar());
						continue ;
					}
				}
		}
		
		//这儿显示在所有在线好友
		
		strcpy(name , msgs.user.name );
		while(1){

		
			pthread_t thid1 ;

			pthread_create( &thid1 , NULL ,(void*)&recv_pack ,NULL );

			pthread_detach(thid1);
			while(1){

				if(!main_menu())return 0;

			}

		
		}
	pthread_mutex_destroy(&mutex);
}

int main_menu(){
	int ch ;
	do{
		//system("clear");
		printf("\n\t\t---------------------------------------------\n");
		printf("\n\t\t\t\t>>>  [2] 加好友\n");
		printf("\n\t\t\t\t>>>  [3] 创建群\n");
		printf("\n\t\t\t\t>>>  [4] 邀请好友\n");
		printf("\n\t\t\t\t>>>  [8] 私聊\n");
		printf("\n\t\t\t\t>>>  [9] 离线消息\n");
		printf("\n\t\t\t\t>>>  [10] 聊天记录\n");
		printf("\n\t\t\t\t>>>  [11] 发送文件\n");
		printf("\n\t\t\t\t>>>  [14] 消息中心\n");
		printf("\n\t\t\t\t>>>  [15] 删除好友\n");
		printf("\n\t\t\t\t>>>  [16] 查看好友信息\n");
		
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

	printf("\n\t\t-------------------------------------------------\n");
	printf("\n\t\t\t\t>>> [L] user login\n");
		
	printf("\n\t\t\t\t>>> [R] register an accunt\n");

	printf("\n\t\t\t\t>>> [F] find password\n");
		
	printf("\n\t\t\t\t>>> [Q] quit\n");

	printf("\n\t\t-------------------------------------------------\n");

	
	printf("\n\t\tInput your choice :");
	
	choice = getchar();
	while('\n' != getchar());
	
	switch(choice){
		

		case 'l':
		case 'L':

			if(log_in() == 1 ){
			
				printf("\n\t\tsend log request ,wait a moment..\n");
			
				sleep(3);
			}else{
				printf("\n\t\tlog failed ,press [enter] to continue ....\n");
				while('\n' != getchar());
				return 0 ;
			}
			return 1 ;
		case 'R':
		case 'r':
			if(re_account()== 0){
			
				printf("\n\t\tregist failed,press[enter] to return ....\n");

				while('\n' !=getchar());
				
				return  0 ;
			}
			printf("\n\t\tsending regist request ,wait a moment.....\n");
			sleep(3);
			return 2 ;
					
		case 'f':
		case 'F':

			if(find_pass() == 0)return 0 ;
		
			else{
				
				printf("\n\t\tthe request is sending to server...loading....\n");
				sleep(3);
				return 3;
			}
		case 'q':
		case 'Q':
		
			exit(0);
			
		default :
			printf("\n\t\t请认真输入....+_+....按回车反回....\n");

			while('\n' != getchar());
			system("clear");
			printf("\n\t\thhhhhhhh\n");
			return 0 ;
		}
	
}

