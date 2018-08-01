#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
//#include<Linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

char panduanmulu(char s[500]);
void myerr(const char *s,int line);
int myreadir( char *path,char ***s,int a);
void paixu(char **s,int l);
void mingchengshuchu(char **s,int l);
void quanxian(int s) ;
void time1(char s[100]);
void lllll(char s[500]  );
int RRR(char **s,int a,int l ,int len ,char mulu[500]);


//查错函数
void myerr(const char *s,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(s);
    exit(1);
}

//获取文件所含目录名称,根据a是否为0判断存储隐含文件
int myreadir(char *path,char ***s,int a)
{

    DIR *dir;
    struct dirent *ptr;
    int i=0;

    if((dir=opendir(path))==NULL)
    {
        (*s)=(char **)malloc(sizeof(char *) * 2);
	*(*s+0) = (char *)malloc(sizeof(char)*1000); 
	strcpy(*(*s+0),path);
	
	return 0;
    }

    /*if((ptr=readdir(dir))==NULL)
    	myerr("readdir",__LINE__);*/
    
    int q=0;
    while((ptr=readdir(dir))!=NULL)
    {    
    	if(a==0)
    	{
	        if(ptr->d_name[0]=='.')
		    continue;
	}
       		q++;
        
    }
    closedir(dir);

   

    (*s)=(char **)malloc(sizeof(char *) * (q+1));       //分配动态数组
    for(i=0;i<q+1;i++)  
      *(*s+i) = (char *)malloc(sizeof(char)*1000); 

    i=0; 
  
    dir=opendir(path);
    while((ptr=readdir(dir))!=NULL)
    {
    	if(a==0)
    	{
	        if(ptr->d_name[0]=='.')
		    continue;
	}
        strcpy( *(*s+i),ptr->d_name);
        i++;  
    }
    closedir(dir);
    return q;
}

//对文件名进行排序-从小到大
void paixu(char **s,int l)
{
    int i,j;
    char k[1000];  
	
    for(i=0;i<l-1;i++)
    {
	
	for(j=0;j<l-i-1;j++)
    	{
	    if(strcmp(*(s+j),*(s+j+1))>0)
	    {  
		
	        strcpy(k,*(s+j+1));
	        strcpy(*(s+j+1),*(s+j));
	        strcpy(*(s+j),k);
            }
        }
    }
}


//设置最大行数控制输出目录名称
void mingchengshuchu(char **s,int l)
{
    int i=0,k=0,a,b;
    while(l--)
    {
	    a=strlen(*(s+i));   
	    if(l==0)
		b=0;
	    else   
           	b=strlen(*(s+i+1));
	    if(k==0 && (k+b+3)<=50)
	    {
	        printf("%s",*(s+i));
	        printf("   ");
	        k=k+a+3;
	    }
	    else if(k==0 && (k+b+3)>50)
	    {
	        printf("%s\n",*(s+i));
	        k=0;
	    }
	    else if(k!=0 && (k+b+3)<=50)
	    {
	        printf("%s",*(s+i));
	        printf("   ");
	        k=k+a+3;
	    }
	    else if(k!=0 && (k+b+3)>50)
	    {
	        printf("%s\n",*(s+i));
	        k=0;
	    }
	    i++;
    }
    printf("\n");
}

//输出权限rwx和类型d/-函数
void quanxian(int s)
{
	int d,u,g,o,i;
	o=s%8;
	g=s/8%8;
	u=s/8/8%8;
	int a[3];
	a[0]=u;a[1]=g;a[2]=o;
	for(i=0;i<3;i++)
	{
		switch(a[i])
		{
			case 0:printf("---");break;
			case 1:printf("--x");break;
			case 4:printf("r--");break;
			case 2:printf("-w-");break;
			case 3:printf("-wx");break;
			case 5:printf("r-x");break;
			case 6:printf("rw-");break;
			case 7:printf("rwx");break;
		}
	}
}

