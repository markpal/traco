float x[200][200][200], y[200][200][200], twiddle[200][200][200];
int main()
{
	int k, i, j;
	int _ret_val_0;
	#pragma cetus private(i, j, k) 
	#pragma cetus parallel 
	#pragma omp parallel for private(i, j, k)
	for (i=1; i<=200; i ++ )
	{
		#pragma cetus private(j, k) 
		for (k=1; k<=200; k ++ )
		{
			#pragma cetus private(j) 
			for (j=1; j<=200; j ++ )
			{
				y[j][k][i]=(y[j][k][i]*twiddle[j][k][i]);
				x[j][k][i]=y[j][k][i];
			}
		}
	}
	_ret_val_0=0;
	return _ret_val_0;
}
