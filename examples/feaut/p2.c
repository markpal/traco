#pragma scop
for(i=0; i<=m; i++)
 for(j=0; j<=2*n; j++)
   a[i][j] = a[i][2*n-j]+a[i-1][j+2];
#pragma endscop
