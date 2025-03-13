int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  xcrref[m] = 1.0;
  xceref[m] = 1.0;
}


#pragma endscop
}