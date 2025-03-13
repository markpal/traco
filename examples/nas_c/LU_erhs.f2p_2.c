int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  zeta =  dble[k-1]  / ( nz - 1 );
  for(j = 1; j <= N2; j++){
    eta =  dble[j-1]  / ( ny0 - 1 );
    for(i = 1; i <= N3; i++){
      xi =  dble[i-1]  / ( nx0 - 1 );
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] =  ce[m][1] + (ce[m][2] + (ce[m][5] + (ce[m][8] +  ce[m][11] * xi) * xi) * xi) * xi + (ce[m][3] + (ce[m][6] + (ce[m][9] +  ce[m][12] * eta) * eta) * eta) * eta + (ce[m][4] + (ce[m][7] + (ce[m][10] +  ce[m][13] * zeta) * zeta) * zeta) * zeta;
      }
    }
  }
}


#pragma endscop
}