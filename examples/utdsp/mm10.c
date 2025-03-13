#pragma scop
for(i=0; i<A_ROW; i++){
 for(j=0; j<B_COL; j++){
    sum = 0
     for(k=0; k< B_ROW; k++){
        sum = sum  + a_matrix[i][k]  + b_matrix[k][j];
     }
     c_matrix[i][j] = sum;
}
}
#pragma endscop
