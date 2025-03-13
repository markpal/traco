int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  eta = dble[j] * dnym1;
  for(i = 1; i <= N2; i++){
    xi = dble[i] * dnxm1;
    ;
    for(k = 0; k <= N3; k++){
      zeta = dble[k] * dnzm1;
      ;
      for(m = 1; m <= 5; m++){
        dtemp[m] =  ce[m][1] + xi*(ce[m][2] + xi*(ce[m][5] + xi*(ce[m][8] + xi*ce[m][11]))) + eta*(ce[m][3] + eta*(ce[m][6] + eta*(ce[m][9] + eta*ce[m][12])))+ zeta*(ce[m][4] + zeta*(ce[m][7] + zeta*(ce[m][10] + zeta*ce[m][13])));
      }
      for(m = 1; m <= 5; m++){
        ue[k][m] = dtemp[m];
      }
      ;
      dtpp = 1.0/dtemp[1];
      ;
      for(m = 2; m <= 5; m++){
        buf[k][m] = dtpp * dtemp[m];
      }
      ;
      cuf[k]   = buf[k][4] * buf[k][4];
      buf[k][1] = cuf[k] + buf[k][2] * buf[k][2] + buf[k][3] * buf[k][3];
      q[k] = 0.5*(buf[k][2]*ue[k][2] + buf[k][3]*ue[k][3] + buf[k][4]*ue[k][4]);
    }
    ;
    for(k = 1; k <= N4; k++){
      km1 = k-1;
      kp1 = k+1;
      ;
      ffff[1][i][j][k] = ffff[1][i][j][k] - tz2*( ue[kp1][4]-ue[km1][4] )+ dz1tz1*(ue[kp1][1]-2.0*ue[k][1]+ue[km1][1]);
      ;
      ffff[2][i][j][k] = ffff[2][i][j][k] - tz2 * ( ue[kp1][2]*buf[kp1][4]-ue[km1][2]*buf[km1][4])+ zzcon2*(buf[kp1][2]-2.0*buf[k][2]+buf[km1][2])+ dz2tz1*( ue[kp1][2]-2.0* ue[k][2]+ ue[km1][2]);
      ;
      ffff[3][i][j][k] = ffff[3][i][j][k] - tz2 * ( ue[kp1][3]*buf[kp1][4]-ue[km1][3]*buf[km1][4])+ zzcon2*(buf[kp1][3]-2.0*buf[k][3]+buf[km1][3])+ dz3tz1*(ue[kp1][3]-2.0*ue[k][3]+ue[km1][3]);
      ;
      ffff[4][i][j][k] = ffff[4][i][j][k] - tz2 * ( (ue[kp1][4]*buf[kp1][4]+c2*(ue[kp1][5]-q[kp1]))- (ue[km1][4]*buf[km1][4]+c2*(ue[km1][5]-q[km1])))+ zzcon1*(buf[kp1][4]-2.0*buf[k][4]+buf[km1][4])+ dz4tz1*( ue[kp1][4]-2.0*ue[k][4] +ue[km1][4]);
      ;
      ffff[5][i][j][k] = ffff[5][i][j][k] - tz2 * ( buf[kp1][4]*(c1*ue[kp1][5]-c2*q[kp1])- buf[km1][4]*(c1*ue[km1][5]-c2*q[km1]))+ 0.5*zzcon3*(buf[kp1][1]-2.0*buf[k][1] +buf[km1][1])+ zzcon4*(cuf[kp1]-2.0*cuf[k]+cuf[km1])+ zzcon5*(buf[kp1][5]-2.0*buf[k][5]+buf[km1][5])+ dz5tz1*( ue[kp1][5]-2.0*ue[k][5]+ ue[km1][5]);
    }
    ;
    for(m = 1; m <= 5; m++){
      k = 1;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (5.0*ue[k][m] - 4.0*ue[k+1][m] +ue[k+2][m]);
      k = 2;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (-4.0*ue[k-1][m] + 6.0*ue[k][m] - 4.0*ue[k+1][m] +       ue[k+2][m]);
    }
    ;
    for(m = 1; m <= 5; m++){
      for(k = 3; k <= N5; k++){
        ffff[m][i][j][k] = ffff[m][i][j][k] - dssp* (ue[k-2][m] - 4.0*ue[k-1][m] + 6.0*ue[k][m] - 4.0*ue[k+1][m] + ue[k+2][m]);
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      k = grid_points[3]-3;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (ue[k-2][m] - 4.0*ue[k-1][m] + 6.0*ue[k][m] - 4.0*ue[k+1][m]);
      k = grid_points[3]-2;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (ue[k-2][m] - 4.0*ue[k-1][m] + 5.0*ue[k][m]);
    }
    ;
  }
}


#pragma endscop
}