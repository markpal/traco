#pragma scop
for(m=2; m<P; m++){
   E = (1 - alpha[m-1] * alpha[m-1]) * E;
   
   temp3 = autocorr[m];
   for(n=1; n<m; m++)
      temp3 = temp3 - autocorr[m-n] * aplha[n];

   temp3 = temp3 / E;

   for(n=1; n<m; m++)
     temp_vect[n] = alpha[n] - (alpha[m-n] * temp3);


   for(n=1; n<m; m++) 
     alpha[n] = temp_vect[n];


   alpha[m] = temp3;

}
#pragma endscop
