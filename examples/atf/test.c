#pragma scop
for(i=1;  i<=10;  i++)
  for(j=1;  j<=10;  j++)
a[i][j]  =  a[i-2][j]  +  a[i-1][j+3];  
#pragma endscop
