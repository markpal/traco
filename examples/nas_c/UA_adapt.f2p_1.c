int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  for(kk = 1; kk <= N2; kk++){
    for(jj = 1; jj <= N3; jj++){
      for(ii = 1; ii <= N4; ii++){
        yone[ii][jj][i][1] = yone[ii][jj][i][1] +ixmc1[ii][kk]*x[kk][jj][i];
        yone[ii][jj][i][2] = yone[ii][jj][i][2] +ixmc2[ii][kk]*x[kk][jj][i];
      }
    }
  }

  for(kk = 1; kk <= N5; kk++){
    for(jj = 1; jj <= N6; jj++){
      for(ii = 1; ii <= N7; ii++){
        ytwo[ii][i][jj][1] = ytwo[ii][i][jj][1] + yone[ii][kk][i][1]*ixtmc1[kk][jj];
        ytwo[ii][i][jj][2] = ytwo[ii][i][jj][2] + yone[ii][kk][i][1]*ixtmc2[kk][jj];
        ytwo[ii][i][jj][3] = ytwo[ii][i][jj][3] + yone[ii][kk][i][2]*ixtmc1[kk][jj];
        ytwo[ii][i][jj][4] = ytwo[ii][i][jj][4] + yone[ii][kk][i][2]*ixtmc2[kk][jj];
      }
    }
  }
}


#pragma endscop
}