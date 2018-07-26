#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<errno.h>
void my_err(const char* err_string,int line){
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	return ;
}
int main(int argc,char ** argv){
	char buf[PATH_MAX+1];
	if(argc<2){
		printf("my_cd <target_file>]\n");
		exit(1);
	}
	if(chdir(argv[1])<0){
		my_err("getcwd",__LINE__);
	}
	if(getcwd(buf,512)<0){
		my_err("get_cwd",__LINE__);
	}
	printf("%s\n",buf);
	return 0;
}
