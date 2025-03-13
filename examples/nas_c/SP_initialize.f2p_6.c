int main(){
#pragma scop

for(j = 0; j <= N1; j++){
  eta = dble[j] * dnym1;
  for(i = 0; i <= N2; i++){
    xi = dble[i] *dnxm1;
    for(m = 1; m <= 5; m++){
      temp[m] =  ce[m][1] + xi*(ce[m][2] + xi*(ce[m][5] + xi*(ce[m][8] + xi*ce[m][11]))) + eta*(ce[m][3] + eta*(ce[m][6] + eta*(ce[m][9] + eta*ce[m][12])))+ zeta*(ce[m][4] + zeta*(ce[m][7] + zeta*(ce[m][10] + zeta*ce[m][13])));
    }
    for(m = 1; m <= 5; m++){
      u[m][i][j][k] = temp[m];
    }
  }
}


#pragma endscop
}