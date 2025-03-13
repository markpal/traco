int main(){
#pragma scop

for(isize = 1; isize <= N1; isize++){
  temp=2*(-isize-1);
  dtemp=1/temp;
  temp1=temp*3;
  temp2=temp*2;
  for(k = 1; k <= N2; k++){
    for(j = 1; j <= N3; j++){
      for(i = 1; i <= N4; i++){
        xrm1_s[i][j][k][isize]=dtemp;
        jacm1_s[i][j][k][isize]=temp1;
        rxm1_s[i][j][k][isize]=temp2;
        g1m1_s[i][j][k][isize]=w3m1[i][j][k]*temp;
        bm1_s[i][j][k][isize]=w3m1[i][j][k]*temp1;
        g4m1_s[i][j][k][isize]=g1m1_s[i][j][k][isize]/wxm1[i];
        g5m1_s[i][j][k][isize]=g1m1_s[i][j][k][isize]/wxm1[j];
        g6m1_s[i][j][k][isize]=g1m1_s[i][j][k][isize]/wxm1[k];
      }
    }
  }
}


#pragma endscop
}