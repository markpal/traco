int main(){
#pragma scop

for(m = 1; m <= 5; m++){
  dtemp[m] =  ce[m][1] + xi*(ce[m][2] + xi*(ce[m][5] + xi*(ce[m][8] + xi*ce[m][11]))) + eta*(ce[m][3] + eta*(ce[m][6] + eta*(ce[m][9] + eta*ce[m][12])))+ zeta*(ce[m][4] + zeta*(ce[m][7] + zeta*(ce[m][10] + zeta*ce[m][13])));
}


#pragma endscop
}