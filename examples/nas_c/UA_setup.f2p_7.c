int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  for(i = 1; i <= N2; i++){
    dxtm1[i][j]=dxm1[j][i];
  }
}


#pragma endscop
}