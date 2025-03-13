int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      w3m1[i][j][k]=wxm1[i]*wxm1[j]*wxm1[k];
    }
  }
}


#pragma endscop
}