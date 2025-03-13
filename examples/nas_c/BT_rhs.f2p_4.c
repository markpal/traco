int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      vijk = vs[i][j][k];
      vp1  = vs[i][j+1][k];
      vm1  = vs[i][j-1][k];
      rhs[1][i][j][k] = rhs[1][i][j][k] + dy1ty1 * (u[1][i][j+1][k] - 2.0*u[1][i][j][k] + u[1][i][j-1][k]) - ty2 * (u[3][i][j+1][k] - u[3][i][j-1][k]);
      rhs[2][i][j][k] = rhs[2][i][j][k] + dy2ty1 * (u[2][i][j+1][k] - 2.0*u[2][i][j][k] + u[2][i][j-1][k]) + yycon2 * (us[i][j+1][k] - 2.0*us[i][j][k] + us[i][j-1][k]) - ty2 * (u[2][i][j+1][k]*vp1 - u[2][i][j-1][k]*vm1);
      rhs[3][i][j][k] = rhs[3][i][j][k] + dy3ty1 * (u[3][i][j+1][k] - 2.0*u[3][i][j][k] + u[3][i][j-1][k]) + yycon2*con43 * (vp1 - 2.0*vijk + vm1) - ty2 * (u[3][i][j+1][k]*vp1 - u[3][i][j-1][k]*vm1 + (u[5][i][j+1][k] - square[i][j+1][k] - u[5][i][j-1][k] + square[i][j-1][k]) *c2);
      rhs[4][i][j][k] = rhs[4][i][j][k] + dy4ty1 * (u[4][i][j+1][k] - 2.0*u[4][i][j][k] + u[4][i][j-1][k]) + yycon2 * (ws[i][j+1][k] - 2.0*ws[i][j][k] + ws[i][j-1][k]) - ty2 * (u[4][i][j+1][k]*vp1 - u[4][i][j-1][k]*vm1);
      rhs[5][i][j][k] = rhs[5][i][j][k] + dy5ty1 * (u[5][i][j+1][k] - 2.0*u[5][i][j][k] + u[5][i][j-1][k]) + yycon3 * (qs[i][j+1][k] - 2.0*qs[i][j][k] + qs[i][j-1][k]) + yycon4 * (vp1*vp1       - 2.0*vijk*vijk + vm1*vm1) + yycon5 * (u[5][i][j+1][k]*rho_i[i][j+1][k] - 2.0*u[5][i][j][k]*rho_i[i][j][k] + u[5][i][j-1][k]*rho_i[i][j-1][k]) - ty2 * ((c1*u[5][i][j+1][k] - c2*square[i][j+1][k]) * vp1 - (c1*u[5][i][j-1][k] - c2*square[i][j-1][k]) * vm1);
    }
  }
  ;
  j = 1;
  for(i = 1; i <= N4; i++){
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k]- dssp * ( 5.0*u[m][i][j][k] - 4.0*u[m][i][j+1][k] + u[m][i][j+2][k]);
    }
  }
  ;
  j = 2;
  for(i = 1; i <= N5; i++){
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * (-4.0*u[m][i][j-1][k] + 6.0*u[m][i][j][k] - 4.0*u[m][i][j+1][k] + u[m][i][j+2][k]);
    }
  }
  ;
  for(j = 3; j <= N6; j++){
    for(i = 1; i <= N7; i++){
      for(m = 1; m <= 5; m++){
        rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * (  u[m][i][j-2][k] - 4.0*u[m][i][j-1][k] + 6.0*u[m][i][j][k] - 4.0*u[m][i][j+1][k] + u[m][i][j+2][k] );
      }
    }
  }
  ;
  j = grid_points[2]-3;
  for(i = 1; i <= N8; i++){
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * ( u[m][i][j-2][k] - 4.0*u[m][i][j-1][k] + 6.0*u[m][i][j][k] - 4.0*u[m][i][j+1][k] );
    }
  }
  ;
  j = grid_points[2]-2;
  for(i = 1; i <= N9; i++){
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * ( u[m][i][j-2][k] - 4.*u[m][i][j-1][k] + 5.*u[m][i][j][k] );
    }
  }
}


#pragma endscop
}