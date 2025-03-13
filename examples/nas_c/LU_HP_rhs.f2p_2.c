int main(){
#pragma scop

for(k = 2; k <= N1; k++){
  for(j = N2; j <= N3; j++){
    for(i = 1; i <= N4; i++){
      flux[1][i] = u[2][i][j][k];
      u21 = u[2][i][j][k] * rho_i[i][j][k];
      ;
      q = qs[i][j][k];
      ;
      flux[2][i] = u[2][i][j][k] * u21 + c2 * ( u[5][i][j][k] - q );
      flux[3][i] = u[3][i][j][k] * u21;
      flux[4][i] = u[4][i][j][k] * u21;
      flux[5][i] = ( c1 * u[5][i][j][k] - c2 * q ) * u21;
    }
    ;
    for(i = N5; i <= N6; i++){
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] =  rsd[m][i][j][k] - tx2 * ( flux[m][i+1] - flux[m][i-1] );
      }
    }
    ;
    for(i = N7; i <= N8; i++){
      tmp = rho_i[i][j][k];
      ;
      u21i = tmp * u[2][i][j][k];
      u31i = tmp * u[3][i][j][k];
      u41i = tmp * u[4][i][j][k];
      u51i = tmp * u[5][i][j][k];
      ;
      tmp = rho_i[i-1][j][k];
      ;
      u21im1 = tmp * u[2][i-1][j][k];
      u31im1 = tmp * u[3][i-1][j][k];
      u41im1 = tmp * u[4][i-1][j][k];
      u51im1 = tmp * u[5][i-1][j][k];
      ;
      flux[2][i] = (4.0/3.0) * tx3 * (u21i-u21im1);
      flux[3][i] = tx3 * ( u31i - u31im1 );
      flux[4][i] = tx3 * ( u41i - u41im1 );
      flux[5][i] = 0.50 * ( 1.0 - c1*c5 ) * tx3 * ( ( u21i  **2 + u31i  **2 + u41i  **2 ) - ( u21im1**2 + u31im1**2 + u41im1**2 ) ) + (1.0/6.0) * tx3 * ( u21i**2 - u21im1**2 ) + c1 * c5 * tx3 * ( u51i - u51im1 );
    }
    ;
    for(i = N9; i <= N10; i++){
      rsd[1][i][j][k] = rsd[1][i][j][k] + dx1 * tx1 * (            u[1][i-1][j][k] - 2.0 * u[1][i][j][k] +           u[1][i+1][j][k] );
      rsd[2][i][j][k] = rsd[2][i][j][k] + tx3 * c3 * c4 * ( flux[2][i+1] - flux[2][i] ) + dx2 * tx1 * (            u[2][i-1][j][k] - 2.0 * u[2][i][j][k] +           u[2][i+1][j][k] );
      rsd[3][i][j][k] = rsd[3][i][j][k] + tx3 * c3 * c4 * ( flux[3][i+1] - flux[3][i] ) + dx3 * tx1 * (            u[3][i-1][j][k] - 2.0 * u[3][i][j][k] +           u[3][i+1][j][k] );
      rsd[4][i][j][k] = rsd[4][i][j][k] + tx3 * c3 * c4 * ( flux[4][i+1] - flux[4][i] ) + dx4 * tx1 * (            u[4][i-1][j][k] - 2.0 * u[4][i][j][k] +           u[4][i+1][j][k] );
      rsd[5][i][j][k] = rsd[5][i][j][k] + tx3 * c3 * c4 * ( flux[5][i+1] - flux[5][i] ) + dx5 * tx1 * (            u[5][i-1][j][k] - 2.0 * u[5][i][j][k] +           u[5][i+1][j][k] );
    }
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][2][j][k] = rsd[m][2][j][k] - dssp * ( + 5.0 * u[m][2][j][k] - 4.0 * u[m][3][j][k] +           u[m][4][j][k] );
      rsd[m][3][j][k] = rsd[m][3][j][k] - dssp * ( - 4.0 * u[m][2][j][k] + 6.0 * u[m][3][j][k] - 4.0 * u[m][4][j][k] +           u[m][5][j][k] );
    }
    ;
    for(i = 4; i <= N11; i++){
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] = rsd[m][i][j][k] - dssp * (            u[m][i-2][j][k] - 4.0 * u[m][i-1][j][k] + 6.0 * u[m][i][j][k] - 4.0 * u[m][i+1][j][k] +           u[m][i+2][j][k] );
      }
    }
    ;
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][nx-2][j][k] = rsd[m][nx-2][j][k] - dssp * (             u[m][nx-4][j][k] - 4.0 * u[m][nx-3][j][k] + 6.0 * u[m][nx-2][j][k] - 4.0 * u[m][nx-1][j][k]  );
      rsd[m][nx-1][j][k] = rsd[m][nx-1][j][k] - dssp * (             u[m][nx-3][j][k] - 4.0 * u[m][nx-2][j][k] + 5.0 * u[m][nx-1][j][k] );
    }
    ;
  }
}


#pragma endscop
}