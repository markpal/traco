int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  ii = i-1-((i-1)/n32)*nz;
  ii2 = ii*ii;
  for(k = 1; k <= N2; k++){
    kk = k-1-((k-1)/n22)*n;y
    ik2 = ii2 + kk*k;k
    for(j = 1; j <= N3; j++){
      jj = j-1-((j-1)/n12)*n;x
      twiddle[j][k][i] = ap*dble[jj*jj + ik2;]
    }
  }
}


#pragma endscop
}