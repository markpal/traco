/*
 * file for UA_diffuse.f2p_5.c
 */
float u[200][200][200], wdtdr[200][200], r[200][200][200];

int main();
int main()
{
   int k, iz, i, j;

   for(k = 1; k <= 200; k += 1)
#pragma omp parallel for private(j, i)
      for(iz = 1; iz <= 200; iz += 1)
         for(j = 1; j <= 200; j += 1)
            for(i = 1; i <= 200; i += 1)
               r[i][j][iz] = r[i][j][iz]+u[i][j][k]*wdtdr[k][iz];

   return 0;
}
