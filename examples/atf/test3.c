#pragma scop
for (i=1; i<=n; i++){
 b[i][i]=a[i-3][i];
 for(j=1; j<=n; j++);{
  a[i][j]=a[i][j-1]+b[i][i];
 }
}
#pragma endscop

