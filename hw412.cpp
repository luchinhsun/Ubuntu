#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main ()
{
  double *a,*b;
  int N;
  printf("please enter N \n N=");
  scanf("%d",&N);
  a=(double*)malloc(N*sizeof(double));
  b=(double*)malloc(N*sizeof(double));
  for(int i=0;i<N;i++)
  {
   a[i]=sin(i);
   b[i]=cos(i);
   //printf("a%d=%f\n",i,a[i]);
   //printf("b%d=%f\n",i,b[i]);
  }
  printf("\n");

  //a*b
  double k=0;
  for(int i=0;i<N;i++)
  {
   k=k+a[i]*b[i];
   //printf("k=%f\n",k);
  }
  printf("a-b=%f\n",k);
  printf("\n");

  //norm a,b
  double norma=0,normb=0;
  for(int i=0;i<N;i++)
  {
   norma=norma+a[i]*a[i];
   normb=normb+b[i]*b[i];
  }
  norma=sqrt(norma);
  normb=sqrt(normb);
  printf("norma=%f\n",norma);
  printf("normb=%f\n",normb);
  printf("\n");

  //a-b
  double *c;
  c=(double*)malloc(N*sizeof(double));
  printf("c=a-b\n");
  for(int i=0;i<N;i++)
  {
   c[i]=a[i]-b[i];
   printf("c%d=%f\n",i,c[i]);
  }

  return 0;
}
