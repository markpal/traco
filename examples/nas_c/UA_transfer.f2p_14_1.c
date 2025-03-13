int main(){
#pragma scop

for(col = 1; col <= N1; col++){
  temp[col][1]=tx[col][1];
  bottom[col]= 0.;
  for(j = 1; j <= 1; j++){
  for(i = 2; i <= N2; i++){
    bottom[col] = bottom[col] + qbnew[i-1][j][1]*tx[col][i];
  }
  }
  
  for(j = 2; j <= N3; j++){
    for(i = 2; i <= N4; i++){
      temp[col][j] = temp[col][j] + qbnew[i-1][j][1]*tx[col][i];
    }
  }
}


#pragma endscop
}