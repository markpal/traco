#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1) {
    for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1)
      for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1) {
        y[c8][c6][1]=x1[c8][c6][1];
        y[c8][c6][2]=0;
      }
    for (c4 = 0; c4 <= floord(N3 - 1, 16); c4 += 1)
      for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1)
          for (c10 = 16 * c4 + 1; c10 <= min(N3, 16 * c4 + 16); c10 += 1)
            y[c8][c6][2]=y[c8][c6][2]+map2[c10]*x1[c8][c6][c10];
    if (N3 >= 1)
      for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1) {
          y[c8][c6][3]=x1[c8][c6][lx1];
          y[c8][c6][4]=0;
        }
    for (c4 = 0; c4 <= floord(N4 - 1, 16); c4 += 1)
      for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1)
          for (c10 = 16 * c4 + 1; c10 <= min(N4, 16 * c4 + 16); c10 += 1)
            y[c8][c6][4]=y[c8][c6][4]+map4[c10]*x2[c8][c6][c10];
    if (N3 >= 1)
      for (c6 = 16 * c0 + 1; c6 <= min(N1, 16 * c0 + 16); c6 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(N2, 16 * c2 + 16); c8 += 1)
          y[c8][c6][lx1]=x2[c8][c6][lx1];
  }
