#pragma omp parallel for
for (c1 = 0; c1 <= floord(N - K + 1, 16); c1 += 1)
  for (c3 = 0; c3 <= (N - K + 1) / 16; c3 += 1) {
    for (c9 = 16 * c1; c9 <= min(N - K + 1, 16 * c1 + 15); c9 += 1)
      for (c11 = 16 * c3; c11 <= min(N - K + 1, 16 * c3 + 15); c11 += 1)
        sum[c9][c11]=0;
    for (c5 = 0; c5 <= floord(K, 16); c5 += 1) {
      for (c7 = 0; c7 <= K / 16; c7 += 1)
        for (c9 = 16 * c1; c9 <= min(N - K + 1, 16 * c1 + 15); c9 += 1)
          for (c11 = 16 * c3; c11 <= min(N - K + 1, 16 * c3 + 15); c11 += 1)
            for (c15 = 16 * c7; c15 <= min(K, 16 * c7 + 15); c15 += 1)
              sum[c9][c11]+=input_image[c9+16*c5][c11+c15]*kernel[16*c5][c15];
      for (c9 = 16 * c1; c9 <= min(N - K + 1, 16 * c1 + 15); c9 += 1)
        for (c11 = 16 * c3; c11 <= min(N - K + 1, 16 * c3 + 15); c11 += 1)
          for (c13 = 16 * c5 + 1; c13 <= min(K, 16 * c5 + 15); c13 += 1)
            for (c15 = 0; c15 <= K; c15 += 1)
              sum[c9][c11]+=input_image[c9+c13][c11+c15]*kernel[c13][c15];
    }
    if (K >= -16)
      for (c9 = 16 * c1; c9 <= min(N - K + 1, 16 * c1 + 15); c9 += 1)
        for (c11 = 16 * c3; c11 <= min(N - K + 1, 16 * c3 + 15); c11 += 1)
          output_image[c9+dead_rows][c11+dead_cols]=(sum[c9][c11]/normal_factor];
  }
