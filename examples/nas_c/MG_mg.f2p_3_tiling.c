#pragma omp parallel for
for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1) {
  for (c4 = N1 + 16 * c0; c4 <= min(N2, N1 + 16 * c0 + 15); c4 += 1)
    for (c6 = 1; c6 <= 3; c6 += 1)
      mi[c6][c4]=2+ng[c6][c4];
  for (c4 = N1 + 16 * c0; c4 <= min(N2, N1 + 16 * c0 + 15); c4 += 1) {
    m1[c4]=mi[1][c4];
    m2[c4]=mi[2][c4];
    m3[c4]=mi[3][c4];
  }
}
