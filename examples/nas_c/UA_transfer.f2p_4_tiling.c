#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1) {
  for (c4 = 16 * c0 + 1; c4 <= min(N1, 16 * c0 + 16); c4 += 1)
    temp[c4]=tx[c4][1][1];
  for (c2 = 0; c2 <= floord(N2 - 2, 16); c2 += 1)
    for (c4 = 16 * c0 + 1; c4 <= min(N1, 16 * c0 + 16); c4 += 1)
      for (c6 = 16 * c2 + 2; c6 <= min(N2, 16 * c2 + 17); c6 += 1)
        temp[c4]=temp[c4]+qbnew[c6-1][1][1]*tx[c4][c6][1];
}
