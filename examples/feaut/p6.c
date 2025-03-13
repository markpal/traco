#pragma scop
for(i=1; i<=n; i++)
for(j=1; j<=n; j++)
  for(k=1; k<=n; k++)
     a[i][j][k] = a[j][k][i];
     #pragma endscop