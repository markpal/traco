if (N2 >= 2)
  for (c0 = 0; c0 <= (N2 - 2) / 16 + 1; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c5 = 16 * c1 + 1; c5 <= min(N1, 16 * c1 + 16); c5 += 1)
          for (c7 = 16 * c0 - 14; c7 <= min(16 * c0 + 1, N2); c7 += 1)
            temp[c5]=temp[c5]+qbnew[c7-1][1][1]*tx[c5][c7][1];
    } else
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c5 = 16 * c1 + 1; c5 <= min(N1, 16 * c1 + 16); c5 += 1)
          temp[c5]=tx[c5][1][1];


