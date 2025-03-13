#pragma scop
if(2*b == n+2 && n > 2){
for(k=1; k<=b; k++){
   for(i=0; i<1; i++){
     for(j=0; j<1; j++){
      det[k] = a[k][k]*a[n-k+1][n-k+1] - a[n-k+1][k]*a[k][n-k+1];
     }
  }
  for(i=k+1; i<=n-k; i++){
    for(j=0; j<1; j++){
    w[i][k] = a[n-k+1][n-k+1]*a[i][k] - a[n-k+1][k]*a[i][n-k+1]/det[k];

    w[i][n-k+1] = a[k][k]*a[i][n-k+1] - a[k][n-k+1]*a[i][k] / det[k];
    }
    for(j=k+1; j<=n-k; j++){
      a[i][j] = a[i][j] - w[i][k]*a[k][j] - w[i][n-k+1]*a[n-k+1][j];
  }
 }
}
}
#pragma endscop
