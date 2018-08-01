#include<stdio.h>
#include<stdlib.h>
#define N 1000
int rear= 1, head= 1;
int vis[100][100];//保存迷宫

typedef struct node{
	int x, y;
	struct node* next;
};
node way[100];//保存路径
typedef struct queue{//队列走地图
	int x,y;
}list ;
list queue[N];
 init(int x ,int y){
	
	
	return list;
}
