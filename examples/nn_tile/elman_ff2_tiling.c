#pragma omp parallel for
for (c0 = 0; c0 <= floord(outputNeurons - 1, 16); c0 += 1) {
  for (c4 = 16 * c0; c4 <= min(outputNeurons - 1, 16 * c0 + 15); c4 += 1)
    sum[c4]=0.0;
  for (c2 = 0; c2 <= floord(hiddenNeurons - 1, 16); c2 += 1)
    for (c4 = 16 * c2; c4 <= min(hiddenNeurons - 1, 16 * c2 + 15); c4 += 1)
      for (c6 = 16 * c0; c6 <= min(outputNeurons - 1, 16 * c0 + 15); c6 += 1)
        sum[c6]+=c4den[c4]*who[c4][c6];
  if (hiddenNeurons >= 1)
    for (c4 = 16 * c0; c4 <= min(outputNeurons - 1, 16 * c0 + 15); c4 += 1) {
      sum[c4]+=who[hiddenNeurons][c4];
      actual[c4]=sum[c4];
    }
}
