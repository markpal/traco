int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      r[i][j][k]=visc*(tm1[i][j][k]*g4m1_s[i][j][k][sizei]+ tm2[i][j][k]*g5m1_s[i][j][k][sizei]+ r[i][j][k]*g6m1_s[i][j][k][sizei])+ bm1_s[i][j][k][sizei]*rdtime*u[i][j][k];
    }
  }
}


#pragma endscop
}