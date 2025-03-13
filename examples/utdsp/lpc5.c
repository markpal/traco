#pragma scop
for(m=0; m<4; m++){
  temp1 = 0.0;
  for(n=0; n<D-m; n++){  
    temp1 += decimated[n] * decimated[n+m];
  }
  autocorr[m] = temp1;
}
#pragma endscop
