#pragma scop
for(i=0; i<=2*n;i++){
a[i][0] = a[2*n-i][m];
  for(j=1; j<=m; j++){
     a[i][j] = a[i][j-1];
     }
     }
     for(i=0; i<=2*n; i++){
       for(j=1; j<=k; j++){
          a[i][j+m] = a[i-1][j+m-1];
          }
          }
          #pragma endscop