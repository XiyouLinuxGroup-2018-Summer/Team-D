
一、项目要求：

1. 采用 Client/Server 架构
2. Client A 登陆聊天服务器前,需要注册自己的 ID 和密码
3. 注册成功后,Client A 就可以通过自己的 ID 和密码登陆聊天服务器
4. 多个 Client X 可以同时登陆聊天服务器之后,与其他用户进行通讯聊天
5. Client A 成功登陆后可以查看当前聊天室内其他在线用户 Client x
6. Client A 可以选择发消息给某个特定的 Client X,即”悄悄话”功能
7. Client A 可以选择发消息全部的在线用户,即”群发消息”功能
8. Client A 在退出时需要保存聊天记录

9. Server 端维护一个所有登陆用户的聊天会的记录文件,以便备查

10.可以进行文件传输

二、附加功能：

1. Server 可以内建一个特殊权限的账号 root,即超级管理员，用于管理聊天室
2. Admin 可以将某个 Client X “提出聊天室”
3. Admin 可以将某个 Client X ”设为只能旁听,不能发言，即禁言功能


三、项目所需相关知识点：网络编程（C/S模型的架构），文件I/O编程（将用户信息和聊天记录保存在数据库文件中，文件传输），多进程或多线程编程（一个服务器可以连接多个客户端）


四、项目使用（测试）说明：将client.c, client.c和server.c分别置于不同目录下，编译命令：gcc  client.c  -o  client   -lpthread  -lsqlite3

运行命令：./client     (server.c同样编译运行)*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sqlite3.h>

#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 20
#define PORT  9999
#define TRUE   1
#define FALSE -1

struct Usr
{
	char name[SIZE];
	int socket;
	int flag;//用来判断该用户是否被禁言，没有被禁设为0，被禁设为1
};

struct Msg
{
	struct Usr usr[SIZE];
	char msg[1024];
	char buf[1024];
	char name[SIZE];
	char fromname[SIZE];
	char toname[SIZE];
	char password[SIZE];
	int cmd;
	int filesize;
	int flag;    //用来判断用户权限   0代表普通用户，1代表超级用户
};

struct Usr usr[SIZE];
int count;

pthread_mutex_t mutex; //互斥锁，用来避免两个客户端同时访问全局变量

//查看在线用户
void see_online(int client_socket, struct Msg *msg)
{
	int i;
	for(i=0; i<20; i++)
	{
		msg->usr[i] = usr[i];
	}

	write(client_socket, msg, sizeof(struct Msg));
}

//保存一条聊天记录
void insert_record(struct Msg *msg)
{
	sqlite3 * database;
	int ret = sqlite3_open("allrecord.db", &database);
	if (ret != SQLITE_OK)
	{
		printf ("打开数据库失败\n");
		return ;
	}

	//获取系统当前时间
	time_t timep;
    char s[30];
    time(&timep);
    strcpy(s,ctime(&timep));
	int count = strlen(s);
	s[count-1] = '\0';

	char *errmsg = NULL;
	char *sql = "create table if not exists allrecord(time TEXT,fromname TEXT,toname TEXT,word TEXT)";
	ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("聊天记录表创建失败：%s\n", errmsg);
		return;
	}

	char buf[100];
	sprintf(buf, "insert into allrecord values('%s','%s','%s','%s')",s,msg->fromname, msg->toname,msg->msg);
	ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("添加聊天记录失败：%s\n", errmsg);
		return ;
	}

	sqlite3_close(database);
	return ;
}

//群聊
void chat_group(int client_socket, struct Msg *msg)
{
	int i = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (usr[i].socket != 0 && strcmp(msg->fromname, usr[i].name) == 0)
		{
			break;
		}
	}
	if(usr[i].flag == 0)     //判断该用户有没有被禁言
	{
		printf ("%s 发一次群消息\n", msg->fromname);
		insert_record(msg);

		for (i = 0; i < SIZE; i++)
		{
			if (usr[i].socket != 0 && strcmp(msg->fromname, usr[i].name) != 0)
			{
				write (usr[i].socket, msg, sizeof(struct Msg));
			}
		}
	}
	else
	{
		msg->cmd = 1003;
		write (client_socket, msg, sizeof(struct Msg));
	}

}

