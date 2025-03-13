int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  xcr[m] = xcr[m] / dt;
}


#pragma endscop
}