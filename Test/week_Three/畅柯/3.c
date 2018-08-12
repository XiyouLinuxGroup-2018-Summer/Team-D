#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>



void *thread3(void*arg){
	
	printf("C");
		
	
	pthread_exit(NULL);
}
void *thread2(void*arg){
		pthread_t thid3 ;

		printf("B");
	
		pthread_create(&thid3 , NULL ,(void *)thread3 , NULL);
		pthread_join(thid3 ,NULL);
		 pthread_exit(NULL);
}
void* thread1(void*arg){
	pthread_t thid2 ;

	while(1){	

		
		printf("A");
		pthread_create(&thid2 , NULL , (void* )thread2 ,NULL);
		pthread_join(thid2 , NULL);
	}
	
}
int main(void){
	
	pthread_t thid1;
	pthread_create(&thid1,NULL,(void*)thread1,NULL);
	pthread_join(thid1 , NULL);
	return 0;
}
