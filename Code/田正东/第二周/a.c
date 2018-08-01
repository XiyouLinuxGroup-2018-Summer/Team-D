#include <stdio.h>
#include <stdlib.h>
int maze[5][5];                    //迷宫大小
int a[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };   //四个方向
struct node{
	int x,y;                                     //记录步数
}queue[100],pre[5][5];
int main()
{
	int i,j,m,n;
	int head = 0;
	int tail = 1;
	struct node p,next;
	int k = 0;
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			scanf("%d",&maze[i][j]);
	p.x = 0;
	p.y = 0;
	maze[0][0] = 1;
	queue[0] = p;
	p.x = queue[head].x;
	p.y = queue[head].y;
	while(head < tail){
		p = queue[head++];
		for(i = 0; i < 4; i++){
			next.x = p.x + a[i][0];
			next.y = p.y + a[i][1];
			if(next.x >= 0 && next.y >= 0 && next.x < 5 && next.y < 5 && maze[next.x][next.y] == 0){
				pre[next.x][next.y].x = p.x;
				pre[next.x][next.y].y = p.y;
				if(next.x != 4 || next.y != 4)
					maze[next.x][next.y] = 1;
					queue[tail++] = next;
            }
        }
    }
	queue[k].x = 4;
	queue[k++].y = 4;
	i = j = 4;
	while(i != 0 || j != 0){
		m = i;
		n = j;
		i = pre[m][n].x;
		j = pre[m][n].y;
		queue[k].x = i;
		queue[k++].y = j;
	}
	for(i = k - 1; i >= 0; i--)
		printf("(%d, %d)\n", queue[i].x,queue[i].y);
	return 0;
}
