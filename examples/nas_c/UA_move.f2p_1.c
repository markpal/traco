int main(){
#pragma scop

for(iel = 1; iel <= N1; iel++){
  mt_to_id[iel]=iel;
  id_to_mt[iel]=iel;
}


#pragma endscop
}