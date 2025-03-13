#pragma omp parallel for
for (c0 = 0; c0 <= floord(N1 - 1, 16); c0 += 1)
  for (c1 = 16 * c0 + 1; c1 <= min(N1, 16 * c0 + 16); c1 += 1) {
    q[c1]=0.0;
    z[c1]=0.0;
    r[c1]=x[c1];
    p[c1]=r[c1];
  }
