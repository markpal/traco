#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= floord(N2 - 1, 16); c1 += 1)
    for (c2 = 0; c2 <= floord(N3 - 1, 16); c2 += 1)
      for (c3 = 16 * c0 + 1; c3 <= min(N1, 16 * c0 + 16); c3 += 1)
        for (c4 = 16 * c1 + 1; c4 <= min(N2, 16 * c1 + 16); c4 += 1)
          for (c5 = 16 * c2 + 1; c5 <= min(N3, 16 * c2 + 16); c5 += 1)
            wdtdr[c3][c4]=wdtdr[c3][c4]+wxm1[c3p]*dxm1[c3p][c3]*dxm1[c3p][c4];
