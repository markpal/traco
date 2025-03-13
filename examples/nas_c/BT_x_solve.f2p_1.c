int main(){
#pragma scop

for(i = 1; i <= 5; i++){
  bvec[i] = bvec[i] - ablock[i][1]*avec[1] - ablock[i][2]*avec[2] - ablock[i][3]*avec[3] - ablock[i][4]*avec[4] - ablock[i][5]*avec[5];
}


#pragma endscop
}