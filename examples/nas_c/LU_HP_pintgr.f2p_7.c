for(l = N1; l <= N2; l++){
  for(i = N3; i <= N4; i++){
    frc2 = frc2 + (  phi1[i][l] + phi1[i+1][l] + phi1[i][l+1] + phi1[i+1][l+1] + phi2[i][l] + phi2[i+1][l] + phi2[i][l+1] + phi2[i+1][l+1] );
  }
}

