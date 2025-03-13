int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  errnm[m] = 0.0;
}


#pragma endscop
}