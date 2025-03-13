#pragma scop
for (i = N-1; i >= 0; i--) {
 for (j = i+1; j < N; j++) {
  for (k = 0; k < j-i; k++) {
	 S[i][j] = MAX(S[i][k+i] + S[k+i+1][j], S[i][j]); 
  }
  S[i][j] = MAX(S[i][j], S[i+1][j-1]) + MAX(i,j);
 }
}
#pragma endscop
