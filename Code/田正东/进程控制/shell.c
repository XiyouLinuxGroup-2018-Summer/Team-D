#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pwd.h>
#include <signal.h>
#include <sys/resource.h>
#define normal          0
#define out_redirect    1
#define in_redirect     2
#define have_pipe       3
#define out_redirect2   4
struct passwd *p;
int find_command(char *command)
{
	DIR *dp;
	struct dirent*  dirp;
	char *path[]={"./","/bin","/usr/bin",NULL};

	if(strncmp(command,"./",2) == 0)
		command = command + 2;
	int i = 0;
	while(path[i] != NULL){
		if((dp = opendir(path[i])) == NULL){
			printf("打不开 /bin\n");
		}
		while((dirp = readdir(dp)) != NULL){
			if(strcmp(dirp -> d_name,command) == 0){
				closedir(dp);
				return 1;
			}
		}
		closedir(dp);
		i++;
	}
	return 0;
}

void do_cmd(int argcount,char arglist[100][256],int his_count,char history[][256])
{
	int flag = 0;
	int how = 0;
	int backgroud = 0;
	int status;
	int i;
	int fd;
	char * arg[argcount + 4];
	char * argnext[argcount + 4];
	char *file;
	char home[256];
	pid_t pid;

	for(i = 0; i < argcount; i++)
		arg[i] = (char *)arglist[i];

	arg[argcount] = NULL;

	for(i = 0; i < argcount; i++){
		if(strncmp(arg[i],"&",1) == 0){
			if(i == argcount - 1){
				backgroud = 1;
				arg[argcount - 1] = NULL;
				break;
			}
			else {
				printf("参数没输对，重新输！\n");
				return ;
			}
		}
	}

	for(i = 0; arg[i] != NULL; i++){
		if(strcmp(arg[i],">") == 0){
			flag++;
			how = out_redirect;
			if (arg[i+1] == NULL)
				flag++;
		}
		if(strcmp(arg[i],">>") == 0){
			flag++;
			how = out_redirect2;
			if(arg[i+1] == NULL)
			flag++;
		}
		if( strcmp(arg[i],"<") == 0){
			flag++;
			how = in_redirect;
			if(i == 0)
				flag++;
		}
		if( strcmp(arg[i],"|") == 0){
			flag++;
			how = have_pipe;
			if(arg[i+1] == NULL)
				flag++;
			if( i == 0)
				flag++;
		}
	}

	if(flag > 1){
		printf("参数没输对，重新输！\n");
		return ;
	}

	if( how == out_redirect){
		for(i = 0; arg[i] != NULL; i++){
			if(strcmp(arg[i],">") == 0){
				file = arg[i+1];
				arg[i] = NULL;
			}
		}
	}
	if(how == in_redirect){
		for(i = 0; arg[i] != NULL; i++){
			if(strcmp(arg[i],"<") == 0){
				file = arg[i+1];
				arg[i] = NULL;
			}
		}
	}
	if(how == out_redirect2){
		for(i = 0; arg[i] != NULL; i++){
			if(strcmp(arg[i],">>") == 0){
				file = arg[i+1];
				arg[i] = NULL;     
			}
		}
	}
	if(how == have_pipe){
		for(i = 0; arg[i] != NULL; i++){
			if(strcmp(arg[i],"|") == 0){
				arg[i] = NULL;
				int j;
				for(j = i+1; arg[j] != NULL; j++){
					argnext[j-i-1] = arg[j];
				}
				argnext[j-i-1] = arg[j];
				break;
			}
		}
	}
	if(strcmp(arg[0],"history") == 0 && argcount == 1){
		for(i = 0; i < his_count; i++){
			printf("%d\t%s\n",i+1,history[i]);
		}
		goto loop;
	}

	if(strcmp(arg[0],"cd") == 0){
		sprintf(home,"/home/%s/",p->pw_name);
		if(argcount == 1 || argcount == 2 && strcmp(arg[1],"~") == 0) {
			chdir(home);
			goto loop;
		}
		if(chdir(arg[1]) == -1){
			perror("chdir");
		}
		goto  loop;
	}

	if( (pid = fork()) < 0){
		printf("fork error\n");
		return ;
	}

	switch(how){
	case 0: //普通命令
		if(pid == 0){
			if( !(find_command(arg[0])) ){
				printf("%s :没有这个命令\n",arg[0]);
				exit(0);
			}
			execvp(arg[0],arg);
			exit(0);
		}
		break;

	case 1: // >
		if(pid == 0){
			if( !(find_command(arg[0])) ){
				printf("%s :没有这个命令\n",arg[0]);
				exit(0);
			}
			fd = open(file,O_RDWR | O_CREAT | O_TRUNC,0644);
			dup2(fd,1);

			execvp(arg[0],arg);
			exit(0);
		}
		break;
	case 2:// <
		if(pid == 0){
			if( !(find_command(arg[0])) ){
				printf("%s :没有这个命令\n",arg[0]);
				exit(0);
			}
			fd = open(file,O_RDONLY);
			dup2(fd,0);
			execvp(arg[0],arg);
			close(fd);
			exit(0);
		}
		break;
	case 4:
		if(pid == 0){
			if( !(find_command(arg[0])) ){
				printf("%s :没有这个命令\n",arg[0]);
				exit(0);
			}
			fd = open(file,O_APPEND|O_WRONLY,0644);
			dup2(fd,1);
			execvp(arg[0],arg);
			exit(0);
		}
		break;
	case 3:// |
		if(pid == 0){
			int pid2;
			int status2;
			int fd2;

			if( (pid2 = fork()) < 0){
				printf("fork2 error\n");
				return ;
			}
			else if(pid2 == 0){
				if(!(find_command)(arg[0])){
					printf("%s :没有这个命令\n",arg[0]);
					exit(0);
				}

				if((fd2 = open("/tmp/tmpfile",O_WRONLY | O_CREAT | O_TRUNC ,0644)) == -1)
					printf("open /tmp/tmpfile failed!");
				dup2(fd2,1);
				execvp(arg[0],arg);
				close(fd2);
				exit(0);
			}

			if(waitpid(pid2,&status2,0) == -1){
				printf("wait for child process error\n");
			}

			if(!(find_command)(argnext[0])){
				printf("%s :没有这个命令\n",argnext[0]);
				exit(0);
			}

			if((fd2 = open("/tmp/tmpfile",O_RDONLY)) == -1) {
				perror("Open");
			}
			dup2(fd2,0);

			execvp(argnext[0],argnext);
			if(remove("/tmp/tmpfile") == -1)//移除文件
				perror("remove");
			exit(0);
		}
		break;
	default :
		break;
	}

    if(backgroud == 1  && pid != 0){
		printf("[process id %d]\n",pid);
		exit(0);
	}

	if(waitpid(pid,&status,0) == -1){
		printf("wait for child process error!\n");
	}
	loop: ;
}

