int main(){
#pragma scop

for(z = 1; z <= 5; z++){
  for(d = 1; d <= 3; d++){
    rms[z] = rms[z] / dble[grid_points-2];
  }
  rms[z] = rms[z];
}


#pragma endscop
}