if (N3 >= 17)
  for (c0 = 0; c0 <= (N3 - 1) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
          for (c4 = 16 * c1 + 1; c4 <= min(N1, 16 * c1 + 16); c4 += 1)
            for (c5 = 16 * c2 + 1; c5 <= min(N2, 16 * c2 + 16); c5 += 1)
              for (c6 = 16 * c0 + 1; c6 <= min(N3, 16 * c0 + 16); c6 += 1)
                wdtdr[c4][c5]=wdtdr[c4][c5]+wxm1[c4p]*dxm1[c4p][c4]*dxm1[c4p][c5];
    } else
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
          for (c4 = 16 * c1 + 1; c4 <= min(N1, 16 * c1 + 16); c4 += 1)
            for (c5 = 16 * c2 + 1; c5 <= min(N2, 16 * c2 + 16); c5 += 1)
              for (c6 = 1; c6 <= 16; c6 += 1)
                wdtdr[c4][c5]=wdtdr[c4][c5]+wxm1[c4p]*dxm1[c4p][c4]*dxm1[c4p][c5];


