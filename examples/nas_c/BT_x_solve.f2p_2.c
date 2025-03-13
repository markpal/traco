int main(){
#pragma scop

for(j = 1; j <= 5; j++){
  cblock[1][j] = cblock[1][j] - ablock[1][1]*bblock[1][j] - ablock[1][2]*bblock[2][j] - ablock[1][3]*bblock[3][j] - ablock[1][4]*bblock[4][j] - ablock[1][5]*bblock[5][j];
  cblock[2][j] = cblock[2][j] - ablock[2][1]*bblock[1][j] - ablock[2][2]*bblock[2][j] - ablock[2][3]*bblock[3][j] - ablock[2][4]*bblock[4][j] - ablock[2][5]*bblock[5][j];
  cblock[3][j] = cblock[3][j] - ablock[3][1]*bblock[1][j] - ablock[3][2]*bblock[2][j] - ablock[3][3]*bblock[3][j] - ablock[3][4]*bblock[4][j] - ablock[3][5]*bblock[5][j];
  cblock[4][j] = cblock[4][j] - ablock[4][1]*bblock[1][j] - ablock[4][2]*bblock[2][j] - ablock[4][3]*bblock[3][j] - ablock[4][4]*bblock[4][j] - ablock[4][5]*bblock[5][j];
  cblock[5][j] = cblock[5][j] - ablock[5][1]*bblock[1][j] - ablock[5][2]*bblock[2][j] - ablock[5][3]*bblock[3][j] - ablock[5][4]*bblock[4][j] - ablock[5][5]*bblock[5][j];
}


#pragma endscop
}