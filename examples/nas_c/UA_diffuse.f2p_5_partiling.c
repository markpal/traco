if (N1 >= 17)
  for (c0 = 0; c0 <= (N1 - 1) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
        for (c3 = 0; c3 <= floord(N3 - 1, 16); c3 += 1)
          for (c4 = 0; c4 <= floord(N4 - 1, 16); c4 += 1)
            for (c5 = 16 * c0 + 1; c5 <= min(N1, 16 * c0 + 16); c5 += 1)
              for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
                for (c7 = 16 * c3 + 1; c7 <= min(N3, 16 * c3 + 16); c7 += 1)
                  for (c8 = 16 * c4 + 1; c8 <= min(N4, 16 * c4 + 16); c8 += 1)
                    r[c8][c7][c8z]=r[c8][c7][c8z]+u[c8][c7][c5]*wdtdr[c5][c8z];
    } else
#pragma omp parallel for
      for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
        for (c3 = 0; c3 <= floord(N3 - 1, 16); c3 += 1)
          for (c4 = 0; c4 <= floord(N4 - 1, 16); c4 += 1)
            for (c5 = 1; c5 <= 16; c5 += 1)
              for (c6 = 16 * c2 + 1; c6 <= min(N2, 16 * c2 + 16); c6 += 1)
                for (c7 = 16 * c3 + 1; c7 <= min(N3, 16 * c3 + 16); c7 += 1)
                  for (c8 = 16 * c4 + 1; c8 <= min(N4, 16 * c4 + 16); c8 += 1)
                    r[c8][c7][c8z]=r[c8][c7][c8z]+u[c8][c7][c5]*wdtdr[c5][c8z];


