/**************************************************************
	Use fft to complex dst and idst and find the error
***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

void initial(double *in, int N);
void print_complex_vector(double *in, int N);
void dst(double *in, double *out, int N);
void idst(double *in, double *out, double *idst_out, int N);
double error(double *x, double *y, int N);


int main()
{

	printf("\n");
	int N, p, q, r;
	printf(" Input size N = 2^p * 3^q * 5^r, (p, q, r) = ");
	scanf("%d, %d, %d", &p, &q, &r);
	N = pow(2, p) * pow(3, q) * pow(5, r);
	printf(" N = %d \n\n", N);

	double *in, *out, *idst_out;
	in = (double *) malloc(N*sizeof(double));
	out = (double *) malloc(N*sizeof(double));
	idst_out = (double *) malloc(N*sizeof(double));

	initial(in, N);

	printf(" in : \n");
	print_complex_vector(in, N);

	dst(in, out, N);

	printf(" dst_out : \n");
	print_complex_vector(out, N);

	idst(in, out, idst_out, N);

	printf(" idst_out : \n");
	print_complex_vector(idst_out, N);

	printf(" The max error between input & idst(input) = %e \n", error(in, idst_out, N));
	return 0;
}

double error(double *x, double *y, int N)
{
	int i;
	double e, temp;
	e = 0.0;
	for (i=0; i<N; i++)
	{
		temp = fabs(x[i] - y[i]);
		if (temp > e)	e = temp;
	}
	return e;
}

void initial(double *in, int N)
{
	int i;

	for (i=0; i<N; i++)	in[i]=1.0*i;
}

void dst(double *in, double *out, int N)
{
	int i, L;

	//expand data size to 2*N + 2
	L = 2*N + 2;

	fftw_complex *dst_in, *dst_out;
	dst_in = (fftw_complex *) malloc(L*sizeof(fftw_complex));
	dst_out = (fftw_complex *) malloc(L*sizeof(fftw_complex));

	dst_in[0][0] = dst_in[0][1] = dst_in[N+1][0] = dst_in[N+1][1] = 0.0;
	for (i=0; i<N; i++)
	{
		dst_in[i+1][0] = in[i];
		dst_in[i+1][1] = 0.0;
		dst_in[N+i+2][0] = -1.0*in[N-1-i];
		dst_in[N+i+2][1] = 0.0;
	}

	fftw_plan plan;
	plan= fftw_plan_dft_1d(L, dst_in, dst_out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);

	for (i=0; i<N; i++)	out[i] = -1.0*dst_out[i+1][1]/2.0;

	free(dst_in);
	free(dst_out);
}

void idst(double *in, double *out, double *idst_out, int N)
{
	int i;
	dst(in, out, N);

	dst(out, idst_out, N);
	double s = 2.0/(N+1);
	for (i=0; i<N; i++)	idst_out[i] = s*idst_out[i];
}

void print_complex_vector(double *in, int N)
{
	int i;

	for (i=0; i<N; i++)	printf(" [%d] = %f \n", i, in[i]);

	printf("\n");
}
