#pragma scop
for(m=0; m<P-1; m++){
  sum= 0;
  for(n=0; n<N-m-1; n++){
     sum += signal[n] * signal[n+m];
  }
  autocorr[m] = sum;
}
#pragma endscop
