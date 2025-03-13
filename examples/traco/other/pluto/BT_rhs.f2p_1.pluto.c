#include <omp.h>
#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

int main(){
int k,i,j,N1,N2,N3;

int rho_inv, u[6][100][100][100], rho_i[100][100][100];
int us[100][100][100], ws[100][100][100], vs[100][100][100];
int qs[100][100][100], square[100][100][100];

  int t1, t2, t3, t4, t5, t6, t7, t8, t9;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if ((N1 >= 0) && (N2 >= 0) && (N3 >= 0)) {
  for (t1=0;t1<=N1;t1++) {
    for (t2=0;t2<=N2;t2++) {
      for (t3=0;t3<=N3;t3++) {
        rho_inv=1.0/u[1][t3][t2][t1];;
        square[t3][t2][t1]=0.5*(u[2][t3][t2][t1]*u[2][t3][t2][t1]+u[3][t3][t2][t1]*u[3][t3][t2][t1]+u[4][t3][t2][t1]*u[4][t3][t2][t1])*rho_inv;;
        qs[t3][t2][t1]=square[t3][t2][t1]*rho_inv;;
        ws[t3][t2][t1]=u[4][t3][t2][t1]*rho_inv;;
        vs[t3][t2][t1]=u[3][t3][t2][t1]*rho_inv;;
        us[t3][t2][t1]=u[2][t3][t2][t1]*rho_inv;;
        rho_i[t3][t2][t1]=rho_inv;;
      }
    }
  }
}
/* End of CLooG code */

return 0;

}
