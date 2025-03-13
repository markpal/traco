int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  errnm[m] =  errnm[m] / ( (nx0-2)*(ny0-2)*(nz0-2) );
}


#pragma endscop
}