void zuker_seq()
{
int i,j,k,m;

#pragma scop
for (i = N-1; i >= 0; i--){
 for (j = i+1; j < N; j++) {
   for (k = i+1; k < j; k++){
   for(m=k+1; m <j; m++){
    if(k-i + j - m > 2)
       V[i][j] = MIN(V[k][m] + EFL[i][j][k][m], V[i][j]);
   }
   W[i][j] += MIN ( MIN(W[i][k], W[k+1][j]), W[i][j]);
   if(k < j-1)
     V[i][j] = MIN(W[i+1][k] + W[k+1][j-1], V[i][j]);
  }
 V[i][j] = MIN( MIN (V[i+1][j-1], EHF[i][j]), V[i][j]);
 W[i][j] = MIN( MIN ( MIN ( W[i+1][j], W[i][j-1]), V[i][j]), W[i][j]);
 }
}
#pragma endscop

}
