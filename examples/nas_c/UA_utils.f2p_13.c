int main(){
#pragma scop

for(ix = N1; ix <= N2; ix++){
  for(iy = N3; iy <= N4; iy++){
    for(iz = N5; iz <= N6; iz++){
      a[ix][iy][iz]=val;
    }
  }
}


#pragma endscop
}