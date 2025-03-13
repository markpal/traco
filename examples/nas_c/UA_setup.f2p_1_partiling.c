for (c0 = 0; c0 <= 1; c0 += 1)
#pragma omp parallel for
  for (c1 = c0; c1 < c0 + floord(-N1 + 2, 16); c1 += 1)
    for (c2 = N1 + 16 * c1; c2 <= min(N1 + 16 * c1 + 15, c0 + 1); c2 += 1)
      if (c0 == 1) {
        xc[c2][1]=0;
      } else
        xc[c2+1][1]=1;


