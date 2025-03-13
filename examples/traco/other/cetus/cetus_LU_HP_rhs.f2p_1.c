float rsd[6][200][200][200];
float u[6][200][200][200];
float rho_i[200][200][200];
float qs[200][200][200];
float frct[6][200][200][200];
int main()
{
	int k, m, i, j, tmp;
	int _ret_val_0;
	#pragma cetus private(i, j, k, m, tmp) 
	#pragma cetus parallel 
	#pragma omp parallel for private(i, j, k, m, tmp)
	for (k=1; k<=200; k+=1)
	{
		#pragma cetus private(i, j, m, tmp) 
		for (j=1; j<=200; j+=1)
		{
			#pragma cetus private(i, m, tmp) 
			for (i=1; i<=200; i+=1)
			{
				#pragma cetus private(m) 
				for (m=1; m<=5; m+=1)
				{
					rsd[m][i][j][k]=( - frct[m][i][j][k]);
				}
				tmp=(1.0/u[1][i][j][k]);
				rho_i[i][j][k]=tmp;
				qs[i][j][k]=((0.5*(((u[2][i][j][k]*u[2][i][j][k])+(u[3][i][j][k]*u[3][i][j][k]))+(u[4][i][j][k]*u[4][i][j][k])))*tmp);
			}
		}
	}
	_ret_val_0=0;
	return _ret_val_0;
}
