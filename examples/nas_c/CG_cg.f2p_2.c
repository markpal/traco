int main(){
#pragma scop

for(j = 1; j <= N1; j++){
  q[j] = 0.0;
  z[j] = 0.0;
  r[j] = 0.0;
  p[j] = 0.0;
}


#pragma endscop
}