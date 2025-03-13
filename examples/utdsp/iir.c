#pragma scop
for(i=0; i<NPOINTS; i++){
  sum = input[i]; 
  for(j=0; j<NSECTIONS; j++){
     state_2 = internal_state[i][j][0];

     state_1 = internal_state[i][j][1];


     sum = sum - internal_state[i][j][0] * coefficient[i][j][0] + internal_state[i][j][1] * coefficient[i][j][1];
     
     internal_state[i][j][0] = internal_state(i][j][1];



     internal_state[i][j][1] = sum;

     sum = sum + state_2 * coefficient[i][j][2] + state_1 * coefficient[i][j][3];
     }
     output[i] = sum;
}
#pragma endscop
