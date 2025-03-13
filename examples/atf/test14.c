#pragma scop
for(i=1; i<=n; i++){
for(j=1; j<=i; j++)
b[j][i] = a[j][i];
for(j=i; j<=n; j++)
a[i][j] = a[j][j];
}
#pragma endscop
