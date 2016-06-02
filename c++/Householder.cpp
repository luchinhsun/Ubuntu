/*******************************************************************
*		Householder QR Factorization
*		Date: 2016/05/27
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double dot(double *x, double *v, int N, int k);
void initial(double *a, double *r, int M, int N);
void print_matrix(double *a, int M, int N);
double sign(double x);
void tran_matrix(double *a, int M, int N, double *b);
void matrix_mult(double *v, double *a, double *va, int k, int M, int N);
double error(double *x, double *y, int N);


int main()
{
	printf("\n");
	int M, N, i, j, k;
	printf(" Input size M = ");
	scanf("%d", &M);
	printf(" Input size N = ");
	scanf("%d", &N);
	printf(" M & N = %d & %d\n\n", M, N);

	//only allow M >= N
	if (M<N)
	{
		printf(" please let M >= N \n");
		return 0;
	}

	double *a, *x, *r;
	a = (double *) malloc(M*N*sizeof(double));
	r = (double *) malloc(M*N*sizeof(double));
	x = (double *) malloc(N*sizeof(double));

	double *v, *va, temp;
	v = (double *) malloc(M*sizeof(double));
	va = (double *) malloc(N*sizeof(double));

	double *V, *b, *bt, temp1;
	V = (double *) malloc(M*N*sizeof(double));
	b = (double *) malloc(M*M*sizeof(double));
	bt = (double *) malloc(M*M*sizeof(double));

	double *qr, *A;
	qr = (double *) malloc(M*N*sizeof(double));
	A = (double *) malloc(M*N*sizeof(double));

	//create a matrix
	initial(a, r, M, N);
	initial(A, r, M, N);
	printf(" input : \n");
	print_matrix(a, M, N);

	//create a identity matrix
	for (i=0; i<M; i++)
	b[i*M+i] = 1.0;
	//print_matrix(b, M, M);

	//Householder QR Factorization
	for (k=0; k<N; k++)
	{
		for (i=k; i<M; i++)
		{
			x[i] = a[N*i+k];
			v[i] = x[i];
			//printf(" %f, %f",v[i],x[i]);
			//printf("\n");
		}
		v[k] += sign(x[k]) * sqrt(dot(x, x, M, k));
		//printf("vk %f",v[k]);
		//printf("\n");
		temp = sqrt(dot(v, v, M, k));
		for (i=k; i<M; i++)
		{
			v[i] = v[i] / temp;
			//printf(" v %f",v[i]);
			//printf("\n");
			V[i*N+k] = v[i];
		}
		//printf("\n");
		//print_matrix(V, M, N);

		for (j=k; j<N; j++)
		{
			va[j] = 0.0;
			for (i=k; i<M; i++)
			va[j] += v[i] * a[i*N+j];
			//printf(" %f",va[j]);
			//printf("\n");
		}
		for (i=k; i<M; i++)
		{
			for (j=k; j<N; j++)
			a[i*N+j] = a[i*N+j] - 2 * v[i] * va[j];
		}
	}


	/*
	//1 to n to make Q*
	for(j=0; j<M; j++)
	{
		for (k=0; k<N; k++)
		{
			temp1 = 0.0;
                	for (i=k; i<M; i++)
			temp1 += V[i*N+k] * b[i*M+j];

                        for (i=k; i<M; i++)
			{
                        b[i*M+j] = b[i*M+j] - 2 * V[i*N+k] * temp1;
			//printf(" %f, %d", b[i*M+j], j);
                        //printf("\n");
			}
			//printf("\n");
		}

	}
	*/

        //n to 1 to make Q
        for(j=M-1; j>-1; j--)
        {
                for (k=N-1; k>-1; k--)
                {
                        temp1 = 0.0;
                        for (i=k; i<M; i++)
                        temp1 += V[i*N+k] * b[i*M+j];

                        for (i=k; i<M; i++)
                        {
                        b[i*M+j] = b[i*M+j] - 2 * V[i*N+k] * temp1;
                        //printf(" %f, %d", b[i*M+j], j);
                        //printf("\n");
                        }
                        //printf("\n");
                }

        }


	tran_matrix(b, M, M, bt);
	printf(" Q : \n");
	//print_matrix(bt, M, M);
	print_matrix(b, M, M);

	printf(" R : \n");
	print_matrix(a, M, N);

	printf(" Q*R : \n");
	//matrix_mult(bt, a, qr, M, M, N);
	matrix_mult(b, a, qr, M, M, N);

	printf(" error : %e \n", error(qr, A, M*N));

	return 0;
}



double dot(double *x, double *v, int N, int k)
{
	int m;
	double dot = 0.0;
	for (m=k; m<N; m++)	dot += x[m] * v[m];
	return dot;
}

void initial(double *a, double *r, int M, int N)
{
	int i;
	for (i=0; i<M*N; i++)
	{
		a[i] = 1.0 * (i+1);
		r[i] = 0.0;
	}
}

void print_matrix(double *a, int M, int N)
{
	int i, j;
	for (i=0; i<M; i++)
	{
		for (j=0; j<N; j++)	printf(" %f ",a[N*i+j]);
		printf("\n");
	}
	printf("\n");
}

double sign(double x)
{
	if (x>=0)	return 1;
	else	return -1;
}

void tran_matrix(double *a, int M, int N, double *b)
{
	int i, j;
	for (i=0; i<M; i++)
		for (j=0; j<N; j++)
			b[i*N+j] = a[j*M+i];
}

void matrix_mult(double *v, double *a, double *va, int k, int M, int N)
{
        int i, j, m;
        for (i=0; i<k; i++)
        {
                for (j=0; j<N; j++)
                {
                        for (m=0; m<M; m++)
                        va[i*N+j] += v[i*M+m] * a[m*N+j];

                        printf(" %f ", va[i*N+j]);
                }
                printf("\n");
        }
        printf("\n");
}

double error(double *x, double *y, int N)
{
        int i;
        double e, temp;
        e = 0.0;
        for (i=0; i<N; i++)
        {
                temp = fabs(x[i] - y[i]);
                if (temp > e)   e = temp;
        }
        return e;
}

