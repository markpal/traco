int main(){
#pragma scop

for(k = 2; k <= N1; k++){
  for(i = N2; i <= N3; i++){
    for(j = 1; j <= N4; j++){
      flux[1][j] = u[3][i][j][k];
      u31 = u[3][i][j][k] * rho_i[i][j][k];
      ;
      q = qs[i][j][k];
      ;
      flux[2][j] = u[2][i][j][k] * u31;
      flux[3][j] = u[3][i][j][k] * u31 + c2 * (u[5][i][j][k]-q);
      flux[4][j] = u[4][i][j][k] * u31;
      flux[5][j] = ( c1 * u[5][i][j][k] - c2 * q ) * u31;
    }
    ;
    for(j = N5; j <= N6; j++){
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] =  rsd[m][i][j][k] - ty2 * ( flux[m][j+1] - flux[m][j-1] );
      }
    }
    ;
    for(j = N7; j <= N8; j++){
      tmp = rho_i[i][j][k];
      ;
      u21j = tmp * u[2][i][j][k];
      u31j = tmp * u[3][i][j][k];
      u41j = tmp * u[4][i][j][k];
      u51j = tmp * u[5][i][j][k];
      ;
      tmp = rho_i[i][j-1][k];
      u21jm1 = tmp * u[2][i][j-1][k];
      u31jm1 = tmp * u[3][i][j-1][k];
      u41jm1 = tmp * u[4][i][j-1][k];
      u51jm1 = tmp * u[5][i][j-1][k];
      ;
      flux[2][j] = ty3 * ( u21j - u21jm1 );
      flux[3][j] = (4.0/3.0) * ty3 * (u31j-u31jm1);
      flux[4][j] = ty3 * ( u41j - u41jm1 );
      flux[5][j] = 0.50 * ( 1.0 - c1*c5 ) * ty3 * ( ( u21j  **2 + u31j  **2 + u41j  **2 ) - ( u21jm1**2 + u31jm1**2 + u41jm1**2 ) ) + (1.0/6.0) * ty3 * ( u31j**2 - u31jm1**2 ) + c1 * c5 * ty3 * ( u51j - u51jm1 );
    }
    ;
    for(j = N9; j <= N10; j++){
      ;
      rsd[1][i][j][k] = rsd[1][i][j][k] + dy1 * ty1 * (            u[1][i][j-1][k] - 2.0 * u[1][i][j][k] +           u[1][i][j+1][k] );
      ;
      rsd[2][i][j][k] = rsd[2][i][j][k] + ty3 * c3 * c4 * ( flux[2][j+1] - flux[2][j] ) + dy2 * ty1 * (            u[2][i][j-1][k] - 2.0 * u[2][i][j][k] +           u[2][i][j+1][k] );
      ;
      rsd[3][i][j][k] = rsd[3][i][j][k] + ty3 * c3 * c4 * ( flux[3][j+1] - flux[3][j] ) + dy3 * ty1 * (            u[3][i][j-1][k] - 2.0 * u[3][i][j][k] +           u[3][i][j+1][k] );
      ;
      rsd[4][i][j][k] = rsd[4][i][j][k] + ty3 * c3 * c4 * ( flux[4][j+1] - flux[4][j] ) + dy4 * ty1 * (            u[4][i][j-1][k] - 2.0 * u[4][i][j][k] +           u[4][i][j+1][k] );
      ;
      rsd[5][i][j][k] = rsd[5][i][j][k] + ty3 * c3 * c4 * ( flux[5][j+1] - flux[5][j] ) + dy5 * ty1 * (            u[5][i][j-1][k] - 2.0 * u[5][i][j][k] +           u[5][i][j+1][k] );
      ;
    }
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][i][2][k] = rsd[m][i][2][k] - dssp * ( + 5.0 * u[m][i][2][k] - 4.0 * u[m][i][3][k] +           u[m][i][4][k] );
      rsd[m][i][3][k] = rsd[m][i][3][k] - dssp * ( - 4.0 * u[m][i][2][k] + 6.0 * u[m][i][3][k] - 4.0 * u[m][i][4][k] +           u[m][i][5][k] );
    }
    ;
    for(j = 4; j <= N11; j++){
      for(m = 1; m <= 5; m++){
        rsd[m][i][j][k] = rsd[m][i][j][k] - dssp * (            u[m][i][j-2][k] - 4.0 * u[m][i][j-1][k] + 6.0 * u[m][i][j][k] - 4.0 * u[m][i][j+1][k] +           u[m][i][j+2][k] );
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      rsd[m][i][ny-2][k] = rsd[m][i][ny-2][k] - dssp * (             u[m][i][ny-4][k] - 4.0 * u[m][i][ny-3][k] + 6.0 * u[m][i][ny-2][k] - 4.0 * u[m][i][ny-1][k]  );
      rsd[m][i][ny-1][k] = rsd[m][i][ny-1][k] - dssp * (             u[m][i][ny-3][k] - 4.0 * u[m][i][ny-2][k] + 5.0 * u[m][i][ny-1][k] );
    }
    ;
  }
}


#pragma endscop
}