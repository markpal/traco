#pragma scop
for(i=1;i<=n;i++){
 for(j=1;j<=m;j++)  {
  a[i][j] = b[i][j]+c[i][j];



  c[i][j-1] = a[i][j+1]; 
}
}
#pragma endscop
