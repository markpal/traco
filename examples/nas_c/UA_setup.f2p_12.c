int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  map4[i]=map2[lx1+1-i];
}


#pragma endscop
}