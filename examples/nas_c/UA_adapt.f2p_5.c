int main(){
#pragma scop

for(i = 1; i <= 2; i++){
  yc[i][ielnew]=y1;
  yc[i+4][ielnew]=y1;
}


#pragma endscop
}