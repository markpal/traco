int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  tmort[i]=tmort[i]/mormult[i];
}


#pragma endscop
}