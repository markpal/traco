#pragma omp parallel for
for (c1 = 0; c1 <= floord(M - 2, 16); c1 += 1)
  for (c2 = 0; c2 <= 1; c2 += 1) {
    if (c2 == 1) {
      for (c3 = 0; c3 <= -c1 + (M - 2) / 16; c3 += 1) {
        if (N >= 1) {
          if (N >= 17)
            for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
              for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1)
                symmat[c7][c9]=0.0;
          for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
            for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1) {
              if (N <= 16)
                symmat[c7][c9]=0.0;
              symmat[c9][c7]=symmat[c7][c9];
            }
        } else
          for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
            for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1)
              symmat[c7][c9]=0.0;
        for (c5 = 0; c5 <= floord(N - 1, 16); c5 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3 - 1); c7 += 1)
            for (c9 = 16 * c3 + c7 + 1; c9 <= min(M, 16 * c3 + c7 + 16); c9 += 1)
              for (c11 = 16 * c5 + 1; c11 <= min(N, 16 * c5 + 16); c11 += 1)
                symmat[c7][c9]+=(data[c11][c7]*data[c11][c9]);
      }
    } else
      for (c7 = 16 * c1 + 1; c7 <= min(M - 1, 16 * c1 + 16); c7 += 1)
        symmat[c7][c7]=1.0;
  }