//输出时间函数
void time1(char s[100])
{
	int i;
	char y[4];
	y[0]=s[4];y[1]=s[5];y[2]=s[6];
	if(strcmp(y,"Jan")==0) printf(" 1月 ");
	else if(strcmp(y,"Feb")==0) printf(" 2月 ");
	else if(strcmp(y,"Mar")==0) printf(" 3月 ");
	else if(strcmp(y,"Apr")==0) printf(" 4月 ");
	else if(strcmp(y,"May")==0) printf(" 5月 ");
	else if(strcmp(y,"Jun")==0) printf(" 6月 ");
	else if(strcmp(y,"Jul")==0) printf(" 7月 ");
	else if(strcmp(y,"Aug")==0) printf(" 8月 ");
	else if(strcmp(y,"Sep")==0) printf(" 9月 ");
	else if(strcmp(y,"Oct")==0) printf(" 10月 ");
	else if(strcmp(y,"Nov")==0) printf(" 11月 ");
	else if(strcmp(y,"Dec")==0) printf(" 12月 ");
	for(i=8;i<16;i++)
		printf("%c",s[i]);
}
//输出-l函数，参数为文件名和当前目录
void lllll(char s[500] )
{
    struct stat buf;
    struct passwd *psd;
    struct group *grp;
   
    if(stat(s,&buf)==-1)
    {
        myerr("stat",__LINE__);
    }
    psd=getpwuid(buf.st_uid);
    grp=getgrgid(buf.st_uid);
    if(S_ISLNK(buf.st_mode))
	printf("l");
    else if(S_ISREG(buf.st_mode))
	printf("-");
    else if(S_ISDIR(buf.st_mode))
	printf("d");
    else if(S_ISCHR(buf.st_mode))
	printf("c");
    else if(S_ISBLK(buf.st_mode))
	printf("b");
    else if(S_ISFIFO(buf.st_mode))
	printf("f");
    else if(S_ISSOCK(buf.st_mode))
	printf("s");
    quanxian(buf.st_mode);
    printf("%4d  ",buf.st_nlink);
    printf("%-8s",psd->pw_name);
    printf("%-8s",grp->gr_name);
    printf("%6d  ",buf.st_size);
    time1(ctime(&buf.st_mtime));
    printf(" %s\n",s);
}

char panduanmulu(char s[500])
{
    struct stat buf;
    if(stat(s,&buf)==-1)
    {
        myerr("stat",__LINE__);
    }
    if(S_ISLNK(buf.st_mode))
	return 'l';
    else if(S_ISREG(buf.st_mode))
	return '-';
    else if(S_ISDIR(buf.st_mode))
	return 'd';
    else if(S_ISCHR(buf.st_mode))
	return 'c';
    else if(S_ISBLK(buf.st_mode))
	return 'b';
    else if(S_ISFIFO(buf.st_mode))
	return 'f';
    else if(S_ISSOCK(buf.st_mode))
	return 's';
}





int RRR(char **s,int a,int l,int len ,char mulu[500] )
{
    char *buf;
    buf=(char*)malloc(sizeof(char)*1000); 
    int j;

    if(getcwd(buf,1000)<0)          //获取当前系统目录,主函数时已经切换过，所以无需担心是系统目录
	myerr("getcwd",__LINE__);

     paixu(s,len);
    
    int i=0,len2=0,x,e;
    char **k;
   /* k=(char**)malloc(sizeof(char*)*1000);            //k的动态数组，用于传下一个递归的目录
    for(e=0;e<1000;e++)  
        k[e]=(char*)malloc(sizeof(char)*1000); */

    char *xin;
    xin=(char*)malloc(sizeof(char)*1000);			//xin为新目录              
					                  
    if(strcmp(buf,mulu)==0)					//如果当前目录和传进来目录一致，则不需要改目录
	strcpy(xin,mulu);
    else
    {							//如果不一致，则更换新目录，这是为了在递归里面可以保证有权限
	strcpy(xin,buf);
	x=strlen(xin);
	if(xin[x-1]!='/')
	{
	   xin[x]='/';
	   xin[x+1]='\0';
	}
	strcat(xin,mulu);                                 //xin即为现在的目录
    }
                                       
     printf("%s:\n",xin);                                  //打印出目录
	if(chdir(xin)<0)
    {
	myerr("chdir",__LINE__);
	return 0;
    }
				                  //如果没有 l 直接打印该目录下所有内容
    if(l==0)
	mingchengshuchu(s,len);
    else
    {
	for(j=0;j<len;j++)
	{
	     lllll(s[j] );
	   	
	}
    }
                                               //切换到现在的目录
    
                                              //如果有隐藏文件，则从第二个吗目录开始递归，否则会死循环
    if(a!=0)
        i=2;
 
  
    while(1)                                 //开始递归，从i开始循环
    {   
	
        if(chdir(xin)<0)                     //确认一遍是在新目录下，防止下一层递归返回后，不在当前目录
        {
	myerr("chdir",__LINE__);
	return 0;
        }

        if(i==len)
		len2=0;
	else                               //得到目录下的目录信息
		len2=myreadir(s[i],&k,a);

	if(len2==0 && i==len)               //目录下已经没有目录了，并且是最后一个文件，返回上一层，释放数组
        {

            free(xin);
	    free(buf);
	    for(e=0;e<len2;e++)  
        	free(*(k+e));
	    return 0;
	}
	else if(len2==0 && i!=len)          //目录下没有目录了，但是还有下面的目录
	{
	   char buf2[500];
	    if(getcwd(buf2,500)<0)
	        myerr("getcwd",__LINE__);
            else
	    {
		if(panduanmulu(*(s+i))== 'd')
	    	        printf("%s/%s :\n",xin,*(s+i));
	    	i++;
	    }
	}
	else if(len2!=0)                    //目录下还有目录，开始递归
	{
	   
	    RRR(k,a,l,len2,*(s+i));
	    i++;
	}
    }
    
}

