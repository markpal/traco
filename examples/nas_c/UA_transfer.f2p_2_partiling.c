if (N1 >= 18)
  for (c0 = 0; c0 <= (N1 - 2) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c2 = 16 * c0 + 2; c2 <= min(N1, 16 * c0 + 17); c2 += 1)
        tmor=tmor+qbnew[c2-1][1][1]*tx[1][c2][1];
    } else
#pragma omp parallel for
      for (c2 = 2; c2 <= 17; c2 += 1)
        tmor=tmor+qbnew[c2-1][1][1]*tx[1][c2][1];


