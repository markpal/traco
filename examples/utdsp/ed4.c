#pragma scop
for(r=0; r<= N-K+1; r++)
 for(c=0; c<= N-K+1; c++)
 {
     sum[r][c] = 0;
     for(i=0; i<= K; i++)
      for(j=0; j<= K; j++)
        sum[r][c] += input_image[r+i][c+j] * kernel[i][j];
     output_image[r+dead_rows][c+dead_cols] = (sum[r][c] / normal_factor);
 }
#pragma endscop
