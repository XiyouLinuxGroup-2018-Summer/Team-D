#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define N 1000
#include<errno.h>
void Init();
void Input();
void  inputfile(char * str);
void *thread1(void * arg);
void *thread2(void * arg );
pthread_mutex_t mutex ;
int fd ;
pthread_cond_t cond ;


typedef struct data{

	char str[N];
	struct data * next;
}data_t;
typedef struct node{

	data_t* head ,*rear ;

}node_t ;

node_t *data ;

void Init(){
	

	
	data->rear= data->head = NULL;
	data ->rear = data->head = (data_t* )malloc(sizeof(data_t ));
	
	 
}
void Input(){

		
		data_t * p = NULL ;
		
		
		while(1){
		
			
			p = (data_t*)malloc(sizeof(data_t));
			
					
			
			scanf("%[^\n]",p->str);
			
			while('\n' != getchar());
			printf("%d\n",strlen(p->str));


			if(*(p->str) == '\n' || *(p->str) == '\0')break ;
		
			p->next = NULL;
			
			data->rear->next = p ;
			

			data->rear = p ;
		}
}

void *thread2(void * arg){


	while(1){
			pthread_mutex_lock(&mutex);
			
			
		
			char buf[N];
	//		while(access("1",0)){

	//			pthread_cond_wait(&cond , &mutex);
			
	//		}
			fd = open("1",O_RDONLY,0766);

		//		perror("open");
			
		//	}

			read(fd , buf ,N);
			while((strlen(buf) == 0 || strlen(buf) > 100)){
			
				pthread_cond_wait(&cond , &mutex);
				

		
			}	
			
			read(fd , buf ,N);
		
			printf("Read string :%s\n",buf);
			
			close(fd);
			remove("1");
			pthread_mutex_unlock(&mutex);
	}
				
}
void *thread1(void * arg){
	
	
		while(1){	
			
			char buf[N];
		
		
			int flag = 0 ;
			data_t  *p ;
	
			p = data ->head ->next ;	
			while(p == NULL){
				remove("1");
				pthread_exit(NULL);
			}
		
			strcpy( buf , p->str);
		
			data->head->next = p->next ;


			free(p);
		
			inputfile(buf);	
		
		
		}

}
void inputfile(char * str){

	pthread_mutex_lock(&mutex);
	
	while(strlen(str) > 100){
		pthread_cond_wait(&cond , &mutex);
	}

		if((fd = open("1",O_RDWR | O_CREAT | O_TRUNC,0766))== -1){
			perror("open");
		}
		write(fd ,str ,1000 );
		
		printf("Writen string: %s\n",str);
	
		pthread_mutex_unlock(&mutex);
		
		close(fd);
		pthread_cond_signal(&cond);

}
int main(){


	data = (node_t*)malloc(sizeof(node_t));
	

	Init();
	Input();
	pthread_t thid1,thid2 ;
	pthread_mutex_init(&mutex , NULL );
	pthread_cond_init(&cond , NULL);
	pthread_create(&thid1 , NULL , (void *)&thread1 , NULL);
	pthread_create(&thid2 ,NULL , (void *)&thread2 , NULL);


	pthread_join(thid1 ,NULL);
	pthread_join(thid2 ,NULL);
}
