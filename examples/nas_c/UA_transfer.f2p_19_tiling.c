#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1) {
  for (c6 = 16 * c0 + 2; c6 <= min(N1, 16 * c0 + 17); c6 += 1)
    tmor[1][c6]=tmor[1][c6]+temp[1][c6];
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c4 = 0; c4 <= floord(N3 - 2, 16); c4 += 1)
      for (c6 = 16 * c0 + 2; c6 <= min(N1, 16 * c0 + 17); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1)
          for (c10 = 16 * c4 + 2; c10 <= min(N3, 16 * c4 + 17); c10 += 1)
            tmor[c8][c6]=tmor[c8][c6]+qbnew[c10-1][c8][1]*temp[c10][c6];
}