//主函数
int main(int argc,char *argv[])
{
    if(argc<2 || strcmp(argv[1],"ls")!=0)
    {
        printf("\033[31m 输入错误！！！\n\033[0m");
        exit(1);
    }
    

    int l=0,a=0,R=0,i,wen=0,len;
    char mulu[500];
    char **s;int e;
                             //解析命令行参数-R,-l,-a等
    for(i=2;i<argc;i++)
    {
	if(strcmp(argv[i],"-l")==0)
		l++;
	else if(strcmp(argv[i],"-R")==0)
		R++;
	else if(strcmp(argv[i],"-a")==0)
		a++;
	else if(argv[i][0]!='-')
	{
		strcpy(mulu,argv[i]);
		wen++;
	}
	else if(argv[i][0]=='-')
	{
	    printf("\033[31m 输入错误！！！\n\033[0m");
	    exit(1);
	}
		
    }                                            //目录名称赋给mulu字符串，若未输入，则引用当前目录
    
   if(wen!=0 && mulu[0]=='/')                    //如果输入目录是从/开始，则直接切换到当前目录
    {
	if(chdir(mulu)<0)
        {
	    myerr("chdir",__LINE__);
	    return 0;
        }
    }

    if(wen==0)                                  //如果未输入目录，则引用当前目录
    {
	if(getcwd(mulu,500)<0)
	    myerr("getcwd",__LINE__);
    }
 
    len=myreadir(mulu,&s,a);   //printf("%s  00  %d \n",s[0],len);			//调用myreadir函数获取数组长度和目录内容
   
			  //-R做单独处理，因为-R中含有递归，还是要切换目录，所以此时不用做处理
    if(R!=0)
    {
    	RRR(s,a,l,len,mulu);
        for(e=0;e<len;e++)  
            free(*(s+e));
	return 0;
    }


                                               //若无-R则需解析出文件名和目录名，切换到该目录下
    char muluming[500],wenjianming[500];
    int ax=0,bx=0,flag=1,fffff;
    if(wen!=0     )
    {
        for(i=0;i<strlen(mulu);i++)
        {
        	if(mulu[i]!='/' && flag!=0)        //flag等于0时给目录赋值，1时给文件名赋值
        	{
	            wenjianming[bx++]=mulu[i];
		    wenjianming[bx]='\0';
        	}
        	else if(mulu[i]!='/' && flag==0)
        	{
	            muluming[ax++]=mulu[i];
        	}
        	else if(mulu[i]=='/' && flag==0)
        	{
                muluming[ax++]='/';
	            flag=1;
        	}
        	else if(mulu[i]=='/' && flag!=0)
        	{
	            muluming[ax++]='/';
	            strcat(muluming,wenjianming);
		    ax=ax+strlen(wenjianming);
		    bx=0;
		    memset(wenjianming,sizeof(wenjianming),'\0');         //切记清零
	            flag=1;
        	}
	    }
	wenjianming[bx]='\0';
    	muluming[ax]='\0'; 
	
        if(ax==0)                                            // 如果得到的目录为0，则引用当前目录
        {
	        if(getcwd(muluming,500)<0)
	            myerr("getcwd",__LINE__);
        }
	else                                                  //目录不为0，则
	{
	        char sss[500];
        	if(getcwd(sss,500)<0)
	            myerr("getcwd",__LINE__);
                strcat(sss,muluming);
	        strcpy(muluming,sss);  
	 }   
    }
    else
    {
	    if(getcwd(muluming,500)<0)
	        myerr("getcwd",__LINE__);
    }


    if(chdir(mulu)<0)
        {
	    myerr("chdir",__LINE__);
	    return 0;
        } 
		
    paixu(s,len);

    if(len==0)
    {
    	if(l==0)
	        mingchengshuchu(s,1);
	else
	        lllll(*(s+0));
	return 0;
    }

       
    /*int v;
    v=strlen(muluming);
    if (muluming[v-1]!='/')
    {
        muluming[v]='/';
        muluming[v+1]='\0';
    }
    strcat(muluming,wenjianming);
    */ 
    if(l==0 && R==0)
    	mingchengshuchu(s,len);
    else if(l>0 && R==0)
    {
	for(i=0;i<len;i++)
	{
	   
	     lllll(*(s+i));
	}
    } 
    for(e=0;e<len;e++)  
        free(*(s+e));
  
    return 0;
   

}

