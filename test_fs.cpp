if (N >= 2)
  for (c0 = 0; c0 < N; c0 += 1)
#pragma omp parallel for
    for (c2 = 0; c2 < N; c2 += 1)
      for (c6 = 0; c6 < N; c6 += 1)
        for (c8 = 0; c8 < N; c8 += 1)
          a[c8][c6]=a[c8][c6-1];
