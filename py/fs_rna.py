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

val = str("4")

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
print PAR


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

J0 = S10.range()
J1 = S11.range()

FS0 = I0.subtract(J0).coalesce()
FS1 = I1.subtract(J1).coalesce()

print FS0
print FS1

print "======="

L10 = FS1.apply(S10)
L11 = FS0.apply(S11)

D10 = J1.apply(S10)
D11 = J0.apply(S11)

Lay10 = L10.subtract(D10).coalesce()
Lay11 = L11.subtract(D11).coalesce()

print Lay10
print Lay11

print "======="

J0 = J0.subtract(Lay10).coalesce()
J1 = J1.subtract(Lay11).coalesce()

L20 = Lay11.apply(S10)
L21 = Lay10.apply(S11)

D20 = J1.apply(S10)
D21 = J0.apply(S11)

Lay20 = L20.subtract(D20).coalesce()
Lay21 = L21.subtract(D21).coalesce()

print Lay20
print Lay21

print "======="


J0 = J0.subtract(Lay20).coalesce()
J1 = J1.subtract(Lay21).coalesce()

L30 = Lay21.apply(S10)
L31 = Lay20.apply(S11)

D30 = J1.apply(S10)
D31 = J0.apply(S11)

Lay30 = L30.subtract(D30).coalesce()
Lay31 = L31.subtract(D31).coalesce()

print Lay30
print Lay31

print "======="


J0 = J0.subtract(Lay30).coalesce()
J1 = J1.subtract(Lay31).coalesce()

L40 = Lay31.apply(S10)
L41 = Lay30.apply(S11)

D40 = J1.apply(S10)
D41 = J0.apply(S11)

Lay40 = L40.subtract(D40).coalesce()
Lay41 = L41.subtract(D41).coalesce()

print Lay40
print Lay41