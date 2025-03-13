int main(){
#pragma scop

for(i = 1; i <= N1; i++){
  ten[ i][ 1 ] = 0.0;
  j1[ i][ 1 ] = 0;
  j2[ i][ 1 ] = 0;
  j3[ i][ 1 ] = 0;
  ten[ i][ 0 ] = 1.0;
  j1[ i][ 0 ] = 0;
  j2[ i][ 0 ] = 0;
  j3[ i][ 0 ] = 0;
}


#pragma endscop
}