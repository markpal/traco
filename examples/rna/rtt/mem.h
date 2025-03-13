long double **mem()
{
int i;
long double **S;
S = (long double **) malloc(DIM * sizeof(long double*));

for (i=0; i<DIM; i++)
    S[i] = (long double*)malloc(DIM * sizeof(long double));

return S;
}

long double ****mem()
{
int i,j,k;
long double ****S;
S = (long double ****) malloc(DIM * sizeof(long double***));

for (i=0; i<DIM; i++)
    S[i] = (long double***)malloc(DIM * sizeof(long double**));

for (i=0; i<DIM; i++)
for (j=0; j<DIM; j++)
    S[i][j] = (long double**)malloc(DIM * sizeof(long double*));

for (i=0; i<DIM; i++)
for (j=0; j<DIM; j++)
for (k=0; k<DIM; k++)
    S[i][j][k] = (long double*)malloc(DIM * sizeof(long double));

return S;
}

