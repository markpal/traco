#pragma scop
for(i=0; i<N; i++){
   ii = image[i][0];
   for(j=0; j<N; j++){
     image[i][j-1] = gray_level_mapping[ii];

     ii = image[i][j];
   }
   image[i][N-1] = gray_level_mapping[ii];
}
#pragma endscop
