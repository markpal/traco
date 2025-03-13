int main(){
#pragma scop

for(k = N1; k <= N2; k++){
  nx[k] = ng[1][k];
  ny[k] = ng[2][k];
  nz[k] = ng[3][k];
}


#pragma endscop
}