#pragma scop
for(i = 1; i <= n; i++)
for(j = 1; j <= n; j++)
a[i][j] = a[i][j+1] + a[i+n-1][j];
#pragma endscop
