int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  sum[m] =  sum[m] /  (nx0-2)*(ny0-2)*(nz0-2);
}


#pragma endscop
}