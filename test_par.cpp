int i,j;

#include <omp.h>
#pragma omp parallel for private(i,j) 
for(i=0; i<N; i++){
 for(j=0; j<N; j++){
  a[i][j] = a[i][j-1];
  }
}
