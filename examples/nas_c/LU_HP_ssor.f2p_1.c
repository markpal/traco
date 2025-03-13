int main(){
#pragma scop

for(l = 1; l <= N1; l++){
  for(n = 1; n <= 5; n++){
    for(m = 1; m <= 5; m++){
      a[m][n][l] = 0.;
      b[m][n][l] = 0.;
      c[m][n][l] = 0.;
      d[m][n][l] = 0.;
    }
  }
}


#pragma endscop
}