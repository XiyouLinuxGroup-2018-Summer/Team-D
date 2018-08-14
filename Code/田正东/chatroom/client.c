#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAX_STR			30
#define MAX_MESSAGE		45

struct sign
{
	int  choice_sign;			//登陆选择
	char usrname[MAX_STR];		//用户名
	char passwd1[MAX_STR];		//登陆密码
	char passwd2[MAX_STR];		//注册密码
	int  result;				//登陆注册包返回结果
};

struct friend_
{
	int  choice_friend;					//进行好友操作选择
	int  friends_status;				//表示好友状态，0离线，1在线
	char friends_name[MAX_STR];			//想要处理的好友姓名
	char friends_message[MAX_MESSAGE];	//要发送的消息
	char date_time[80];					//发送消息的时间
	char log_in_out_message[20];		//上下线提醒
};

struct group
{
	int  choice_group;					//进行群聊
	char group_message[MAX_MESSAGE];	//发送群聊消息
	char group_name[MAX_STR];			//群组名
	char member_name[MAX_STR];			//群成员
	int  group_result;					//进行操作的结果或状态
	char date_time[80];					//发送消息的时间
};

struct file
{
	int  file_flag;
	int  len;
	char file_name[MAX_STR];			//传输的文件名
	char file_data[50];					//一次读200字节的内容
};

struct node_client
{
	int flag;							//标记是用来进行登陆注册或其他操作，1为登陆，2为私聊，3为群聊
	int decision;						//表示是否同意请求，1是，2否
	struct sign		consumer;			//登陆结构体
	struct friend_	my_friend;			//私聊结构体
	struct group	my_group;			//群聊结构体
	struct file		my_file;			//进行文件传输的结构体
};

int  sock_fd_create(void);				//连接套接字创建函数
void work(int sock_fd);					//传入连接套接字进行工作
void _recv(void *socket_fd);			//一直进行内容获取的线程
void sign_in(int sock_fd);				//登陆操作函数
void chat_data(int sock_fd);			//登陆后进行操作的函数
int  chat_status;						//不进入和子/私聊前为0
char *get_time(void);
void change(char *str);
struct node_client recv_user;	//用来判定登陆注册情况，直接退出
void _error(const char *string,int line);

int main(int argc,char **argv){
	int sock_fd;						//创建套接字
	pthread_t	thid;					//创建线程ID
	chat_status = 0;					//表明在消息和子外

	system("clear");
	sock_fd = sock_fd_create();
	if(sock_fd < 0){												//创建用于连接的sock_fd
		printf("\t\t\t\terror\n");
		exit(EXIT_SUCCESS);
	}
	pthread_create(&thid,NULL,(void *)_recv,(void)&sock_fd);		//开线程一直处于recv状态，进行信息的获取
	pthread_detach(thid);											//回收线程消息
	work(sock_fd);													//工作函数
	return 0;
}

void work(int sock_fd){
	//向work函数中传入的已经是进行过连接的套接字，用于实现C/S通信
	sign_in(sock_fd);							//进行登陆注册操作
	if(recv_user.consumer.choice_sign == 2){
		exit(0);
	}
	chat_data(sock_fd);							//登陆后进行操作的函数
}

void error(const char *string,int line){
	printf("\t\t\t\terror line:%d",line);
	perror(string);
	printf("\n");
}

char *get_time(void){
	time_t timenow;
	time(&timenow);
	return ctime(&timenow);
}

void change(char *str){
	int i;
	str[strlen(str)] = '\0';
	for(i = 0; str[i] != '\0'; i++){
		if(str[i] == ' '){
			str[i] = ' ';
		}
	}
}

void _recv(void *socket_fd){
	int sock_fd = *(int *)socket_fd;
	int  ret;								//处理返回值
	char ch;								//判断键位
	int  sp;								//系统调用打开的标识符
	FILE *fp;								//用于buffer的文件指针
	char path[100];							//文件接收
	while(1){
		ret = recv(sock_fd,&recv_user,sizeof(struct node_client),0);		//收包
		//参数解析
		switch(recv_user.flag){
			case 1:
				switch(recv_user.consumer.choice_sign){
					case 1:
						switch(recv_user.consumer.result){
							case 0:
								printf("\t\t\t\t登陆成功\n");
								break;
							case 1:
								printf("\t\t\t\t账号已被登陆\n");
								exit(EXIT_SUCCESS);
								break;
							case 2:
								printf("\t\t\t\t请先注册\n");
								exit(EXIT_SUCCESS);
								break;
							case 3:
								printf("\t\t\t\t密码错误\n");
								exit(EXIT_SUCCESS);
								break;
						}
						break;
					case 2:
						switch(recv_user.consumer.result){
							case 0:
								printf("")
						}
				}
		}
	}
}

























