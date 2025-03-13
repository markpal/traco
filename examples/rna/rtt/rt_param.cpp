#include <stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <iostream>
#include <string>
#include<vector>
#include<math.h>

#define N 2048

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define ceild(n,d) ceil(((double)(n))/((double)(d)))




using namespace std;

void split(const string& s, char c,
           vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

int can_pair(long double*input, int a, int b){
   return ((((input[a] + input[b]) == 3) && (a < b - 1))) ? 1 : 0;
}


int main(int argc, char *argv[]){

    int i,j,k;
    int c1,c2,c3,c5,c7,c9,c11,c10,c4,c12;
    std::string kafle;
    int b1,b2,b3;

    vector<string> v;

    if(argc < 2)
        exit(0);
    kafle = argv[1];

    split(kafle, ',', v);

    b1 = atoi(v[0].c_str());
    b2 = atoi(v[1].c_str());
    b3 = atoi(v[2].c_str());

    cout << "TILE: " << b1 << ' ' << b2 << ' ' << b3 << ' ' << endl;

    long double **S = new long double*[N];
    for(i=0; i<N; i++)
      S[i] = new long double[N];


    long double **S1 = new long double*[N];
    for(i=0; i<N; i++)
      S1[i] = new long double[N];

    long double * RNA = new long double[N];

    for(i=0; i<N; i++)
      for(j=0; j<N; j++){
        S[i][j] = i*j*0.001;
        S1[i][j] = S[i][j];
    }

    double start = omp_get_wtime();

if(1==0)
    for (i = N-1; i >= 0; i--) {
     for (j = i+1; j < N; j++) {
      for (k = 0; k < j-i; k++) {
    S1[i][j] = max(S1[i][k+i] + S1[k+i+1][j], S1[i][j]);

      }
      for (k = 0; k < 1; k++) {
    S1[i][j] = max(S1[i][j], S1[i+1][j-1]  + can_pair(RNA, i, j));

     }
    }
   }
//else


    for( c1 = 0; c1 <= floord(N - 1, b1); c1 += 1)
     for( c3 = 0; c3 <= min(floord(N - 2, b2), (b1 * c1 + (b1-2)) / b2); c3 += 1){
       for( c5 = 0; c5 <= b2 * c3 / b3; c5 += 1)
        for( c7 = max(-N + b1 * c1 + 1, -N + b2 * c3 + 2); c7 <= min(0, -N + b1 * c1 + b1); c7 += 1) {
         if (N + c7 >= b1 * c1 + 2) {
          for( c11 = b3 * c5; c11 <= min(b2 * c3, b3 * c5 + (b3-1)); c11 += 1)
            S[(-c7)][(b2*c3-c7+1)] = max(S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][(b2*c3-c7+1)], S[(-c7)][(b2*c3-c7+1)]);
         } else
          for( c9 = N - b1 * c1 + b2 * c3; c9 <= min(N - 1, N - b1 * c1 + b2 * c3 + (b2-1)); c9 += 1)
           for( c11 = b3 * c5; c11 <= min(b2 * c3, b3 * c5 + (b3-1)); c11 += 1)
            S[(N-b1*c1-1)][c9] = max(S[(N-b1*c1-1)][c11+(N-b1*c1-1)] + S[c11+(N-b1*c1-1)+1][c9], S[(N-b1*c1-1)][c9]);
        }
        for( c7 = max(-N + b1 * c1 + 1, -N + b2 * c3 + 2); c7 <= min(0, -N + b1 * c1 + b1); c7 += 1)
         for( c9 = b2 * c3 - c7 + 1; c9 <= min(N - 1, b2 * c3 - c7 + b2); c9 += 1)
          for( c10 = max(0, b2 * c3 - c7 - c9 + 2); c10 <= 1; c10 += 1)
           if(c10==1)
            S[(-c7)][c9] = max(S[(-c7)][c9], S[(-c7)+1][c9-1] + can_pair(RNA, -c7, c9));
           else{
            if (N + c7 >= b1 * c1 + 2)
             for( c11 = 0; c11 <= b2 * c3; c11 += 1)
              S[(-c7)][c9] = max(S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9], S[(-c7)][c9]);
            for( c11 = b2 * c3 + 1; c11 < c7 + c9; c11 += 1)
             S[(-c7)][c9] = max(S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9], S[(-c7)][c9]);
          }
    }


    double stop = omp_get_wtime();
    printf("%.4f\n",stop - start);

    FILE * plik = fopen("wyniki.csv", "a+");
    fprintf(plik, "%i,%i,%i,%.4f\n",b1,b2,b3,stop-start);
    fclose(plik);


    /* End of CLooG code */


    if(1==0)
    for(i=0; i<N; i++)
     for(j=0; j<N; j++){
       if(S1[i][j] != S[i][j]){
     printf("error %i %i  \n ", i,j);
    exit(0);
        //printf("error %i %i %Lf %Lf \n ", i,j, S[i][j], S1[i][j]);
      //  printf("error\n");
    //exit(0);
      }
    }


return 0;
}
