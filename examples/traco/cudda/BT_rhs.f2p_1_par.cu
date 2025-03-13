int k;
int j;
int i;
#include <omp.h>
#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

#ifndef __O2G_HEADER__ 

#define __O2G_HEADER__ 

/******************************************/
/* Added codes for OpenMP2GPU translation */
/******************************************/
#include <cutil.h>
#include <math.h>
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/**********************************************************/
/* Maximum width of linear memory bound to texture memory */
/**********************************************************/
/* width in bytes */
#define LMAX_WIDTH    134217728
/* width in words */
#define LMAX_WWIDTH  33554432
/**********************************/
/* Maximum memory pitch (in bytes)*/
/**********************************/
#define MAX_PITCH   262144
/****************************************/
/* Maximum allowed GPU global memory    */
/* (should be less than actual size ) */
/****************************************/
#define MAX_GMSIZE  1600000000
/****************************************/
/* Maximum allowed GPU shared memory    */
/****************************************/
#define MAX_SMSIZE  16384
/********************************************/
/* Maximum size of each dimension of a grid */
/********************************************/
#define MAX_GDIMENSION  65535
#define MAX_NDIMENSION  10000

#define BLOCK_SIZE  128


static int gpuNumThreads = BLOCK_SIZE;
static int gpuNumBlocks;
static int gpuNumBlocks1;
static int gpuNumBlocks2;
static int totalNumThreads;
unsigned int gpuGmemSize = 0;
unsigned int gpuSmemSize = 0;
static unsigned int gpuBytes = 0;

#endif 
/* End of __O2G_HEADER__ */



int N = 50;
int N1;
int N2;
int N3;
int N4;
int DIM;
int DIM1;
int DIM2;
int DIM3;
__global__ void seq_kernel0(int * N1, int * N2, int * N3, float qs[DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float u[6][DIM1][DIM2][DIM3], float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3])
{
int i;
int j;
int k;
int rho_inv;
int _bid = (blockIdx.x+(blockIdx.y*gridDim.x));
int _gtid = (threadIdx.x+(_bid*blockDim.x));
k=_gtid;
if (k<=( * N1))
{
for (j=0; j<=( * N2); j ++ )
{
for (i=0; i<=( * N3); i ++ )
{
rho_inv=(1.0/u[1][i][j][k]);
rho_i[i][j][k]=rho_inv;
us[i][j][k]=(u[2][i][j][k]*rho_inv);
vs[i][j][k]=(u[3][i][j][k]*rho_inv);
ws[i][j][k]=(u[4][i][j][k]*rho_inv);
square[i][j][k]=((0.5*(((u[2][i][j][k]*u[2][i][j][k])+(u[3][i][j][k]*u[3][i][j][k]))+(u[4][i][j][k]*u[4][i][j][k])))*rho_inv);
qs[i][j][k]=(square[i][j][k]*rho_inv);
}
}
}
}

void seq(float u[6][DIM1][DIM2][DIM3], float us[DIM1][DIM2][DIM3], float vs[DIM1][DIM2][DIM3], float ws[DIM1][DIM2][DIM3], float qs[DIM1][DIM2][DIM3], float square[DIM1][DIM2][DIM3], float rho_i[DIM1][DIM2][DIM3])
{
int * gpu__N1;
int * gpu__N2;
int * gpu__N3;
float * gpu__qs;
float * gpu__rho_i;
float * gpu__square;
float * gpu__u;
float * gpu__us;
float * gpu__vs;
float * gpu__ws;
gpuBytes=sizeof (int);
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__N1)), gpuBytes));
dim3 dimBlock0(gpuNumThreads, 1, 1);
gpuNumBlocks=((int)ceil((((float)(1+N1))/128.0F)));
if ((gpuNumBlocks>MAX_GDIMENSION))
{
gpuNumBlocks2=((int)ceil((((float)gpuNumBlocks)/10000.0F)));
gpuNumBlocks1=MAX_NDIMENSION;
}
else
{
gpuNumBlocks2=1;
gpuNumBlocks1=gpuNumBlocks;
}
dim3 dimGrid0(gpuNumBlocks1, gpuNumBlocks2, 1);
gpuNumBlocks=(gpuNumBlocks1*gpuNumBlocks2);
totalNumThreads=(gpuNumBlocks*gpuNumThreads);
CUDA_SAFE_CALL(cudaMemcpy(gpu__N1, ( & N1), gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=sizeof (int);
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__N2)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__N2, ( & N2), gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=sizeof (int);
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__N3)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__N3, ( & N3), gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__qs)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__qs, qs, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__rho_i)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__rho_i, rho_i, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__square)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__square, square, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=((((6*DIM1)*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__u)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__u, u, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__us)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__us, us, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__vs)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__vs, vs, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__ws)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__ws, ws, gpuBytes, cudaMemcpyHostToDevice));
#pragma omp parallel for shared(N1, N2, N3, qs, rho_i, square, u, us, vs, ws) private(i, j, k, rho_inv)
#pragma cuda ainfo kernelid(0) procname(seq) 
#pragma cuda gpurun nog2cmemtr(N1, N2, N3, u) 
seq_kernel0<<<dimGrid0, dimBlock0, 0, 0>>>(gpu__N1, gpu__N2, gpu__N3, ((float (*)[DIM2][DIM3])gpu__qs), ((float (*)[DIM2][DIM3])gpu__rho_i), ((float (*)[DIM2][DIM3])gpu__square), ((float (*)[DIM1][DIM2][DIM3])gpu__u), ((float (*)[DIM2][DIM3])gpu__us), ((float (*)[DIM2][DIM3])gpu__vs), ((float (*)[DIM2][DIM3])gpu__ws));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMemcpy(ws, gpu__ws, gpuBytes, cudaMemcpyDeviceToHost));
CUDA_SAFE_CALL(cudaFree(gpu__ws));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMemcpy(vs, gpu__vs, gpuBytes, cudaMemcpyDeviceToHost));
CUDA_SAFE_CALL(cudaFree(gpu__vs));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMemcpy(us, gpu__us, gpuBytes, cudaMemcpyDeviceToHost));
CUDA_SAFE_CALL(cudaFree(gpu__us));
gpuBytes=((((6*DIM1)*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaFree(gpu__u));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMemcpy(square, gpu__square, gpuBytes, cudaMemcpyDeviceToHost));
CUDA_SAFE_CALL(cudaFree(gpu__square));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMemcpy(rho_i, gpu__rho_i, gpuBytes, cudaMemcpyDeviceToHost));
CUDA_SAFE_CALL(cudaFree(gpu__rho_i));
gpuBytes=(((DIM1*DIM2)*DIM3)*sizeof (float));
CUDA_SAFE_CALL(cudaMemcpy(qs, gpu__qs, gpuBytes, cudaMemcpyDeviceToHost));
CUDA_SAFE_CALL(cudaFree(gpu__qs));
gpuBytes=sizeof (int);
CUDA_SAFE_CALL(cudaFree(gpu__N3));
gpuBytes=sizeof (int);
CUDA_SAFE_CALL(cudaFree(gpu__N2));
gpuBytes=sizeof (int);
CUDA_SAFE_CALL(cudaFree(gpu__N1));
return ;
}

