int main(){
#pragma scop

for(k = 0; k <= N1; k++){
  zeta = dble[k] * dnzm1;
  for(j = 0; j <= N2; j++){
    eta = dble[j] * dnym1;
    for(i = 0; i <= N3; i++){
      xi = dble[i] * dnxm1;
      for(n = 1; n <= 5; n++){
        u_exact[n] =  ce[n][1] + xi*(ce[n][2] + xi*(ce[n][5] + xi*(ce[n][8] + xi*ce[n][11]))) + eta*(ce[n][3] + eta*(ce[n][6] + eta*(ce[n][9] + eta*ce[n][12]))) + zeta*(ce[n][4] + zeta*(ce[n][7] + zeta*(ce[n][10] +  zeta*ce[n][13])));
      }
      for(m = 1; m <= 5; m++){
        add = u[m][i][j][k]-u_exact[m];
        rms[m] = rms[m] + add*add;
      }
    }
  }
}


#pragma endscop
}