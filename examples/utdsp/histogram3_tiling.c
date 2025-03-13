#pragma omp parallel for
for (c1 = 0; c1 <= floord(N - 1, 16); c1 += 1)
  for (c3 = 0; c3 <= (N - 1) / 16 + 1; c3 += 1)
    for (c5 = 16 * c1; c5 <= min(N - 1, 16 * c1 + 15); c5 += 1) {
      if (c3 == 0)
        ii=image[c5][0];
      for (c7 = 16 * c3; c7 <= min(N - 1, 16 * c3 + 15); c7 += 1) {
        image[c5][c7-1]=gray_level_mapping[ii];
        ii=image[c5][c7];
      }
      if (16 * c3 >= N)
        image[c5][N-1]=gray_level_mapping[ii];
    }
