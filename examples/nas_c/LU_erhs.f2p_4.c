int main(){
#pragma scop

for(k = 2; k <= N1; k++){
  for(i = N2; i <= N3; i++){
    for(j = 1; j <= N4; j++){
      flux[1][j] = rsd[3][i][j][k];
      u31 = rsd[3][i][j][k] / rsd[1][i][j][k];
      q = 0.5 * (  rsd[2][i][j][k] * rsd[2][i][j][k] + rsd[3][i][j][k] * rsd[3][i][j][k] + rsd[4][i][j][k] * rsd[4][i][j][k] ) / rsd[1][i][j][k];
      flux[2][j] = rsd[2][i][j][k] * u31;
      flux[3][j] = rsd[3][i][j][k] * u31 + c2 * ( rsd[5][i][j][k] - q );
      flux[4][j] = rsd[4][i][j][k] * u31;
      flux[5][j] = ( c1 * rsd[5][i][j][k] - c2 * q ) * u31;
    }
    ;
    for(j = N5; j <= N6; j++){
      for(m = 1; m <= 5; m++){
        frct[m][i][j][k] =  frct[m][i][j][k] - ty2 * ( flux[m][j+1] - flux[m][j-1] );
      }
    }
    ;
    for(j = N7; j <= N8; j++){
      tmp = 1.0 / rsd[1][i][j][k];
      ;
      u21j = tmp * rsd[2][i][j][k];
      u31j = tmp * rsd[3][i][j][k];
      u41j = tmp * rsd[4][i][j][k];
      u51j = tmp * rsd[5][i][j][k];
      ;
      tmp = 1.0 / rsd[1][i][j-1][k];
      ;
      u21jm1 = tmp * rsd[2][i][j-1][k];
      u31jm1 = tmp * rsd[3][i][j-1][k];
      u41jm1 = tmp * rsd[4][i][j-1][k];
      u51jm1 = tmp * rsd[5][i][j-1][k];
      ;
      flux[2][j] = ty3 * ( u21j - u21jm1 );
      flux[3][j] = (4.0/3.0) * ty3 * ( u31j - u31jm1 );
      flux[4][j] = ty3 * ( u41j - u41jm1 );
      flux[5][j] = 0.5 * ( 1.0 - c1*c5 ) * ty3 * ( ( u21j  *2 + u31j  *2 + u41j  *2 ) - ( u21jm1*2 + u31jm1*2 + u41jm1*2 ) ) + (1.0 / 6.0) * ty3 * ( u31j*2 - u31jm1*2 ) + c1 * c5 * ty3 * ( u51j - u51jm1 );
    }
    ;
    for(j = N9; j <= N10; j++){
      frct[1][i][j][k] = frct[1][i][j][k] + dy1 * ty1 * (            rsd[1][i][j-1][k] - 2.0 * rsd[1][i][j][k] +           rsd[1][i][j+1][k] );
      frct[2][i][j][k] = frct[2][i][j][k] + ty3 * c3 * c4 * ( flux[2][j+1] - flux[2][j] ) + dy2 * ty1 * (            rsd[2][i][j-1][k] - 2.0 * rsd[2][i][j][k] +           rsd[2][i][j+1][k] );
      frct[3][i][j][k] = frct[3][i][j][k] + ty3 * c3 * c4 * ( flux[3][j+1] - flux[3][j] ) + dy3 * ty1 * (            rsd[3][i][j-1][k] - 2.0 * rsd[3][i][j][k] +           rsd[3][i][j+1][k] );
      frct[4][i][j][k] = frct[4][i][j][k] + ty3 * c3 * c4 * ( flux[4][j+1] - flux[4][j] ) + dy4 * ty1 * (            rsd[4][i][j-1][k] - 2.0 * rsd[4][i][j][k] +           rsd[4][i][j+1][k] );
      frct[5][i][j][k] = frct[5][i][j][k] + ty3 * c3 * c4 * ( flux[5][j+1] - flux[5][j] ) + dy5 * ty1 * (            rsd[5][i][j-1][k] - 2.0 * rsd[5][i][j][k] +           rsd[5][i][j+1][k] );
    }
    ;
    for(m = 1; m <= 5; m++){
      frct[m][i][2][k] = frct[m][i][2][k] - dssp * ( + 5.0 * rsd[m][i][2][k] - 4.0 * rsd[m][i][3][k] +           rsd[m][i][4][k] );
      frct[m][i][3][k] = frct[m][i][3][k] - dssp * ( - 4.0 * rsd[m][i][2][k] + 6.0 * rsd[m][i][3][k] - 4.0 * rsd[m][i][4][k] +           rsd[m][i][5][k] );
    }
    ;
    for(j = 4; j <= N11; j++){
      for(m = 1; m <= 5; m++){
        frct[m][i][j][k] = frct[m][i][j][k] - dssp * (            rsd[m][i][j-2][k] - 4.0 * rsd[m][i][j-1][k] + 6.0 * rsd[m][i][j][k] - 4.0 * rsd[m][i][j+1][k] +           rsd[m][i][j+2][k] );
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      frct[m][i][ny-2][k] = frct[m][i][ny-2][k] - dssp * (             rsd[m][i][ny-4][k] - 4.0 * rsd[m][i][ny-3][k] + 6.0 * rsd[m][i][ny-2][k] - 4.0 * rsd[m][i][ny-1][k]  );
      frct[m][i][ny-1][k] = frct[m][i][ny-1][k] - dssp * (             rsd[m][i][ny-3][k] - 4.0 * rsd[m][i][ny-2][k] + 5.0 * rsd[m][i][ny-1][k]  );
    }
    ;
  }
}


#pragma endscop
}