#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


// Rezerwacja pamieci
float ***ReserveMemoryandFill3D(float ***s, int dim1, int dim2, int dim3)
{
	int i, k, j;
	float ***g;

	//Alokacja pamieci

	g = (float***)malloc(dim1*sizeof(float**));

	for(i=0; i<dim1; i++)
	{
		g[i] = (float**)malloc(dim2*sizeof(float*));
		for(j=0; j<dim2; j++)
		{
			g[i][j] = (float*)malloc(dim3*sizeof(float));
		}
	}


	// Losowane dane
	if (s !=NULL)
	for(k=0; k<dim1; k++)
		for(i=0; i<dim2; i++)
			for(j=0; j<dim3; j++)
				g[k][i][j] = s[k][i][j];

	else
	{
	for(k=0; k<dim1; k++)
		for(i=0; i<dim2; i++)
			for(j=0; j<dim3; j++)
				g[k][i][j] = (int) (10.0*rand()/(RAND_MAX+1.0));
	}

	return g;
}

// Rezerwacja pamieci
float **ReserveMemoryandFill2D(float **s, int dim1, int dim2)
{
	int i, k, j;
	float **g;

	//Alokacja pamieci

	g = (float**)malloc(dim1*sizeof(float*));

	for(i=0; i<dim1; i++)
	{
		g[i] = (float*)malloc(dim2*sizeof(float));
	}


	// Losowane dane
	if (s !=NULL)
	for(k=0; k<dim1; k++)
		for(i=0; i<dim2; i++)
		    g[k][i] = s[k][i];

	else
	{
	for(k=0; k<dim1; k++)
		for(i=0; i<dim2; i++)
			g[k][i] = (int) (10.0*rand()/(RAND_MAX+1.0));
	}

	return g;
}

// Rezerwacja pamieci
float **ReserveMemoryandClear(int dim1, int dim2)
{
	int i, k;
	float **g;

	//Alokacja pamieci

	g = (float**)malloc(dim1*sizeof(float*));

	for(i=0; i<=dim1; i++)
	{
		g[i] = (float*)malloc(dim2*sizeof(float));
	}


	// Losowane dane

	for(k=0; k<dim1; k++)
		for(i=0; i<dim2; i++)
		{
			g[k][i] = 0;
		}


	return g;
}



// Walidacja petli
// ==== CHECK========

int loopcheck(float ***a1, float ***a2, int dim1, int dim2, int dim3)
{
	int i, k, j, check =0;

	for(k=0; k<dim1; k++)
		for(i=0; i<dim2; i++)
			for(j=0; j<dim3; j++)
			{
				if (a2[k][i][j] != a1[k][i][j])
					check=1;
			}

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
	if(a > b)
		return a;
	else
		return b;
}

int min(int a, int b)
{
	if(a < b)
		return a;
	else
		return b;
}


//obciazenie
int burnproc(int c)
{

	double z=0;
	int i;
	struct timeval s1;


	for(i=0; i<c; i++)
	{
		long y = 15;
		while(y>0)
			{
			gettimeofday(&s1, NULL);
			z += sin(2*z*s1.tv_usec);
			y--;
		}
	}
	return 0;

}

int is_int(float z)
{
	int tmp = (int)z;
	if((float)tmp == z )
		return 1;
	else
		return 0;
}


unsigned char ***ReserveMemoryandFill_Int(int dim1, int dim2, int dim3)
{
	int i, k, j;
	unsigned char ***g;

	//Alokacja pamieci

	g = (unsigned char***)malloc(dim1*sizeof(unsigned char**));

	for(i=0; i<dim1; i++)
	{
		g[i] = (unsigned char**)malloc(dim2*sizeof(unsigned char*));
		for(j=0; j<dim2; j++)
		{
			g[i][j] = (unsigned char*)malloc(dim3*sizeof(unsigned char));
		}
	}


		for(k=0; k<dim1; k++)
			for(i=0; i<dim2; i++)
				for(j=0; j<dim3; j++)
					g[k][i][j] = -1;

	return g;
}

float ***ReserveMemoryC(int dim1, int dim2, int dim3)
{
	int i, k, j;
	float ***g;

	//Alokacja pamieci

	g = (float***)calloc(dim1, sizeof(float**));

	for(i=0; i<dim1; i++)
	{
		g[i] = (float**)calloc(dim2, sizeof(float*));
		for(j=0; j<dim2; j++)
		{
			g[i][j] = (float*)calloc(dim3, sizeof(float));
		}
	}

	return g;
}
