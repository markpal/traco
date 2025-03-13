int main(){
#pragma scop

for(i = 1; i <= 6; i++){
  cbc[i][1]=0;
}


#pragma endscop
}