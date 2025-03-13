#pragma scop
for(i=0; i<=2*n; i++)
 for(j=0; j<=m; j++)
   a[i][j] = a[2*n-i][j+m]+a[i][i-1];
#pragma endscop
