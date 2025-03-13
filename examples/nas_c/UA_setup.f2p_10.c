int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  for(i = 1; i <= N2; i++){
    ixtmc2[i][j]=ixtmc1[lx1+1-i][lx1+1-j];
  }
}


#pragma endscop
}