int main(){
#pragma scop

for(k = N1; k <= N2; k++){
  for(j = N3; j <= N4; j++){
    frc3 = frc3 + (  phi1[j][k] + phi1[j+1][k] + phi1[j][k+1] + phi1[j+1][k+1] + phi2[j][k] + phi2[j+1][k] + phi2[j][k+1] + phi2[j+1][k+1] );
  }
}


#pragma endscop
}