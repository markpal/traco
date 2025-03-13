// source /home/student/accull/env-parameters.sh
// /home/student/accull/accull -o 3mm.exe 3mm_acc.c


#include<omp.h>
#include<stdio.h>
#include<openacc.h>

#define N 128


float czm[N+1];
float czp[N+1];
float cxmh[N+1];
float cymh[N+1];
float cxph[N+1];
float cyph[N+1];

float Ry[N+1][N+1];
float Ax[N+1][N+1];

float Ex[N+1][N+1][N+1];
float Ey[N+1][N+1][N+1];
float Hz[N+1][N+1][N+1];
float Bza[N+1][N+1][N+1];


// This is 'fdtd-2d-apml', a 2D finite different time domain kernel using an anisotropic perfectly matched layer
int main(int argc, char *argv[]) {


	int i,j,k;
	int ix,iy,iz;
	float clf, tmp;
	float czm_iz, czp_iz;
	float cymh_iy, cyph_iy;


	// Set the constants
	float mui = 2341;
	float ch = 42;


    int CZ=N;
    int CYM = CYM;
    int CXM = CXM;
    const int n = N+1;

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


	#pragma acc data copy(HZ[0:n*n*n],Bza[0:n*n*n]) copynin(Ry[0:n*n],AXx[0:n*n],Ex[0:n*n*n],Ey[0:n*n*n],Hz[0:n*n*n],czm[0:n],czp[0:n],cxmh[0:n],cxph[0:n],cymh[0:n],cyph[0:n],mui,ch,n,CZ,CXM,CYM) create(iz,iy,ix,czm_iz,czp_iz,cymh_iy,cyph_iy,clf,tmp)
	{
	#pragma acc kernels loop private(iz,iy,ix,czm_iz,czp_iz,cymh_iy,cyph_iy,clf,tmp)
	for (iz=0; iz<CZ; iz++) {
	    #pragma acc loop
		for (iy=0; iy<CYM; iy++) {
			czm_iz = czm[iz];
			czp_iz = czp[iz];
			cymh_iy = cymh[iy];
			cyph_iy = cyph[iy];
            #pragma acc loop
			for (ix=0; ix<CXM; ix++) {
				clf = Ex[iz][iy][ix] - Ex[iz][iy+1][ix] + Ey[iz][iy][ix+1] - Ey[iz][iy][ix];
				tmp = (cymh_iy/cyph_iy) * Bza[iz][iy][ix] - (ch/cyph_iy) * clf;
				Hz[iz][iy][ix] = Hz[iz][iy][ix] * (cxmh[ix]/cxph[ix]) + (mui * czp_iz/cxph[ix]) * tmp - (mui * czm_iz/cxph[ix]) * Bza[iz][iy][ix];
				Bza[iz][iy][ix] = tmp;
			}

			clf = Ex[iz][iy][CXM] - Ex[iz][iy+1][CXM] + Ry[iz][iy] - Ey[iz][iy][CXM];
			tmp = (cymh_iy/cyph_iy) * Bza[iz][iy][CXM] - (ch/cyph_iy) * clf;
			Hz[iz][iy][CXM] = (cxmh[CXM]/cxph[CXM]) * Hz[iz][iy][CXM] + (mui * czp_iz/cxph[CXM]) * tmp - (mui * czm_iz/cxph[CXM]) * Bza[iz][iy][CXM];
			Bza[iz][iy][CXM] = tmp;

            #pragma acc loop
			for (ix=0; ix<CXM; ix++) {
				clf = Ex[iz][CYM][ix] - Ax[iz][ix] + Ey[iz][CYM][ix+1] - Ey[iz][CYM][ix];
				tmp = (cymh[CYM]/cyph_iy) * Bza[iz][iy][ix] - (ch/cyph_iy) * clf;
				Hz[iz][CYM][ix] = (cxmh[ix]/cxph[ix]) * Hz[iz][CYM][ix] + (mui * czp_iz/cxph[ix]) * tmp - (mui * czm_iz/cxph[ix]) * Bza[iz][CYM][ix];
				Bza[iz][CYM][ix] = tmp;
			}

			clf = Ex[iz][CYM][CXM] - Ax[iz][CXM] + Ry[iz][CYM] - Ey[iz][CYM][CXM];
			tmp = (cymh[CYM]/cyph[CYM]) * Bza[iz][CYM][CXM] - (ch/cyph[CYM]) * clf;
			Hz[iz][CYM][CXM] = (cxmh[CXM]/cxph[CXM]) * Hz[iz][CYM][CXM] + (mui * czp_iz/cxph[CXM]) * tmp - (mui * czm_iz/cxph[CXM]) * Bza[iz][CYM][CXM];
			Bza[iz][CYM][CXM] = tmp;
		}
	}
	}


    double end = omp_get_wtime( );

    printf("%.16g\n",  end - start);

	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

