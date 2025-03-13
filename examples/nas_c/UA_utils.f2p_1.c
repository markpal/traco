int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  a[i] = 1./a[i];
}


#pragma endscop
}