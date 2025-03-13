#pragma omp parallel for
for( c1 = 0; c1 <= floord(N - 1, 8); c1 += 1)
  for( c3 = max(0, c1 - (N + 15) / 16 + 1); c3 <= min(c1, (N - 1) / 16); c3 += 1)
    for( c5 = 16 * c1 - 16 * c3; c5 <= min(N - 1, 16 * c1 - 16 * c3 + 15); c5 += 1)
      for( c7 = 16 * c3; c7 <= min(N - 1, 16 * c3 + 15); c7 += 1)
        a[c5][c7] = a[c5][c7-1];

