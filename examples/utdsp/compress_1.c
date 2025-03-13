#pragma scop
for(m=0; m<B; m++){
 for(n=0; n<B; n++){
     temp_cos=(factor2 * (2*n + 1)) / B;

     cos1[m][n]=temp_cos;


     cos2[n][m]=temp_cos;
   }
   factor2+=factor1;
}
#pragma endscop
