int main(){
#pragma scop

for(k = 1; k <= N1; k++){
  zeta = dble[k] * dnzm1;
  for(j = 1; j <= N2; j++){
    eta = dble[j] * dnym1;
    ;
    for(i = 0; i <= N3; i++){
      xi = dble[i] * dnxm1;
      ;
      for(m = 1; m <= 5; m++){
        dtemp[m] =  ce[m][1] + xi*(ce[m][2] + xi*(ce[m][5] + xi*(ce[m][8] + xi*ce[m][11]))) + eta*(ce[m][3] + eta*(ce[m][6] + eta*(ce[m][9] + eta*ce[m][12])))+ zeta*(ce[m][4] + zeta*(ce[m][7] + zeta*(ce[m][10] + zeta*ce[m][13])));
      }
      for(m = 1; m <= 5; m++){
        ue[i][m] = dtemp[m];
      }
      ;
      dtpp = 1.0 / dtemp[1];
      ;
      for(m = 2; m <= 5; m++){
        buf[i][m] = dtpp * dtemp[m];
      }
      ;
      cuf[i]   = buf[i][2] * buf[i][2];
      buf[i][1] = cuf[i] + buf[i][3] * buf[i][3] + buf[i][4] * buf[i][4];
      q[i] = 0.5*(buf[i][2]*ue[i][2] + buf[i][3]*ue[i][3] + buf[i][4]*ue[i][4]);
      ;
    }
    ;
    for(i = 1; i <= N4; i++){
      im1 = i-1;
      ip1 = i+1;
      ;
      ffff[1][i][j][k] = ffff[1][i][j][k] - tx2*( ue[ip1][2]-ue[im1][2] )+ dx1tx1*(ue[ip1][1]-2.0*ue[i][1]+ue[im1][1]);
      ;
      ffff[2][i][j][k] = ffff[2][i][j][k] - tx2 * ( (ue[ip1][2]*buf[ip1][2]+c2*(ue[ip1][5]-q[ip1]))- (ue[im1][2]*buf[im1][2]+c2*(ue[im1][5]-q[im1])))+ xxcon1*(buf[ip1][2]-2.0*buf[i][2]+buf[im1][2])+ dx2tx1*( ue[ip1][2]-2.0* ue[i][2]+ue[im1][2]);
      ;
      ffff[3][i][j][k] = ffff[3][i][j][k] - tx2 * ( ue[ip1][3]*buf[ip1][2]-ue[im1][3]*buf[im1][2])+ xxcon2*(buf[ip1][3]-2.0*buf[i][3]+buf[im1][3])+ dx3tx1*( ue[ip1][3]-2.0*ue[i][3] +ue[im1][3]);
      ;
      ffff[4][i][j][k] = ffff[4][i][j][k] - tx2*( ue[ip1][4]*buf[ip1][2]-ue[im1][4]*buf[im1][2])+ xxcon2*(buf[ip1][4]-2.0*buf[i][4]+buf[im1][4])+ dx4tx1*( ue[ip1][4]-2.0* ue[i][4]+ ue[im1][4]);
      ;
      ffff[5][i][j][k] = ffff[5][i][j][k] - tx2*( buf[ip1][2]*(c1*ue[ip1][5]-c2*q[ip1])- buf[im1][2]*(c1*ue[im1][5]-c2*q[im1]))+ 0.5*xxcon3*(buf[ip1][1]-2.0*buf[i][1]+ buf[im1][1])+ xxcon4*(cuf[ip1]-2.0*cuf[i]+cuf[im1])+ xxcon5*(buf[ip1][5]-2.0*buf[i][5]+buf[im1][5])+ dx5tx1*( ue[ip1][5]-2.0* ue[i][5]+ ue[im1][5]);
    }
    ;
    for(m = 1; m <= 5; m++){
      i = 1;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (5.0*ue[i][m] - 4.0*ue[i+1][m] +ue[i+2][m]);
      i = 2;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (-4.0*ue[i-1][m] + 6.0*ue[i][m] - 4.0*ue[i+1][m] +       ue[i+2][m]);
    }
    ;
    for(m = 1; m <= 5; m++){
      for(i = 3; i <= N5; i++){
        ffff[m][i][j][k] = ffff[m][i][j][k] - dssp* (ue[i-2][m] - 4.0*ue[i-1][m] + 6.0*ue[i][m] - 4.0*ue[i+1][m] + ue[i+2][m]);
      }
    }
    ;
    for(m = 1; m <= 5; m++){
      i = grid_points[1]-3;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (ue[i-2][m] - 4.0*ue[i-1][m] + 6.0*ue[i][m] - 4.0*ue[i+1][m]);
      i = grid_points[1]-2;
      ffff[m][i][j][k] = ffff[m][i][j][k] - dssp * (ue[i-2][m] - 4.0*ue[i-1][m] + 5.0*ue[i][m]);
    }
    ;
  }
}


#pragma endscop
}