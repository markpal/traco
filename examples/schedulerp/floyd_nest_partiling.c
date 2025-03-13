for(l=0; l < N ; l++){
  if (N >= l + 1 && l >= 34)
    for (c0 = 0; c0 <= min(3, N - l + 1); c0 += 1)
      if (c0 <= 2) {
        if (N >= l + c0)
#pragma omp parallel for
          for (c2 = 0; c2 <= min(c0 + l / 16 - 1, -c0 + l / 16 + 1); c2 += 1)
            if (c0 == 2) {
              for (c4 = l / 16 + 1; c4 <= (N - 1) / 16; c4 += 1)
                for (c6 = 16 * c2; c6 <= 16 * c2 + 15; c6 += 1)
                  for (c8 = 16 * c4; c8 <= min(N - 1, 16 * c4 + 15); c8 += 1)
                    path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
            } else if (c0 == 0) {
              for (c4 = 0; c4 < l / 16; c4 += 1)
                for (c6 = 16 * c2; c6 <= 16 * c2 + 15; c6 += 1)
                  for (c8 = 16 * c4; c8 <= 16 * c4 + 15; c8 += 1)
                    path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
            } else if (l >= 16 * c2 + 16) {
              for (c6 = 16 * c2; c6 <= 16 * c2 + 15; c6 += 1)
                for (c8 = -(l % 16) + l; c8 <= min(-(l % 16) + l + 15, N - 1); c8 += 1)
                  path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
            } else
              for (c4 = 0; c4 < l / 16; c4 += 1)
                for (c6 = 16 * c2; c6 <= min(N - 1, 16 * c2 + 15); c6 += 1)
                  for (c8 = 16 * c4; c8 <= 16 * c4 + 15; c8 += 1)
                    path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
        if (c0 == 2)
#pragma omp parallel for
          for (c2 = l / 16; c2 <= (N - 1) / 16; c2 += 1)
            if (16 * c2 >= l + 1) {
              for (c4 = 0; c4 < l / 16; c4 += 1)
                for (c6 = 16 * c2; c6 <= min(16 * c2 + 15, N - 1); c6 += 1)
                  for (c8 = 16 * c4; c8 <= 16 * c4 + 15; c8 += 1)
                    path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
            } else
              for (c6 = 16 * c2; c6 <= min(N - 1, 16 * c2 + 15); c6 += 1)
                for (c8 = 16 * c2; c8 <= min(N - 1, 16 * c2 + 15); c8 += 1)
                  path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
      } else
#pragma omp parallel for
        for (c2 = l / 16; c2 <= (N - 1) / 16; c2 += 1)
          if (16 * c2 >= l + 1) {
            for (c6 = 16 * c2; c6 <= min(N - 1, 16 * c2 + 15); c6 += 1)
              for (c8 = -(l % 16) + l; c8 <= -(l % 16) + l + 15; c8 += 1)
                path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
          } else
            for (c4 = c2 + 1; c4 <= (N - 1) / 16; c4 += 1)
              for (c6 = 16 * c2; c6 <= 16 * c2 + 15; c6 += 1)
                for (c8 = 16 * c4; c8 <= min(16 * c4 + 15, N - 1); c8 += 1)
                  path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
  if (l >= 34)
#pragma omp parallel for
    for (c2 = l / 16 + 1; c2 <= floord(N - 1, 16); c2 += 1)
      for (c4 = l / 16 + 1; c4 <= (N - 1) / 16; c4 += 1)
        for (c6 = 16 * c2; c6 <= min(16 * c2 + 15, N - 1); c6 += 1)
          for (c8 = 16 * c4; c8 <= min(N - 1, 16 * c4 + 15); c8 += 1)
            path[c6][c8]=path[c6][c8]+path[c6][l]+path[l][c8]+path[c6][c8]+path[c6][l]+path[l][c8];
}


