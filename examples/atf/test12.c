#pragma scop
for(i = 0; i <= n; i++){
for(j = 0; j <= n; j++){
a[i][j] = a[i+1][j-1]+a[i+4][j];
}
}
#pragma endscop
