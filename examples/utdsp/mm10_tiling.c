#pragma omp parallel for
for (c1 = 0; c1 <= floord(A_ROW - 1, 16); c1 += 1)
  for (c3 = 0; c3 <= floord(B_COL - 1, 16); c3 += 1) {
    for (c5 = 0; c5 <= floord(B_ROW - 1, 16) + 1; c5 += 1)
      for (c7 = 16 * c1; c7 <= min(A_ROW - 1, 16 * c1 + 15); c7 += 1)
        for (c9 = 16 * c3; c9 <= min(B_COL - 1, 16 * c3 + 15); c9 += 1) {
          if (B_ROW >= 1) {
            if (c5 == 0)
              sum=0;
            for (c11 = 16 * c5; c11 <= min(B_ROW - 1, 16 * c5 + 15); c11 += 1)
              sum=sum+a_matrix[c7][c11]+b_matrix[c11][c9];
          }
          if (16 * c5 >= B_ROW) {
            if (c5 == 0)
              sum=0;
            c_matrix[c7][c9]=sum;
          }
        }
    if (B_ROW <= -16)
      for (c7 = 16 * c1; c7 <= min(A_ROW - 1, 16 * c1 + 15); c7 += 1)
        for (c9 = 16 * c3; c9 <= min(B_COL - 1, 16 * c3 + 15); c9 += 1)
          sum=0;
  }
