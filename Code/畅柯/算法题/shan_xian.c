#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long start,end;
long time ;


typedef  struct node{
	long data ;
	struct node *next;
}node_t;
node_t p[100001];
void init();
void inset(int a,node_t * next);
long head ,tail;
void go_end(int start);
node_t*  pop();
void init(){
	time = 0;
	head = 0;
	tail = 0;
	p[tail].data=start;
	p[tail].next =NULL;
}

void inset(int a,node_t * next){
	p[tail].data = a;
	p[tail].next =next;
	tail ++;
}
node_t*  pop(){
	
	return &p[head++] ; 
}

void go_end(int start){
	node_t *q=NULL;
	inset(start,NULL);
	while(start != end){
		
		long num;
		q=pop();
	
		if(q->data == end){
			while(q->next != NULL){
				time ++;
				q = q->next ;
				
			}
			return ;
		}
		num = q->data -1;
		inset(num ,q); 
		num = q->data +1 ;
		inset(num ,q);
		num = (q->data)*2;
		inset(num,q);
	}
	
}
int main(){
	
	while(scanf("%ld%ld",&start,&end)!=EOF){
	
		init();
		go_end(start);
		printf("%ld\n",time);		
	}
	return 0;
}
