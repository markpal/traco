int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  a[i]=a[i]+b[i];
}


#pragma endscop
}