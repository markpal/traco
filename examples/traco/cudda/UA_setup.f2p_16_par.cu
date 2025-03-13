int i;
int j;
int ip;
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



int N = 200;
int N1;
int N2;
int N3;
int DIM;
int DIM1;
int DIM2;
__global__ void seq_kernel0(int * N1, int * N2, int * N3, float dxm1[DIM1][DIM2], float wdtdr[DIM1][DIM2], float * wxm1)
{
int i;
int ip;
int j;
int _bid = (blockIdx.x+(blockIdx.y*gridDim.x));
int _gtid = (threadIdx.x+(_bid*blockDim.x));
i=(_gtid+1);
if (i<=( * N1))
{
for (j=1; j<=( * N2); j ++ )
{
for (ip=1; ip<=( * N3); ip ++ )
{
wdtdr[i][j]=(wdtdr[i][j]+((wxm1[ip]*dxm1[ip][i])*dxm1[ip][j]));
}
}
}
}

void seq(float wdtdr[DIM1][DIM2], float wxm1[DIM1], float dxm1[DIM1][DIM2])
{
int * gpu__N1;
int * gpu__N2;
int * gpu__N3;
float * gpu__dxm1;
float * gpu__wdtdr;
float * gpu__wxm1;
gpuBytes=sizeof (int);
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__N1)), gpuBytes));
dim3 dimBlock0(gpuNumThreads, 1, 1);
gpuNumBlocks=((int)ceil((((float)N1)/128.0F)));
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
gpuBytes=((DIM1*DIM2)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__dxm1)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__dxm1, dxm1, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=((DIM1*DIM2)*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__wdtdr)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__wdtdr, wdtdr, gpuBytes, cudaMemcpyHostToDevice));
gpuBytes=(DIM1*sizeof (float));
CUDA_SAFE_CALL(cudaMalloc(((void * *)( & gpu__wxm1)), gpuBytes));
CUDA_SAFE_CALL(cudaMemcpy(gpu__wxm1, wxm1, gpuBytes, cudaMemcpyHostToDevice));
#pragma omp parallel for shared(N1, N2, N3, dxm1, wdtdr, wxm1) private(i, ip, j)
#pragma cuda ainfo kernelid(0) procname(seq) 
#pragma cuda gpurun nog2cmemtr(N1, N2, N3, dxm1, wxm1) 
seq_kernel0<<<dimGrid0, dimBlock0, 0, 0>>>(gpu__N1, gpu__N2, gpu__N3, ((float (*)[DIM2])gpu__dxm1), ((float (*)[DIM2])gpu__wdtdr), gpu__wxm1);
gpuBytes=(DIM1*sizeof (float));
CUDA_SAFE_CALL(cudaFree(gpu__wxm1));
gpuBytes=((DIM1*DIM2)*sizeof (float));
CUDA_SAFE_CALL(cudaMemcpy(wdtdr, gpu__wdtdr, gpuBytes, cudaMemcpyDeviceToHost));
CUDA_SAFE_CALL(cudaFree(gpu__wdtdr));
gpuBytes=((DIM1*DIM2)*sizeof (float));
CUDA_SAFE_CALL(cudaFree(gpu__dxm1));
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
float (* dxm1)[DIM2];
float (* wxm1);
float (* wdtdr)[DIM2];
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
DIM=(N1=(N2=(N3=(DIM1=(DIM2=N)))));
wdtdr=((float (* )[DIM2])malloc(((DIM1*DIM2)*sizeof (float))));
wxm1=((float (* ))malloc((DIM1*sizeof (float))));
dxm1=((float (* )[DIM2])malloc(((DIM1*DIM2)*sizeof (float))));
/* variables to meassure time */
printf("Ilosc procesorow: %i \n\n", num_proc);
omp_set_num_threads(num_proc);
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
gettimeofday(( & s1), ((void * )0));
if ((num_proc==1))
{
seq(wdtdr, wxm1, dxm1);
}
gettimeofday(( & f1), ((void * )0));
/* ----------------------------------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
duration=((((double)f1.tv_sec)+(((double)f1.tv_usec)/1000000))-(((double)s1.tv_sec)+(((double)s1.tv_usec)/1000000)));
printf("Czas sekwencyjny: %2.3f seconds\n", duration);
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

