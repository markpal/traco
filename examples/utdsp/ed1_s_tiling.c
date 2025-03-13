#pragma omp parallel for
for (c0 = 0; c0 <= floord(N - 1, 16); c0 += 1)
  for (c1 = 0; c1 <= (N - 1) / 16; c1 += 1)
    for (c2 = 16 * c0; c2 <= min(N - 1, 16 * c0 + 15); c2 += 1)
      for (c3 = 16 * c1; c3 <= min(N - 1, 16 * c1 + 15); c3 += 1) {
        temp1=image_buffer1[c2][c3];
        temp2=image_buffer2[c2][c3];
        temp3=temp1+temp2;
        image_buffer3[c2][c3]=temp3+T;
      }
