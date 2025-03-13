for (c1 = 0; c1 <= 1; c1 += 1) {
  temp1=0.0;
  for (c2 = max(1, -D + c1 + floord(D, 2) + 2); c2 <= 2; c2 += 1) {
    if (c2 == 2) {
      for (c3 = max(0, -c1 + floord(D, 2)); c3 <= -c1 + (D + 1) / 2; c3 += 1)
        for (c5 = max(2 * c1, D - 2 * c3); c5 <= min(2 * c1 + 1, D - 2 * c3 + 1); c5 += 1)
          autocorr[c5]=temp1;
    } else
      for (c3 = 0; c3 < -c1 + (D + 1) / 2; c3 += 1)
        for (c7 = 2 * c3; c7 <= min(D - 2 * c1 - 1, 2 * c3 + 1); c7 += 1)
          temp1+=decimated[c7]*decimated[c7+2*c1];
  }
}
