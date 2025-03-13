if (N2 >= 17)
  for (c0 = 0; c0 <= (N2 - 1) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 2, 16); c1 += 1)
        for (c3 = 16 * c1 + 2; c3 <= min(N1, 16 * c1 + 17); c3 += 1)
          for (c4 = 16 * c0 + 1; c4 <= min(N2, 16 * c0 + 16); c4 += 1)
            tmp[c3][1]=tmp[c3][1]+qbnew[c3-1][c4][1]*tc3g[c4];
    } else
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 2, 16); c1 += 1)
        for (c3 = 16 * c1 + 2; c3 <= min(N1, 16 * c1 + 17); c3 += 1)
          for (c4 = 1; c4 <= 16; c4 += 1)
            tmp[c3][1]=tmp[c3][1]+qbnew[c3-1][c4][1]*tc3g[c4];


