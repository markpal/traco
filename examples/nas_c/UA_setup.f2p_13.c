int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  xfrac[i]=zgm1[i]*0.5 + 0.5;
}


#pragma endscop
}