//私聊
void chat_private(int client_socket, struct Msg *msg)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (usr[i].socket != 0 && strcmp(msg->fromname, usr[i].name) == 0)
		{
			break;
		}
	}
	if(usr[i].flag == 0)
	{
		printf("%s给%s发了一条消息\n", msg->fromname, msg->toname);
		insert_record(msg);

		for (i = 0; i < SIZE; i++)
		{
			if (usr[i].socket != 0 && strcmp(usr[i].name, msg->toname)==0)
			{
				write (usr[i].socket, msg, sizeof(struct Msg));
				break;
			}
		}
	}
	else
	{
		msg->cmd = 1003;
		write (client_socket, msg, sizeof(struct Msg));
	}
}

//获取文件大小
int file_size(char* filename)
{
    struct stat statbuf;
    stat(filename,&statbuf);
    int size=statbuf.st_size;

    return size;
}

//上传文件
void send_file(int client_socket, struct Msg *msg)
{
	printf("用户%s在聊天室内上传了一个文件%s\n",msg->fromname,msg->msg);

	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (usr[i].socket != 0 && strcmp(usr[i].name, msg->fromname) != 0)
		{
			write (usr[i].socket, msg, sizeof(struct Msg));
			break;
		}
	}

	int fd = open(msg->msg, O_RDWR | O_CREAT, 0777);
	if(fd == -1)
	{
		perror("open");
		printf("文件传输失败\n");
	}

	int size = msg->filesize;
	char buf[65535];
	memset(buf, 0, 65535);

	int ret = read(client_socket, buf, size);
	if(ret == -1)
	{
		perror("read");
		return;
	}
	write(fd, buf, ret);
	close(fd);
}

//从用户数据库删除一个用户
void del_fromsql(struct Msg *msg)
{
	sqlite3 * database;
	int ret = sqlite3_open("usr.db", &database);
	if (ret != SQLITE_OK)
	{
		printf ("打开数据库失败\n");
		return;
	}

	char *errmsg = NULL;
	char buf[100];
	sprintf(buf, "delete from usr where name = '%s'", msg->name);
	ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("删除用户失败：%s\n", errmsg);
		return;
	}

	sqlite3_close(database);
	return;
}

//注销用户
void logout(int client_socket,struct Msg *msg)
{
	int i,j;
	for(i=0; i<count; i++)
	{
		if(strcmp(msg->name, usr[i].name) == 0)
			break;
	}
	for(j=i; j<count; j++)
	{
		usr[j] = usr[j+1];
	}
	count--;
	printf("正在注销用户%s\n",msg->name);
	del_fromsql(msg);

	write(client_socket, msg, sizeof(struct Msg));
	return;

}

//用户下线
void off_line(int client_socket,struct Msg *msg)
{
	pthread_mutex_lock(&mutex);    // 抢锁

	printf("用户%s下线\n",msg->name);
	int i,j;
	for(i=0; i<count; i++)
	{
		if(strcmp(msg->name, usr[i].name) == 0)
			break;
	}
	for(j=i; j<count; j++)
	{
		usr[j] = usr[j+1];
	}
	count--;

	pthread_mutex_unlock(&mutex);  // 解锁
	write(client_socket, msg, sizeof(struct Msg));

	return;
}

//用户下载文件
void download_file(int client_socket,struct Msg *msg)
{
	printf("用户%s下载了文件%s\n", msg->name, msg->msg);
	int size = file_size(msg->msg);
	msg->filesize = size;
	write(client_socket, msg, sizeof(struct Msg));

	usleep(100000);

	int fd = open(msg->msg, O_RDONLY, 0777);
	if(fd == -1)
	{
		perror("open");
		printf("文件下载失败\n");
	}

	char buf[65535];
	memset(buf, 0, 65535);

	int ret = read(fd, buf, size);
	if(ret == -1)
	{
		perror("read");
		return;
	}

	write(client_socket, buf, ret);
	close(fd);
}

