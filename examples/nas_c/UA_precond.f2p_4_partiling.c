if (N3 >= 17)
  for (c0 = 0; c0 <= (N3 - 1) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 2, 16); c3 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 2; c9 <= min(N2, 16 * c3 + 17); c9 += 1)
              for (c11 = 16 * c0 + 1; c11 <= min(N3, 16 * c0 + 16); c11 += 1)
                tcpre[c7][c9]=tcpre[c7][c9]+qbnew[c9-1][c11][1]*tmp[c7][c11];
    } else
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 2, 16); c3 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 2; c9 <= min(N2, 16 * c3 + 17); c9 += 1)
              for (c11 = 1; c11 <= 16; c11 += 1)
                tcpre[c7][c9]=tcpre[c7][c9]+qbnew[c9-1][c11][1]*tmp[c7][c11];


