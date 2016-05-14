/******************************************************************
*		Modified Gram-Schmidt in Lioyd
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void initial(double *a, double *r, int N);
double dot_in_matrix(double *q, double *v, int N, int i, int j);
void print_matrix(double *q, int N);
void matrix_mult(double *q, double *r, double*aq, int N);


int main()
{
	printf("\n");
	int N, i, j, k;
	printf(" Input size N = ");
	scanf("%d", &N);
	printf(" N = %d\n\n", N);

	double *a, *q, *r, *v, *n, *aq;
	a = (double *) malloc(N*N*sizeof(double));
	q = (double *) malloc(N*N*sizeof(double));
	v = (double *) malloc(N*N*sizeof(double));
	r = (double *) malloc(N*N*sizeof(double));
	aq = (double *) malloc(N*N*sizeof(double));

	//create the matrix
	initial(a, r, N);
	printf(" input : \n");
	print_matrix(a, N);

	//modified Gram-Schmidt
	for (i=0; i<N; i++)
	{
		for(k=0; k<N; k++)	v[i+k*N] = a[i+k*N];
	}

	for (i=0; i<N; i++)
	{
		r[i*N+i] = sqrt(dot_in_matrix(v, v, N, i, i));
		for (k=0; k<N; k++)
		q[i+k*N] = v[i+k*N] / r[i*N+i];

		for (j=i+1; j<N; j++)
		{
			r[i*N+j] = dot_in_matrix(q, v, N, i, j);

			for (k=0; k<N; k++)
			v[j+k*N] = v[j+k*N] - r[i*N+j] * q[i+k*N];
		}
	}

	//print result
	printf(" Q : \n");
	print_matrix(q, N);

	printf(" r : \n");
	print_matrix(r, N);

	//matrix_mult
	printf(" Q * r : \n");
	matrix_mult(q, r, aq, N);

	//error
	double e, temp;
	e = 0.0;

	for (i=0; i<N*N; i++)
	{
		temp = fabs(aq[i] - a[i]);
		if (temp > e)	e = temp;
	}

	//e = log10(e);

	printf("\n");
	printf(" The max error between Q * r and a : \n");
	printf(" error = %f \n", e);

	return 0;
}

void initial(double *a, double *r, int N)
{
	int i;

	for (i=0; i<N*N; i++)
	{
		a[i] = 1.0*i;
		r[i] = 0.0;
	}
}

double dot_in_matrix(double *q, double *v, int N, int i, int j)
{
	int k;
	double dot = 0.0;
	//vector save in row of matrix
	for (k=0; k<N; k++)	dot += q[k*N+i] * v[k*N+j];
	return dot;
}

void print_matrix(double *q, int N)
{
	int i, j;
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)	printf(" %f ",q[N*i+j]);
		printf("\n");
	}
	printf("\n");
}

void matrix_mult(double *q, double *r, double *aq, int N)
{
	int i, j, k;
        for(i=0; i<N;i++)
        {
                for(j=0; j<N; j++)
                {
                        for(k=0; k<N; k++)
			aq[i*N+j] += q[i*N+k] * r[k*N+j];

                        printf(" %f ", aq[i*N+j]);
                }
                printf("\n");
        }

}
