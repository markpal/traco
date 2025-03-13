for (c0 = 0; c0 <= floord(N - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= (N - 1) / 16; c1 += 1)
    for (c2 = 16 * c0; c2 <= min(N - 1, 16 * c0 + 15); c2 += 1) {
      if (16 * c1 + 16 >= N)
        for (c3 = 16 * c0; c3 < min(c2, 16 * c1); c3 += 1)
          A[c3]=A[c3]+A[c2];
      if (c1 == c0 && c2 >= 16 * c0 + 1)
        for (c3 = 0; c3 < 16 * c0; c3 += 1)
          A[c3]=A[c3]+A[c2];
      for (c3 = 16 * c1; c3 <= min(16 * c1 + 15, N - 1); c3 += 1) {
        A[c3]=A[c3]+A[c2];
        if (c2 == 16 * c0 && c0 >= c1 + 1) {
          A[c3]=A[c3]+A[16*c0];
        } else if (c3 >= c2 && N >= 16 * c1 + 17) {
          A[c3]=A[c3]+A[c2];
        } else if (16 * c1 + 16 >= N)
          A[c3]=A[c3]+A[c2];
      }
    }