int main(int argc, char * argv[])
{
/* number of processors */
int num_proc = 1;
float (* u)[6][DIM2][DIM3];
float (* square)[DIM2][DIM3];
float (* qs)[DIM2][DIM3];
float (* ws)[DIM2][DIM3];
float (* vs)[DIM2][DIM3];
float (* us)[DIM2][DIM3];
float (* rho_i)[DIM2][DIM3];
struct timeval s1;
struct timeval f1;
double duration;
int _ret_val_0;

////////////////////////////////
// CUDA Device Initialization //
////////////////////////////////
int deviceCount;
CUDA_SAFE_CALL_NO_SYNC(cudaGetDeviceCount(&deviceCount));
if (deviceCount == 0) {
	fprintf(stderr, "cutil error: no devices supporting CUDA.\n");
	exit(EXIT_FAILURE);
}
int dev = 0;
cudaDeviceProp deviceProp;
CUDA_SAFE_CALL_NO_SYNC(cudaGetDeviceProperties(&deviceProp, dev));
	fprintf(stderr, "Using device %d: %s\n", dev, deviceProp.name);
CUDA_SAFE_CALL(cudaSetDevice(dev));


num_proc=atoi(argv[1]);
if ((argc>2))
{
N=atoi(argv[2]);
}
N1=(N2=(N3=(N4=N)));
DIM=(DIM1=(DIM2=(DIM3=(N+2))));
us=((float (* )[DIM2][DIM3])malloc((((DIM1*DIM2)*DIM3)*sizeof (float))));
vs=((float (* )[DIM2][DIM3])malloc((((DIM1*DIM2)*DIM3)*sizeof (float))));
ws=((float (* )[DIM2][DIM3])malloc((((DIM1*DIM2)*DIM3)*sizeof (float))));
square=((float (* )[DIM2][DIM3])malloc((((DIM1*DIM2)*DIM3)*sizeof (float))));
qs=((float (* )[DIM2][DIM3])malloc((((DIM1*DIM2)*DIM3)*sizeof (float))));
rho_i=((float (* )[DIM2][DIM3])malloc((((DIM1*DIM2)*DIM3)*sizeof (float))));
u=((float (* )[6][DIM2][DIM3])malloc(((((DIM1*DIM2)*DIM3)*6)*sizeof (float))));
/* variables to meassure time */
printf("Ilosc procesorow: %i \n\n", num_proc);
omp_set_num_threads(num_proc);
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
gettimeofday(( & s1), ((void * )0));
if ((num_proc==1))
{
seq(u, us, vs, ws, qs, square, rho_i);
}
else
{
comp(u, us, vs, ws, qs, square, rho_i);
}
gettimeofday(( & f1), ((void * )0));
/* ----------------------------------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
duration=((((double)f1.tv_sec)+(((double)f1.tv_usec)/1000000))-(((double)s1.tv_sec)+(((double)s1.tv_usec)/1000000)));
printf("Czas: %2.3f seconds\n", duration);
printf("/***********************/ \n/* Input Configuration */ \n/***********************/ \n");
printf("====> GPU Block Size: 128 \n");
printf("/**********************/ \n/* Used Optimizations */ \n/**********************/ \n");
printf("====> CPU-GPU Mem Transfer Opt Level: 2\n");
printf("====> Cuda Malloc Opt Level: 0\n");
printf("====> local array reduction variable configuration = 1\n");
fflush(stdout);
fflush(stderr);
return _ret_val_0;
}

