for (c1 = 0; c1 <= floord(NPOINTS - 1, 16); c1 += 1) {
  sum=0;
  for (c3 = 0; c3 <= floord(NTAPS - 1, 16); c3 += 1) {
    for (c7 = 16 * c3; c7 <= min(NTAPS - 1, 16 * c3 + 15); c7 += 1) {
      sum=sum+input[16*c1-c7+NTAPS]*coefficient[c7];
      sum=sum+input[16*c1-c7]*coefficient[c7];
    }
    for (c5 = 16 * c1 + 1; c5 <= min(min(min(NPOINTS - 1, NTAPS - 2), 16 * c1 + 15), 16 * c3 + 14); c5 += 1) {
      if (c3 == c1)
        for (c7 = 16 * c1; c7 <= c5; c7 += 1)
          sum=sum+input[c5-c7+NTAPS]*coefficient[c7];
      for (c7 = max(16 * c3, c5 + 1); c7 <= min(NTAPS - 1, 16 * c3 + 15); c7 += 1)
        sum=sum+input[c5-c7]*coefficient[c7];
    }
    for (c5 = max(16 * c1 + 1, 16 * c3 + 15); c5 <= min(min(NPOINTS - 1, NTAPS - 2), 16 * c1 + 15); c5 += 1)
      for (c7 = 16 * c3; c7 <= 16 * c3 + 15; c7 += 1)
        sum=sum+input[c5-c7+NTAPS]*coefficient[c7];
    for (c5 = max(NTAPS - 1, 16 * c1 + 1); c5 <= min(NPOINTS - 1, 16 * c1 + 15); c5 += 1)
      for (c7 = 16 * c3; c7 <= min(NTAPS - 1, 16 * c3 + 15); c7 += 1)
        sum=sum+input[c5-c7+NTAPS]*coefficient[c7];
  }
  if (NTAPS >= -15)
    for (c5 = 16 * c1; c5 <= min(NPOINTS - 1, 16 * c1 + 15); c5 += 1)
      output[NTAPS]=sum;
}
