#pragma omp parallel for
for (c0 = 0; c0 <= floord(hiddenNeurons - 1, 16); c0 += 1) {
  for (c4 = 16 * c0; c4 <= min(hiddenNeurons - 1, 16 * c0 + 15); c4 += 1)
    sum[c4]=0.0;
  for (c2 = 0; c2 <= floord(inputNeurons - 1, 16); c2 += 1)
    for (c4 = 16 * c0; c4 <= min(hiddenNeurons - 1, 16 * c0 + 15); c4 += 1)
      for (c6 = 16 * c2; c6 <= min(inputNeurons - 1, 16 * c2 + 15); c6 += 1)
        sum[c4]+=inputs[c6]*wih[c6][c4];
  for (c2 = 0; c2 <= floord(contextNeurons - 1, 16); c2 += 1)
    for (c4 = 16 * c0; c4 <= min(hiddenNeurons - 1, 16 * c0 + 15); c4 += 1)
      for (c6 = 16 * c2; c6 <= min(contextNeurons - 1, 16 * c2 + 15); c6 += 1)
        sum[c4]+=context[c6]*wch[c6][c4];
  if (inputNeurons >= 1)
    for (c4 = 16 * c0; c4 <= min(hiddenNeurons - 1, 16 * c0 + 15); c4 += 1) {
      sum[c4]+=wih[inputNeurons][c4];
      sum[c4]+=wch[contextNeurons][c4];
      hidden[c4]=sum[c4];
    }
}
