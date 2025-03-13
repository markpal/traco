int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  for(i = 1; i <= N2; i++){
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k]- dssp * ( 5.0*u[m][i][j][k] - 4.0*u[m][i][j][k+1] + u[m][i][j][k+2]);
    }
  }
}


#pragma endscop
}