#pragma scop
for(i=0; i<N; i++)
 for(j=0; j<N; j++){
  temp1[i][j] = image_buffer1[i][j];

  temp2[i][j] = image_buffer2[i][j];


  temp3[i][j] = temp1[i][j] + temp2[i][j];

  image_buffer3[i][j] = temp3[i][j] + T;
}
#pragma endscop
