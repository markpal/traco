if (N >= 1)
#pragma omp parallel for
  for (c1 = 0; c1 <= floord(M - 1, 16); c1 += 1)
    for (c3 = 0; c3 <= -c1 + (M - 1) / 16; c3 += 1)
      if (c1 >= 0 && N >= 1 && c3 >= 0) {
        for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3); c7 += 1)
          for (c9 = 16 * c3 + c7; c9 <= min(M, 16 * c3 + c7 + 15); c9 += 1)
            symmat[c9][c7]=symmat[c7][c9];
        for (c5 = 0; c5 <= floord(N - 1, 16); c5 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(16 * c1 + 16, M - 16 * c3); c7 += 1)
            for (c9 = 16 * c3 + c7; c9 <= min(M, 16 * c3 + c7 + 15); c9 += 1)
              for (c11 = 16 * c5 + 1; c11 <= min(N, 16 * c5 + 16); c11 += 1)
                symmat[c7][c9]+=data[c11][c7]*data[c11][c9];
      }
      // independent statements 
{
}


