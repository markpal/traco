/*  */
/* This file is part of the Bones source-to-source compiler examples. The C-code */
/* is largely identical in terms of functionality and variable naming to the code */
/* found in PolyBenchC version 3.2. For more information on PolyBench/C or Bones */
/* please use the contact information below. */
/*  */
/* == More information on PolyBenchC */
/* Contact............Louis-Noel Pouchet <pouchet@cse.ohio-state.edu> */
/* Web address........http:polybench.sourceforge.net */
/*  */
/* == More information on Bones */
/* Contact............Cedric Nugteren <c.nugteren@tue.nl> */
/* Web address........http:parse.ele.tue.nlbones */
/*  */
/* == File information */
/* Filename...........benchmarksyr2k.c */
/* Author.............Cedric Nugteren */
/* Last modified on...03-April-2012 */
/*  */
#include "/home/marek/issf/examples/traco/other/cetus/common.h"
#include "/home/marek/issf/examples/traco/other/cetus/looplib_a.h"
/* This is 'syr2k', an algorithm for symmetric rank-2k operations */
int main(void )
{
	int i, j, k;
	/* Declare arrays on the stack */
	float * * A = ReserveMemoryandClear(1024, 1024);
	float * * B = ReserveMemoryandClear(1024, 1024);
	float * * C = ReserveMemoryandClear(1024, 1024);
	/* Set the constants */
	int alpha = 32412;
	int beta = 2123;
	/* Set the input data */
	int _ret_val_0;
	#pragma cetus private(i, j) 
	#pragma loop name main#0 
	#pragma cetus parallel 
	#pragma omp parallel for private(i, j)
	for (i=0; i<1024; i ++ )
	{
		#pragma cetus private(j) 
		#pragma loop name main#0#0 
		for (j=0; j<1024; j ++ )
		{
			A[i][j]=((((float)i)*j)/1024);
			B[i][j]=((((float)i)*j)/1024);
		}
	}
	#pragma cetus private(i, j) 
	#pragma loop name main#1 
	#pragma cetus parallel 
	#pragma omp parallel for private(i, j)
	for (i=0; i<1024; i ++ )
	{
		#pragma cetus private(j) 
		#pragma loop name main#1#0 
		for (j=0; j<1024; j ++ )
		{
			C[i][j]=((((float)i)*j)/1024);
		}
	}
	#pragma cetus private(i, j, k) 
	#pragma loop name main#2 
	#pragma cetus parallel 
	#pragma omp parallel for private(i, j, k)
	for (i=0; i<1024; i ++ )
	{
		#pragma cetus private(j, k) 
		#pragma loop name main#2#0 
		for (j=0; j<1024; j ++ )
		{
			C[i][j]*=beta;
			#pragma cetus private(k) 
			#pragma loop name main#2#0#0 
			/* #pragma cetus reduction(+: C[i][j])  */
			for (k=0; k<1024; k ++ )
			{
				C[i][j]+=((alpha*A[i][k])*B[j][k]);
				C[i][j]+=((alpha*B[i][k])*A[j][k]);
			}
		}
	}
	/* Clean-up and exit the function */
	fflush(stdout);
	_ret_val_0=0;
	return _ret_val_0;
}
