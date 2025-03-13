int main(){
#pragma scop

for(j = N1; j <= N2; j++){
  for(i = N3; i <= N4; i++){
    for(k = 1; k <= N5; k++){
      utmp[1][k] = u[1][i][j][k];
      utmp[2][k] = u[2][i][j][k];
      utmp[3][k] = u[3][i][j][k];
      utmp[4][k] = u[4][i][j][k];
      utmp[5][k] = u[5][i][j][k];
      utmp[6][k] = rho_i[i][j][k];
    }
    for(k = 1; k <= N6; k++){
      flux[1][k] = utmp[4][k];
      u41 = utmp[4][k] * utmp[6][k];
      ;
      q = qs[i][j][k];
      ;
      flux[2][k] = utmp[2][k] * u41;
      flux[3][k] = utmp[3][k] * u41;
      flux[4][k] = utmp[4][k] * u41 + c2 * (utmp[5][k]-q);
      flux[5][k] = ( c1 * utmp[5][k] - c2 * q ) * u41;
    }
    ;
    for(k = 2; k <= N7; k++){
      for(m = 1; m <= 5; m++){
        rtmp[m][k] =  rsd[m][i][j][k] - tz2 * ( flux[m][k+1] - flux[m][k-1] );
      }
    }
    ;
    for(k = 2; k <= N8; k++){
      tmp = utmp[6][k];
      ;
      u21k = tmp * utmp[2][k];
      u31k = tmp * utmp[3][k];
      u41k = tmp * utmp[4][k];
      u51k = tmp * utmp[5][k];
      ;
      tmp = utmp[6][k-1];
      ;
      u21km1 = tmp * utmp[2][k-1];
      u31km1 = tmp * utmp[3][k-1];
      u41km1 = tmp * utmp[4][k-1];
      u51km1 = tmp * utmp[5][k-1];
      ;
      flux[2][k] = tz3 * ( u21k - u21km1 );
      flux[3][k] = tz3 * ( u31k - u31km1 );
      flux[4][k] = (4.0/3.0) * tz3 * (u41k-u41km1);
      flux[5][k] = 0.50 * ( 1.0 - c1*c5 ) * tz3 * ( ( u21k  **2 + u31k  **2 + u41k  **2 ) - ( u21km1**2 + u31km1**2 + u41km1**2 ) ) + (1.0/6.0) * tz3 * ( u41k**2 - u41km1**2 ) + c1 * c5 * tz3 * ( u51k - u51km1 );
    }
    ;
    for(k = 2; k <= N9; k++){
      rtmp[1][k] = rtmp[1][k] + dz1 * tz1 * (            utmp[1][k-1] - 2.0 * utmp[1][k] +           utmp[1][k+1] );
      rtmp[2][k] = rtmp[2][k] + tz3 * c3 * c4 * ( flux[2][k+1] - flux[2][k] ) + dz2 * tz1 * (            utmp[2][k-1] - 2.0 * utmp[2][k] +           utmp[2][k+1] );
      rtmp[3][k] = rtmp[3][k] + tz3 * c3 * c4 * ( flux[3][k+1] - flux[3][k] ) + dz3 * tz1 * (            utmp[3][k-1] - 2.0 * utmp[3][k] +           utmp[3][k+1] );
      rtmp[4][k] = rtmp[4][k] + tz3 * c3 * c4 * ( flux[4][k+1] - flux[4][k] ) + dz4 * tz1 * (            utmp[4][k-1] - 2.0 * utmp[4][k] +           utmp[4][k+1] );
      rtmp[5][k] = rtmp[5][k] + tz3 * c3 * c4 * ( flux[5][k+1] - flux[5][k] ) + dz5 * tz1 * (            utmp[5][k-1] - 2.0 * utmp[5][k] +           utmp[5][k+1] );
    }
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][i][j][2] = rtmp[m][2] - dssp * ( + 5.0 * utmp[m][2] - 4.0 * utmp[m][3] +           utmp[m][4] );
      rsd[m][i][j][3] = rtmp[m][3] - dssp * ( - 4.0 * utmp[m][2] + 6.0 * utmp[m][3] - 4.0 * utmp[m][4] +           utmp[m][5] );
    }
    ;
    for(k = 4; k <= N10; k++){
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] = rtmp[m][k] - dssp * (            utmp[m][k-2] - 4.0 * utmp[m][k-1] + 6.0 * utmp[m][k] - 4.0 * utmp[m][k+1] +           utmp[m][k+2] );
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][i][j][nz-2] = rtmp[m][nz-2] - dssp * (             utmp[m][nz-4] - 4.0 * utmp[m][nz-3] + 6.0 * utmp[m][nz-2] - 4.0 * utmp[m][nz-1]  );
      rsd[m][i][j][nz-1] = rtmp[m][nz-1] - dssp * (             utmp[m][nz-3] - 4.0 * utmp[m][nz-2] + 5.0 * utmp[m][nz-1] );
    }
  }
}


#pragma endscop
}