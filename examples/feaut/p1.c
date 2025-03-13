#pragma scop
for(i=0; i<=2*n; i++)
 a[i] = a[2*n-i];
#pragma endscop
