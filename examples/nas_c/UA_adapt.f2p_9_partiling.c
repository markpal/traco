{
  if (lx1 <= 3 && N3 >= 1) {
    for (c0 = 0; c0 <= (N3 - 1) / 16 + 1; c0 += 1)
      if (c0 >= 1) {
#pragma omp parallel for
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 - 15; c11 <= min(N3, 16 * c0); c11 += 1)
                  y[c9][c7][2]=y[c9][c7][2]+map2[c11]*x1[c9][c7][c11];
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 - 15; c11 <= min(N4, 16 * c0); c11 += 1)
                  y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
            if (c0 == 1 && lx1 == 1) {
              if (N3 >= 17) {
                for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                  for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                    y[c9][c7][lx1]=x2[c9][c7][lx1];
              } else
                for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                  for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                    y[c9][c7][lx1]=x2[c9][c7][lx1];
            } else if (c0 == 1 && lx1 == 3)
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  y[c9][c7][lx1]=x2[c9][c7][lx1];
          }
      } else
#pragma omp parallel for
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1) {
                if (lx1 == 1)
                  y[c9][c7][1]=x1[c9][c7][1];
                y[c9][c7][2]=0;
              }
            if (N4 >= 1 && lx1 <= 2) {
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  y[c9][c7][4]=0;
            } else if (lx1 == 3)
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1) {
                  y[c9][c7][3]=x1[c9][c7][lx1];
                  if (N4 >= 1)
                    y[c9][c7][4]=0;
                }
          }
    if (lx1 == 2) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
          if (((N3 + 15) % 16) + N4 >= N3 + 16)
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = max(N3 + 1, 17); c11 <= min(N3 + 31, N4); c11 += 1)
                  if (((c11 + 15) % 16) + N3 + 16 >= c11 && c11 >= ((c11 + 15) % 16) + N3 + 1)
                    y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
              y[c9][c7][lx1]=x2[c9][c7][lx1];
        }
      for (c0 = (N3 - 1) / 16 + 3; c0 <= floord(N4 - 1, 16) + 1; c0 += 1)
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 - 15; c11 <= min(N4, 16 * c0); c11 += 1)
                  y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
    }
  } else if (lx1 == 4 && N3 >= 1) {
    for (c0 = 0; c0 <= min(floord(N4 - 1, 16) + 1, (N3 - 1) / 16 + 1); c0 += 1)
      if (c0 >= 1) {
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 - 15; c11 <= min(N3, 16 * c0); c11 += 1)
                  y[c9][c7][2]=y[c9][c7][2]+map2[c11]*x1[c9][c7][c11];
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 - 15; c11 <= min(N4, 16 * c0); c11 += 1)
                  y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
          }
      } else
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                y[c9][c7][2]=0;
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                y[c9][c7][4]=0;
          }
  } else if (lx1 >= 5 && N3 >= 1)
    for (c0 = 0; c0 <= (N3 - 1) / 16 + 1; c0 += 1)
      if (c0 >= 1) {
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 - 15; c11 <= min(N3, 16 * c0); c11 += 1)
                  y[c9][c7][2]=y[c9][c7][2]+map2[c11]*x1[c9][c7][c11];
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 - 15; c11 <= min(N4, 16 * c0); c11 += 1)
                  y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
          }
      } else
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                y[c9][c7][2]=0;
            if (N4 >= 1)
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  y[c9][c7][4]=0;
          }
  if (lx1 >= 3 && N3 >= 1) {
    for (c0 = (N3 - 1) / 16 + 2; c0 <= floord(N4 - 1, 16) + 1; c0 += 1)
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
              for (c11 = 16 * c0 - 15; c11 <= min(N4, 16 * c0); c11 += 1)
                y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
    if (lx1 == 4 && N4 >= 1 && N4 <= 16 && N3 <= 16)
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
              y[c9][c7][lx1]=x2[c9][c7][lx1];
    if (lx1 == 4) {
      for (c0 = max(floord(N4 - 1, 16) + 2, 0); c0 <= min(2, (N3 - 1) / 16 + 1); c0 += 1)
        if (c0 >= 1) {
          for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
            for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  for (c11 = 16 * c0 - 15; c11 <= min(16 * c0, N3); c11 += 1)
                    y[c9][c7][2]=y[c9][c7][2]+map2[c11]*x1[c9][c7][c11];
              if (c0 == 1) {
                if (N3 >= 17) {
                  for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                    for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                      y[c9][c7][lx1]=x2[c9][c7][lx1];
                } else
                  for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                    for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                      y[c9][c7][lx1]=x2[c9][c7][lx1];
              } else if (N4 >= 1)
                if (N3 >= 33) {
                  for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                    for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                      y[c9][c7][lx1]=x2[c9][c7][lx1];
                } else
                  for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                    for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                      y[c9][c7][lx1]=x2[c9][c7][lx1];
            }
        } else
          for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
            for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  y[c9][c7][2]=0;
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  y[c9][c7][4]=0;
            }
      if (N3 + 31 >= 16 * floord(N4 + 31, 16) && N4 >= 17)
        if (N3 >= ((N3 - 1) % 16) + N4 + 17) {
          for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
            for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  for (c11 = max(N4 + 1, 33); c11 <= min(N4 + 31, N3); c11 += 1)
                    if (((c11 + 15) % 16) + N4 + 16 >= c11 && c11 >= ((c11 + 15) % 16) + N4 + 1)
                      y[c9][c7][2]=y[c9][c7][2]+map2[c11]*x1[c9][c7][c11];
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  y[c9][c7][lx1]=x2[c9][c7][lx1];
            }
        } else
          for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
            for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1) {
              if (((N4 + 15) % 16) + N3 >= N4 + 16 && N4 + 31 >= ((N4 + 15) % 16) + N3)
                for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                  for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                    for (c11 = -((N3 - 1) % 16) + N3; c11 <= N3; c11 += 1)
                      y[c9][c7][2]=y[c9][c7][2]+map2[c11]*x1[c9][c7][c11];
              for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
                for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                  y[c9][c7][lx1]=x2[c9][c7][lx1];
            }
    }
  }
  if (lx1 == 4) {
    for (c0 = max(floord(N4 - 1, 16) + 3, 3); c0 <= floord(N3 - 1, 16) + 1; c0 += 1)
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
              for (c11 = 16 * c0 - 15; c11 <= min(N3, 16 * c0); c11 += 1)
                y[c9][c7][2]=y[c9][c7][2]+map2[c11]*x1[c9][c7][c11];
    if (N3 >= 1 && N4 >= 16 * floord(N3 - 1, 16) + 17)
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
              y[c9][c7][lx1]=x2[c9][c7][lx1];
  } else if (lx1 <= 1 && N3 >= 1)
    for (c0 = (N3 - 1) / 16 + 2; c0 <= floord(N4 - 1, 16) + 1; c0 += 1)
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
          for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
            for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
              for (c11 = 16 * c0 - 15; c11 <= min(N4, 16 * c0); c11 += 1)
                y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
  if (N3 <= 0 && N4 >= 17)
    for (c0 = 0; c0 <= (N4 - 1) / 16; c0 += 1)
      if (c0 >= 1) {
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 16 * c0 + 1; c11 <= min(N4, 16 * c0 + 16); c11 += 1)
                  y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
      } else
        for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
          for (c3 = 0; c3 <= floord(N2 - 1, 16); c3 += 1)
            for (c7 = 16 * c1 + 1; c7 <= min(N1, 16 * c1 + 16); c7 += 1)
              for (c9 = 16 * c3 + 1; c9 <= min(N2, 16 * c3 + 16); c9 += 1)
                for (c11 = 1; c11 <= 16; c11 += 1)
                  y[c9][c7][4]=y[c9][c7][4]+map4[c11]*x2[c9][c7][c11];
}


