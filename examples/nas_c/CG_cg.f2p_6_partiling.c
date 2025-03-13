for (c0 = 0; c0 <= floord(N1 - 2, 16); c0 += 1)
#pragma omp parallel for
  for (c2 = 16 * c0 + 2; c2 <= min(N1, 16 * c0 + 17); c2 += 1)
    rowstr[c2]=rowstr[c2]+rowstr[c2-1];


