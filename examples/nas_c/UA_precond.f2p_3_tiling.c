#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 16 * c0 + 2; c2 <= min(N1, 16 * c0 + 17); c2 += 1)
      for (c3 = 16 * c1 + 1; c3 <= min(N2, 16 * c1 + 16); c3 += 1)
        tmp[c2][1]=tmp[c2][1]+qbnew[c2-1][c3][1]*tc2g[c3];
