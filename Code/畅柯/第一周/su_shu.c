/*     对于表达式n^2+n+41，当n在（x,y）范围内取整数值时（包括x,y）(-39<=x<y<=50)，判定该表达式的值是否都为素数。 
Input
    输入数据有多组，每组占一行，由两个整数x，y组成，当x=0,y=0时，表示输入结束，该行不做处理。
Output
    对于每个给定范围内的取值，如果表达式的值都为素数，则输出"OK",否则请输出“Sorry”,每组输出占一行。
Sample Input

    0 1
    0 0

Sample Output

    OK*/
#include<stdio.h>
#include<stdlib.h>
int IsPrime(int s);
int main(){
	int x,y;
	int i,s,flag=1;
	while((scanf("%d%d",&x,&y))!=EOF){
		if(x==0&&y==0)break;
		for(i=x;i<=y;i++){
			s=i*i+i+41;
			if(IsPrime(s)==0){
				flag=0;
				break;
			}
		}
		if(flag==1){
			printf("OK\n");
			}
		else{
			printf("Sorry\n");
		}
	}
}
int IsPrime(int s){
	int i,flag=1;
	if(s==2)return flag;
	for(i=2;i<=s/2+1;i++){
		if(s%i==0)flag=0;
	}
	return flag;
}