//设置禁言
void forbid_speak(int client_socket,struct Msg *msg)
{
	msg->cmd = 1003;
	printf("用户%s已被禁言\n",msg->msg);

	pthread_mutex_lock(&mutex);
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (usr[i].socket != 0 && strcmp(usr[i].name, msg->msg)==0)
		{
			write (usr[i].socket, msg, sizeof(struct Msg));
			usr[i].flag = 1;
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
}

//解除禁言
void relieve_speak(int client_socket,struct Msg *msg)
{
	msg->cmd = 1004;
	printf("用户%s已被解除禁言\n",msg->msg);

	pthread_mutex_lock(&mutex);
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (usr[i].socket != 0 && strcmp(usr[i].name, msg->msg)==0)
		{
			write (usr[i].socket, msg, sizeof(struct Msg));
			usr[i].flag = 0;
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
}

//踢出聊天室
void kickout_room(int client_socket,struct Msg *msg)
{
	msg->cmd = 1005;
	printf("用户%s已被踢出聊天室\n",msg->msg);

	pthread_mutex_lock(&mutex);
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (usr[i].socket != 0 && strcmp(usr[i].name, msg->msg) != 0)
		{
			//给在线用户通知某某某被踢出聊天室
			write (usr[i].socket, msg, sizeof(struct Msg));
		}
	}
	pthread_mutex_unlock(&mutex);

	for (i = 0; i < SIZE; i++)
	{
		if (usr[i].socket != 0 && strcmp(usr[i].name, msg->msg) == 0)
		{
			break;
		}
	}
	msg->cmd = 1006;
	//strcpy(msg->name,msg->msg);
	//off_line(usr[i].socket,msg);
	write (usr[i].socket, msg, sizeof(struct Msg));
}

//超级用户
void surperusr(int client_socket)
{
	struct Msg msg;

	while(1)
	{
		int ret = read(client_socket, &msg, sizeof(msg));
		if (ret == -1)
		{
			perror ("read");
			break;
		}
		if (ret == 0)
		{
			printf ("客户端退出\n");
			break;
		}

		switch (msg.cmd)
		{
			case 1:
				see_online(client_socket, &msg);
				break;
			case 2:
				chat_group(client_socket, &msg);
				break;
			case 3:
				chat_private(client_socket, &msg);
				break;
			case 6:
				forbid_speak(client_socket, &msg);  // 设置禁言
				break;
			case 7:
				relieve_speak(client_socket,&msg);  // 解除禁言
				break;
			case 8:
				off_line(client_socket,&msg);
				return;
			case 9:
				kickout_room(client_socket,&msg);   // 踢出聊天室
				break;

		}
	}
}

//普通用户
void commonusr(int client_socket)
{
	struct Msg msg;

	while(1)
	{
		int ret = read(client_socket, &msg, sizeof(msg));
		if (ret == -1)
		{
			perror ("read");
			break;
		}
		if (ret == 0)
		{
			printf ("客户端退出\n");
			break;
		}

		switch (msg.cmd)
		{
			case 1:
				see_online(client_socket, &msg);
				break;
			case 2:
				chat_group(client_socket, &msg);
				break;
			case 3:
				chat_private(client_socket, &msg);
				break;
			case 6:
				send_file(client_socket, &msg);
				break;
			case 7:
				logout(client_socket,&msg);
				return;
			case 8:
				off_line(client_socket,&msg);
				return;
			case 9:
				download_file(client_socket,&msg);
				break;
		}
	}

}

//添加到在线用户列表
void add_usr(struct Msg *msg, int client_socket)
{
	pthread_mutex_lock(&mutex);    // 抢锁

	strcpy(usr[count].name, msg->name);
	usr[count].socket = client_socket;
	count++;

	pthread_mutex_unlock(&mutex);  // 解锁
}

// 注册
void reg(int client_socket, struct Msg *msg)
{
	//查找用户是否已经被注册
	printf("正在查找该用户是否被注册...\n");
	if(find_name(msg) == TRUE)
	{
		printf("用户%s已经被注册\n",msg->name);
		msg->cmd = 0;
	}
	else
	{
		if(insert_sql(msg) == TRUE)
		{
			msg->cmd = 1;
			printf("用户%s成功添加到数据库\n",msg->name);
		}
	}
	write(client_socket, msg, sizeof(struct Msg));
}

// 登陆
void login(int client_socket, struct Msg *msg)
{
	int flag1 = 0; //用来判断该用户有没有成功登陆  1代表成功
	//检查该用户有没有注册
	printf("正在查找该用户有没有注册...\n");
	if(find_name(msg) == TRUE)
	{
		if(find_np(msg) == TRUE)
		{
			if(check_ifonline(msg) == TRUE)
			{
				msg->cmd = 3;
				printf("用户%s已经登陆过了\n",msg->name);
			}
			else
			{
				msg->cmd = 0;

				printf("检查该用户权限\n");
				if(check_root(msg) == TRUE)
				{
					printf("该用户是超级用户\n");
					msg->flag = 1;
				}
				else
				{
					printf("该用户是普通用户\n");
					msg->flag = 0;
				}
				printf("用户%s登陆成功\n",msg->name);
				flag1 = 1;

				add_usr(msg, client_socket);    //添加到在线用户列表

			}
		}
		else
		{
			msg->cmd = 1;
			printf("用户%s密码输入错误\n",msg->name);
		}
	}
	else
	{
		msg->cmd = 2;
		printf("用户%s还没有注册\n",msg->name);
	}

	write(client_socket, msg, sizeof(struct Msg));

	if(flag1 == 1)
	{
		if(msg->flag == 1)
			surperusr(client_socket);
		if(msg->flag == 0)
			commonusr(client_socket);
	}
}


//查看用户权限
int check_root(struct Msg *msg)
{
	if(strcmp(msg->name, "root") == 0)
		return TRUE;
	else
		return FALSE;
}


void* hanld_client(void* v)
{
	struct Msg msg;
	int client_socket = (int)v;

	while(1)
	{
		// 从客户端读一个结构体数据
		int ret = read(client_socket, &msg, sizeof(msg));
		if (ret == -1)
		{
			perror ("read");
			break;
		}
		// 代表客户端退出
		if (ret == 0)
		{
			printf ("客户端退出\n");
			break;
		}

		printf("从客户端读到一个用户：%s, %s, %d\n", msg.name, msg.password, msg.cmd);

		switch (msg.cmd)
		{
			case 1:
				reg(client_socket, &msg);
				break;
			case 2:
				login(client_socket, &msg);
				break;
		}
	}
	close (client_socket);
}

//检查该用户是否在线
int check_ifonline(struct Msg *msg)
{
	int i;
	for(i=0; i<count; i++)
	{
		if(strcmp(msg->name, usr[i].name) == 0)
			return TRUE;
	}
	if(i == count)
		return FALSE;
}

//查找用户名
int find_name(struct Msg *msg)
{
	sqlite3 * database;
	int ret = sqlite3_open("usr.db", &database);
	if (ret != SQLITE_OK)
	{
		printf ("打开数据库失败\n");
		return FALSE;
	}

	char *errmsg = NULL;
	char **resultp = NULL;
	int nrow, ncolumn;
	char *sql = "select name from usr";
	ret = sqlite3_get_table(database, sql, &resultp, &nrow, &ncolumn, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("用户查找失败：%s\n", errmsg);
		return FALSE;
	}

	int i;
	for(i=0; i<nrow+1; i++)
	{
		if(strcmp(resultp[i], msg->name) == 0)
			return TRUE;
	}
	return FALSE;
}

//查找用户名和密码
int find_np(struct Msg *msg)
{
	sqlite3 * database;
	int ret = sqlite3_open("usr.db", &database);
	if (ret != SQLITE_OK)
	{
		printf ("打开数据库失败\n");
		return FALSE;
	}

	char *errmsg = NULL;
	char **resultp = NULL;
	int nrow, ncolumn;
	char *sql = "select * from usr";
	ret = sqlite3_get_table(database, sql, &resultp, &nrow, &ncolumn, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("用户查找失败：%s\n", errmsg);
		return FALSE;
	}

	int i;
	for(i=0; i<(nrow+1)*ncolumn; i++)
	{
		if(strcmp(resultp[i], msg->name) == 0 &&
		strcmp(resultp[i+1], msg->password) == 0)
			return TRUE;
	}
	return FALSE;
}

//添加用户到数据库
int insert_sql(struct Msg *msg)
{
	sqlite3 * database;
	int ret = sqlite3_open("usr.db", &database);
	if (ret != SQLITE_OK)
	{
		printf ("打开数据库失败\n");
		return FALSE;
	}

	char *errmsg = NULL;
	char buf[100];
	sprintf(buf, "insert into usr values('%s','%s')", msg->name, msg->password);
	ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("添加用户失败：%s\n", errmsg);
		return FALSE;
	}

	sqlite3_close(database);
	return TRUE;
}

