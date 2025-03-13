for (c1 = 0; c1 <= floord(D - 6, 16); c1 += 1)
  for (c2 = 0; c2 <= 1; c2 += 1)
    for (c5 = 16 * c1 + 4; c5 <= min(D - 2, 16 * c1 + 15 * c2 + 4); c5 += 1)
      for (c7 = -c2; c7 <= -3 * c2 + 2; c7 += 1) {
        if (c2 == 0 && c5 == 16 * c1 + 4) {
          temp1+=decimated[16*c1+4-1-c7]*coeff[c7];
        } else
          IFout[c5]=temp1;
      }
