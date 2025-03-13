/*
 * file for LU_HP_rhs.f2p_1.c
 */
float rsd[6][200][200][200];
float u[6][200][200][200];
float rho_i[200][200][200];
float qs[200][200][200];
float frct[6][200][200][200];


int main();
int main()
{
   int k, m, i, j, tmp;

#pragma omp parallel for private(j, i, tmp, m)
   for(k = 1; k <= 200; k += 1)
      for(j = 1; j <= 200; j += 1)
         for(i = 1; i <= 200; i += 1) {
            for(m = 1; m <= 5; m += 1)
               rsd[m][i][j][k] = -frct[m][i][j][k];
            tmp = 1.0/u[1][i][j][k];
            rho_i[i][j][k] = tmp;
            qs[i][j][k] = 0.5*(u[2][i][j][k]*u[2][i][j][k]+u[3][i][j][k]*u[3][i][j][k]+u[4][i][j][k]*u[4][i][j][k])*tmp;
         }

   return 0;
}
