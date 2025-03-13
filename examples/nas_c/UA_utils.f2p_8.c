int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  a[i]=c1*a[i]+b[i];
}


#pragma endscop
}