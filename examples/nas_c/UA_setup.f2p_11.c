int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  for(i = 1; i <= N2; i++){
    ixmc2[i][j]=ixtmc2[j][i];
  }
}


#pragma endscop
}