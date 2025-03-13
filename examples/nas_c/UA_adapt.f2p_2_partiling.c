if (N2 >= 17)
  for (c0 = 0; c0 <= (N2 - 1) / 16; c0 += 1)
    if (c0 >= 1) {
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N3 - 1, 16); c3 += 1)
          for (c4 = 0; c4 <= floord(N4 - 1, 16); c4 += 1)
            for (c5 = 16 * c1 + 1; c5 <= min(N1, 16 * c1 + 16); c5 += 1)
              for (c6 = 16 * c0 + 1; c6 <= min(N2, 16 * c0 + 16); c6 += 1)
                for (c7 = 16 * c3 + 1; c7 <= min(N3, 16 * c3 + 16); c7 += 1)
                  for (c8 = 16 * c4 + 1; c8 <= min(N4, 16 * c4 + 16); c8 += 1) {
                    y[c8][c5][c7]=y[c8][c5][c7]+ytwo[c8][c6][c5][1]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][1]=y1[c8][c5][c7][1]+ytwo[c8][c6][c5][3]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][2]=y1[c8][c5][c7][2]+ytwo[c8][c6][c5][2]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][3]=y1[c8][c5][c7][3]+ytwo[c8][c6][c5][4]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][4]=y1[c8][c5][c7][4]+ytwo[c8][c6][c5][1]*ixtmc2[c6][c7];
                    y1[c8][c5][c7][5]=y1[c8][c5][c7][5]+ytwo[c8][c6][c5][3]*ixtmc2[c6][c7];
                    y1[c8][c5][c7][6]=y1[c8][c5][c7][6]+ytwo[c8][c6][c5][2]*ixtmc2[c6][c7];
                    y1[c8][c5][c7][7]=y1[c8][c5][c7][7]+ytwo[c8][c6][c5][4]*ixtmc2[c6][c7];
                  }
    } else
#pragma omp parallel for
      for (c1 = 0; c1 <= floord(N1 - 1, 16); c1 += 1)
        for (c3 = 0; c3 <= floord(N3 - 1, 16); c3 += 1)
          for (c4 = 0; c4 <= floord(N4 - 1, 16); c4 += 1)
            for (c5 = 16 * c1 + 1; c5 <= min(N1, 16 * c1 + 16); c5 += 1)
              for (c6 = 1; c6 <= 16; c6 += 1)
                for (c7 = 16 * c3 + 1; c7 <= min(N3, 16 * c3 + 16); c7 += 1)
                  for (c8 = 16 * c4 + 1; c8 <= min(N4, 16 * c4 + 16); c8 += 1) {
                    y[c8][c5][c7]=y[c8][c5][c7]+ytwo[c8][c6][c5][1]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][1]=y1[c8][c5][c7][1]+ytwo[c8][c6][c5][3]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][2]=y1[c8][c5][c7][2]+ytwo[c8][c6][c5][2]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][3]=y1[c8][c5][c7][3]+ytwo[c8][c6][c5][4]*ixtmc1[c6][c7];
                    y1[c8][c5][c7][4]=y1[c8][c5][c7][4]+ytwo[c8][c6][c5][1]*ixtmc2[c6][c7];
                    y1[c8][c5][c7][5]=y1[c8][c5][c7][5]+ytwo[c8][c6][c5][3]*ixtmc2[c6][c7];
                    y1[c8][c5][c7][6]=y1[c8][c5][c7][6]+ytwo[c8][c6][c5][2]*ixtmc2[c6][c7];
                    y1[c8][c5][c7][7]=y1[c8][c5][c7][7]+ytwo[c8][c6][c5][4]*ixtmc2[c6][c7];
                  }


