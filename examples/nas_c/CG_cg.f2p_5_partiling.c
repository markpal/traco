for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
  for (c2 = 16 * c1 + 1; c2 <= min(N1, 16 * c1 + 16); c2 += 1)
    rowstr[c2]=0;


