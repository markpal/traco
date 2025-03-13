#define N 200
#define N1 200
#define N2 200
#define N3 200
#define N4 200

#define DIM1 200
#define DIM2 200
#define DIM3 200

float u[DIM1][DIM2][DIM3], wdtdr[DIM1][DIM2], r[DIM1][DIM2][DIM3];

int main() {
int k, iz, i, j;

    for(k = 1; k <= N1; k++){
      for(iz = 1; iz <= N2; iz++){
        for(j = 1; j <= N3; j++){
          for(i = 1; i <= N4; i++){
            r[i][j][iz] = r[i][j][iz]+u[i][j][k]*wdtdr[k][iz];
          }
        }
      }
    }

    return 0;
}

