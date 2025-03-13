#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


#define min(a,b) (((a)<(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define ceild(n,d) ceil(((double)(n))/((double)(d)))

#define CHECK_VALID 0

long double **W;
long double **V;
long double **V1;
long double **tmp_V;
long double ****EFL;
long double **EHF;

int N = 100, DIM = 102;

#include "zuker_oryg.h"
#include "zuker_pluto.h"
#include "zuker_pluto2.h"
#include "zuker_pluto2a.h"
#include "zuker_traco.h"
#include "zuker_traco2.h"
#include "zuker_traco3.h"
#include "mem.h"




int main(int argc, char *argv[]){

    int i,j,k;
//

    int num_proc=1;
    num_proc = atoi(argv[1]);

    int kind;

    if(argc > 2)
        N = atoi(argv[2]);
    DIM = N+2;


    if(argc > 3)
        kind = atoi(argv[3]);

    W = mem();
    V = mem();
    V1 = mem();
    EFL = mem4();
    EHF = mem();


    for(i=0; i<N; i++)
     for(j=0; j<N; j++){
     W[i][j] = i*j*0.001;
     V[i][j] = i*j*0.004;
    }

    omp_set_num_threads(num_proc);

    double start = omp_get_wtime();

    if(kind == 4){
        //printf("!!!\n");
        zuker_traco3();
    }

    if(kind == 7){
        //printf("!!!\n");
        zuker_traco2();
    }

    if(kind == 3){
        //printf("!!!\n");
        zuker_traco();
    }

    if(kind == 2)
        zuker_pluto();

    if(kind == 5)
        zuker_pluto2();

    if(kind == 6)
        zuker_pluto2a();

    if(kind == 1 || CHECK_VALID)
    {    tmp_V = V;
        V = V1;
        zuker_seq();
        V = tmp_V;

    if(CHECK_VALID && kind > 1)
     for(i=0; i<N; i++)
      for(j=0; j<N; j++)
       if(V[i][j] != V1[i][j]){
          printf("error!\n");
          exit(0);
      }

    }

    double stop = omp_get_wtime();
    printf("%.2f\n",stop - start);






return 0;
}