//建立所有用户的聊天记录数据库
void setup_record()
{
	sqlite3 * database;

	int ret = sqlite3_open("allrecord.db", &database);
	if (ret != SQLITE_OK)
	{
		printf ("打开数据库失败\n");
		return;
	}

	char *errmsg = NULL;
	char *sql = "create table if not exists allrecord(time TEXT,fromname TEXT,toname TEXT,word TEXT)";
	ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("聊天记录表创建失败：%s\n", errmsg);
		return;
	}

	sqlite3_close(database);
	return;
}

//建立用户数据库，并在里面添加超级用户
int setup_sql()
{
	sqlite3 * database;

	int ret = sqlite3_open("usr.db", &database);
	if (ret != SQLITE_OK)
	{
		printf ("打开数据库失败\n");
		return FALSE;
	}

	char *errmsg = NULL;
	char *sql = "create table if not exists usr(name TEXT,password TEXT)";
	ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf ("用户表创建失败：%s\n", errmsg);
		return FALSE;
	}

	struct Msg msg;
	strcpy(msg.name, "root");
	strcpy(msg.password, "123");

	insert_sql(&msg);

	sqlite3_close(database);
	return TRUE;
}

// 初始化套接字，返回监听套接字
int init_socket()
{
	//1、创建socket
	int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket == -1)
	{
		perror ("socket");
		return -1;
	}

	// 2、命名套接字，绑定本地的ip地址和端口
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family  = AF_INET;     // 设置地址族
	addr.sin_port    = htons(PORT); // 设置本地端口
	addr.sin_addr.s_addr = htonl(INADDR_ANY);   // 使用本地的任意IP地址

	int  ret = bind(listen_socket,  (struct sockaddr *)&addr, sizeof(addr));
	if (ret == -1)
	{
		perror ("bind");
		return -1;
	}

	// 3、监听本地套接字
	ret = listen(listen_socket, 5);
	if (ret == -1)
	{
		perror ("listen");
		return -1;
	}

	printf ("等待客户端连接.......\n");
	return listen_socket;
}

// 处理客户端连接，返回与连接上的客户端通信的套接字
int  MyAccept(int listen_socket)
{
	struct sockaddr_in client_addr;
	int len = sizeof(client_addr);
	int client_socket = accept(listen_socket, (struct sockaddr *)&client_addr,  &len);
	if (client_socket == -1)
	{
		perror ("accept");
		return -1;
	}

	printf ("\n\t\t成功接收一个客户端: %s\n", inet_ntoa(client_addr.sin_addr));

	return client_socket;
}

int main()
{
	setup_sql();
	setup_record();

	pthread_mutex_init(&mutex, NULL);

	int listen_socket = init_socket();

	while (1)
	{
		// 获取与客户端连接的套接字
		int client_socket = MyAccept(listen_socket);

		// 创建一个线程去处理客户端的请求，主线程依然负责监听
		pthread_t id;
		pthread_create(&id, NULL, hanld_client,  (void *)client_socket);
		pthread_detach(id);
	}

	close (listen_socket);

	pthread_mutex_destroy(&mutex);
	return 0;
}
