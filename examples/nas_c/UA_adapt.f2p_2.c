for(iz = 1; iz <= N1; iz++){
  for(ll = 1; ll <= N2; ll++){
    for(jj = 1; jj <= N3; jj++){
      for(ii = 1; ii <= N4; ii++){
        y[ii][iz][jj] = y[ii][iz][jj] + ytwo[ii][ll][iz][1]*ixtmc1[ll][jj];
        y1[ii][iz][jj][1] = y1[ii][iz][jj][1] + ytwo[ii][ll][iz][3]*ixtmc1[ll][jj];
        y1[ii][iz][jj][2] = y1[ii][iz][jj][2] + ytwo[ii][ll][iz][2]*ixtmc1[ll][jj];
        y1[ii][iz][jj][3] = y1[ii][iz][jj][3] + ytwo[ii][ll][iz][4]*ixtmc1[ll][jj];
        y1[ii][iz][jj][4] = y1[ii][iz][jj][4] + ytwo[ii][ll][iz][1]*ixtmc2[ll][jj];
        y1[ii][iz][jj][5] = y1[ii][iz][jj][5] + ytwo[ii][ll][iz][3]*ixtmc2[ll][jj];
        y1[ii][iz][jj][6] = y1[ii][iz][jj][6] + ytwo[ii][ll][iz][2]*ixtmc2[ll][jj];
        y1[ii][iz][jj][7] = y1[ii][iz][jj][7] + ytwo[ii][ll][iz][4]*ixtmc2[ll][jj];
      }
    }
  }
}

