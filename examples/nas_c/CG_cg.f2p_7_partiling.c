if (N1 >= 17)
  for (c0 = 0; c0 <= (N1 - 1) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c3 = 0; c3 <= floord(-N2 + N3, 16); c3 += 1)
        for (c5 = 16 * c0 + 1; c5 <= min(N1, 16 * c0 + 16); c5 += 1)
          for (c7 = N2 + 16 * c3; c7 <= min(N3, N2 + 16 * c3 + 15); c7 += 1) {
            a[c7]=0.;
            colidx[c7]=0;
          }
    } else
#pragma omp parallel for
      for (c3 = 0; c3 <= floord(-N2 + N3, 16); c3 += 1)
        for (c5 = 1; c5 <= 16; c5 += 1)
          for (c7 = N2 + 16 * c3; c7 <= min(N3, N2 + 16 * c3 + 15); c7 += 1) {
            a[c7]=0.;
            colidx[c7]=0;
          }


