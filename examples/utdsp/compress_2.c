#pragma scop
for(i=0; i<B; i++){
for(j=0; j<B; j++){
  sum=0.0;
 for(k=0; k<B; k++){
    sum+=block[i][k]*cos2[k][j];
 }
 temp2d[i][j]=sum;
}
}
#pragma endscop
