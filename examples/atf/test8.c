#pragma scop
for(i=1; i<=10; i++)
 for(j=1; j<=10; j++)
  a[j+4][j+1] = a[i+2*j+1][i+j+3];
#pragma endscop
