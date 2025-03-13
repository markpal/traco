#pragma scop
for(i=0; i<NPOINTS; i++){
sum = 0;
for(j=0; j<NTAPS; j++){
     if(i-j<0) {
     sum = sum + input[i-j+NTAPS] * coefficient[j];
     }
     else{
     sum = sum + input[i-j] * coefficient[j];
}
}
  output[NTAPS] = sum;
}
#pragma endscop
