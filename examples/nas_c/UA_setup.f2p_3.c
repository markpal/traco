int main(){
#pragma scop

for(i = 1; i <= 4; i++){
  zc[i][1]=0.;
  zc[4+i][1]=1.;
}


#pragma endscop
}