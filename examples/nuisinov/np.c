#include <stdio.h>
#include <omp.h>

#define N 2500

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define floord(n,d) floor(((double)(n))/((double)(d)))

long double d[N][N];
long double d1[N][N];

int main(){

int i,j,k, t2,t4,t6,lbp,ubp;
int c1,c2,c3,c5,c7,c9,c11,c10,c4,c12;
double start,stop;


for(i=0; i<N; i++)
 for(j=0; j<N; j++){
 d[i][j] = i*j;
 d1[i][j] = d[i][j];


}

int a=0;

start = omp_get_wtime();
for (j=0; j<N; j++)
 for (i=j-1; i>-1; i--)
  for (k=i; k<j; k++)
    d[i][j] = min(d[i][j], d[i][k]+d[k][j]);


stop = omp_get_wtime();


printf("%i %.2f\n",a, stop-start);
a=0;

start = omp_get_wtime();
/*for( c1 = 0; c1 <= floord(N - 2, 16); c1 += 1)
  for( c3 = c1; c3 <= (N - 1) / 16; c3 += 1)
    for( c5 = 0; c5 <= c1; c5 += 1)
      for( c7 = max(16 * c1 + 1, 16 * c3); c7 <= min(N - 1, 16 * c3 + 15); c7 += 1)
        for( c9 = 16 * c1 - c7 + 1; c9 <= min(0, 16 * c1 - c7 + 16); c9 += 1)
          for( c11 = 16 * c5 - c9; c11 <= min(c7 - 1, 16 * c5 - c9 + 15); c11 += 1)
            d[-c9][c7] = min(d[-c9][c7], d[-c9][c11] + d[c11][c7]);
*/

for( c1 = 0; c1 <= floord(N - 2, 8); c1 += 1)
#pragma omp parallel for private(c3,c5,c7,c9,c11) shared(c1,d)
  for( c3 = (c1 + 1) / 2; c3 <= min(c1, (N - 1) / 16); c3 += 1)
    for( c5 = 0; c5 <= c1 - c3; c5 += 1)
      for( c7 = max(16 * c3, 16 * c1 - 16 * c3 + 1); c7 <= min(N - 1, 16 * c3 + 15); c7 += 1)
        for( c9 = 16 * c1 - 16 * c3 - c7 + 1; c9 <= min(0, 16 * c1 - 16 * c3 - c7 + 16); c9 += 1)
          for( c11 = 16 * c5 - c9; c11 <= min(c7 - 1, 16 * c5 - c9 + 15); c11 += 1)
            d[-c9][c7] = min(d[-c9][c7], d[-c9][c11] + d[c11][c7]);


stop = omp_get_wtime();


printf("%i %.2f\n",a, stop-start);

for(i=0; i<N; i++)
 for(j=0; j<N; j++){
   if(d1[i][j] != d[i][j]){
    printf("error %i %i %Lf %Lf \n ", i,j, d[i][j], d1[i][j]);
  //  printf("error\n");
exit(0);
  }
}


return 0;
}
