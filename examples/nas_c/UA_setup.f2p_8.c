int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  for(i = 1; i <= 3; i++){
    qbnew[i][j][2]=qbnew[4-i][lx1+1-j][1];
  }
}


#pragma endscop
}