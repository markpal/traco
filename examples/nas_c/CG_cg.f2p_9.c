int main(){
#pragma scop

for(j = 2; j <= N1; j++){
  rowstr[j] = rowstr[j] - nzloc[j-1];
}


#pragma endscop
}