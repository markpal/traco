int main(){
#pragma scop

for(i3 = 2; i3 <= N1; i3++){
  for(i2 = 2; i2 <= N2; i2++){
    for(i1 = 1; i1 <= N3; i1++){
      u1[i1] = u[i1][i2-1][i3] + u[i1][i2+1][i3] + u[i1][i2][i3-1] + u[i1][i2][i3+1];
      u2[i1] = u[i1][i2-1][i3-1] + u[i1][i2+1][i3-1] + u[i1][i2-1][i3+1] + u[i1][i2+1][i3+1];
    }
    for(i1 = 2; i1 <= N4; i1++){
      r[i1][i2][i3] = v[i1][i2][i3] - a[0] * u[i1][i2][i3] - a[2] * ( u2[i1] + u1[i1-1] + u1[i1+1] ) - a[3] * ( u2[i1-1] + u2[i1+1] );
    }
  }
}


#pragma endscop
}