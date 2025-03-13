#pragma scop
for(i=0; i<N; i++)
 for(j=0; j<N; j++){
  temp1 = image_buffer1[i][j];

  temp2 = image_buffer2[i][j];


  temp3 = temp1 + temp2;

  image_buffer3[i][j] = temp3 + T;
}
#pragma endscop
