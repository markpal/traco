if (N2 >= N1 + 16)
  for (c0 = 0; c0 <= (-N1 + N2) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c3 = 1; c3 <= 3; c3 += 1)
        for (c4 = N1 + 16 * c0; c4 <= min(N2, N1 + 16 * c0 + 15); c4 += 1)
          ng[c3][c4]=ng[c3][c4+1]/2;
    } else
#pragma omp parallel for
      for (c3 = 1; c3 <= 3; c3 += 1)
        for (c4 = N1; c4 <= N1 + 15; c4 += 1)
          ng[c3][c4]=ng[c3][c4+1]/2;


