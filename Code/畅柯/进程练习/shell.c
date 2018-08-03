#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<sys/wait.h>
#define N 50
#define normal 0 //一般命令
#define histroy 5
#define out_redirect 1//输出重定向
#define in_redirect  2//输入重定向
#define zhui_jia 4    //往文件后面追加
#define have_pipe   3//命令中有管道
char *histroyfile = "/tmp/histroy";
void printprompt(char * str);  //打印提示信息
void get_input( char *buf , char *str);   //接受信息
void get_userdir(char *path);
void explain_cmd();//解析命令
int find_command(char * command);//查找命令
void devide_dir(char * path);//在shell 中设置，显示当前工作的目录名称
int do_command(char cmdlist[100][256] , int argcount);//执行命令

void get_userdir(char*  path){//获取用户主目录
	
	char buf[N];
	int flag ;
	if(getcwd(buf , N) < 0){
		printf("获取路径失败！\n");
		return ;
	}
	if(!strcmp(buf , "/") || !strcmp(buf ,"/root")||!strcmp(buf ,"/root/home")){
		strcpy(path , buf);
		return ;
	}
	int i = 0;
	flag = 0;
	while(*(buf + i) != '\0'){
		
		if(*(buf +  i ) == '/'){
			flag ++ ;
		}

		if(flag > 2){
	
			*(buf + i + 1) = '\0';
		
			break ;
		}
		i ++ ;
	}
	*(buf + i ) == '\0' ;

	strcpy( path , buf);
}
int main( int argc ,char ** argv ){

	char* buf ;
	char str[N];
	int  argcount = 0 ;
	char cmdlist[100][256];
	buf = (char *)malloc(256) ;
	
	while(1){
		memset( buf , 0 , 256);
		
		printprompt(str);
		
		get_input(buf , str);
		if(*buf == '\0' || *buf == '\n'){

			continue ;

		}
		
		if(!strcmp( buf , "exit\n") || !strcmp( buf , "logout\n")){
			return ;
		}
		argcount = 0 ;
		explain_cmd(buf, &argcount ,cmdlist);
		do_command(cmdlist,argcount);
	}
	
	if(buf != NULL){
		free( buf ) ;
		buf = NULL ;
	}
	
	exit(0);
}
int do_command(char cmdlist[100][256] , int argcount){//执行命令

	int i = 0 ,how = 0 ,num = 0;
	char * file ;
	int background = 0 ;
	int status ;
	int fd ;
	int k =  0 ;
	pid_t pid ;
	char path[N] ;
	FILE *fp ;
	char command[N];
	char* arg[argcount + 1];
	char * argnext[argcount + 1];
	for( i = 0 ; i < argcount ; i++ ){

		arg[i] = ( char* )cmdlist[i];

	}
	arg[argcount] = NULL;
	if(!strcmp( arg[0] , "cd")){//若为cd命令
		DIR * dir ;
		if(arg[1] == NULL){
			get_userdir(path);
			chdir(path);
			return 0;

		}
		if((dir == opendir(arg[1])) < 0){
		
			printf("Directory not found!\n");
			return 0;

		}
		else{
			chdir(arg[1]);
		}
		return 0;
	}

	if(!strcmp(arg[0] , "histroy") && arg[1] == NULL){
				int i = 0;
				fp =fopen(histroyfile , "r");
				if(fp == NULL){
					printf("can't open file!\n");
					return 0;
				}
				while((fscanf(fp , "%s" , command)) != EOF){
					i ++;
					printf("%-15s",command);
					if(i == 6){
						printf("\n");
						i = 0 ;
					}
					
				}
				printf("\n");
				fclose(fp);
				return 0 ;
	}
	for ( i = 0 ; arg[i] != NULL ; i++){
		if(!strncmp(arg[i] ,"&" , 1 )){
			if( i == argcount - 1){//判断&若是最后一个符号，那么就是后台运行
				background = 1;
				arg [ argcount -1 ] = NULL ;
				}
			else {
				printf("wrong command!\n");
				return 0;
			}
		}
	}
	for( i = 0 ; arg[i] != NULL ; i++ ){//是否为输出重定向
	
		if( !strcmp(arg[i] ,">")){
			k++ ;
			
			num ++ ;

			how = out_redirect ;
		}
		if(!strcmp( arg[i] ,"<")){//输入重定向
			num ++;
			how = in_redirect;
		}

		if( !strcmp(arg[i] , ">>")){
			
			num ++ ;
			how = zhui_jia ;
		}

		if( !strcmp( arg[i] ,"|") ){
			how = have_pipe;
			if(arg[i + 1] == NULL){
	
				num ++ ;
				}
				if( i == 0 ) num++ ;
			}
		}

	if( num > 1 ){
		
		printf("wrong command!\n");
		return 0;
		}
	if( how == out_redirect ){//获取输出重定向符号后面的文件名
		for ( i = 0 ; arg[i] != NULL ; i++){//数据流导向
			if( !strcmp(arg[i] ,">")){//替换
				file = arg [i + 1];
				arg[i] = NULL ;
			}

			else if(!strcmp( arg[i],">>")){//追加形式
				file = arg[i + 1] ;
				arg[i] = NULL ;
			}
		}
	}
	if(how == zhui_jia){
		for ( i = 0 ; arg[i] != NULL ; i++){//数据流导向
			if( !strcmp(arg[i] ,">")){//替换
				file = arg [i + 1];
				arg[i] = NULL ;
			}
			else if(!strcmp( arg[i],">>")){//追加形式
				file = arg[i + 1] ;
				arg[i] = NULL ;
			}
		}
	}
	if( how == in_redirect){
		for( i = 0 ; arg[i] != NULL ; i++){
			if(!strcmp(arg[i] , "<")){
				file = arg[i + 1];
				arg[i] = NULL ;
			}
		}
	}
	int j ;
	
	if( how == have_pipe){
		for( i = 0 ; arg[i] != NULL ; i++){
			if( !strcmp( arg[i] , "|")){

				arg[i] = NULL ;
				j = 0;
				for(j = i + 1; arg[j]!=NULL ; j++){
					argnext[j -i -1]=  arg[j];
				}

				argnext[j-i-1]=arg[j];
				break ;
			}
		}
		
	}
	
	if((pid = fork())<0){
		printf("fork error!\n");
		exit(1);
	}
	switch(how){
		case 0 :
			if(pid == 0){
				
				if( find_command(arg[0]) == 0 ){
					printf("command not find!\n");
					exit(0);
				}
				execvp( arg[0] , arg);
				exit(0);
			}
		
			break ;
		case 2 :
			if(pid == 0){
				if( find_command(arg[0]) == 0){
					printf("command is not find !\n");
					exit(0);
				}
				fd = open (file , O_RDONLY);
				dup2(fd , 0);
				
				execvp( arg[0] , arg);
				exit(0);
			}
			break ;
		case 4 :

			if(pid == 0){
				if( find_command(arg[0]) == 0){
					printf("command not find!\n");
					exit(0);
				}
				fd = open( file ,O_RDWR|O_CREAT|O_APPEND , 0642) ;
				dup2(fd , 1);
				execvp(arg[0] , arg);
				exit(0);
			}
			break ;
		case 1 :
			if(pid == 0){
				if(find_command(arg[0]) ==0){
					printf("command is not find!\n");
					exit(0);
				}
				fd = open(file ,O_RDWR|O_CREAT|O_TRUNC ,0642);
				dup2(fd , 1);
				execvp(arg[0] , arg);
				exit(0);
			}
			break;
		case 3 :
			if(pid == 0){
				int pid2 ;
				int status ;
				int fd2 ;

				if((pid2 =fork()) < 0){
					printf("fork2 error!\n");
					return 0;
				}
				else if(pid2 == 0 ){
					if(find_command(arg[0]) == 0){
						printf(" command is not find!\n");
						exit(0);
					}
					fd2 = open("/tmp/jincheng" , O_WRONLY|O_CREAT|O_TRUNC ,0642);
					dup2(fd2 , 1);
					execvp(arg[0] , arg);
					exit(0) ;
				}
				if(waitpid(pid2 , &status , 0) == -1){
						printf("wait for child process error!\n");
					}
				if( !(find_command(argnext[0]))){
					printf("command not find!\n");
					exit(0);
				}
				fd2 = open("/tmp/jincheng" , O_RDONLY);
			 	dup2(fd2,0);
				execvp(argnext[0] , argnext);
				if(remove("/tmp/jincheng")){
					printf("remove error!\n");
				
				}
				exit(0);
			}
			break ;
		default :
			break;
	}
	if(background == 1){

		printf("process id %d",pid);
		return 0;

	}
	if(waitpid(pid , &status, 0) == -1){

		printf("wait for process error!\n");

	}
	return 0;
}
void devide_dir(char * path){//将当前工作目录切换出来
	int i, flag = 0;
	char str[N];
	int j = strlen( path );
	if(!strcmp(path , "/")){
		return ;
		}
	for(i = 0 ;path[i]!='\0'  ;i ++){
		if(*(path + i - 1) == '/'){

			flag = i;
		}
	}
	strcpy( str , path + flag );
	strcpy(path,str);
}
int find_command(char * command ){
	

	DIR * dir ;
	struct dirent * ptr ;
	char * path[] = { "./" ,"/bin","/usr/bin",NULL};
	if(!(strncmp( command, "./",2))){
	
		command = command + 2;
	}
	int i = 0;
	while( path[i] != NULL){
		if((dir = opendir(path[i])) == NULL){
			printf("\nfile not find!\n");
		
		}
		while((ptr = readdir(dir)) != NULL){
			if(!strcmp(ptr->d_name , ".")||!strcmp(ptr->d_name,"..")){
				continue ;
			}
		
		
			if(!strcmp( ptr->d_name , command)){
				closedir(dir);
				return 1;
			}
		}
		closedir(dir);
		i++ ;
	}
	return 0;
}

