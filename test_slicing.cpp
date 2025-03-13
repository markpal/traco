if (N >= 2)
#pragma omp parallel for
  for (c0 = 0; c0 < N; c0 += 1)
    for (c3 = 0; c3 < N; c3 += 1)
      if (c3 >= 0 && N >= 2 && N >= c3 + 1)
        for (c3_0 = 0; c3_0 < N; c3_0 += 1)
          for (c8 = 0; c8 < N; c8 += 1)
            a[c3][c8]=a[c3][c8-1];
      
