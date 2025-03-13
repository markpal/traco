for (c1 = 0; c1 <= floord(B - 1, 16); c1 += 1)
  for (c2 = 0; c2 <= 1; c2 += 1) {
    if (c2 == 1) {
      for (c5 = 16 * c1; c5 <= min(B - 1, 16 * c1 + 15); c5 += 1)
        factor2+=factor1;
    } else
      for (c3 = 0; c3 <= (B - 1) / 16; c3 += 1)
        for (c7 = 16 * c3; c7 <= min(B - 1, 16 * c3 + 15); c7 += 1) {
          temp_cos=(factor2*(2*c7+1])/B;
          cos1[16*c1][c7]=temp_cos;
          cos2[c7][16*c1]=temp_cos;
        }
  }
