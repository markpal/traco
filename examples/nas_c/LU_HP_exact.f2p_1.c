int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  u000ijk[m] =  ce[m][1] + (ce[m][2] + (ce[m][5] + (ce[m][8] +  ce[m][11] * xi) * xi) * xi) * xi + (ce[m][3] + (ce[m][6] + (ce[m][9] +  ce[m][12] * eta) * eta) * eta) * eta + (ce[m][4] + (ce[m][7] + (ce[m][10] +  ce[m][13] * zeta) * zeta) * zeta) * zeta;
}


#pragma endscop
}