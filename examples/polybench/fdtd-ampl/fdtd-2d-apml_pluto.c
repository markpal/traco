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

#include "common.h"
#include "looplib_a.h"
#include <omp.h>

// This is 'fdtd-2d-apml', a 2D finite different time domain kernel using an anisotropic perfectly matched layer
int main(int argc, char *argv[]) {


	int i,j,k;
	int ix,iy,iz;
	float clf, tmp;
	float czm_iz, czp_iz;
	float cymh_iy, cyph_iy;

	// Declare arrays on the stack
	float *czm= (float*)malloc((CZ+1)*sizeof(float));
	float *czp= (float*)malloc((CZ+1)*sizeof(float));
	float *cxmh= (float*)malloc((CXM+1)*sizeof(float));
	float *cxph= (float*)malloc((CXM+1)*sizeof(float));
	float *cymh= (float*)malloc((CYM+1)*sizeof(float));
	float *cyph = (float*)malloc((CYM+1)*sizeof(float));
	float **Ry = ReserveMemoryandClear(CZ+1,CYM+1);
	float **Ax = ReserveMemoryandClear(CZ+1,CYM+1);
	float ***Ex = ReserveMemoryC(CZ+1,CYM+1,CXM+1);
	float ***Ey = ReserveMemoryC(CZ+1,CYM+1,CXM+1);
	float ***Hz = ReserveMemoryC(CZ+1,CYM+1,CXM+1);
	float ***Bza = ReserveMemoryC(CZ+1,CYM+1,CXM+1);

	// Set the constants
	float mui = 2341;
	float ch = 42;

	// Set the input data
	for (i=0; i<=CZ; i++) {
		czm[i] = ((float) i+1) / CXM;
		czp[i] = ((float) i+2) / CXM;
	}
	for (i=0; i<=CXM; i++) {
		cxmh[i] = ((float) i+3) / CXM;
		cxph[i] = ((float) i+4) / CXM;
	}
	for (i=0; i<=CYM; i++) {
		cymh[i] = ((float) i+5) / CXM;
		cyph[i] = ((float) i+6) / CXM;
	}
	for (i=0; i<=CZ; i++) {
		for (j=0; j<=CYM; j++) {
			Ry[i][j] = ((float) i*(j+1) + 10) / CYM;
			Ax[i][j] = ((float) i*(j+2) + 11) / CYM;
			for (k=0; k<=CXM; k++) {
				Ex[i][j][k] = ((float) i*(j+3) + k+1) / CXM;
				Ey[i][j][k] = ((float) i*(j+4) + k+2) / CYM;
				Hz[i][j][k] = ((float) i*(j+5) + k+3) / CZ;
			}
		}
	}


	double start = omp_get_wtime( );
	// Perform the computation
	int num_proc = atoi(argv[2]);
	omp_set_num_threads(num_proc);

  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if ((CYM >= 1) && (CZ >= 1)) {
  if (CXM >= 1) {
    for (t1=0;t1<=CZ-1;t1++) {
      for (t2=0;t2<=CYM-1;t2++) {
        cyph_iy=cyph[t2];;
        cymh_iy=cymh[t2];;
        czp_iz=czp[t1];;
        czm_iz=czm[t1];;
        for (t4=0;t4<=CXM-1;t4++) {
          clf=Ex[t1][t2][t4]-Ex[t1][t2+1][t4]+Ey[t1][t2][t4+1]-Ey[t1][t2][t4];;
          tmp=(cymh_iy/cyph_iy)*Bza[t1][t2][t4]-(ch/cyph_iy)*clf;;
          Hz[t1][t2][t4]=Hz[t1][t2][t4]*(cxmh[t4]/cxph[t4])+(mui*czp_iz/cxph[t4])*tmp-(mui*czm_iz/cxph[t4])*Bza[t1][t2][t4];;
          Bza[t1][t2][t4]=tmp;;
        }
        clf=Ex[t1][t2][CXM]-Ex[t1][t2+1][CXM]+Ry[t1][t2]-Ey[t1][t2][CXM];;
        tmp=(cymh_iy/cyph_iy)*Bza[t1][t2][CXM]-(ch/cyph_iy)*clf;;
        Hz[t1][t2][CXM]=(cxmh[CXM]/cxph[CXM])*Hz[t1][t2][CXM]+(mui*czp_iz/cxph[CXM])*tmp-(mui*czm_iz/cxph[CXM])*Bza[t1][t2][CXM];;
        Bza[t1][t2][CXM]=tmp;;
        for (t4=0;t4<=CXM-1;t4++) {
          clf=Ex[t1][CYM][t4]-Ax[t1][t4]+Ey[t1][CYM][t4+1]-Ey[t1][CYM][t4];;
          tmp=(cymh[CYM]/cyph_iy)*Bza[t1][t2][t4]-(ch/cyph_iy)*clf;;
          Hz[t1][CYM][t4]=(cxmh[t4]/cxph[t4])*Hz[t1][CYM][t4]+(mui*czp_iz/cxph[t4])*tmp-(mui*czm_iz/cxph[t4])*Bza[t1][CYM][t4];;
          Bza[t1][CYM][t4]=tmp;;
        }
        clf=Ex[t1][CYM][CXM]-Ax[t1][CXM]+Ry[t1][CYM]-Ey[t1][CYM][CXM];;
        tmp=(cymh[CYM]/cyph[CYM])*Bza[t1][CYM][CXM]-(ch/cyph[CYM])*clf;;
        Hz[t1][CYM][CXM]=(cxmh[CXM]/cxph[CXM])*Hz[t1][CYM][CXM]+(mui*czp_iz/cxph[CXM])*tmp-(mui*czm_iz/cxph[CXM])*Bza[t1][CYM][CXM];;
        Bza[t1][CYM][CXM]=tmp;;
      }
    }
  }
  if (CXM <= 0) {
    for (t1=0;t1<=CZ-1;t1++) {
      for (t2=0;t2<=CYM-1;t2++) {
        cyph_iy=cyph[t2];;
        cymh_iy=cymh[t2];;
        czp_iz=czp[t1];;
        czm_iz=czm[t1];;
        clf=Ex[t1][t2][CXM]-Ex[t1][t2+1][CXM]+Ry[t1][t2]-Ey[t1][t2][CXM];;
        tmp=(cymh_iy/cyph_iy)*Bza[t1][t2][CXM]-(ch/cyph_iy)*clf;;
        Hz[t1][t2][CXM]=(cxmh[CXM]/cxph[CXM])*Hz[t1][t2][CXM]+(mui*czp_iz/cxph[CXM])*tmp-(mui*czm_iz/cxph[CXM])*Bza[t1][t2][CXM];;
        Bza[t1][t2][CXM]=tmp;;
        clf=Ex[t1][CYM][CXM]-Ax[t1][CXM]+Ry[t1][CYM]-Ey[t1][CYM][CXM];;
        tmp=(cymh[CYM]/cyph[CYM])*Bza[t1][CYM][CXM]-(ch/cyph[CYM])*clf;;
        Hz[t1][CYM][CXM]=(cxmh[CXM]/cxph[CXM])*Hz[t1][CYM][CXM]+(mui*czp_iz/cxph[CXM])*tmp-(mui*czm_iz/cxph[CXM])*Bza[t1][CYM][CXM];;
        Bza[t1][CYM][CXM]=tmp;;
      }
    }
  }
}
/* End of CLooG code */


    double end = omp_get_wtime( );

    printf("%.16g\n",  end - start);


	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

