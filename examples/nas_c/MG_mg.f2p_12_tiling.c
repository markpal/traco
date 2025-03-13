#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 16 * c0 + 2; c2 <= min(N1, 16 * c0 + 17); c2 += 1) {
      if (16 * c1 + 16 >= N2)
        endfor;
      for (c3 = 16 * c1 + 1; c3 <= min(N2, 16 * c1 + 16); c3 += 1) {
        u[c3][1][c2]=u[c3][n2-1][c2];
        u[c3][n2][c2]=u[c3][2][c2];
      }
    }
