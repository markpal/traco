#define N 200
#define N1 200
#define N2 200
#define N3 200

#define DIM1 200
#define DIM2 200
#define DIM3 200

float rsd[6][DIM1][DIM2][DIM3];
float u[6][DIM1][DIM2][DIM3];
float rho_i[DIM1][DIM2][DIM3];
float qs[DIM1][DIM2][DIM3];
float frct[6][DIM1][DIM2][DIM3];


int main() {
int k, m, i, j,tmp;
#pragma scop
   for(k = 1; k <= N1; k += 1)
      for(j = 1; j <= N2; j += 1)
         for(i = 1; i <= N3; i += 1) {
            for(m = 1; m <= 5; m += 1)
               rsd[m][i][j][k] = -frct[m][i][j][k];
            tmp = 1.0/u[1][i][j][k];
            rho_i[i][j][k] = tmp;
            qs[i][j][k] = 0.5*(u[2][i][j][k]*u[2][i][j][k]+u[3][i][j][k]*u[3][i][j][k]+u[4][i][j][k]*u[4][i][j][k])*tmp;
         }
#pragma endscop
return 0;
}


