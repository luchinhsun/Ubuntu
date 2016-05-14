#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cblas.h>

void dgemm_row(double *a, double *b, double *c, int N);
void initial(double *a, double *b, double *c, int N);
void print_matrix(double *a, int N);
double error(double *a, double *b, int N);

int main()
{
	double *a, *b, *c, *d;
	int i, j, k, N;
	double t1, t2, t3, t4;

	printf("\n");
	printf(" Please enter N \n N =");
	scanf(" %d",&N);

	a=(double*)malloc(N*N*sizeof(double));
	b=(double*)malloc(N*N*sizeof(double));
	c=(double*)malloc(N*N*sizeof(double));
	d=(double*)malloc(N*N*sizeof(double));

	//enter matrix
	initial(a, b, c, N);

/*
	//print matrix a
	printf(" a =\n");
	print_matrix(a, N);

	//print matrix b
	printf(" b =\n");
	print_matrix(b, N);
*/

	t1 = clock();

	//solve & print ans
	//printf(" a * b =\n");
	for (i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			for (k=0; k<N; k++)	c[i*N+j] += a[i*N+k] * b[k*N+j];
			//printf(" %f ", c[i*N+j]);
		}
		//printf("\n");
	}

	t2 = clock();
	printf("\n Time = %f s\n\n",(t2 - t1)/CLOCKS_PER_SEC);

	//use blas to solve
	t3 = clock();

	dgemm_row(a, b, d, N);

	t4 = clock();
	printf("\n Time for Cblas = %f s\n\n",(t4 - t3)/CLOCKS_PER_SEC);

	printf(" The error between normal and blas\n");
	printf(" %e\n\n", error(c, d, N));
	return 0;
}

void dgemm_row(double *a, double *b, double *c, int N)
{
	double alpha, beta;
	alpha = 1.0;
	beta = 0.0;
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, alpha, a, N, b, N, beta, c, N);
}

void initial(double *a, double *b, double *c, int N)
{
	int i;
	for (i=0; i<N*N; i++)
	{
		a[i] = i;
		b[i] = N*N-i;
		c[i] = 0.0;
	}
}

void print_matrix(double *a, int N)
{
	int i, j;
	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)	printf(" %f ", a[i*N+j]);
		printf("\n");
	}
}

double error(double *a, double *b, int N)
{
	int i;
	double e, temp;
	e = 0.0;
	for (i=0; i<N*N; i++)
	{
		temp = fabs(a[i] - b[i]);
		if (temp > e)	e = temp;
	}
	return e;
}
