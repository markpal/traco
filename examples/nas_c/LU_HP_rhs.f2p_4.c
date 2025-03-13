int main(){
#pragma scop

for(j = N1; j <= N2; j++){
  for(i = N3; i <= N4; i++){
    for(k = 1; k <= N5; k++){
      flux[1][k] = u[4][i][j][k];
      u41 = u[4][i][j][k] * rho_i[i][j][k];
      ;
      q = qs[i][j][k];
      ;
      flux[2][k] = u[2][i][j][k] * u41;
      flux[3][k] = u[3][i][j][k] * u41;
      flux[4][k] = u[4][i][j][k] * u41 + c2 * (u[5][i][j][k]-q);
      flux[5][k] = ( c1 * u[5][i][j][k] - c2 * q ) * u41;
    }
    ;
    for(k = 2; k <= N6; k++){
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] =  rsd[m][i][j][k] - tz2 * ( flux[m][k+1] - flux[m][k-1] );
      }
    }
    ;
    for(k = 2; k <= N7; k++){
      tmp = rho_i[i][j][k];
      ;
      u21k = tmp * u[2][i][j][k];
      u31k = tmp * u[3][i][j][k];
      u41k = tmp * u[4][i][j][k];
      u51k = tmp * u[5][i][j][k];
      ;
      tmp = rho_i[i][j][k-1];
      ;
      u21km1 = tmp * u[2][i][j][k-1];
      u31km1 = tmp * u[3][i][j][k-1];
      u41km1 = tmp * u[4][i][j][k-1];
      u51km1 = tmp * u[5][i][j][k-1];
      ;
      flux[2][k] = tz3 * ( u21k - u21km1 );
      flux[3][k] = tz3 * ( u31k - u31km1 );
      flux[4][k] = (4.0/3.0) * tz3 * (u41k-u41km1);
      flux[5][k] = 0.50 * ( 1.0 - c1*c5 ) * tz3 * ( ( u21k  **2 + u31k  **2 + u41k  **2 ) - ( u21km1**2 + u31km1**2 + u41km1**2 ) ) + (1.0/6.0) * tz3 * ( u41k**2 - u41km1**2 ) + c1 * c5 * tz3 * ( u51k - u51km1 );
    }
    ;
    for(k = 2; k <= N8; k++){
      rsd[1][i][j][k] = rsd[1][i][j][k] + dz1 * tz1 * (            u[1][i][j][k-1] - 2.0 * u[1][i][j][k] +           u[1][i][j][k+1] );
      rsd[2][i][j][k] = rsd[2][i][j][k] + tz3 * c3 * c4 * ( flux[2][k+1] - flux[2][k] ) + dz2 * tz1 * (            u[2][i][j][k-1] - 2.0 * u[2][i][j][k] +           u[2][i][j][k+1] );
      rsd[3][i][j][k] = rsd[3][i][j][k] + tz3 * c3 * c4 * ( flux[3][k+1] - flux[3][k] ) + dz3 * tz1 * (            u[3][i][j][k-1] - 2.0 * u[3][i][j][k] +           u[3][i][j][k+1] );
      rsd[4][i][j][k] = rsd[4][i][j][k] + tz3 * c3 * c4 * ( flux[4][k+1] - flux[4][k] ) + dz4 * tz1 * (            u[4][i][j][k-1] - 2.0 * u[4][i][j][k] +           u[4][i][j][k+1] );
      rsd[5][i][j][k] = rsd[5][i][j][k] + tz3 * c3 * c4 * ( flux[5][k+1] - flux[5][k] ) + dz5 * tz1 * (            u[5][i][j][k-1] - 2.0 * u[5][i][j][k] +           u[5][i][j][k+1] );
    }
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][i][j][2] = rsd[m][i][j][2] - dssp * ( + 5.0 * u[m][i][j][2] - 4.0 * u[m][i][j][3] +           u[m][i][j][4] );
      rsd[m][i][j][3] = rsd[m][i][j][3] - dssp * ( - 4.0 * u[m][i][j][2] + 6.0 * u[m][i][j][3] - 4.0 * u[m][i][j][4] +           u[m][i][j][5] );
    }
    ;
    for(k = 4; k <= N9; k++){
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] = rsd[m][i][j][k] - dssp * (            u[m][i][j][k-2] - 4.0 * u[m][i][j][k-1] + 6.0 * u[m][i][j][k] - 4.0 * u[m][i][j][k+1] +           u[m][i][j][k+2] );
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][i][j][nz-2] = rsd[m][i][j][nz-2] - dssp * (             u[m][i][j][nz-4] - 4.0 * u[m][i][j][nz-3] + 6.0 * u[m][i][j][nz-2] - 4.0 * u[m][i][j][nz-1]  );
      rsd[m][i][j][nz-1] = rsd[m][i][j][nz-1] - dssp * (             u[m][i][j][nz-3] - 4.0 * u[m][i][j][nz-2] + 5.0 * u[m][i][j][nz-1] );
    }
  }
}


#pragma endscop
}