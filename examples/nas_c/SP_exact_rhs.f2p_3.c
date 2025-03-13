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
      for(m = 1; m <= 5; m++){
        dtemp[m] =  ce[m][1] + xi*(ce[m][2] + xi*(ce[m][5] + xi*(ce[m][8] + xi*ce[m][11]))) + eta*(ce[m][3] + eta*(ce[m][6] + eta*(ce[m][9] + eta*ce[m][12])))+ zeta*(ce[m][4] + zeta*(ce[m][7] + zeta*(ce[m][10] + zeta*ce[m][13])));
      }
      for(m = 1; m <= 5; m++){
        ue[j][m] = dtemp[m];
      }
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
      ffff[1][i][j][k] = ffff[1][i][j][k] - ty2*( ue[jp1][3]-ue[jm1][3] )+ dy1ty1*(ue[jp1][1]-2.0*ue[j][1]+ue[jm1][1]);
      ;
      ffff[2][i][j][k] = ffff[2][i][j][k] - ty2*( ue[jp1][2]*buf[jp1][3]-ue[jm1][2]*buf[jm1][3])+ yycon2*(buf[jp1][2]-2.0*buf[j][2]+buf[jm1][2])+ dy2ty1*( ue[jp1][2]-2.0* ue[j][2]+ ue[jm1][2]);
      ;
      ffff[3][i][j][k] = ffff[3][i][j][k] - ty2*( (ue[jp1][3]*buf[jp1][3]+c2*(ue[jp1][5]-q[jp1]))- (ue[jm1][3]*buf[jm1][3]+c2*(ue[jm1][5]-q[jm1])))+ yycon1*(buf[jp1][3]-2.0*buf[j][3]+buf[jm1][3])+ dy3ty1*( ue[jp1][3]-2.0*ue[j][3] +ue[jm1][3]);
      ;
      ffff[4][i][j][k] = ffff[4][i][j][k] - ty2*( ue[jp1][4]*buf[jp1][3]-ue[jm1][4]*buf[jm1][3])+ yycon2*(buf[jp1][4]-2.0*buf[j][4]+buf[jm1][4])+ dy4ty1*( ue[jp1][4]-2.0*ue[j][4]+ ue[jm1][4]);
      ;
      ffff[5][i][j][k] = ffff[5][i][j][k] - ty2*( buf[jp1][3]*(c1*ue[jp1][5]-c2*q[jp1])- buf[jm1][3]*(c1*ue[jm1][5]-c2*q[jm1]))+ 0.5*yycon3*(buf[jp1][1]-2.0*buf[j][1]+ buf[jm1][1])+ yycon4*(cuf[jp1]-2.0*cuf[j]+cuf[jm1])+ yycon5*(buf[jp1][5]-2.0*buf[j][5]+buf[jm1][5])+ dy5ty1*(ue[jp1][5]-2.0*ue[j][5]+ue[jm1][5]);
    }
    ;
    for(m = 1; m <= 5; m++){
      j = 1;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (5.0*ue[j][m] - 4.0*ue[j+1][m] +ue[j+2][m]);
      j = 2;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (-4.0*ue[j-1][m] + 6.0*ue[j][m] - 4.0*ue[j+1][m] +       ue[j+2][m]);
    }
    ;
    for(m = 1; m <= 5; m++){
      for(j = 3; j <= N5; j++){
        ffff[m][i][j][k] = ffff[m][i][j][k] - dssp* (ue[j-2][m] - 4.0*ue[j-1][m] + 6.0*ue[j][m] - 4.0*ue[j+1][m] + ue[j+2][m]);
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      j = grid_points[2]-3;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (ue[j-2][m] - 4.0*ue[j-1][m] + 6.0*ue[j][m] - 4.0*ue[j+1][m]);
      j = grid_points[2]-2;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (ue[j-2][m] - 4.0*ue[j-1][m] + 5.0*ue[j][m]);
      ;
    }
    ;
  }
}


#pragma endscop
}