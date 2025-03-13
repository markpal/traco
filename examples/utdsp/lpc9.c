#pragma scop
for(m=0; m<D; m++){
 temp1 = 0;
for(n=0; n<D-m; m++){
  temp1 += IFout[n] * IFout[n+m];  
}
autoc[m] = temp1;
}
#pragma endscop
