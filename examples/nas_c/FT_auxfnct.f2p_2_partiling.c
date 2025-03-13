for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
  for (c2 = 0; c2 <= floord(N2 - 1, 16); c2 += 1)
    for (c3 = 0; c3 <= floord(N3 - 1, 16); c3 += 1)
      for (c4 = 16 * c1 + 1; c4 <= min(N1, 16 * c1 + 16); c4 += 1)
        for (c5 = 16 * c2 + 1; c5 <= min(N2, 16 * c2 + 16); c5 += 1)
          for (c6 = 16 * c3 + 1; c6 <= min(N3, 16 * c3 + 16); c6 += 1) {
            y[c6][c5][c4]=y[c6][c5][c4]*twc4ddc5e[c6][c5][c4];
            x[c6][c5][c4]=y[c6][c5][c4];
          }


