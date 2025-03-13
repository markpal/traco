int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  zeta = dble[k] * dnzm1;
  for(i = 1; i <= N2; i++){
    xi = dble[i] * dnxm1;
    ;
    for(j = 0; j <= N3; j++){
      eta = dble[j] * dnym1;
      ;
      for(n = 1; n <= 5; n++){
        dtemp[n] =  ce[n][1] + xi*(ce[n][2] + xi*(ce[n][5] + xi*(ce[n][8] + xi*ce[n][11]))) + eta*(ce[n][3] + eta*(ce[n][6] + eta*(ce[n][9] + eta*ce[n][12]))) + zeta*(ce[n][4] + zeta*(ce[n][7] + zeta*(ce[n][10] +  zeta*ce[n][13])));
      }
      for(m = 1; m <= 5; m++){
        ue[j][m] = dtemp[m];
      }
      ;
      dtpp = 1.0/dtemp[1];
      ;
      for(m = 2; m <= 5; m++){
        buf[j][m] = dtpp * dtemp[m];
      }
      ;
      cuf[j]   = buf[j][3] * buf[j][3];
      buf[j][1] = cuf[j] + buf[j][2] * buf[j][2] + buf[j][4] * buf[j][4];
      q[j] = 0.5*(buf[j][2]*ue[j][2] + buf[j][3]*ue[j][3] + buf[j][4]*ue[j][4]);
    }
    ;
    for(j = 1; j <= N4; j++){
      jm1 = j-1;
      jp1 = j+1;
      ;
      fff[1][i][j][k] = fff[1][i][j][k] - ty2*( ue[jp1][3]-ue[jm1][3] )+ dy1ty1*(ue[jp1][1]-2.0*ue[j][1]+ue[jm1][1]);
      ;
      fff[2][i][j][k] = fff[2][i][j][k] - ty2*( ue[jp1][2]*buf[jp1][3]-ue[jm1][2]*buf[jm1][3])+ yycon2*(buf[jp1][2]-2.0*buf[j][2]+buf[jm1][2])+ dy2ty1*( ue[jp1][2]-2.0* ue[j][2]+ ue[jm1][2]);
      ;
      fff[3][i][j][k] = fff[3][i][j][k] - ty2*( (ue[jp1][3]*buf[jp1][3]+c2*(ue[jp1][5]-q[jp1]))- (ue[jm1][3]*buf[jm1][3]+c2*(ue[jm1][5]-q[jm1])))+ yycon1*(buf[jp1][3]-2.0*buf[j][3]+buf[jm1][3])+ dy3ty1*( ue[jp1][3]-2.0*ue[j][3] +ue[jm1][3]);
      ;
      fff[4][i][j][k] = fff[4][i][j][k] - ty2*( ue[jp1][4]*buf[jp1][3]-ue[jm1][4]*buf[jm1][3])+ yycon2*(buf[jp1][4]-2.0*buf[j][4]+buf[jm1][4])+ dy4ty1*( ue[jp1][4]-2.0*ue[j][4]+ ue[jm1][4]);
      ;
      fff[5][i][j][k] = fff[5][i][j][k] - ty2*( buf[jp1][3]*(c1*ue[jp1][5]-c2*q[jp1])- buf[jm1][3]*(c1*ue[jm1][5]-c2*q[jm1]))+ 0.5*yycon3*(buf[jp1][1]-2.0*buf[j][1]+ buf[jm1][1])+ yycon4*(cuf[jp1]-2.0*cuf[j]+cuf[jm1])+ yycon5*(buf[jp1][5]-2.0*buf[j][5]+buf[jm1][5])+ dy5ty1*(ue[jp1][5]-2.0*ue[j][5]+ue[jm1][5]);
    }
    ;
    for(m = 1; m <= 5; m++){
      j = 1;
      fff[m][i][j][k] = fff[m][i][j][k] - dssp * (5.0*ue[j][m] - 4.0*ue[j+1][m] +ue[j+2][m]);
      j = 2;
      fff[m][i][j][k] = fff[m][i][j][k] - dssp * (-4.0*ue[j-1][m] + 6.0*ue[j][m] - 4.0*ue[j+1][m] +       ue[j+2][m]);
    }
    ;
    for(j = 3; j <= N5; j++){
      for(m = 1; m <= 5; m++){
        fff[m][i][j][k] = fff[m][i][j][k] - dssp* (ue[j-2][m] - 4.0*ue[j-1][m] + 6.0*ue[j][m] - 4.0*ue[j+1][m] + ue[j+2][m]);
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      j = grid_points[2]-3;
      fff[m][i][j][k] = fff[m][i][j][k] - dssp * (ue[j-2][m] - 4.0*ue[j-1][m] + 6.0*ue[j][m] - 4.0*ue[j+1][m]);
      j = grid_points[2]-2;
      fff[m][i][j][k] = fff[m][i][j][k] - dssp * (ue[j-2][m] - 4.0*ue[j-1][m] + 5.0*ue[j][m]);
      ;
    }
    ;
  }
}


#pragma endscop
}