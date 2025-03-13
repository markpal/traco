#pragma scop
for(i=0; i<N; i++){
 for(j=0; j<N; j++){
  a[i][j] = a[i][j-1];
}
}
#pragma endscop
