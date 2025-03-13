#pragma scop
for(i=1; i<=n; i++)
 for(j=1; j<=m; j++)
  a[i][j] = a[2*i+2*j][2*j] + a[i][j-1];
#pragma endscop
