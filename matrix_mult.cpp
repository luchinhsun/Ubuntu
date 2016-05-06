#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
 double *a,*b,*c;
 int N;

 printf("Please enter N \n N=");
 scanf("%d",&N);

 a=(double*)malloc(N*N*sizeof(double));
 b=(double*)malloc(N*N*sizeof(double));
 c=(double*)malloc(N*N*sizeof(double));

 //enter matrix
 for(int i=0;i<N*N;i++)
 {
	a[i]=i;
	b[i]=N*N-i-1;
	c[i]=0;
 }

 //print matrix a
 printf("a=\n");
 for(int i=0;i<N;i++)
 {
	for(int j=0;j<N;j++)
	{
		printf("%.2f ",a[N*i+j]);
	}
	printf("\n");
 }

 //print matrix b
 printf("b=\n");
 for(int i=0;i<N;i++)
 {
	for(int j=0;j<N;j++)
	{
		printf("%.2f ",b[N*i+j]);
	}
	printf("\n");
 }

 //solve & print ans
 printf("a*b=\n");
 for(int i=0;i<N;i++)
 {
	for(int j=0;j<N;j++)
	{
		for(int k=0;k<N;k++)
		{
			c[i*N+j]+=a[i*N+k]*b[k*N+j];
		}
		printf("%.2f ",c[i*N+j]);
	}
	printf("\n");
 }
}
