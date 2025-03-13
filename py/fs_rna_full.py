import iscc
import re
import test_isl

try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()
    ctx = isl.Context()


# for (i = N-1; i >= 0; i--) {
#  for (j = i+1; j < N; j++) {
#     for (k = 0; k < j-i; k++) {
#        S[i][j] = MAX(S[i][k+i] + S[k+i+1][j], S[i][j]);
#      }
#     S[i][j] = MAX(S[i][j], S[i+1][j-1] );
#    }
#  }

# 0 : 0
# {[i,j,k] -> [i,j',j-i] : j < j' < N && 0 <= k && i+k < j && 0 <= i} union
#  {[i,j,k] -> [i',j,i-i'-1] : 0 <= i' < i && j < N && 0 <= k && i+k < j} union
#  {[i,j,k] -> [i,j,k'] : 0 <= k < k' && j < N && 0 <= i && i+k' < j}
#
# 0 : 1
# {[i,j,k] -> [i-1,j+1] : j <= N-2 && 0 <= k && i+k < j && 1 <= i} union
#  {[i,j,k] -> [i,j] : j < N && 0 <= k && i+k < j && 0 <= i}
#
# 1 : 0
# {[i,j] -> [i,j',j-i] : 0 <= i < j < j' < N} union
#  {[i,j] -> [i',j,i-i'-1] : 0 <= i' < i < j < N}
#
# 1 : 1
# {[i,j] -> [i-1,j+1] : 1 <= i < j <= N-2}

N= 2500
val = str(N)

_par = "[N] -> {[i,j]->[i',j'] : N = " + val + "; [i,j]->[i',j',k'] : N = " + val + "; [i,j,k]->[i',j'] : N = " + val + "; [i,j,k]->[i',j',k'] : N = " + val + " } "

r00 = "[N] -> {[i,j,k] -> [i,j',j-i] : j < j' < N && 0 <= k && i+k < j && 0 <= i; [i,j,k] -> [i',j,i-i'-1] : 0 <= i' < i && j < N && 0 <= k && i+k < j; [i,j,k] -> [i,j,k'] : 0 <= k < k' && j < N && 0 <= i && i+k' < j}"

R00 = isl.UnionMap(str(r00))

r01 = "[N] -> {[i,j,k] -> [i-1,j+1] : j <= N-2 && 0 <= k && i+k < j && 1 <= i; [i,j,k] -> [i,j] : j < N && 0 <= k && i+k < j && 0 <= i}"

R01 = isl.UnionMap(str(r01))

r10 = "[N] -> {[i,j] -> [i,j',j-i] : 0 <= i < j < j' < N; [i,j] -> [i',j,i-i'-1] : 0 <= i' < i < j < N}"

R10 = isl.UnionMap(str(r10))

r11 = "[N] -> {[i,j] -> [i-1,j+1] : 1 <= i < j <= N-2}"

R11 = isl.UnionMap(str(r11))

PAR = isl.UnionMap(_par)
#print PAR


#statements
it = ['i','j','k']
s0 = "S[i][j] = MAX(S[i][k+i] + S[k+i+1][j], S[i][j]);"
s1 = "S[i][j] = MAX(S[i][j], S[i+1][j-1] + can_par(RNA, i, j));"


R00 = R00.intersect(PAR).coalesce()
R10 = R10.intersect(PAR).coalesce()
R01 = R01.intersect(PAR).coalesce()
R11 = R11.intersect(PAR).coalesce()

S10 = R00.union(R10).coalesce()
S20 = R00.union(R01).coalesce()

S11 = R11.union(R01).coalesce()
S21 = R11.union(R10).coalesce()

I0 = S20.domain()
I1 = S21.domain()

all = ''

for i in range(0,2*N):
    if i == 0:

        J0 = S10.range()
        J1 = S11.range()

        FS0 = I0.subtract(J0).coalesce()
        FS1 = I1.subtract(J1).coalesce()

        #print FS0
        #print FS1

        tmp_L0 = FS0
        tmp_L1 = FS1

        L0 = FS1.apply(S10)
        L1 = FS0.apply(S11)
    else:
        L0 = Lay1.apply(S10)
        L1 = Lay0.apply(S11)

        J0 = J0.subtract(Lay0).coalesce()
        J1 = J1.subtract(Lay1).coalesce()


    D0 = J1.apply(S10)
    D1 = J0.apply(S11)


    L0 = L0.subtract(D0).coalesce()
    L1 = L1.subtract(D1).coalesce()

    Lay0 = L0.subtract(D0).coalesce()
    Lay1 = L1.subtract(D1).coalesce()

    if Lay0.is_empty() and Lay1.is_empty():
        break


    Lay = Lay0.union(Lay1).coalesce()

    #Lay.card()
    crd = test_isl.StringToCard(str(Lay))
    crd = crd.replace("[N] -> { ", "")
    crd = crd.replace(" : N = " + str(N) + " }", "")



    if(int(crd) < 1000):
        all = all + '// --------------\n'
    else:
        all = all + '// parallel -----\n'



    all = all + iscc.iscc_communicate("L :=" + str(Lay) + "; codegen L;")







lines = all.split('\n')

lines2 = []

pragma_par = 0
pragma_single = 0
single_block = 0

#lines2.append('#pragma acc kernels copyin(RNA) copy(S)')
lines2.append("#pragma omp parallel shared(S,RNA)")
lines2.append('{')

for line in lines:
    if '(' in line and not 'if' in line and not 'for' in line:
        #line = line + ' // s' + str(line.count(',') -1)

        tab = " " * (len(line) - len(line.lstrip()))
        line = line.replace('(','').replace(')','').replace(' ','').replace(';','')
        st = line.count(',')-1
        vector = line.split(',')

        if st == 0:
            line = s1
        else:
            line = s0

        for i in range(0,len(vector)):
            line = line.replace(it[i], vector[i])

        line = tab + line
        line = line.replace('par', 'pair')

    line = line.replace('int ', '')

    if '// parallel -----' in line:
        pragma_par = 1
        if(single_block == 1):
            lines2.append('}')
            single_block = 0

    if '// -------------' in line:
        pragma_single = 1

    if 'for' in line and pragma_par == 1:
        #lines2.append('#pragma acc loop independent')
        lines2.append('#pragma omp for')
        pragma_par = 0


    if 'for' in line and pragma_single == 1 and single_block == 0:
        #lines2.append('#pragma acc loop independent')
        lines2.append('#pragma omp single')
        lines2.append('{')
        pragma_single = 0
        single_block = 1


    if(line == 'if (N == '+str(N)+') {'):
        #lines2.append('} // GPU')
        pragma = 0

    if(not line == 'if (N == '+str(N)+')'):
        lines2.append(line)


lines2.append('}')
lines2.append('}') #CPU


all = '\n'.join(lines2)
print all