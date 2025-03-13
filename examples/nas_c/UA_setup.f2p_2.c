int main(){
#pragma scop

for(i = 1; i <= 2; i++){
  yc[i][1]=0.;
  yc[2+i][1]=1.;
  yc[4+i][1]=0.;
  yc[6+i][1]=1.;
}


#pragma endscop
}