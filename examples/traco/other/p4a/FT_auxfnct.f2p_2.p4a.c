/*
 * file for FT_auxfnct.f2p_2.c
 */
float x[200][200][200], y[200][200][200], twiddle[200][200][200];



int main();
int main()
{
   int k, i, j;
   
   
#pragma omp parallel for private(k, j)
   for(i = 1; i <= 200; i += 1)
      for(k = 1; k <= 200; k += 1)
         for(j = 1; j <= 200; j += 1) {
            y[j][k][i] = y[j][k][i]*twiddle[j][k][i];
            x[j][k][i] = y[j][k][i];
         }
   return 0;
}
