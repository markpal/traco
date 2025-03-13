for(i = 0; i < N; i++){
for(j = 0; j < N; j++) {
  A[j] = A[j] + B[i];
  if(i == j)
   B[i+1] = A[j];
  }
}
