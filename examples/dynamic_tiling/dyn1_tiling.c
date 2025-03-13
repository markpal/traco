for (c0 = 0; c0 <= floord(N - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= (N - 1) / 16; c1 += 1)
    for (c2 = 16 * c0; c2 <= min(N - 1, 16 * c0 + 15); c2 += 1) {
      if (c1 == c0 && c2 >= 16 * c0 + 1)
        for (c3 = 0; c3 < 16 * c0; c3 += 1)
          A[c3]=A[c3]+B[c2];
      for (c3 = 16 * c1; c3 <= min(16 * c1 + 15, N - 1); c3 += 1) {
        if (c2 == 16 * c0 && c0 >= c1 + 1) {
          A[c3]=A[c3]+B[16*c0];
        } else if (c1 >= c0)
          A[c3]=A[c3]+B[c2];
        B[c2+1]=A[c3];
      }
    }
