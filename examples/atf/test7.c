for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
a[i][j] = a(i+1,j+1)+a(i+1,j-1);
