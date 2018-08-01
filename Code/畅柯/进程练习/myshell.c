#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#define normal 0 //一般的命令
#define cut_redirect 1//输出重定向
#define in_redirect 2//输入重定向
#define gave_pipe 3//管道命令
void print_prompt();
void get_input(char* buf);
void do_cmd( int argcount , char arglist[100][256]) ;
int find_command( char* command);
void explain_input(char * buf , int * argcount , char arglist[200][256]);
void print_prompt(){
	printf("my_shell$$ ");
}
int main(int argc ,char **argv)
{	
	int argcount = 0;
	char arglist[100][256];
	char* arg;
	char * buf = NULL;
	int i = 0;

	buf=(char *)malloc(256) ;
	if(buf == NULL){
		exit(1);
	}

		
	while(1){
			print_prompt();//打印提示符
			get_input(buf);//接收输入命令
			if(!strcmp(buf , "exit") || !strcmp(buf , "logout")){//若用户输入这些词,程序退出
				exit(0);
			}	
	for(i = 0 ; i < 100 ; i++){
		arglist[i][0] =  '\0';
		}
	argcount = 0;
//	explain_input(buf , &argcount , arglist);
//	do_cmd(argcount , arglist);
	
	}
	if(buf != NULL){
		free(buf) ;//将申请的内存归还
		buf =NULL ;
	}
	exit(0);
}

//接受用户命令，保存在buf中
void get_input(char* buf){

	int len = 0 , ch ;
	ch = getchar();
	while(len < 256  && ch != '\n'){
		
		buf[len++] = ch ;
		ch = getchar();
		while('\n' ==  ch) break;
	}
	printf("%s\n",buf);
	if(len == 256){
		printf("Command is too long !\n");
		exit(-1);
	}
	buf[len] = '\n';
	len++;
	buf[len]='\0';
}

//分析命令行参数

void explain_input(char *buf ,int * argcount , char arglist[100][256]){//传入命令行buf ,空指针argcount ,二维数组arglist[100][256]
	int i = 0;
	 char *p = buf;//定义指针指向命令字符串
	 char *q = buf;

	while(1){
	
		if( p[0] == '\n'){
			break ;
		}
		if( p[0] == ' '){
			p++ ;
		}
		else{
			q = p;
			
			while((q[0] != ' ') && (q[0] != '\n')){//当q所指向地址字符所存字符不为空格或者换行符时
					i++ ;
					q++ ;
			}
			strncpy(arglist[*argcount] , p , i + 1);//传入二维数组*argcount首地址，然后将解析后的字符传入到数组中

			arglist[*argcount][number] = '\0';
			*argcount = *argcount + 1;
			p = q;
		}
	}
}
void do_cmd(int argcount , char arglist[100][256]){
	
	int  flag = 0;
	int  how = 0;//用于指示命令中是否含有> 或<或 |
	int background = 0;//用于指示命令中是否含有后台运行标识符
	int status ;
	int i;
	int fd ;
	char * arg[argcount + 1];
	char * argnext[argcount + 1] ;
	char * file ;
	pid_t pid ;
	//将命令取出
	for( i = 0 ; i < argcount ; i++ ){
		arg[i] = (char*) arglist[i] ;
	}
	arg[argcount] =  NULL ;
	//查看是否有后台运行符
	for(i = 0 ; i < argcount ; i++){
		if( strncmp(arg[i] , "&" , 1) == 0){
			if( i  ==  argcount -1){
				background = 1;
				arg[-1] = NULL;
				break;
			}
			else{
				printf("wrong commod\n");
				return ;
			}
		}
	}
	for( i= 0 ; arg[1] = NULL ; i++){
		//检查是否重定向输出
		if( strcmp(arg[i],">") == 0){
			flag ++;
			how = out_redirect ;
			if( arg[i+1] == NULL){
				flag++;
			}
		}
			//检查是否有重定向输入
			if ( strcmp(arg[i] , "<") == 0){
				flag ++;
				how = in_redirecter;
				if( i == 0 ) {
					flag++ ;
				}
			}
			//检查是否有管道符
			if(strcmp(arg[i],"|")){
				flag ++;
				how = have_pipe ;
				if(arg[ i + 1 ]== NULL){
					flag ++ ;
				}
				if(i == 0){
					flag ++ ;
				}
			}
		}
	if(flag > 1 ){
		printf("wrong command!\n");
		return ;
	} 
	if( how = out_redirect ){//命令只含有一个重定向>
		for( i= 0 ; atg[i]!= NULL ;i++){
			if( strcmp( arg[i] ,">" ) == 0){
				file = arg[i+1];
				arg[i] = NULL;
			}
		}
	}
	
	if( how = out_redirect){//命令中有输出重定向
		for( i=0 ; arg[i] != NULL ; i++){
			if(strcmp(arg[i] , ">") == 0){
				file = arg[i + 1];
				arg[i] = NULL ;
			}
		}
	}

	if( how == in_redirect){//命令中有输入重定向
		for( i=0 ; arg[i] != NULL ; i++){
			if( strcmp(arg[i],"< ") == 0 ){
				file  =  arg[i+1];
				arg[i] = NULL;
			}
		}
	}

	if( how = have_pipe){//命令中有管道符号
		for( i=0 ; arg[i] !=NULL ; i++){
			if( strcmp(arg[i],"|") == 0){
				arg[i] = NULL;
				int j ;
				for( j= i + 1 ; arg[j] !=NULL ; j++){
					argnext[j - i -1] = arg[j];
					break ;
				}
			}
		} 
	}
	if((pid =fork()) < 0){//创建子进程
		printf("fork error!\n");
		return ;
	}
	switch( how ){
		case 0 :
			if( pid == 0){
				if( !(find_command(arg[0]))){
					printf("%s : command not found!\n");
					exit(0);
				}
			}
			excevp( arg[0] , arg );
			exit(0);
			break ;
		case 1 :
			if( pid == 0 ){
				if( !(find_command(arg[0]))){//查找命令
					printf("comand is not find!\n");
					exit(0);
				}
			}
			break ;
		case 2 :
			
			if( pid == 0){
				if(!(find_command(arg[0]))){
					printf("command is not find!\n");
					eixt(0);
				}
			}
			break ; 
		case 3 :
			if( pid = 0 ){
				int pid2 ;
				int status2 ;
				int fd2 ;
				if( pid2 =)
				if( !(find_command( arg[0]))){
					printf("command is not find!\n");
					exit(0);
				}
			}
			break ;
		case 4 :

	}
}