void printprompt(char *str){
	
	char  path[N] ;

	if(getcwd(path , N) < 0){
		strcpy(path,"错误路径");
	}

	else{
		devide_dir(path);
	}
	
	

	printf("\33[31m [my_shell@畅柯$$%s] \33[0m",path);

}
void get_input(char * buf ,char * str){

	
	FILE * fp;
	char command[N];
	
	signal( SIGINT ,SIG_IGN);
	signal( SIGQUIT , SIG_IGN);
	signal(SIGSTOP  , SIG_IGN);
	signal( SIGTSTP ,SIG_IGN);

	
	strcpy(buf,readline(""));
	*(buf + strlen(buf)) ='\n';
	*(buf + strlen(buf) + 1) ='\0';

	add_history(buf);
	fp=fopen( histroyfile,"a+");
	if(fp == NULL){
		printf("histroy is not storage!\n");
	}
	fprintf(fp,"%s\n",buf);
	fclose(fp);

}
void explain_cmd(char * buf,int * argcount,char cmdlist[100][256]){//解析命令
	char * p = buf ;
	char * q = buf ;
	int i = 0;
	while(1){
		if( p[0]== '\n') break ;
		if(p[0] == ' '){
			p ++ ;
		}
		else{
			
			q = p ;
			i = 0 ;
			while(*(q) != ' ' && *(q) !=  '\n'){
				q ++ ;
				i ++ ;
			}
			strncpy( cmdlist[*argcount] , p , i + 1) ;
			cmdlist[*argcount][ i ]='\0';
			(*argcount) ++ ;
			p = q ;
		}	
	}
	
}
