int main(){
#pragma scop

for(i = 0; i <= N1; i++){
  for(k = 0; k <= N2; k++){
    phi1[i][k] = 0.;
    phi2[i][k] = 0.;
  }
}


#pragma endscop
}