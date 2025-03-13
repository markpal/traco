int main(){
#pragma scop

for(j = N1; j <= N2; j++){
  for(i = N3; i <= N4; i++){
    for(k = 1; k <= N5; k++){
      flux[1][k] = rsd[4][i][j][k];
      u41 = rsd[4][i][j][k] / rsd[1][i][j][k];
      q = 0.50 * (  rsd[2][i][j][k] * rsd[2][i][j][k] + rsd[3][i][j][k] * rsd[3][i][j][k] + rsd[4][i][j][k] * rsd[4][i][j][k] ) / rsd[1][i][j][k];
      flux[2][k] = rsd[2][i][j][k] * u41;
      flux[3][k] = rsd[3][i][j][k] * u41;
      flux[4][k] = rsd[4][i][j][k] * u41 + c2 * ( rsd[5][i][j][k] - q );
      flux[5][k] = ( c1 * rsd[5][i][j][k] - c2 * q ) * u41;
    }
    ;
    for(k = 2; k <= N6; k++){
      for(m = 1; m <= 5; m++){
        frct[m][i][j][k] =  frct[m][i][j][k] - tz2 * ( flux[m][k+1] - flux[m][k-1] );
      }
    }
    ;
    for(k = 2; k <= N7; k++){
      tmp = 1.0 / rsd[1][i][j][k];
      ;
      u21k = tmp * rsd[2][i][j][k];
      u31k = tmp * rsd[3][i][j][k];
      u41k = tmp * rsd[4][i][j][k];
      u51k = tmp * rsd[5][i][j][k];
      ;
      tmp = 1.0 / rsd[1][i][j][k-1];
      ;
      u21km1 = tmp * rsd[2][i][j][k-1];
      u31km1 = tmp * rsd[3][i][j][k-1];
      u41km1 = tmp * rsd[4][i][j][k-1];
      u51km1 = tmp * rsd[5][i][j][k-1];
      ;
      flux[2][k] = tz3 * ( u21k - u21km1 );
      flux[3][k] = tz3 * ( u31k - u31km1 );
      flux[4][k] = (4.0/3.0) * tz3 * ( u41k - u41km1 );
      flux[5][k] = 0.50 * ( 1.0 - c1*c5 ) * tz3 * ( ( u21k  *2 + u31k  *2 + u41k  *2 ) - ( u21km1*2 + u31km1*2 + u41km1*2 ) ) + (1.0/6.0) * tz3 * ( u41k*2 - u41km1*2 ) + c1 * c5 * tz3 * ( u51k - u51km1 );
    }
    ;
    for(k = 2; k <= N8; k++){
      frct[1][i][j][k] = frct[1][i][j][k] + dz1 * tz1 * (            rsd[1][i][j][k+1] - 2.0 * rsd[1][i][j][k] +           rsd[1][i][j][k-1] );
      frct[2][i][j][k] = frct[2][i][j][k] + tz3 * c3 * c4 * ( flux[2][k+1] - flux[2][k] ) + dz2 * tz1 * (            rsd[2][i][j][k+1] - 2.0 * rsd[2][i][j][k] +           rsd[2][i][j][k-1] );
      frct[3][i][j][k] = frct[3][i][j][k] + tz3 * c3 * c4 * ( flux[3][k+1] - flux[3][k] ) + dz3 * tz1 * (            rsd[3][i][j][k+1] - 2.0 * rsd[3][i][j][k] +           rsd[3][i][j][k-1] );
      frct[4][i][j][k] = frct[4][i][j][k] + tz3 * c3 * c4 * ( flux[4][k+1] - flux[4][k] ) + dz4 * tz1 * (            rsd[4][i][j][k+1] - 2.0 * rsd[4][i][j][k] +           rsd[4][i][j][k-1] );
      frct[5][i][j][k] = frct[5][i][j][k] + tz3 * c3 * c4 * ( flux[5][k+1] - flux[5][k] ) + dz5 * tz1 * (            rsd[5][i][j][k+1] - 2.0 * rsd[5][i][j][k] +           rsd[5][i][j][k-1] );
    }
    ;
    for(m = 1; m <= 5; m++){
      frct[m][i][j][2] = frct[m][i][j][2] - dssp * ( + 5.0 * rsd[m][i][j][2] - 4.0 * rsd[m][i][j][3] +           rsd[m][i][j][4] );
      frct[m][i][j][3] = frct[m][i][j][3] - dssp * (- 4.0 * rsd[m][i][j][2] + 6.0 * rsd[m][i][j][3] - 4.0 * rsd[m][i][j][4] +           rsd[m][i][j][5] );
    }
    ;
    for(k = 4; k <= N9; k++){
      for(m = 1; m <= 5; m++){
        frct[m][i][j][k] = frct[m][i][j][k] - dssp * (           rsd[m][i][j][k-2] - 4.0 * rsd[m][i][j][k-1] + 6.0 * rsd[m][i][j][k] - 4.0 * rsd[m][i][j][k+1] +           rsd[m][i][j][k+2] );
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      frct[m][i][j][nz-2] = frct[m][i][j][nz-2] - dssp * (            rsd[m][i][j][nz-4] - 4.0 * rsd[m][i][j][nz-3] + 6.0 * rsd[m][i][j][nz-2] - 4.0 * rsd[m][i][j][nz-1]  );
      frct[m][i][j][nz-1] = frct[m][i][j][nz-1] - dssp * (             rsd[m][i][j][nz-3] - 4.0 * rsd[m][i][j][nz-2] + 5.0 * rsd[m][i][j][nz-1]  );
    }
  }
}


#pragma endscop
}