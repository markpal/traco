int main(){
#pragma scop

for(ie = 1; ie <= N1; ie++){
  for(k = 1; k <= N2; k++){
    for(j = 1; j <= N3; j++){
      for(i = 1; i <= N4; i++){
        pdiff[i][j][k][ie] = dpcelm[i][j][k][ie]*trhs[i][j][k][ie];
        rho1            = rho1 + trhs[i][j][k][ie]*pdiff[i][j][k][ie]*   tmult[i][j][k][ie];
      }
    }
  }
}


#pragma endscop
}