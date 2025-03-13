for (c0 = 0; c0 <= 1; c0 += 1)
  if (c0 == 1) {
#pragma omp parallel for
    for (c1 = 0; c1 <= floord(-N1 + N2, 16); c1 += 1)
      for (c5 = N1 + 16 * c1; c5 <= min(N2, N1 + 16 * c1 + 15); c5 += 1) {
        m1[c5]=mi[1][c5];
        m2[c5]=mi[2][c5];
        m3[c5]=mi[3][c5];
      }
  } else
#pragma omp parallel for
    for (c1 = 0; c1 <= floord(-N1 + N2, 16); c1 += 1)
      for (c5 = N1 + 16 * c1; c5 <= min(N2, N1 + 16 * c1 + 15); c5 += 1)
        for (c7 = 1; c7 <= 3; c7 += 1)
          mi[c7][c5]=2+ng[c7][c5];


