#pragma scop
  for (j1 = 1; j1 <= M; j1++) {
    for (j2 = j1; j2 <= M; j2++) {
      for (i = 1; i <= N; i++) {
        symmat[j1][j2] += data[i][j1] * data[i][j2];
      }
      symmat[j2][j1] = symmat[j1][j2];
    }
  }
#pragma endscop
