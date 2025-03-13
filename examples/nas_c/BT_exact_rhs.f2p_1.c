int main(){
#pragma scop



for(k = 0; k <= N1; k++){
  for(j = 0; j <= N2; j++){
    for(i = 0; i <= N3; i++){
      for(m = 1; m <= 5; m++){
        forcing[m][i][j][k] = 0.0;
      }
    }
  }
}


#pragma endscop
}