#include<stdio.h>
#include<stdlib.h>
#define PI 3.1415927
#define N 20
int main(){
	double r,V;
	while((scanf("%lf",&r))!=EOF){
		V=4*1.0/3*PI*r*r*r;
		printf("%.3lf\n",V);
	}
}
