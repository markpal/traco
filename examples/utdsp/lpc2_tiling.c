for (c1 = 0; c1 <= floord(P - 3, 16); c1 += 1) {
  E=(1-alpha[16*c1+2-1]*alpha[16*c1+2-1])*E;
  temp3=autocorr[16*c1+2];
  for (c2 = 2; c2 <= 6; c2 += 1) {
    if (c2 >= 4 && c2 <= 5) {
      for (c3 = 0; c3 <= c1; c3 += 1)
        for (c7 = 16 * c3 + 1; c7 <= min(16 * c1 + 1, 16 * c3 + 16); c7 += 1) {
          if (c2 == 5) {
            alpha[c7]=temp_vect[c7];
          } else
            temp_vect[c7]=alpha[c7]-(alpha[16*c1+2-c7]*temp3];
        }
    } else if (c2 == 6) {
      for (c5 = 16 * c1 + 2; c5 <= min(P - 1, 16 * c1 + 17); c5 += 1)
        alpha[c5]=temp3;
    } else if (c2 == 3) {
      temp3=temp3/E;
    } else
      for (c3 = 0; c3 <= c1; c3 += 1)
        for (c7 = 16 * c3 + 1; c7 <= min(16 * c1 + 1, 16 * c3 + 16); c7 += 1)
          temp3=temp3-autocorr[16*c1+2-c7]*aplha[c7];
  }
}
