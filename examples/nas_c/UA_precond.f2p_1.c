int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  for(i = 1; i <= N2; i++){
    dxtm1_2[i][j]=dxtm1[i][j]**2;
  }
}


#pragma endscop
}