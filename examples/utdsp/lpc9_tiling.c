for (c1 = 0; c1 <= floord(D - 1, 16); c1 += 1)
  for (c2 = 0; c2 <= 2; c2 += 1) {
    if (c2 == 2) {
      for (c3 = max(1, -c1 + D / 16); c3 <= -c1 + (D - 1) / 16 + 1; c3 += 1)
        for (c5 = max(16 * c1, D - 16 * c3); c5 <= min(16 * c1 + 15, D - 16 * c3 + 15); c5 += 1)
          autoc[c5]=temp1;
    } else if (c2 == 1) {
      for (c3 = 0; c3 <= -c1 + (D - 1) / 16; c3 += 1)
        for (c7 = 16 * c3; c7 <= min(D - 16 * c1 - 1, 16 * c3 + 15); c7 += 1)
          temp1+=IFout[c7]*IFout[c7+16*c1];
    } else
      temp1=0;
  }
