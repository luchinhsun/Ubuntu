#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
 double **a,**b;
 int N;
 printf("Please enter N \n N=");
 scanf("%d",&N);
 a=(double**)malloc(N*sizeof(double));
 b=(double**)malloc(N*sizeof(double));
 double *aData,*bData;
 aData=(double*)malloc(N*N*sizeof(double));
 bData=(double*)malloc(N*N*sizeof(double));
 for(int i=0;i<N*N;i++)
 {
  aData[i]=i+1;
  bData[i]=N*N-i-1;
 }
 for(int i=0;i<N;i++,aData+=N,bData+=N)
 {
  a[i]=aData;
  b[i]=bData;
 }
//print a,b
 printf("a=\n");
 for(int i=0;i<N;i++)
 {
  for(int j=0;j<N;j++)
  {
   printf("%.2f ",a[i][j]);
  }
  printf("\n");
 }
 printf("b=\n");
 for(int i=0;i<N;i++)
 {
  for(int j=0;j<N;j++)
  {
   printf("%.2f ",b[i][j]);
  }
  printf("\n");
 }
//print a*b
 double **c;
 c=(double**)malloc(N*sizeof(double));
 double *cData;
 cData=(double*)malloc(N*N*sizeof(double));
 for(int i=0;i<N*N;i++)
 {
  cData[i]=0;
 }
 for(int i=0;i<N;i++)
 {
   c[i]=cData;
 }
 printf("a*b=\n");
 for(int i=0;i<N;i++)
 {
  for(int j=0;j<N;j++)
  {
   c[i][j]=0; //WHY
   for(int k=0;k<N;k++)
   {
    c[i][j]+=+a[i][k]*b[k][j];
   }
   printf("%.2f ",c[i][j]);
  }
  printf("\n");
 }
}
