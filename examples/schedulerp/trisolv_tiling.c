#pragma omp parallel for
for (c1 = 0; c1 <= floord(N - 1, 16); c1 += 1)
  for (c3 = 0; c3 <= (N - 1) / 16; c3 += 1) {
    for (c5 = max(0, c3 - 1); c5 <= min(c3, floord(N - 2, 16)); c5 += 1)
      for (c7 = 16 * c1; c7 <= min(N - 1, 16 * c1 + 15); c7 += 1)
        for (c9 = max(16 * c3, 16 * c5 + 1); c9 <= min(min(N - 1, 16 * c3 + 15), 16 * c5 + 16); c9 += 1) {
          B[c9][c7]=B[c9][c7]/L[c9][c9];
          for (c11 = 16 * c3 + 1; c11 < c9; c11 += 1)
            B[c9][c7]=B[c9][c7]-L[c9][c11]*B[c11][c7];
        }
    for (c5 = 0; c5 < c3; c5 += 1)
      for (c7 = 16 * c1; c7 <= min(N - 1, 16 * c1 + 15); c7 += 1)
        for (c9 = 16 * c3; c9 <= min(N - 1, 16 * c3 + 15); c9 += 1)
          for (c11 = 16 * c5; c11 <= 16 * c5 + 15; c11 += 1)
            B[c9][c7]=B[c9][c7]-L[c9][c11]*B[c11][c7];
  }
