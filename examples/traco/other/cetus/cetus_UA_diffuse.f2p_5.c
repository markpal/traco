#include <stdlib.h>
float u[200][200][200], wdtdr[200][200], r[200][200][200];
int main()
{
	int k, iz, i, j;
	int _ret_val_0;
	#pragma cetus parallel 
	#pragma cetus private(i, iz, j, k) 
	#pragma omp parallel private(i, iz, j, k)
	{
		float (* reduce)[201][201] = (float (* )[201][201])malloc(8120601*sizeof (float));
		int reduce_span_0;
		int reduce_span_1;
		int reduce_span_2;
		for (reduce_span_0=0; reduce_span_0<201; reduce_span_0 ++ )
		{
			for (reduce_span_1=0; reduce_span_1<201; reduce_span_1 ++ )
			{
				
			}
			for (reduce_span_2=0; reduce_span_2<201; reduce_span_2 ++ )
			{
				reduce[reduce_span_0][reduce_span_1][reduce_span_2]=0;
			}
		}
		#pragma cetus for  
		#pragma omp for
		for (k=1; k<=200; k ++ )
		{
			#pragma cetus private(i, iz, j) 
			for (iz=1; iz<=200; iz ++ )
			{
				#pragma cetus private(i, j) 
				for (j=1; j<=200; j ++ )
				{
					#pragma cetus private(i) 
					for (i=1; i<=200; i ++ )
					{
						reduce[i][j][iz]=(reduce[i][j][iz]+(u[i][j][k]*wdtdr[k][iz]));
					}
				}
			}
		}
		#pragma cetus critical  
		#pragma omp critical
		{
			for (reduce_span_0=0; reduce_span_0<201; reduce_span_0 ++ )
			{
				for (reduce_span_1=0; reduce_span_1<201; reduce_span_1 ++ )
				{
					
				}
				for (reduce_span_2=0; reduce_span_2<201; reduce_span_2 ++ )
				{
					r[reduce_span_0][reduce_span_1][reduce_span_2]+=reduce[reduce_span_0][reduce_span_1][reduce_span_2];
				}
			}
		}
	}
	_ret_val_0=0;
	return _ret_val_0;
}
