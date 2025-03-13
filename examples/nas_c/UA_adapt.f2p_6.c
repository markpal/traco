int main(){
#pragma scop

for(i = 3; i <= 4; i++){
  yc[i][ielnew]=y2;
  yc[i+4][ielnew]=y2;
}


#pragma endscop
}