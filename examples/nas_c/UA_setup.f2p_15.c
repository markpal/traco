int main(){
#pragma scop

for(iel = 1; iel <= N1; iel++){
  ntemp=lx1*lx1*lx1*(iel-1);
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      idel[i][j][1][iel]=ntemp+(i-1)*lx1 + (j-1)*lx1*lx1+lx1;
      idel[i][j][2][iel]=ntemp+(i-1)*lx1 + (j-1)*lx1*lx1+1;
      idel[i][j][3][iel]=ntemp+(i-1)*1 + (j-1)*lx1*lx1+lx1*(lx1-1)+1;
      idel[i][j][4][iel]=ntemp+(i-1)*1 + (j-1)*lx1*lx1+1;
      idel[i][j][5][iel]=ntemp+(i-1)*1 + (j-1)*lx1+lx1*lx1*(lx1-1)+1;
      idel[i][j][6][iel]=ntemp+(i-1)*1 + (j-1)*lx1+1;
    }
  }
}


#pragma endscop
}