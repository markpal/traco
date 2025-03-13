if (N2 >= 1 && N3 >= 2)
  for (c0 = 0; c0 <= (N3 - 2) / 16 + 1; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 2, 16); c1 += 1) {
        for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
          for (c9 = 1; c9 <= min(16, N2); c9 += 1)
            for (c11 = 16 * c0 - 14; c11 <= min(16 * c0 + 1, N3); c11 += 1)
              tmor[c9][c7]=tmor[c9][c7]+qbnew[c11-1][c9][1]*temp[c11][c7];
        for (c3 = 1; c3 <= floord(N2 - 1, 16); c3 += 1)
          for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
            for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
              for (c11 = 16 * c0 + 2; c11 <= min(N3, 16 * c0 + 17); c11 += 1)
                tmor[c9][c7]=tmor[c9][c7]+qbnew[c11-1][c9][1]*temp[c11][c7];
      }
    } else
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 2, 16); c1 += 1) {
        for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
          tmor[1][c7]=tmor[1][c7]+temp[1][c7];
        if (N3 >= 18)
          for (c3 = 1; c3 <= floord(N2 - 1, 16); c3 += 1)
            for (c7 = 16 * c1 + 2; c7 <= min(N1, 16 * c1 + 17); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 2; c11 <= 17; c11 += 1)
                  tmor[c9][c7]=tmor[c9][c7]+qbnew[c11-1][c9][1]*temp[c11][c7];
      }


