#pragma scop
for(i=1; i<=n; i++)
for(j=1; j<=n; j++)
 a[i][j] = a[2*i+j][i+j];
 #pragma endscop