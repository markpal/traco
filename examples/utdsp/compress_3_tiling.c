if (B >= 1) {
  for (c1 = 0; c1 <= floord(B - 2, 16); c1 += 1) {
    if (c1 == 0)
      for (c3 = 0; c3 <= (B - 1) / 16; c3 += 1)
        for (c4 = 0; c4 <= 2; c4 += 1) {
          if (c4 == 2) {
            for (c9 = 16 * c3; c9 <= min(B - 1, 16 * c3 + 15); c9 += 1)
              block[0][c9]=sum;
          } else if (c4 == 1) {
            for (c5 = 0; c5 <= (B - 1) / 16; c5 += 1)
              for (c11 = 16 * c5; c11 <= min(B - 1, 16 * c5 + 15); c11 += 1)
                sum+=cos1[0][c11]*temp2d[c11][16*c3];
          } else
            sum=0.0;
        }
    for (c7 = 16 * c1 + 1; c7 <= min(B - 1, 16 * c1 + 15); c7 += 1)
      for (c9 = 0; c9 < B; c9 += 1)
        block[c7][c9]=sum;
  }
  if (B == 1)
    for (c4 = 0; c4 <= 2; c4 += 1) {
      if (c4 <= 1) {
        if (c4 == 1) {
          sum+=cos1[0][0]*temp2d[0][0];
        } else
          sum=0.0;
      } else
        block[0][0]=sum;
    }
}
