if (NMAX >= 34)
  for (c0 = 0; c0 <= (NMAX - 1) / 16 + 1; c0 += 1)
#pragma omp parallel for
    for (c2 = 0; c2 <= (NMAX - 1) / 16; c2 += 1)
      if (16 * c0 >= NMAX + 14) {
        for (c6 = 0; c6 < c0 - 1; c6 += 1)
          for (c8 = 16 * c2; c8 <= min(NMAX - 1, 16 * c2 + 15); c8 += 1)
            for (c10 = 16 * c0 - 16; c10 < NMAX; c10 += 1)
              for (c12 = 16 * c6; c12 <= min(16 * c6 + 15, c10 - 2); c12 += 1)
                c[c8][c12]+=a[c10][c12]*b[c8][c10];
      } else if (c0 >= 1) {
        for (c4 = c0 - 1; c4 <= (NMAX - 1) / 16; c4 += 1) {
          for (c8 = 16 * c2; c8 <= min(16 * c2 + 15, NMAX - 1); c8 += 1)
            for (c10 = max(16 * c4, 16 * c0 - 14); c10 <= min(min(NMAX - 1, 16 * c0 + 1), 16 * c4 + 15); c10 += 1) {
              c[c8][c10]+=a[c10][c10]*b[c8][c10];
              if (c4 + 1 == c0)
                for (c12 = 16 * c0 - 14; c12 < c10 - 1; c12 += 1)
                  c[c8][c12]+=a[c10][c12]*b[c8][c10];
            }
          if (c4 + 1 == c0)
            for (c6 = 0; c6 < c0 - 1; c6 += 1)
              for (c8 = 16 * c2; c8 <= min(NMAX - 1, 16 * c2 + 15); c8 += 1)
                for (c10 = 16 * c0 - 16; c10 < min(16 * c0, NMAX); c10 += 1)
                  for (c12 = 16 * c6; c12 <= min(c10 - 2, 16 * c6 + 15); c12 += 1)
                    c[c8][c12]+=a[c10][c12]*b[c8][c10];
          for (c8 = 16 * c2; c8 <= min(NMAX - 1, 16 * c2 + 15); c8 += 1)
            for (c10 = max(16 * c0 + 2, 16 * c4); c10 <= min(NMAX - 1, 16 * c4 + 15); c10 += 1)
              for (c12 = 16 * c0; c12 <= min(16 * c0 + 15, c10 - 2); c12 += 1)
                c[c8][c10]+=a[c10][c10]*b[c8][c10];
        }
      } else
        for (c4 = 0; c4 <= (NMAX - 1) / 16; c4 += 1)
          for (c8 = 16 * c2; c8 <= min(16 * c2 + 15, NMAX - 1); c8 += 1)
            for (c10 = max(2, 16 * c4); c10 <= min(16 * c4 + 15, NMAX - 1); c10 += 1)
              for (c12 = 0; c12 <= min(c10 - 2, 15); c12 += 1)
                c[c8][c10]+=a[c10][c10]*b[c8][c10];