void get_input(char *buf,char *path,int *his_count,char history[][256])
{
	int count = 0,i,len;
	uid_t  uid;
	char  *test;
	char  str[500];
	uid = getuid ();
	p = getpwuid (uid);
	if (!p){
		printf ("没有这个银 %d./n", (int)uid);
		return ;
	}
	sprintf(str,"\033[;34m%s@\033[0m\033[;34m画地的辣鸡shell:~\033[0m\033[;34m%s\033[0m\033[;34m$\033[0m ",p -> pw_name,path);
	test = (char* )malloc(sizeof(256));
	test = readline(str);
	strcpy(buf, test);

	len = strlen(buf);
	for(i = 0; i < len; i++)
		if(buf[i] == ' ' || buf[i] == '\n')
			count++;

	if(count != len){
		if(*his_count != 0){
			if(strcmp(history[*his_count-1],buf) != 0){
				strcpy(history[*his_count],buf);
				*his_count = *his_count + 1;
				add_history(buf);
			}
		}
		else{
			strcpy(history[*his_count],buf);
			*his_count = *his_count + 1;
			add_history(buf);
		}
	}
	free(test);
}

void explain_input(char *buf,int *argcount,char arglist[100][256])
{
	int number = 0 ;
	char *p = buf;
	char *q = buf;
	while(1){
		if(p[0] == '\n' || p[0] == '\0')
			break;
		if(p[0] == ' ')
			p++;
		else{
			q = p;
			number = 0;
			while( (q[0] != ' ') && (q[0] != '\0') && (q[0] != '\n')){
				number++;
				q++;
			}
			strncpy(arglist[*argcount],p,number+1);
			arglist[*argcount][number] = '\0';
			*argcount = *argcount + 1;
			p = q;
		}
	}
}

int main(int argc,char *argv[])
{
	signal( SIGINT,SIG_IGN );
	int i;
	char history[256][256];
	int his_count = 0;
	int argcount = 0;
	char arglist[100][256];
	char **arg = NULL;
	char *buf  = NULL;
	char path [256];

	buf = (char *)malloc(256);
	if(buf == NULL){
		perror("malloc failed");
		exit(-1);
	}

	while(1){
		if (getcwd(path, 256) == NULL){
			printf("read path error!\n");
			exit(-1);
		}

		get_input(buf,path,&his_count,history);	

		while(strlen(buf) == 0){
			get_input(buf,path,&his_count,history); 
		}

		if( strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0)
			break;

		for(i = 0; i < 100; i++){
			arglist[i][0] = '\0';
		}

		argcount = 0;
		explain_input(buf,&argcount,arglist);

		do_cmd(argcount,arglist,his_count,history);
	}

	if(buf != NULL){
		free(buf);
		buf = NULL;
	}

	exit(0);
}
