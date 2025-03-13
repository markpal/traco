#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 16 * c0 + 1; c2 <= min(N1, 16 * c0 + 16); c2 += 1)
      for (c3 = 16 * c1 + 1; c3 <= min(N2, 16 * c1 + 16); c3 += 1) {
        u[c3][c2][1]=u[c3][c2][n3-1];
        u[c3][c2][n3]=u[c3][c2][2];
      }
