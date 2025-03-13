int main(){
#pragma scop

for(i3 = 1; i3 <= N1; i3++){
  for(i2 = 1; i2 <= N2; i2++){
    for(i1 = 1; i1 <= N3; i1++){
      z[i1][i2][i3]=0.0;
    }
  }
}


#pragma endscop
}