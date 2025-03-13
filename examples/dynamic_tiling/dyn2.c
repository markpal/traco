for(i = 0; i < N; i++){
for( j = 0; j < N; j++) {
  if(j > i)
    A[j] = A[j] + A[i];
  if(j < i)
    A[j] = A[j] + A[i];
  }
}
