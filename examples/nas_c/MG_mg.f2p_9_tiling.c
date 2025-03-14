#pragma omp parallel for
if (N8 >= 1 && N11 >= 1) {
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1) {
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1) {
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N3 + 16 * c2 + 15, N4); c8 += 1)
            for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
      for (c4 = 0; c4 <= floord(N11 - 1, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1) {
          for (c8 = N3 + 16 * c2; c8 <= min(N3 + 16 * c2 + 15, N4); c8 += 1)
            for (c10 = 16 * c4 + 1; c10 <= min(16 * c4 + 16, N7); c10 += 1)
              u[2*c10-t1][2*c8-d2][2*c6-d3]=u[2*c10-t1][2*c8-d2][2*c6-d3]+0.5*(z[c10+1][c8][c6]+z[c10][c8][c6]);
          for (c8 = 16 * c2 + 1; c8 <= min(N8, 16 * c2 + 16); c8 += 1)
            for (c10 = 16 * c4 + 1; c10 <= min(N11, 16 * c4 + 16); c10 += 1)
              u[2*c10-t1][2*c8-t2][2*c6-d3]=u[2*c10-t1][2*c8-t2][2*c6-d3]+0.25*(z[c10+1][c8+1][c6]+z[c10+1][c8][c6]+z[c10][c8+1][c6]+z[c10][c8][c6]);
        }
      for (c4 = (N11 - 1) / 16 + 1; c4 <= floord(N7 - 1, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N3 + 16 * c2 + 15, N4); c8 += 1)
            for (c10 = 16 * c4 + 1; c10 <= min(16 * c4 + 16, N7); c10 += 1)
              u[2*c10-t1][2*c8-d2][2*c6-d3]=u[2*c10-t1][2*c8-d2][2*c6-d3]+0.5*(z[c10+1][c8][c6]+z[c10][c8][c6]);
    }
    if (N7 <= 0) {
      for (c2 = (N8 - 1) / 16 + 1; c2 <= floord(-N3 + N4, 16); c2 += 1)
        for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
          for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
            for (c8 = N3 + 16 * c2; c8 <= min(N3 + 16 * c2 + 15, N4); c8 += 1)
              for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
                u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
    } else
      for (c2 = (N8 - 1) / 16 + 1; c2 <= floord(-N3 + N4, 16); c2 += 1) {
        for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
          for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
            for (c8 = N3 + 16 * c2; c8 <= min(N3 + 16 * c2 + 15, N4); c8 += 1)
              for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
                u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
        for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
          for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
            for (c8 = N3 + 16 * c2; c8 <= min(N3 + 16 * c2 + 15, N4); c8 += 1)
              for (c10 = 16 * c4 + 1; c10 <= min(N7, 16 * c4 + 16); c10 += 1)
                u[2*c10-t1][2*c8-d2][2*c6-d3]=u[2*c10-t1][2*c8-d2][2*c6-d3]+0.5*(z[c10+1][c8][c6]+z[c10][c8][c6]);
      }
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = 16 * c2 + 1; c8 <= min(N8, 16 * c2 + 16); c8 += 1)
            for (c10 = N9 + 16 * c4; c10 <= min(N10, N9 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-t2][2*c6-d3]=u[2*c10-d1][2*c8-t2][2*c6-d3]+0.5*(z[c10][c8+1][c6]+z[c10][c8][c6]);
  }
} else if (N7 >= 1 && N9 >= N10 + 1 && N11 <= 0) {
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1)
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1) {
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
      for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = 16 * c4 + 1; c10 <= min(N7, 16 * c4 + 16); c10 += 1)
              u[2*c10-t1][2*c8-d2][2*c6-d3]=u[2*c10-t1][2*c8-d2][2*c6-d3]+0.5*(z[c10+1][c8][c6]+z[c10][c8][c6]);
    }
} else if (N7 <= 0 && N9 >= N10 + 1 && N11 <= 0) {
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1)
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
} else if (N10 >= N9 && N8 >= 1 && N11 <= 0) {
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1) {
    if (N7 <= 0) {
      for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
        for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
          for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
            for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
              for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
                u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
    } else
      for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1) {
        for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
          for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
            for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
              for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
                u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
        for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
          for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
            for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
              for (c10 = 16 * c4 + 1; c10 <= min(N7, 16 * c4 + 16); c10 += 1)
                u[2*c10-t1][2*c8-d2][2*c6-d3]=u[2*c10-t1][2*c8-d2][2*c6-d3]+0.5*(z[c10+1][c8][c6]+z[c10][c8][c6]);
      }
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = 16 * c2 + 1; c8 <= min(N8, 16 * c2 + 16); c8 += 1)
            for (c10 = N9 + 16 * c4; c10 <= min(N10, N9 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-t2][2*c6-d3]=u[2*c10-d1][2*c8-t2][2*c6-d3]+0.5*(z[c10][c8+1][c6]+z[c10][c8][c6]);
  }
} else if (N7 >= 1 && N11 >= 1) {
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1)
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1) {
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
      for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = 16 * c4 + 1; c10 <= min(N7, 16 * c4 + 16); c10 += 1)
              u[2*c10-t1][2*c8-d2][2*c6-d3]=u[2*c10-t1][2*c8-d2][2*c6-d3]+0.5*(z[c10+1][c8][c6]+z[c10][c8][c6]);
    }
} else if (N7 <= 0 && N11 >= 1) {
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1)
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
} else if (N7 >= 1) {
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1)
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1) {
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
      for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = 16 * c4 + 1; c10 <= min(N7, 16 * c4 + 16); c10 += 1)
              u[2*c10-t1][2*c8-d2][2*c6-d3]=u[2*c10-t1][2*c8-d2][2*c6-d3]+0.5*(z[c10+1][c8][c6]+z[c10][c8][c6]);
    }
} else
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1)
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N1 + 16 * c0; c6 <= min(N2, N1 + 16 * c0 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N5 + 16 * c4; c10 <= min(N6, N5 + 16 * c4 + 15); c10 += 1)
              u[2*c10-d1][2*c8-d2][2*c6-d3]=u[2*c10-d1][2*c8-d2][2*c6-d3]+z[c10][c8][c6];
