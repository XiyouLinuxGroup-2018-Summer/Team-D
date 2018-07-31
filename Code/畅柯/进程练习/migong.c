#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* Description


定义一个二维数组：

int maze[5][5] = {

	0, 1, 0, 0, 0,

	0, 1, 0, 1, 0,

	0, 0, 0, 0, 0,

	0, 1, 1, 1, 0,

	0, 0, 0, 1, 0,

};


它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。
Input

一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。
Output

左上角到右下角的最短路径，格式如样例所示。
Sample Input
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0

Output
(0, 0)
(1, 0)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 4)
(4, 4)
因为先学DFS所以第一次用的DFS来做，将每一条路径走到底，保存路径以及路径的长度（到达终点时递归了几层），后来发现有的数据会因为堆栈溢出。
后来才知道寻找最短路径最好用BFS。

涉及两个重要的东西：
1.队列。
用来储存可搜索的点
2.链表。
用来储存路径。*/

//代码：

#include <stdio.h>
#include <stdlib.h>
//结构体node 用来保存点的坐标
struct node
{
    int a ;
    int b ;
    //next链接上一个父节点
    struct node *next;
};
//保存迷宫
int vis[50][50];
//保存路径，以便正序输出
struct node way[100];
//路径点个数
int cnt;


//在迷宫的外围加上一层围墙，方便bfs处理
void setMark()
{
    int i,j;
    for(i=0; i<7; i++)
    {
        for(j=0; j<7; j++)
        {
            if(i==0||i==6||j==0||j==6)
            {
                vis[i][j] = 1;
            }


        }
    }
}
//创建一个队列
struct node list[10000];
int head,tail;
void init()
{
    memset(vis,0,sizeof(vis));
    head = 0;
    tail = 0;
    cnt = 0;
}


void Inset(int a,int b,struct node *next)//传入坐标，保存在队列中
{
    list[tail].a = a;
    list[tail].b = b;
    list[tail].next = next;
    tail ++;
}
struct node * Rem()//出队
{
    struct node * q;
    q = &list[head++];
    return q;
}
//------------------------
void disp()//输出路径坐标
{


    int i;
    for(i=cnt-1; i>=0; i--)
    {
        printf("(%d, %d)\n",way[i].a-1,way[i].b-1);
    }
//输出队列中存在的元素
//    for(i=head;i<tail;i++){
//        printf("(%d, %d) ",list[i].a,list[i].b);
//    }
//    printf("\n");
//查看迷宫整体
//    int j;
//    for(i=0;i<7;i++){
//        for(j=0;j<7;j++){
//
//                printf("%d ",vis[i][j]);
//
//
//        }
//        printf("\n");
//
//    }


}
void bfs()
{
    //零时指针变量，指向每次取出的点
    struct node *tem;
    //bfs从起始点开始搜索，将起始点加入队列中
    Inset(1,1,NULL);
    while(1)
    {


        //当队列为空时结束
        if(head>=tail)
        {
            return;
        }
        //取出元素
        tem = Rem();
        //到达右下角
        if(tem->a==5&&tem->b==5)
        {
            //保存路径在way中
            while(tem!=NULL)
            {

                way[cnt].a = tem->a;
                way[cnt].b = tem->b;
                cnt++;
                tem = tem->next;
            }
            return;
        }
        //搜索4个方向
        if(vis[tem->a][tem->b-1] == 0)
        {
            //满足可以走通的点就加入搜索队列
            Inset(tem->a,tem->b-1,tem);
            //搜索过的点被标记，防止被重新加入搜索队列
            vis[tem->a][tem->b] = 1;
        }
        if(vis[tem->a][tem->b+1] == 0)
        {
            Inset(tem->a,tem->b+1,tem);
            vis[tem->a][tem->b] = 1;
        }
        if(vis[tem->a-1][tem->b] == 0)
        {
            Inset(tem->a-1,tem->b,tem);
            vis[tem->a][tem->b] = 1;
        }
        if(vis[tem->a+1][tem->b] == 0)
        {
            Inset(tem->a+1,tem->b,tem);
            vis[tem->a][tem->b] = 1;
        }
    }
}


//-----------------------
int main()
{
    while(1)
    {
        init();
        int i,j;
        for(i=1; i<=5; i++)
        {
            for(j=1; j<=5; j++)
            {
                if(scanf("%d",&vis[i][j])==EOF){
                    return 0;
                }
            }
        }
        setMark();
        bfs();
        disp();
    }


    return 0;
}

/*
处理过程：
注意：因为加了外围，所以坐标都加了1，答案输出时减1就可以了。
(1, 1)   //将第一个点加入搜索队列，取出(1,1)点，搜索到(2,1)，(2,1)点被加入搜索队列
(2, 1)   //取出(2,1)点，搜索到(3,1)点，(3,1)点被加入搜索队列
(3, 1) //取出(3,1)点，搜索到(3,2),(4,1)点，(3,1),(4,1)点被加入搜索队列
(3, 2) (4, 1) //取出(3,2)点，搜索到(3,3)，(3,3)点被加入搜索队列
(4, 1) (3, 3) //取出(4,1)点，搜索到(5,1)，(5,1)点被加入搜索队列
(3, 3) (5, 1) //以此类推
(5, 1) (3, 4) (2, 3)
(3, 4) (2, 3) (5, 2)
(2, 3) (5, 2) (3, 5)
(5, 2) (3, 5) (1, 3)
(3, 5) (1, 3) (5, 3)
(1, 3) (5, 3) (2, 5) (4, 5)
(5, 3) (2, 5) (4, 5) (1, 4)
(2, 5) (4, 5) (1, 4)
(4, 5) (1, 4) (1, 5)
(1, 4) (1, 5) (5, 5)
(1, 5) (5, 5) (1, 5)
(5, 5) (1, 5) //当取到(5,5)点的时候就结束

关于路径保存：
因为所有搜索过的点都将保存在队列中，所以我们可以直接将队列中的点的地址保存在需要链接的
点的next中。
比如：
搜索(1,1)点周围可以移动的点是(2,1),那么我们可以在将(2,1)加入队列的Inset()操作中把(1,1)的地址存
于(2,1)中，当然如果有两个点或者三个点也是同样的操作，因为他们的父节点只会有一个。

当然这样操作也是有风险的，因为队列需要保存所有不是墙的节点，在我的程序中为list申请的是10000，
那么在巨大的地图面前是无力的。我希望能找到更好的办法。
*/

