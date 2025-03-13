if (N2 >= 18)
  for (c0 = 0; c0 <= (N2 - 2) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 16 * c1 + 1; c3 <= min(N1, 16 * c1 + 16); c3 += 1)
          for (c4 = 16 * c0 + 2; c4 <= min(N2, 16 * c0 + 17); c4 += 1)
            tmor[c3][1]=tmor[c3][1]+qbnew[c4-1][c3][1]*tx[c4][1][1];
    } else
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 16 * c1 + 1; c3 <= min(N1, 16 * c1 + 16); c3 += 1)
          for (c4 = 2; c4 <= 17; c4 += 1)
            tmor[c3][1]=tmor[c3][1]+qbnew[c4-1][c3][1]*tx[c4][1][1];


