#pragma omp parallel for
for (c1 = 0; c1 <= floord(-N1 + N2, 16); c1 += 1)
  for (c2 = 1; c2 <= 3; c2 += 1)
    for (c3 = N1 + 16 * c1; c3 <= min(N2, N1 + 16 * c1 + 15); c3 += 1)
      ng[c2][c3]=ng[c2][c3+1]/2;
