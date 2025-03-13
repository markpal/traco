#pragma scop
for(m=4; m<D-1; m++){
 for(n=0; n<=2; n++)
    temp1 += decimated[m-1-n] * coeff[n];
  IFout[m] = temp1;
}
#pragma endscop

