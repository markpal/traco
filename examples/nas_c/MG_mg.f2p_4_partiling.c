if (N2 >= N1 + 16)
  for (c0 = 0; c0 <= (-N1 + N2) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c2 = N1 + 16 * c0; c2 <= min(N2, N1 + 16 * c0 + 15); c2 += 1)
        ir[c2]=ir[c2+1]+m1[c2+1]*m2[c2+1]*m3[c2+1];
    } else
#pragma omp parallel for
      for (c2 = N1; c2 <= N1 + 15; c2 += 1)
        ir[c2]=ir[c2+1]+m1[c2+1]*m2[c2+1]*m3[c2+1];


