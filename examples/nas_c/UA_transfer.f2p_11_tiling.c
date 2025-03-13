#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1) {
  for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1) {
    i=1;
    tmp[i][c6]=tmor[i][c6];
  }
  for (c2 = 0; c2 <= floord(N2 - 2, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1)
        for (c8 = 16 * c2 + 2; c8 <= min(N2, 16 * c2 + 17); c8 += 1)
          for (c10 = 16 * c4 + 1; c10 <= min(N3, 16 * c4 + 16); c10 += 1)
            tmp[c8][c6]=tmp[c8][c6]+qbnew[c8-1][c10][1]*tmor[c10][c6];
}
