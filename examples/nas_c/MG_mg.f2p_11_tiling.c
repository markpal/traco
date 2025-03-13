#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 2, 16); c1 += 1)
    for (c2 = 16 * c0 + 2; c2 <= min(N1, 16 * c0 + 17); c2 += 1)
      for (c3 = 16 * c1 + 2; c3 <= min(N2, 16 * c1 + 17); c3 += 1) {
        u[1][c3][c2]=u[n1-1][c3][c2];
        u[n1][c3][c2]=u[2][c3][c2];
      }
