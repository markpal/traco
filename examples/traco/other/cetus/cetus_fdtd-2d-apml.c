/*  */
/* This file is part of the Bones source-to-source compiler examples. The C-code */
/* is largely identical in terms of functionality and variable naming to the code */
/* found in PolyBenchC version 3.2. For more information on PolyBench/C or Bones */
/* please use the contact information below. */
/*  */
/* == More information on PolyBenchC */
/* Contact............Louis-Noel Pouchet <pouchet@cse.ohio-state.edu> */
/* Web address........http:polybench.sourceforge.net */
/*  */
/* == More information on Bones */
/* Contact............Cedric Nugteren <c.nugteren@tue.nl> */
/* Web address........http:parse.ele.tue.nlbones */
/*  */
/* == File information */
/* Filename...........benchmarkfdtd-2d-apml.c */
/* Author.............Cedric Nugteren */
/* Last modified on...30-May-2012 */
/*  */
#include "/home/marek/issf/examples/traco/other/cetus/common.h"
#include "/home/marek/issf/examples/traco/other/cetus/looplib_a.h"
/* This is 'fdtd-2d-apml', a 2D finite different time domain kernel using an anisotropic perfectly matched layer */
int main(void )
{
	int i, j, k;
	int ix, iy, iz;
	float clf, tmp;
	float czm_iz, czp_iz;
	float cymh_iy, cyph_iy;
	/* Declare arrays on the stack */
	float * czm = (float * )malloc((32+1)*sizeof (float));
	float * czp = (float * )malloc((32+1)*sizeof (float));
	float * cxmh = (float * )malloc((32+1)*sizeof (float));
	float * cxph = (float * )malloc((32+1)*sizeof (float));
	float * cymh = (float * )malloc((32+1)*sizeof (float));
	float * cyph = (float * )malloc((32+1)*sizeof (float));
	float * * Ry = ReserveMemoryandClear(32+1, 32+1);
	float * * Ax = ReserveMemoryandClear(32+1, 32+1);
	float * * * Ex = ReserveMemoryC(32+1, 32+1, 32+1);
	float * * * Ey = ReserveMemoryC(32+1, 32+1, 32+1);
	float * * * Hz = ReserveMemoryC(32+1, 32+1, 32+1);
	float * * * Bza = ReserveMemoryC(32+1, 32+1, 32+1);
	/* Set the constants */
	float mui = 2341;
	float ch = 42;
	/* Set the input data */
	int _ret_val_0;
	#pragma cetus private(i) 
	#pragma cetus parallel 
	/*
	Disabled due to low profitability: #pragma omp parallel for private(i)
	*/
	for (i=0; i<=32; i ++ )
	{
		czm[i]=((((float)i)+1)/32);
		czp[i]=((((float)i)+2)/32);
	}
	#pragma cetus private(i) 
	#pragma cetus parallel 
	/*
	Disabled due to low profitability: #pragma omp parallel for private(i)
	*/
	for (i=0; i<=32; i ++ )
	{
		cxmh[i]=((((float)i)+3)/32);
		cxph[i]=((((float)i)+4)/32);
	}
	#pragma cetus private(i) 
	#pragma cetus parallel 
	/*
	Disabled due to low profitability: #pragma omp parallel for private(i)
	*/
	for (i=0; i<=32; i ++ )
	{
		cymh[i]=((((float)i)+5)/32);
		cyph[i]=((((float)i)+6)/32);
	}
	#pragma cetus private(i, j, k) 
	#pragma cetus parallel 
	#pragma omp parallel for private(i, j, k)
	for (i=0; i<=32; i ++ )
	{
		#pragma cetus private(j, k) 
		for (j=0; j<=32; j ++ )
		{
			Ry[i][j]=(((((float)i)*(j+1))+10)/32);
			Ax[i][j]=(((((float)i)*(j+2))+11)/32);
			#pragma cetus private(k) 
			for (k=0; k<=32; k ++ )
			{
				Ex[i][j][k]=((((((float)i)*(j+3))+k)+1)/32);
				Ey[i][j][k]=((((((float)i)*(j+4))+k)+2)/32);
				Hz[i][j][k]=((((((float)i)*(j+5))+k)+3)/32);
			}
		}
	}
	#pragma cetus private(clf, cymh_iy, cyph_iy, czm_iz, czp_iz, ix, iy, iz, tmp) 
	#pragma cetus parallel 
	#pragma omp parallel for private(clf, cymh_iy, cyph_iy, czm_iz, czp_iz, ix, iy, iz, tmp)
	for (iz=0; iz<32; iz ++ )
	{
		#pragma cetus private(clf, cymh_iy, cyph_iy, czm_iz, czp_iz, ix, iy, tmp) 
		for (iy=0; iy<32; iy ++ )
		{
			czm_iz=czm[iz];
			czp_iz=czp[iz];
			cymh_iy=cymh[iy];
			cyph_iy=cyph[iy];
			#pragma cetus private(clf, ix, tmp) 
			for (ix=0; ix<32; ix ++ )
			{
				clf=(((Ex[iz][iy][ix]-Ex[iz][iy+1][ix])+Ey[iz][iy][ix+1])-Ey[iz][iy][ix]);
				tmp=(((cymh_iy/cyph_iy)*Bza[iz][iy][ix])-((ch/cyph_iy)*clf));
				Hz[iz][iy][ix]=(((Hz[iz][iy][ix]*(cxmh[ix]/cxph[ix]))+(((mui*czp_iz)/cxph[ix])*tmp))-(((mui*czm_iz)/cxph[ix])*Bza[iz][iy][ix]));
				Bza[iz][iy][ix]=tmp;
			}
			clf=(((Ex[iz][iy][32]-Ex[iz][iy+1][32])+Ry[iz][iy])-Ey[iz][iy][32]);
			tmp=(((cymh_iy/cyph_iy)*Bza[iz][iy][32])-((ch/cyph_iy)*clf));
			Hz[iz][iy][32]=((((cxmh[32]/cxph[32])*Hz[iz][iy][32])+(((mui*czp_iz)/cxph[32])*tmp))-(((mui*czm_iz)/cxph[32])*Bza[iz][iy][32]));
			Bza[iz][iy][32]=tmp;
			#pragma cetus private(clf, ix, tmp) 
			for (ix=0; ix<32; ix ++ )
			{
				clf=(((Ex[iz][32][ix]-Ax[iz][ix])+Ey[iz][32][ix+1])-Ey[iz][32][ix]);
				tmp=(((cymh[32]/cyph_iy)*Bza[iz][iy][ix])-((ch/cyph_iy)*clf));
				Hz[iz][32][ix]=((((cxmh[ix]/cxph[ix])*Hz[iz][32][ix])+(((mui*czp_iz)/cxph[ix])*tmp))-(((mui*czm_iz)/cxph[ix])*Bza[iz][32][ix]));
				Bza[iz][32][ix]=tmp;
			}
			clf=(((Ex[iz][32][32]-Ax[iz][32])+Ry[iz][32])-Ey[iz][32][32]);
			tmp=(((cymh[32]/cyph[32])*Bza[iz][32][32])-((ch/cyph[32])*clf));
			Hz[iz][32][32]=((((cxmh[32]/cxph[32])*Hz[iz][32][32])+(((mui*czp_iz)/cxph[32])*tmp))-(((mui*czm_iz)/cxph[32])*Bza[iz][32][32]));
			Bza[iz][32][32]=tmp;
		}
	}
	/* Clean-up and exit the function */
	fflush(stdout);
	_ret_val_0=0;
	return _ret_val_0;
}
