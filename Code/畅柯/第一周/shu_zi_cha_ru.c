#include<stdio.h>
#include<stdlib.h>
/*     有n(n<=100)个整数，已经按照从小到大顺序排列好，现在另外给一个整数x，请将该数插入到序列中，并使新的序列仍然有序。 
Input
    输入数据包含多个测试实例，每组数据由两行组成，第一行是n和m，第二行是已经有序的n个数的数列。n和m同时为0标示输入数据的结束，本行不做处理。
Output
    对于每个测试实例，输出插入新的元素后的数列。
Sample Input

    3 3
    1 2 4
    0 0

Sample Output

    1 2 3 4*/
#define N 50
int main(){
	int a[N];
	int m,n,i,temp,j,temp1;
	while((scanf("%d%d",&m,&n))!=EOF){
		if(m==0&&n==0)break;
		for(i=0;i<m;i++){
			scanf("%d",&a[i]);
		}
		for(i=0;i<m;i++){
			if(n<a[i]){
				temp=a[i];
				a[i]=n;
				for(i=i+1;i<m+1;i++){
					temp1=a[i];
					a[i]=temp;
					temp=temp1;		
				}
			}
			else{
				continue;
			}
		}
	for(i=0;i<m+1;i++){
		printf("%d",a[i]);
		if(i!=m+1)printf(" ");
		}
		printf("\n");
	}
}
