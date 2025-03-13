for(j = N1; j <= N2; j++){
  for(i = N3; i <= N4; i++){
    frc1 = frc1 + (  phi1[i][j] + phi1[i+1][j] + phi1[i][j+1] + phi1[i+1][j+1] + phi2[i][j] + phi2[i+1][j] + phi2[i][j+1] + phi2[i+1][j+1] );
  }
}

