if (loop >= 34 && n >= 34)
  for (c0 = 0; c0 <= (n + 2 * loop - 4) / 16; c0 += 1)
    if (n + 2 * loop >= 16 * c0 + 6) {
#pragma omp parallel for
      for (c2 = max(0, floord(-n + 16 * c0 + 1, 32) + 1); c2 <= min(min((loop - 1) / 16, c0 - 1), c0 / 2); c2 += 1)
        for (c8 = 16 * c2 + 1; c8 <= min(16 * c2 + 16, loop); c8 += 1)
          for (c10 = 1; c10 <= 5; c10 += 1) {
            for (c12 = max(16 * c0 - 16 * c2 - c8 + 2, 1); c12 <= 16 * c0 - 32 * c2; c12 += 1)
              za[c10][c12]+=za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12];
            if (n + 32 * c2 >= 16 * c0 + 18) {
              for (c12 = 16 * c0 - 32 * c2 + 1; c12 <= 16 * c0 - 16 * c2 - c8 + 17; c12 += 1)
                za[c10][c12]+=za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12];
            } else
              for (c12 = 16 * c0 - 32 * c2 + 1; c12 < n; c12 += 1)
                za[c10][c12]+=za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12];
          }
      if (c0 == 0)
        for (c8 = 1; c8 <= 16; c8 += 1)
          for (c10 = 1; c10 <= 5; c10 += 1)
            for (c12 = 1; c12 <= -c8 + 17; c12 += 1)
              za[c10][c12]+=za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12];
    } else if ((loop - 1) % 16 == 0)
#pragma omp parallel for
      for (c10 = 1; c10 <= 5; c10 += 1)
        for (c12 = -2 * loop + 16 * c0 + 3; c12 < n; c12 += 1)
          za[c10][c12]+=za[c10+1][c12]*zr[c10][c12]+za[c10-1][c12]*zb[c10][c12]+za[c10][c12+1]*zu[c10][c12]+za[c10][c12-1]*zv[c10][c12]+zz[c10][c12]-za[c10][c12];


