#define N 200
#define N1 200
#define N2 200
#define N3 200

#define DIM1 200
#define DIM2 200
#define DIM3 200

float x[DIM1][DIM2][DIM3], y[DIM1][DIM2][DIM3], twiddle[DIM1][DIM2][DIM3];



int main(){
int k, i, j;

#pragma scop
for(i = 1; i <= N1; i++){
  for(k = 1; k <= N2; k++){
    for(j = 1; j <= N3; j++){
      y[j][k][i]=y[j][k][i]*twiddle[j][k][i];
      x[j][k][i]=y[j][k][i];
    }
  }
}
#pragma endscop
return 0;
}


