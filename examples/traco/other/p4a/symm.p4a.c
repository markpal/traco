/*
 * file for symm.c
 */
//
// This file is part of the Bones source-to-source compiler examples. The C-code
// is largely identical in terms of functionality and variable naming to the code
// found in PolyBench/C version 3.2. For more information on PolyBench/C or Bones
// please use the contact information below.
//
// == More information on PolyBench/C
// Contact............Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
// Web address........http://polybench.sourceforge.net/
//
// == More information on Bones
// Contact............Cedric Nugteren <c.nugteren@tue.nl>
// Web address........http://parse.ele.tue.nl/bones/
//
// == File information
// Filename...........benchmark/symm.c
// Author.............Cedric Nugteren
// Last modified on...23-May-2012
//

#include "/home/marek/issf/examples/traco/other/p4a/common.h"
#include "/home/marek/issf/examples/traco/other/p4a/looplib_a.h"


// This is 'symm', a symmetric matrix multiplication kernel
int main(void);
static unsigned short __bswap_16(unsigned short __bsx)
{
   return (unsigned short) (__bsx>>8&0xff|(__bsx&0xff)<<8);
}
static unsigned int __bswap_32(unsigned int __bsx)
{
   return (__bsx&0xff000000)>>24|(__bsx&0x00ff0000)>>8|(__bsx&0x0000ff00)<<8|(__bsx&0x000000ff)<<24;
}
float * * * ReserveMemoryandFill3D(float ***s, int dim1, int dim2, int dim3)
{
   int i, k, j;
   float ***g;
   
   //Alokacja pamieci
   
   g = (float ***) malloc(dim1*sizeof(float * *));

   for(i = 0; i <= dim1-1; i += 1) {
      g[i] = (float **) malloc(dim2*sizeof(float *));
      for(j = 0; j <= dim2-1; j += 1)
         g[i][j] = (float *) malloc(dim3*sizeof(float));
   }
   
   
   // Losowane dane
   if (s!=(void *) 0)
      for(k = 0; k <= dim1-1; k += 1)
         for(i = 0; i <= dim2-1; i += 1)
            for(j = 0; j <= dim3-1; j += 1)
               g[k][i][j] = s[k][i][j];
   else
      for(k = 0; k <= dim1-1; k += 1)
         for(i = 0; i <= dim2-1; i += 1)
            for(j = 0; j <= dim3-1; j += 1)
               g[k][i][j] = (int) (10.0*rand()/(2147483647+1.0));

   return g;
}
float * * ReserveMemoryandFill2D(float **s, int dim1, int dim2)
{
   int i, k, j;
   float **g;
   
   //Alokacja pamieci
   
   g = (float **) malloc(dim1*sizeof(float *));

   for(i = 0; i <= dim1-1; i += 1)
      g[i] = (float *) malloc(dim2*sizeof(float));
   
   
   // Losowane dane
   if (s!=(void *) 0)
      for(k = 0; k <= dim1-1; k += 1)
         for(i = 0; i <= dim2-1; i += 1)
            g[k][i] = s[k][i];
   else
      for(k = 0; k <= dim1-1; k += 1)
         for(i = 0; i <= dim2-1; i += 1)
            g[k][i] = (int) (10.0*rand()/(2147483647+1.0));

   return g;
}
float * * ReserveMemoryandClear(int dim1, int dim2)
{
   int i, k;
   float **g;
   
   //Alokacja pamieci
   
   g = (float **) malloc(dim1*sizeof(float *));

   for(i = 0; i <= dim1; i += 1)
      g[i] = (float *) malloc(dim2*sizeof(float));
   
   
   // Losowane dane
   
#pragma omp parallel for private(i)
   for(k = 0; k <= dim1-1; k += 1)
      for(i = 0; i <= dim2-1; i += 1)
         g[k][i] = 0;
   
   
   return g;
}
int loopcheck(float ***a1, float ***a2, int dim1, int dim2, int dim3)
{
   int i, k, j, check = 0;

   for(k = 0; k <= dim1-1; k += 1)
      for(i = 0; i <= dim2-1; i += 1)
         for(j = 0; j <= dim3-1; j += 1)
            if (a2[k][i][j]!=a1[k][i][j])
               check = 1;

   return check;
}
int intDiv(int a, int b)
{
   int c;
   c = abs(a/b);
   return c;
}
int intMod(int a, int b)
{
   int c;
   a = abs(a);
   c = a%b;
   return c;
}
int max(int a, int b)
{
   if (a>b)
      return a;
   else
      return b;
}
int min(int a, int b)
{
   if (a<b)
      return a;
   else
      return b;
}
int burnproc(int c)
{

   double z = 0;
   int i;
   struct timeval s1;
   
   
   for(i = 0; i <= c-1; i += 1) {
      long int y = 15;
      while (y>0) {
         gettimeofday(&s1, (void *) 0);
         z += sin(2*z*s1.tv_usec);
         y--;
      }
   }
   return 0;
}
int is_int(float z)
{
   int tmp = (int) z;
   if ((float) tmp==z)
      return 1;
   else
      return 0;
}
unsigned char * * * ReserveMemoryandFill_Int(int dim1, int dim2, int dim3)
{
   int i, k, j;
   unsigned char ***g;
   
   //Alokacja pamieci
   
   g = (unsigned char ***) malloc(dim1*sizeof(unsigned char * *));

   for(i = 0; i <= dim1-1; i += 1) {
      g[i] = (unsigned char **) malloc(dim2*sizeof(unsigned char *));
      for(j = 0; j <= dim2-1; j += 1)
         g[i][j] = (unsigned char *) malloc(dim3*sizeof(unsigned char));
   }
   
   
   for(k = 0; k <= dim1-1; k += 1)
      for(i = 0; i <= dim2-1; i += 1)
         for(j = 0; j <= dim3-1; j += 1)
            g[k][i][j] = -1;

   return g;
}
float * * * ReserveMemoryC(int dim1, int dim2, int dim3)
{
   int i, k, j;
   float ***g;
   
   //Alokacja pamieci
   
   g = (float ***) calloc(dim1, sizeof(float * *));

   for(i = 0; i <= dim1-1; i += 1) {
      g[i] = (float **) calloc(dim2, sizeof(float *));
      for(j = 0; j <= dim2-1; j += 1)
         g[i][j] = (float *) calloc(dim3, sizeof(float));
   }

   return g;
}
int main(void)
{
   int i, j, k;
   float acc[100];
   float bij;
   
   // Declare arrays on the stack
   float **A = ReserveMemoryandClear(1024, 1024);
   float **B = ReserveMemoryandClear(1024, 1024);
   float **C = ReserveMemoryandClear(1024, 1024);
   
   // Set the constants
   float alpha = 32412;
   float beta = 2123;
   
   // Set the input data
#pragma omp parallel for private(j)
   for(i = 0; i <= 1023; i += 1)
      for(j = 0; j <= 1023; j += 1) {
         C[i][j] = (float) i*j/1024;
         B[i][j] = (float) i*j/1024;
      }
#pragma omp parallel for private(j)
   for(i = 0; i <= 1023; i += 1)
      for(j = 0; j <= 1023; j += 1)
         A[i][j] = (float) i*j/1024;
   
   
   
   
#pragma omp parallel for private(k, i, bij)
   for(j = 0; j <= 1023; j += 1)
      for(i = 0; i <= 1023; i += 1) {
         acc[j] = 0;
         bij = B[i][j];
         for(k = 0; k <= j-1-1; k += 1)
            C[k][j] += alpha*A[k][i]*bij;
         for(k = 0; k <= j-1-1; k += 1)
            acc[j] += B[k][j]*A[k][i];
         C[i][j] = beta*C[i][j]+alpha*A[i][i]*bij+alpha*acc[j];
      }
   
   
   // Clean-up and exit the function
   fflush(stdout);
   return 0;
}
