int main(){
#pragma scop

for(k = 2; k <= N1; k++){
  for(j = N2; j <= N3; j++){
    for(i = 1; i <= N4; i++){
      flux[1][i] = rsd[2][i][j][k];
      u21 = rsd[2][i][j][k] / rsd[1][i][j][k];
      q = 0.50 * (  rsd[2][i][j][k] * rsd[2][i][j][k] + rsd[3][i][j][k] * rsd[3][i][j][k] + rsd[4][i][j][k] * rsd[4][i][j][k] ) / rsd[1][i][j][k];
      flux[2][i] = rsd[2][i][j][k] * u21 + c2 * ( rsd[5][i][j][k] - q );
      flux[3][i] = rsd[3][i][j][k] * u21;
      flux[4][i] = rsd[4][i][j][k] * u21;
      flux[5][i] = ( c1 * rsd[5][i][j][k] - c2 * q ) * u21;
    }
    ;
    for(i = N5; i <= N6; i++){
      for(m = 1; m <= 5; m++){
        frct[m][i][j][k] =  frct[m][i][j][k] - tx2 * ( flux[m][i+1] - flux[m][i-1] );
      }
    }
    for(i = N7; i <= N8; i++){
      tmp = 1.0 / rsd[1][i][j][k];
      ;
      u21i = tmp * rsd[2][i][j][k];
      u31i = tmp * rsd[3][i][j][k];
      u41i = tmp * rsd[4][i][j][k];
      u51i = tmp * rsd[5][i][j][k];
      ;
      tmp = 1.0 / rsd[1][i-1][j][k];
      ;
      u21im1 = tmp * rsd[2][i-1][j][k];
      u31im1 = tmp * rsd[3][i-1][j][k];
      u41im1 = tmp * rsd[4][i-1][j][k];
      u51im1 = tmp * rsd[5][i-1][j][k];
      ;
      flux[2][i] = (4.0/3.0) * tx3 * ( u21i - u21im1 );
      flux[3][i] = tx3 * ( u31i - u31im1 );
      flux[4][i] = tx3 * ( u41i - u41im1 );
      flux[5][i] = 0.50 * ( 1.0 - c1*c5 ) * tx3 * ( ( u21i  **2 + u31i  **2 + u41i  **2 ) - ( u21im1**2 + u31im1**2 + u41im1**2 ) ) + (1.0/6.0) * tx3 * ( u21i**2 - u21im1**2 ) + c1 * c5 * tx3 * ( u51i - u51im1 );
    }
    ;
    for(i = N9; i <= N10; i++){
      frct[1][i][j][k] = frct[1][i][j][k] + dx1 * tx1 * (            rsd[1][i-1][j][k] - 2.0 * rsd[1][i][j][k] +           rsd[1][i+1][j][k] );
      frct[2][i][j][k] = frct[2][i][j][k] + tx3 * c3 * c4 * ( flux[2][i+1] - flux[2][i] ) + dx2 * tx1 * (            rsd[2][i-1][j][k] - 2.0 * rsd[2][i][j][k] +           rsd[2][i+1][j][k] );
      frct[3][i][j][k] = frct[3][i][j][k] + tx3 * c3 * c4 * ( flux[3][i+1] - flux[3][i] ) + dx3 * tx1 * (            rsd[3][i-1][j][k] - 2.0 * rsd[3][i][j][k] +           rsd[3][i+1][j][k] );
      frct[4][i][j][k] = frct[4][i][j][k] + tx3 * c3 * c4 * ( flux[4][i+1] - flux[4][i] ) + dx4 * tx1 * (            rsd[4][i-1][j][k] - 2.0 * rsd[4][i][j][k] +           rsd[4][i+1][j][k] );
      frct[5][i][j][k] = frct[5][i][j][k] + tx3 * c3 * c4 * ( flux[5][i+1] - flux[5][i] ) + dx5 * tx1 * (            rsd[5][i-1][j][k] - 2.0 * rsd[5][i][j][k] +           rsd[5][i+1][j][k] );
    }
    ;
    for(m = 1; m <= 5; m++){
      frct[m][2][j][k] = frct[m][2][j][k] - dssp * ( + 5.0 * rsd[m][2][j][k] - 4.0 * rsd[m][3][j][k] +           rsd[m][4][j][k] );
      frct[m][3][j][k] = frct[m][3][j][k] - dssp * ( - 4.0 * rsd[m][2][j][k] + 6.0 * rsd[m][3][j][k] - 4.0 * rsd[m][4][j][k] +           rsd[m][5][j][k] );
    }
    ;
    for(i = 4; i <= N11; i++){
      for(m = 1; m <= 5; m++){
        frct[m][i][j][k] = frct[m][i][j][k] - dssp * (            rsd[m][i-2][j][k] - 4.0 * rsd[m][i-1][j][k] + 6.0 * rsd[m][i][j][k] - 4.0 * rsd[m][i+1][j][k] +           rsd[m][i+2][j][k] );
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      frct[m][nx-2][j][k] = frct[m][nx-2][j][k] - dssp * (             rsd[m][nx-4][j][k] - 4.0 * rsd[m][nx-3][j][k] + 6.0 * rsd[m][nx-2][j][k] - 4.0 * rsd[m][nx-1][j][k]  );
      frct[m][nx-1][j][k] = frct[m][nx-1][j][k] - dssp * (             rsd[m][nx-3][j][k] - 4.0 * rsd[m][nx-2][j][k] + 5.0 * rsd[m][nx-1][j][k] );
    }
    ;
  }
}


#pragma endscop
}