for (i = 1; i < ni; i++){
    for (c0 = 0; c0 <= (i - 1) / 16; c0 += 1) {
#pragma omp parallel for
      for (c2 = 0; c2 < i / 16; c2 += 1)
        for (c6 = 16 * c2; c6 <= 16 * c2 + 15; c6 += 1)
          if (c0 >= 1) {
            for (c8 = 16 * c0; c8 <= min(16 * c0 + 15, i - 1); c8 += 1)
              B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
          } else
            for (c8 = 0; c8 <= 15; c8 += 1)
              B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
      if (c0 == 0 && i >= 17) {
        for (c2 = i / 16 + 1; c2 <= floord(ni - 1, 16); c2 += 1)
          for (c6 = 16 * c2; c6 <= min(ni - 1, 16 * c2 + 15); c6 += 1)
            for (c8 = 0; c8 <= 15; c8 += 1)
              B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
      } else if (c0 >= 1)
        for (c2 = i / 16 + 1; c2 <= floord(ni - 1, 16); c2 += 1)
          for (c6 = 16 * c2; c6 <= min(ni - 1, 16 * c2 + 15); c6 += 1)
            for (c8 = 16 * c0; c8 <= min(i - 1, 16 * c0 + 15); c8 += 1)
              B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
    }
  for (c0 = max(-floord(i, 16) + floord(-floord(i, 16), 7) + 3, floord(i - 1, 16) + 1); c0 <= min(2 * floord(i, 16) + 1, floord(i - 1, 8) + 1); c0 += 1)
#pragma omp parallel for
    for (c6 = -(i % 16) + i; c6 <= min(i, i + i / 16 - (-i + 16 * c0) / 16 - 1); c6 += 1)
      for (c8 = -((-i + 16 * c0) % 16) - i + 16 * c0; c8 <= min(-((-i + 16 * c0) % 16) - i + 16 * c0 + 15, i - 1); c8 += 1)
        B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
  if (i >= 16 * floord(i, 16) + 1 && i >= 16)
    if ((i + 1) % 16 >= 2 && ni >= i + 2) {
      for (c8 = -((i + 1) % 16) + i + 1; c8 < i; c8 += 1)
        B[i][i]+=alpha*A[i][c8]*B[i][c8];
      for (c6 = i + 1; c6 <= min(ni - 1, -((i + 1) % 16) + i + 16); c6 += 1)
        for (c8 = 0; c8 < i; c8 += 1)
          B[i][c6]+=alpha*A[i][c8]*B[c6][c8];
    } else {
      if (ni == i + 1)
        for (c8 = -((i + 1) % 16) + i + 1; c8 < i; c8 += 1)
          B[i][i]+=alpha*A[i][c8]*B[i][c8];
      if ((i - 15) % 16 == 0)
        for (c8 = i - 15; c8 < i; c8 += 1)
          B[i][i]+=alpha*A[i][c8]*B[i][c8];
    }
}
}

