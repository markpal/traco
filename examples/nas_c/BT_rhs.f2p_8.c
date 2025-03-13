int main(){
#pragma scop

for(k = 3; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      for(m = 1; m <= 5; m++){
        rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * (  u[m][i][j][k-2] - 4.0*u[m][i][j][k-1] + 6.0*u[m][i][j][k] - 4.0*u[m][i][j][k+1] + u[m][i][j][k+2] );
      }
    }
  }
}


#pragma endscop
}