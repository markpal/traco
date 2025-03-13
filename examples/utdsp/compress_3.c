#pragma scop
for(i=0; i<B; i++){
for(j=0; j<B; j++){
  sum=0.0;
 for(k=0; k<B; k++){
    sum+=cos1[i][k]*temp2d[k][j];
 }
 block[i][j]=sum;
}
}
#pragma endscop
