 void zuker_pluto2(){
  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13;
 register int lbv, ubv;

/* Start of CLooG code */
if (N >= 2) {
  for (t1=1;t1<=N-1;t1++) {
    if (t1 >= 4) {
      for (t9=0;t9<=floord(t1-4,16);t9++) {
        for (t10=t9;t10<=floord(t1-2,16);t10++) {
          for (t11=16*t9;t11<=min(min(t1-4,16*t10+14),16*t9+15);t11++) {
            for (t12=max(16*t10,t11+1);t12<=min(t1-2,16*t10+15);t12++) {
              for (t13=t12+1;t13<=min(t1-1,t1-t11+t12-3);t13++) {
                V[t11][t1] += V[t12][t13] + EFL;;
              }
            }
          }
        }
      }
    }
    if (t1 >= 3) {
      for (t5=0;t5<=floord(t1-3,16);t5++) {
        for (t6=t5;t6<=floord(t1-2,16);t6++) {
          for (t7=16*t5;t7<=min(min(t1-3,16*t5+15),16*t6+14);t7++) {
            for (t8=max(16*t6,t7+1);t8<=min(t1-2,16*t6+15);t8++) {
              V[t7][t1] += W[t7+1][t8] + W[t8+1][t1-1];;
            }
          }
        }
      }
    }
    for (t4=0;t4<=floord(t1-1,16);t4++) {
      lbv=16*t4;
      ubv=min(t1-1,16*t4+15);
#pragma ivdep
#pragma vector always
      for (t5=lbv;t5<=ubv;t5++) {
        V[t5][t1] += V[t5+1][t1-1] * EHF;;
      }
    }
    for (t3=0;t3<=t1-1;t3++) {
      W[t3][t1] += W[t3+1][t1]* W[t3][t1-1] * V[t3][t1];;
      if ((t1 >= 2) && (t3 == 0)) {
        for (t7=0;t7<=floord(t1-2,16);t7++) {
          for (t8=t7;t8<=floord(t1-1,16);t8++) {
            for (t9=16*t7;t9<=min(min(t1-2,16*t7+15),16*t8+14);t9++) {
              for (t10=max(16*t8,t9+1);t10<=min(t1-1,16*t8+15);t10++) {
                W[t9][t1] += W[t9][t10] * W[t10+1][t1];;
              }
            }
          }
        }
      }
    }
  }
}
/* End of CLooG code */
}
