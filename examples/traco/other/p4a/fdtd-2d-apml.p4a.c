/*
 * file for fdtd-2d-apml.c
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
// Filename...........benchmark/fdtd-2d-apml.c
// Author.............Cedric Nugteren
// Last modified on...30-May-2012
//

#include "/home/marek/issf/examples/traco/other/p4a/common.h"
#include "/home/marek/issf/examples/traco/other/p4a/looplib_a.h"


// This is 'fdtd-2d-apml', a 2D finite different time domain kernel using an anisotropic perfectly matched layer
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

#pragma omp parallel for private(j)
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
   int ix, iy, iz;
   float clf, tmp;
   float czm_iz, czp_iz;
   float cymh_iy, cyph_iy;
   
   // Declare arrays on the stack
   float *czm = (float *) malloc((256+1)*sizeof(float));
   float *czp = (float *) malloc((256+1)*sizeof(float));
   float *cxmh = (float *) malloc((256+1)*sizeof(float));
   float *cxph = (float *) malloc((256+1)*sizeof(float));
   float *cymh = (float *) malloc((256+1)*sizeof(float));
   float *cyph = (float *) malloc((256+1)*sizeof(float));
   float **Ry = ReserveMemoryandClear(256+1, 256+1);
   float **Ax = ReserveMemoryandClear(256+1, 256+1);
   float ***Ex = ReserveMemoryC(256+1, 256+1, 256+1);
   float ***Ey = ReserveMemoryC(256+1, 256+1, 256+1);
   float ***Hz = ReserveMemoryC(256+1, 256+1, 256+1);
   float ***Bza = ReserveMemoryC(256+1, 256+1, 256+1);
   
   // Set the constants
   float mui = 2341;
   float ch = 42;
   
   // Set the input data
#pragma omp parallel for
   for(i = 0; i <= 256; i += 1) {
      czm[i] = ((float) i+1)/256;
      czp[i] = ((float) i+2)/256;
   }
#pragma omp parallel for
   for(i = 0; i <= 256; i += 1) {
      cxmh[i] = ((float) i+3)/256;
      cxph[i] = ((float) i+4)/256;
   }
#pragma omp parallel for
   for(i = 0; i <= 256; i += 1) {
      cymh[i] = ((float) i+5)/256;
      cyph[i] = ((float) i+6)/256;
   }
#pragma omp parallel for private(j, k)
   for(i = 0; i <= 256; i += 1)
      for(j = 0; j <= 256; j += 1) {
         Ry[i][j] = ((float) i*(j+1)+10)/256;
         Ax[i][j] = ((float) i*(j+2)+11)/256;
         for(k = 0; k <= 256; k += 1) {
            Ex[i][j][k] = ((float) i*(j+3)+k+1)/256;
            Ey[i][j][k] = ((float) i*(j+4)+k+2)/256;
            Hz[i][j][k] = ((float) i*(j+5)+k+3)/256;
         }
      }

#pragma omp parallel for private(tmp, iy, ix, czp_iz, czm_iz, cyph_iy, cymh_iy, clf)
   for(iz = 0; iz <= 255; iz += 1)
      for(iy = 0; iy <= 255; iy += 1) {
         czm_iz = czm[iz];
         czp_iz = czp[iz];
         cymh_iy = cymh[iy];
         cyph_iy = cyph[iy];

         for(ix = 0; ix <= 255; ix += 1) {
            clf = Ex[iz][iy][ix]-Ex[iz][iy+1][ix]+Ey[iz][iy][ix+1]-Ey[iz][iy][ix];
            tmp = cymh_iy/cyph_iy*Bza[iz][iy][ix]-ch/cyph_iy*clf;
            Hz[iz][iy][ix] = Hz[iz][iy][ix]*cxmh[ix]/cxph[ix]+mui*czp_iz/cxph[ix]*tmp-mui*czm_iz/cxph[ix]*Bza[iz][iy][ix];
            Bza[iz][iy][ix] = tmp;
         }

         clf = Ex[iz][iy][256]-Ex[iz][iy+1][256]+Ry[iz][iy]-Ey[iz][iy][256];
         tmp = cymh_iy/cyph_iy*Bza[iz][iy][256]-ch/cyph_iy*clf;
         Hz[iz][iy][256] = cxmh[256]/cxph[256]*Hz[iz][iy][256]+mui*czp_iz/cxph[256]*tmp-mui*czm_iz/cxph[256]*Bza[iz][iy][256];
         Bza[iz][iy][256] = tmp;

         for(ix = 0; ix <= 255; ix += 1) {
            clf = Ex[iz][256][ix]-Ax[iz][ix]+Ey[iz][256][ix+1]-Ey[iz][256][ix];
            tmp = cymh[256]/cyph_iy*Bza[iz][iy][ix]-ch/cyph_iy*clf;
            Hz[iz][256][ix] = cxmh[ix]/cxph[ix]*Hz[iz][256][ix]+mui*czp_iz/cxph[ix]*tmp-mui*czm_iz/cxph[ix]*Bza[iz][256][ix];
            Bza[iz][256][ix] = tmp;
         }

         clf = Ex[iz][256][256]-Ax[iz][256]+Ry[iz][256]-Ey[iz][256][256];
         tmp = cymh[256]/cyph[256]*Bza[iz][256][256]-ch/cyph[256]*clf;
         Hz[iz][256][256] = cxmh[256]/cxph[256]*Hz[iz][256][256]+mui*czp_iz/cxph[256]*tmp-mui*czm_iz/cxph[256]*Bza[iz][256][256];
         Bza[iz][256][256] = tmp;
      }
   
   
   
   
   // Clean-up and exit the function
   fflush(stdout);
   return 0;
}
