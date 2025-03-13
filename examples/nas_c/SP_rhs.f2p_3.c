int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  for(j = 1; j <= N2; j++){
    for(i = 1; i <= N3; i++){
      uijk = us[i][j][k];
      up1  = us[i+1][j][k];
      um1  = us[i-1][j][k];
      ;
      rhs[1][i][j][k] = rhs[1][i][j][k] + dx1tx1 * (u[1][i+1][j][k] - 2.0*u[1][i][j][k] + u[1][i-1][j][k]) - tx2 * (u[2][i+1][j][k] - u[2][i-1][j][k]);
      ;
      rhs[2][i][j][k] = rhs[2][i][j][k] + dx2tx1 * (u[2][i+1][j][k] - 2.0*u[2][i][j][k] + u[2][i-1][j][k]) + xxcon2*con43 * (up1 - 2.0*uijk + um1) - tx2 * (u[2][i+1][j][k]*up1 - u[2][i-1][j][k]*um1 + (u[5][i+1][j][k]- square[i+1][j][k]- u[5][i-1][j][k]+ square[i-1][j][k])* c2);
      ;
      rhs[3][i][j][k] = rhs[3][i][j][k] + dx3tx1 * (u[3][i+1][j][k] - 2.0*u[3][i][j][k] + u[3][i-1][j][k]) + xxcon2 * (vs[i+1][j][k] - 2.0*vs[i][j][k] + vs[i-1][j][k]) - tx2 * (u[3][i+1][j][k]*up1 - u[3][i-1][j][k]*um1);
      ;
      rhs[4][i][j][k] = rhs[4][i][j][k] + dx4tx1 * (u[4][i+1][j][k] - 2.0*u[4][i][j][k] + u[4][i-1][j][k]) + xxcon2 * (ws[i+1][j][k] - 2.0*ws[i][j][k] + ws[i-1][j][k]) - tx2 * (u[4][i+1][j][k]*up1 - u[4][i-1][j][k]*um1);
      ;
      rhs[5][i][j][k] = rhs[5][i][j][k] + dx5tx1 * (u[5][i+1][j][k] - 2.0*u[5][i][j][k] + u[5][i-1][j][k]) + xxcon3 * (qs[i+1][j][k] - 2.0*qs[i][j][k] + qs[i-1][j][k]) + xxcon4 * (up1*up1 -       2.0*uijk*uijk + um1*um1) + xxcon5 * (u[5][i+1][j][k]*rho_i[i+1][j][k] - 2.0*u[5][i][j][k]*rho_i[i][j][k] + u[5][i-1][j][k]*rho_i[i-1][j][k]) - tx2 * ( (c1*u[5][i+1][j][k] - c2*square[i+1][j][k])*up1 - (c1*u[5][i-1][j][k] - c2*square[i-1][j][k])*um1 );
    }
    ;
    ;
    i = 1;
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k]- dssp * ( 5.0*u[m][i][j][k] - 4.0*u[m][i+1][j][k] + u[m][i+2][j][k]);
    }
    ;
    i = 2;
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * (-4.0*u[m][i-1][j][k] + 6.0*u[m][i][j][k] - 4.0*u[m][i+1][j][k] + u[m][i+2][j][k]);
    }
    ;
    for(i = 3; i <= N4; i++){
      for(m = 1; m <= 5; m++){
        rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * (  u[m][i-2][j][k] - 4.0*u[m][i-1][j][k] + 6.0*u[m][i][j][k] - 4.0*u[m][i+1][j][k] + u[m][i+2][j][k] );
      }
    }
    ;
    i = nx2-1;
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * ( u[m][i-2][j][k] - 4.0*u[m][i-1][j][k] + 6.0*u[m][i][j][k] - 4.0*u[m][i+1][j][k] );
    }
    ;
    i = nx2;
    for(m = 1; m <= 5; m++){
      rhs[m][i][j][k] = rhs[m][i][j][k] - dssp * ( u[m][i-2][j][k] - 4.*u[m][i-1][j][k] + 5.*u[m][i][j][k] );
    }
  }
}


#pragma endscop
}