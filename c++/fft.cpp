/******************************************************************
*	Computer		fft		result
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

void initial(fftw_complex *x,int N);
void print_complex_vector(fftw_complex *x,int N);

int main()
{

	printf("\n");
	int N, p, q, r;
	printf(" Input size N = 2^p * 3^q * 5^r, (p, q, r) = ");
	scanf("%d, %d, %d", &p, &q, &r);
	N = pow(2, p) * pow(3, q) * pow(5, r);

	fftw_complex *in, *out;
	fftw_plan plan;
	in = (fftw_complex *) fftw_malloc(N*sizeof(fftw_complex));
	out = (fftw_complex *) fftw_malloc(N*sizeof(fftw_complex));

	initial(in, N);

	printf(" in : \n");
	print_complex_vector(in, N);

	//fft excution
	plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);

	printf(" out : \n");
	print_complex_vector(out, N);

	return 0;
}

void initial(fftw_complex *x, int N)
{
	int i;

	for (i=0; i<N; i++)
	{
		x[i][0]=1.0*i;
		x[i][1]=0.0;
	}

	printf(" Initial success. \n");
}

void print_complex_vector(fftw_complex *x, int N)
{
	int i;

	for (i=0; i<N; i++)
	{
		if (x[i][1] >= 0.0)	printf(" [%d] = %f +%fi \n", i, x[i][0], x[i][1]);
		else printf(" [%d] = %f %fi \n", i, x[i][0], x[i][1]);
	}

	printf("\n");
}
