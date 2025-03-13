int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  rms[m] = 0.0;
}


#pragma endscop
}