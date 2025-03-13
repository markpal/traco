int main(){
#pragma scop

for(iel = 1; iel <= N1; iel++){
  ieltotal=0;
  isize=size_e[iel];
  for(k = 1; k <= N2; k++){
    for(j = 1; j <= N3; j++){
      for(i = 1; i <= N4; i++){
        ieltotal=ieltotal+ta1[i][j][k][iel]*w3m1[i][j][k]  *jacm1_s[i][j][k][isize];
      }
    }
  }
  total=total+ieltotal;
}


#pragma endscop
}