#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1)
  for (c1 = 16 * c0 + 2; c1 <= min(N1, 16 * c0 + 17); c1 += 1) {
    dummy=randc1c[start][an];
    RanStarts[c1]=start;
  }
