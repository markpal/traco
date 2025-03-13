int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  x[i] = 1.0;
}


#pragma endscop
}