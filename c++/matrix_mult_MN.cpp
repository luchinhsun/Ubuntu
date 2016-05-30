#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void initial(double *a, double *r, int M, int N);
void print_matrix(double *a, int M, int N);
void matrix_mult(double *v, double *a, double *va, int M, int N, int k);

int main()
{
	printf("\n");
        int M, N, i, j, k;
        printf(" Input size M ");
        scanf("%d", &N);
        printf(" Input size N ");
        scanf("%d", &M);
	printf(" Input size k ");
        scanf("%d", &k);
        printf(" M & N & k = %d & %d & %d\n\n", M, N, k);

        double *a, *x, *v, *r, *va;
        a = (double *) malloc(M*N*sizeof(double));
        r = (double *) malloc(M*N*sizeof(double));
        v = (double *) malloc(k*M*sizeof(double));

        va = (double *) malloc(k*N*sizeof(double));

	initial(a,r,M,N);
	initial(v,r,k,M);

	print_matrix(a,M,N);
	print_matrix(v,k,M);

	matrix_mult(v, a, va, M, N, k);
	print_matrix(va, k,N);


	return 0;
}


void initial(double *a, double *r, int M, int N)
{
        int i;
        for (i=0; i<M*N; i++)
        {
                a[i] = 1.0 * i;
                r[i] = 0.0;
        }
}

void print_matrix(double *a, int M, int N)
{
        int i, j;
        for (i=0; i<M; i++)
        {
                for (j=0; j<N; j++)     printf(" %f ",a[N*i+j]);
                printf("\n");
        }
        printf("\n");
}

void matrix_mult(double *v, double *a, double *va, int M, int N, int k)
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
