for (c1 = 0; c1 <= floord(P - 2, 16); c1 += 1) {
  sum=0;
  for (c2 = max(1, c1 + floord(-N + 1, 16) + 2); c2 <= 2; c2 += 1) {
    if (c2 == 2) {
      for (c3 = max(max(0, -c1 + floord(N - 1, 16)), floord(-P + N, 16) + 1); c3 <= -c1 + (N + 14) / 16; c3 += 1)
        for (c5 = max(16 * c1, N - 16 * c3 - 1); c5 <= min(min(P - 2, 16 * c1 + 15), N - 16 * c3 + 14); c5 += 1)
          autocorr[c5]=sum;
    } else
      for (c3 = 0; c3 <= -c1 + (N - 2) / 16; c3 += 1)
        for (c7 = 16 * c3; c7 <= min(N - 16 * c1 - 2, 16 * c3 + 15); c7 += 1)
          sum+=signal[c7]*signal[c7+16*c1];
  }
}
