#pragma omp parallel for
for (c1 = 0; c1 <= floord(NPOINTS - 1, 16); c1 += 1) {
  for (c5 = 16 * c1; c5 <= min(NPOINTS - 1, 16 * c1 + 15); c5 += 1) {
    sum=input[c5];
    if (NSECTIONS <= 0 && NSECTIONS >= -15)
      output[c5]=sum;
    for (c7 = 0; c7 <= min(15, NSECTIONS - 1); c7 += 1) {
      state_2=ernal_state[c5][c7][0];
      state_1=ernal_state[c5][c7][1];
      sum=sum-ernal_state[c5][c7][0]*coefficient[c5][c7][0]+ernal_state[c5][c7][1]*coefficient[c5][c7][1];
      ernal_state[c5][c7][0]=ernal_state[c5][c7][1];
      ernal_state[c5][c7][1]=sum;
      sum=sum+state_2*coefficient[c5][c7][2]+state_1*coefficient[c5][c7][3];
    }
  }
  for (c3 = 1; c3 <= floord(NSECTIONS - 1, 16) + 1; c3 += 1)
    for (c5 = 16 * c1; c5 <= min(NPOINTS - 1, 16 * c1 + 15); c5 += 1) {
      for (c7 = 16 * c3; c7 <= min(NSECTIONS - 1, 16 * c3 + 15); c7 += 1) {
        state_2=ernal_state[c5][c7][0];
        state_1=ernal_state[c5][c7][1];
        sum=sum-ernal_state[c5][c7][0]*coefficient[c5][c7][0]+ernal_state[c5][c7][1]*coefficient[c5][c7][1];
        ernal_state[c5][c7][0]=ernal_state[c5][c7][1];
        ernal_state[c5][c7][1]=sum;
        sum=sum+state_2*coefficient[c5][c7][2]+state_1*coefficient[c5][c7][3];
      }
      if (16 * c3 >= NSECTIONS)
        output[c5]=sum;
    }
}
