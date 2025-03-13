// An OpenMP matrix-matrix multiply
#ifndef MIC_DEV
#define MIC_DEV 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mkl.h>
#include <math.h>

void doMultiply(int size, float (*restrict Matrix_A)[size], \
          float (*restrict Matrix_B)[size], \
          float (*restrict Matrix_C)[size])
{
   #pragma offload target(mic:MIC_DEV), in(Matrix_A:length(size*size)) \
      in(Matrix_B:length(size*size)), out(Matrix_C:length(size*size))
{
// Zero the Matrix_C matrix
#pragma omp parallel for default(none) shared(Matrix_C,size)
   for ( i = 0; i < size; ++i)
      for (j = 0; j < size; ++j)
            Matrix_C[i][j] = 0.f;

// Below fragment of the code should be re-written to use numthreads in which
// each thread will compute one or many rows of the output matrix Matrix_C by
// calculating the Offset parameters.

// Compute matrix multiplication.
  #pragma omp parallel for default(none) \
      shared(Matrix_A,Matrix_B,Matrix_C,size)

for ( i = 0; i < size; ++i)
   for ( k = 0; k < size; ++k)
      for ( j = 0; j < size; ++j)
         Matrix_C[i][j] += Matrix_A[i][k] * Matrix_B[k][j];
      }
}

/* .................... Main Program ............ */
int main(int argc, char* argv[])
{
      if(argc != 4)
{
         fprintf(stderr,"Use: %s size nThreads nIter \n",argv[0]);
           return -1;
}
   int i, j, k;
   int size = atoi(argv[1]);
   int nThreads = atoi(argv[2]);
   int nIter = atoi(argv[3]);

   omp_set_num_threads(nThreads);

   float (*restrict Matrix_A)[size] = malloc(sizeof(float)*size*size);
   float (*restrict Matrix_B)[size] = malloc(sizeof(float)*size*size);
   float (*restrict Matrix_C)[size] = malloc(sizeof(float)*size*size);
// Initialize matrices
for ( i = 0; i < size; i++) {
      for ( j = 0; j < size; j++) {
         Matrix_A[i][j] = (float)i + j;
         Matrix_B[i][j] = (float)i - j;
      }
}

// warm up
   doMultiply (size, Matrix_A, Matrix_B, Matrix_C);

   double aveTime, minTime=1e6, maxTime=0.;
   for (i=0; i < nIter; i++) {
      double startTime = dsecnd();

      doMultiply (size, Matrix_A, Matrix_B, Matrix_C);

   double endTime = dsecnd();
   double runtime = endTime - startTime;

   maxTime = (maxTime> runtime)?maxTime:runtime;
   minTime = (minTime< runtime)?minTime:runtime;
   aveTime += runtime;
}
   Time /= nIter;

   printf( "%s nThrds %d matrix %d maxRT %g minRT %g aveRT %g \
      ave_GFlop/s %g\n " argv[0], omp_get_num_threads(), size, \
      maxTime, minTime, aveTime, 2e-9*size*size*size/aveTime);

   free(Matrix_A); free(Matrix_B); free(Matrix_C);
   return 0;
}
