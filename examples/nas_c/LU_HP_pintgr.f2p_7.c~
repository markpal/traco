int main(){
#pragma scop

for(k = N1; k <= N2; k++){
  for(i = N3; i <= N4; i++){
    frc2 = frc2 + (  phi1[i][k] + phi1[i+1][k] + phi1[i][k+1] + phi1[i+1][k+1] + phi2[i][k] + phi2[i+1][k] + phi2[i][k+1] + phi2[i+1][k+1] );
  }
}


#pragma endscop
}