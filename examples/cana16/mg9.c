#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))


int N = 200;
int N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, DIM;
int DIM1;
int DIM2;
int DIM3;





void seq(float u[DIM1][DIM3][DIM2], float z[DIM1][DIM3][DIM2]) {
int i1, i2, i3, d1=0, d2=0, d3=0, t1=0, t2=0, t3=0;

for(i3 = N1; i3 <= N2; i3++){
  for(i2 = N3; i2 <= N4; i2++){
    for(i1 = N5; i1 <= N6; i1++){
      u[2*i1-d1][2*i2-d2][2*i3-d3]=u[2*i1-d1][2*i2-d2][2*i3-d3] +z[i1][i2][i3];
    }
    for(i1 = 1; i1 <= N7; i1++){
      u[2*i1-t1][2*i2-d2][2*i3-d3]=u[2*i1-t1][2*i2-d2][2*i3-d3] +0.5*(z[i1+1][i2][i3]+z[i1][i2][i3]);
    }
  }
  for(i2 = 1; i2 <= N8; i2++){
    for(i1 = N9; i1 <= N10; i1++){
      u[2*i1-d1][2*i2-t2][2*i3-d3]=u[2*i1-d1][2*i2-t2][2*i3-d3] +0.5*(z[i1][i2+1][i3]+z[i1][i2][i3]);
    }
    for(i1 = 1; i1 <= N11; i1++){
      u[2*i1-t1][2*i2-t2][2*i3-d3]=u[2*i1-t1][2*i2-t2][2*i3-d3] +0.25*(z[i1+1][i2+1][i3]+z[i1+1][i2][i3] +z[i1][i2+1][i3]+z[i1][i2][i3]);
    }
  }
}

}

void comp(float u[DIM1][DIM3][DIM2], float z[DIM1][DIM3][DIM2]) {
int i1, i2, i3, d1=0, d2=0, d3=0, t1=0, t2=0, t3=0;
int c0, c2, c4, c6, c8, c10;



#pragma omp parallel for
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1) {
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
        for (c6 = N5 + 16 * c4; c6 <= min(N6, N5 + 16 * c4 + 15); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
              u[2*c6-d1][2*c8-d2][2*c10-d3]=u[2*c6-d1][2*c8-d2][2*c10-d3]+z[c6][c8][c10];
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
        for (c6 = 16 * c4 + 1; c6 <= min(N7, 16 * c4 + 16); c6 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
            for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
              u[2*c6-t1][2*c8-d2][2*c10-d3]=u[2*c6-t1][2*c8-d2][2*c10-d3]+0.5*(z[c6+1][c8][c10]+z[c6][c8][c10]);
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 16); c4 += 1)
        for (c6 = N9 + 16 * c4; c6 <= min(N10, N9 + 16 * c4 + 15); c6 += 1)
          for (c8 = 16 * c2 + 1; c8 <= min(N8, 16 * c2 + 16); c8 += 1)
            for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
              u[2*c6-d1][2*c8-t2][2*c10-d3]=u[2*c6-d1][2*c8-t2][2*c10-d3]+0.5*(z[c6][c8+1][c10]+z[c6][c8][c10]);
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(N11 - 1, 16); c4 += 1)
        for (c6 = 16 * c4 + 1; c6 <= min(N11, 16 * c4 + 16); c6 += 1)
          for (c8 = 16 * c2 + 1; c8 <= min(N8, 16 * c2 + 16); c8 += 1)
            for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
              u[2*c6-t1][2*c8-t2][2*c10-d3]=u[2*c6-t1][2*c8-t2][2*c10-d3]+0.25*(z[c6+1][c8+1][c10]+z[c6+1][c8][c10]+z[c6][c8+1][c10]+z[c6][c8][c10]);
  }



