int main(){
#pragma scop

for(nn2 = N1; nn2 <= N2; nn2++){
  for(nn1 = N3; nn1 <= N4; nn1++){
    for(j = N5; j <= N6; j++){
      for(i = N7; i <= N8; i++){
        imor=idmo[i][j][nn1][nn2][iside][iel];
        temp=anc1* pcmor_nc1[i][j][nn1][nn2][isize] + ac*  pcmor_c[i][j][isize+1]+  anc0*  pcmor_nc0[i][j][nn1][nn2][isize]+ anc2*pcmor_nc2[i][j][nn1][nn2][isize];
        dpcmor[imor]=1/temp;
      }
    }
  }
}


#pragma endscop
}