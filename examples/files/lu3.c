#pragma scop
    for (l=0; l<N; l++) {
        for (i=l+1; i<N; i++)   {
        for(j=0; j<1; j++){ 
            a[l][i] = a[l][i]/a[l][l];
        }
        }
        for(i=l+1; i<N; i++)    {
            for (j=l+1; j<N; j++)   {
                a[i][j] = a[i][j] - a[i][l]*a[l][j];
            }
        }
    }
#pragma endscop
