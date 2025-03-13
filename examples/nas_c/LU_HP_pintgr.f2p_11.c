for(l = N1; l <= N2; l++){
  for(j = N3; j <= N4; j++){
    frc3 = frc3 + (  phi1[j][l] + phi1[j+1][l] + phi1[j][l+1] + phi1[j+1][l+1] + phi2[j][l] + phi2[j+1][l] + phi2[j][l+1] + phi2[j+1][l+1] );
  }
}