/*

#pragma omp parallel for
  for (c0 = 0; c0 <= floord(-N1 + N2, 16); c0 += 1) {
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N5 + N6, 16); c4 += 1)
            for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
             for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
             for (c6 = N5 + 16 * c4; c6 <= min(N6, N5 + 16 * c4 + 15); c6 += 1)
              u[2*c6-d1][2*c8-d2][2*c10-d3]=u[2*c6-d1][2*c8-d2][2*c10-d3]+z[c6][c8][c10];
    for (c2 = 0; c2 <= floord(-N3 + N4, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(N7 - 1, 16); c4 += 1)
      for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
          for (c8 = N3 + 16 * c2; c8 <= min(N4, N3 + 16 * c2 + 15); c8 += 1)
           for (c6 = 16 * c4 + 1; c6 <= min(N7, 16 * c4 + 16); c6 += 1)
              u[2*c6-t1][2*c8-d2][2*c10-d3]=u[2*c6-t1][2*c8-d2][2*c10-d3]+0.5*(z[c6+1][c8][c10]+z[c6][c8][c10]);
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(-N9 + N10, 16); c4 += 1)
         for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
         for (c8 = 16 * c2 + 1; c8 <= min(N8, 16 * c2 + 16); c8 += 1)
        for (c6 = N9 + 16 * c4; c6 <= min(N10, N9 + 16 * c4 + 15); c6 += 1)
              u[2*c6-d1][2*c8-t2][2*c10-d3]=u[2*c6-d1][2*c8-t2][2*c10-d3]+0.5*(z[c6][c8+1][c10]+z[c6][c8][c10]);
    for (c2 = 0; c2 <= floord(N8 - 1, 16); c2 += 1)
      for (c4 = 0; c4 <= floord(N11 - 1, 16); c4 += 1)
            for (c10 = N1 + 16 * c0; c10 <= min(N2, N1 + 16 * c0 + 15); c10 += 1)
            for (c8 = 16 * c2 + 1; c8 <= min(N8, 16 * c2 + 16); c8 += 1)
                    for (c6 = 16 * c4 + 1; c6 <= min(N11, 16 * c4 + 16); c6 += 1)
              u[2*c6-t1][2*c8-t2][2*c10-d3]=u[2*c6-t1][2*c8-t2][2*c10-d3]+0.25*(z[c6+1][c8+1][c10]+z[c6+1][c8][c10]+z[c6][c8+1][c10]+z[c6][c8][c10]);
  }

*/

/*
#pragma omp parallel for
for(i3 = N1; i3 <= N2; i3++){
  for(i2 = N3; i2 <= N4; i2++){
    for(i1 = N5; i1 <= N6; i1++){
      u[2*i1-d1][2*i2-d2][2*i3-d3]=u[2*i1-d1][2*i2-d2][2*i3-d3] +z[i1][i2][i3];
    }
    for(i1 = 1; i1 <= N7; i1++){
      u[2*i1-t1][2*i2-d2][2*i3-d3]=u[2*i1-t1][2*i2-d2][2*i3-d3] +0.5*(z[i1+1][i2][i3]+z[i1][i2][i3]);
    }
  }
  for(i2 = 1; i2 <= N8; i2++){
    for(i1 = N9; i1 <= N10; i1++){
      u[2*i1-d1][2*i2-t2][2*i3-d3]=u[2*i1-d1][2*i2-t2][2*i3-d3] +0.5*(z[i1][i2+1][i3]+z[i1][i2][i3]);
    }
    for(i1 = 1; i1 <= N11; i1++){
      u[2*i1-t1][2*i2-t2][2*i3-d3]=u[2*i1-t1][2*i2-t2][2*i3-d3] +0.25*(z[i1+1][i2+1][i3]+z[i1+1][i2][i3] +z[i1][i2+1][i3]+z[i1][i2][i3]);
    }
  }
}
*/
}



int main(int argc, char *argv[]) {

  // number of processors
  int tile_kind=1;
  tile_kind = atoi(argv[1]);

  if(argc > 2)
    N = atoi(argv[2]);

  N1 = N5 = N3 =N9 =  1;
  N2 = N4 =N6 = N7 = N8 = N10 = N11= N;
  DIM = DIM1 = DIM2 = DIM3 = N+20;

  float (*z)[DIM2][DIM3], (*u)[DIM2][DIM3];

  u = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * 8 * sizeof(float));
  z = (float (*)[DIM2][DIM3])malloc(DIM1 * DIM2 * DIM3 * sizeof(float));



  printf("Ilosc procesorow: %i \n\n", tile_kind);
  omp_set_num_threads(tile_kind);

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   double start = omp_get_wtime();

  if(tile_kind == 1)
    seq(u, z);
  else if (tile_kind == 2)
         comp(u, z);



   double end = omp_get_wtime();

   printf("%.3f\n", end - start);

  // -----------------------------------
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





}












