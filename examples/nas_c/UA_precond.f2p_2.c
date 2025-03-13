int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  dpcmor[i]=1./dpcmor[i];
}


#pragma endscop
}