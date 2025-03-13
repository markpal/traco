#pragma scop
for(i=1; i<=100; i++)
for(j=1; j<=100; j++)
  a[i][j]=a[i][j+1]+a[i+2][j+1];
#pragma endscop
