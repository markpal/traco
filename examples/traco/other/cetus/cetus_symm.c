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
/* Filename...........benchmarksymm.c */
/* Author.............Cedric Nugteren */
/* Last modified on...23-May-2012 */
/*  */
#include "/home/marek/issf/examples/traco/other/cetus/common.h"
#include "/home/marek/issf/examples/traco/other/cetus/looplib_a.h"
/* This is 'symm', a symmetric matrix multiplication kernel */
int main(void )
{
	int i, j, k;
	float acc[100];
	float bij;
	/* Declare arrays on the stack */
	float * * A = ReserveMemoryandClear(32, 32);
	float * * B = ReserveMemoryandClear(32, 32);
	float * * C = ReserveMemoryandClear(32, 32);
	/* Set the constants */
	float alpha = 32412;
	float beta = 2123;
	/* Set the input data */
	int _ret_val_0;
	#pragma cetus private(i, j) 
	#pragma cetus parallel 
	/*
	Disabled due to low profitability: #pragma omp parallel for private(i, j)
	*/
	for (i=0; i<32; i ++ )
	{
		#pragma cetus private(j) 
		for (j=0; j<32; j ++ )
		{
			C[i][j]=((((float)i)*j)/32);
			B[i][j]=((((float)i)*j)/32);
		}
	}
	#pragma cetus private(i, j) 
	#pragma cetus parallel 
	/*
	Disabled due to low profitability: #pragma omp parallel for private(i, j)
	*/
	for (i=0; i<32; i ++ )
	{
		#pragma cetus private(j) 
		for (j=0; j<32; j ++ )
		{
			A[i][j]=((((float)i)*j)/32);
		}
	}
	#pragma cetus private(acc, bij, i, j, k) 
	#pragma cetus parallel 
	#pragma omp parallel for private(acc, bij, i, j, k)
	for (j=0; j<32; j ++ )
	{
		#pragma cetus firstprivate(acc) 
		#pragma cetus private(bij, i, k) 
		#pragma cetus lastprivate(acc) 
		for (i=0; i<32; i ++ )
		{
			acc[j]=0;
			bij=B[i][j];
			#pragma cetus private(k) 
			for (k=0; k<(j-1); k ++ )
			{
				C[k][j]+=((alpha*A[k][i])*bij);
			}
			#pragma cetus private(k) 
			/* #pragma cetus reduction(+: acc[j])  */
			for (k=0; k<(j-1); k ++ )
			{
				acc[j]+=(B[k][j]*A[k][i]);
			}
			C[i][j]=(((beta*C[i][j])+((alpha*A[i][i])*bij))+(alpha*acc[j]));
		}
	}
	/* Clean-up and exit the function */
	fflush(stdout);
	_ret_val_0=0;
	return _ret_val_0;
}
