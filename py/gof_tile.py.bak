import sys
import iscc
import imperf_tile
import relation_util
import copyconstr
import tiling_v3

try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()

from termcolor import colored
import tiling_schedule


#pragma scop
#for (t = 0; t < T; t++) {
#   for (i = 1; i < N-1; i++) {
#     for (j = 1; j < N-1; j++) {
#         life[(t+1)%2][i][j] = life[t%2][i][j] + life[t%2][i-1][j+1] + life[t%2][i-1][j] + life[t%2][i-1][j-1] + life[t%2][i][j+1] + life[t%2][i][j-1]  + life[t%2][i+1][j+1] + life[t%2][i+1][j] + life[t%2][i+1][j-1];
#       }
#     }
#
#   }
#pragma endscop


def GetRapply(vars, sym_exvars, _SYM):
    R = "R := ["
    R = R + _SYM

    R = R[:-1] + "] -> {["
    for s in vars:
        R = R + s + ","
    R = R[:-1] + ",0] -> ["
    for s in sym_exvars:
        R = R + s + ","
    for s in vars:
        R = R + s + ","
    R = R[:-1] + ",0] : "
    R = R + " true };\n"

    print R
    isl_Rapply = isl.Map(R.replace('R := ',''))
    return isl_Rapply


#rel = " [T, N] -> { [t, i, j] -> [t', 1 + i, 1 + j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -3 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j] -> [t', 1 + i, j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -3 + N and 0 < j <= -2 + N and t < t' < T; [t, i, j] -> [t', 1 + i, -1 + j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -3 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j] -> [t', i, 1 + j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -2 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j] -> [t', i, j] : t >= 0 and 0 < i <= -2 + N and 0 < j <= -2 + N and t < t' < T and (2*floor((-t + t')/2) = -t + t' or 2*floor((-1 - t + t')/2) = -1 - t + t'); [t, i, j] -> [t', -1 + i, -1 + j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 2 <= i <= -2 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j] -> [t', i, -1 + j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -2 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j] -> [t', -1 + i, 1 + j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 2 <= i <= -2 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j] -> [t', -1 + i, j] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 2 <= i <= -2 + N and 0 < j <= -2 + N and t < t' < T }"
rel = " [T, N] -> { [t, i, j,0] -> [t', 1 + i, 1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -3 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j,0] -> [t', 1 + i, j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -3 + N and 0 < j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', 1 + i, -1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -3 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', i, 1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -2 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j,0] -> [t', i, j,0] : t >= 0 and 0 < i <= -2 + N and 0 < j <= -2 + N and t < t' < T and (2*floor((-t + t')/2) = -t + t' or 2*floor((-1 - t + t')/2) = -1 - t + t'); [t, i, j,0] -> [t', -1 + i, -1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 2 <= i <= -2 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', i, -1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 0 < i <= -2 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', -1 + i, 1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 2 <= i <= -2 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j,0] -> [t', -1 + i, j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and t >= 0 and 2 <= i <= -2 + N and 0 < j <= -2 + N and t < t' < T }"

#rel = "[T, N] -> { [t, i, j,0] -> [t', 1 + i, 1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 0 < i <= -3 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j,0] -> [t', 1 + i, j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 0 < i <= -3 + N and 0 < j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', 1 + i, -1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 0 < i <= -3 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', i, 1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 0 < i <= -2 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j,0] -> [t', i, j,0] : T >= 65 and N >= 65 and t >= 0 and 0 < i <= -2 + N and 0 < j <= -2 + N and t < t' < T and (2*floor((-t + t')/2) = -t + t' or 2*floor((-1 - t + t')/2) = -1 - t + t'); [t, i, j,0] -> [t', -1 + i, -1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 2 <= i <= -2 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', i, -1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 0 < i <= -2 + N and 2 <= j <= -2 + N and t < t' < T; [t, i, j,0] -> [t', -1 + i, 1 + j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 2 <= i <= -2 + N and 0 < j <= -3 + N and t < t' < T; [t, i, j,0] -> [t', -1 + i, j,0] : 2*floor((-1 - t + t')/2) = -1 - t + t' and T >= 65 and N >= 65 and t >= 0 and 2 <= i <= -2 + N and 0 < j <= -2 + N and t < t' < T }"

rel = isl.Map(rel)

print colored('R', 'green')
print rel

rplus = rel.transitive_closure()



print colored('R+', 'green')

if(rplus[1] == 1):
    print colored('exact', 'green')
else:
    print colored('approx', 'red')

Rplus = rplus[0]

print Rplus


rpow = rel.power()



print colored('R^k', 'green')

if(rpow[1] == 1):
    print colored('exact', 'green')
else:
    print colored('approx', 'red')

Rpow = rpow[0]



Rpow = isl.Map(iscc.RepairRk(str(Rpow), 0)) # przesun k do symb
print Rpow
uds = rel.domain().subtract(rel.range()).coalesce()
print "UDS"
print uds
sk = uds.apply(Rpow).subtract(uds.apply(Rpow).apply(Rplus)).coalesce()
sk = sk.insert_dims(isl.dim_type.set, 0, 1)
sk = sk.set_dim_name(isl.dim_type.set, 0, "ink")
c = isl.Constraint.eq_from_names(sk.get_space(), {"k": -1, "ink":1})
sk = sk.add_constraint(c)
sk = tiling_v3.Project(sk, ["k"])
uds = uds.insert_dims(isl.dim_type.set, 0, 1)
uds = uds.set_dim_name(isl.dim_type.set, 0, "ink")
c= isl.Constraint.eq_from_names(sk.get_space(), {1: 0, "ink":1})
uds = uds.add_constraint(c)
sk = sk.union(uds).coalesce()
print 'Sk'
print sk
nloop = iscc.iscc_communicate("L :=" + str(sk) + "; codegen L;")
print nloop
print '--------------------------------------------------------'




TILE_S1 = '[T,N,tt,ii,jj] -> '
TILE_S1 += '{[t,i,j,0] : '


tile_j_s1 = '0 + b1 * tt <= t <= b1*(tt+1) + 0 -1 ,T-1 && tt >=0 && '
tile_i_s1 = '1 + b2 * ii <= i <= b2*(ii+1) + 1 -1 ,N-2 && ii >=0 && '
tile_k_s1 = '1 + b3 * jj <= j <= b3*(jj+1) + 1 -1 ,N-2 && jj >=0 '

TILE_S1 += tile_j_s1 + tile_i_s1 + tile_k_s1 + '}'

#######################################################################


B = ['64', '64', '64']

def ReplaceB(str, B):
    str = str.replace('b1', B[0])
    str = str.replace('b2', B[1])
    str = str.replace('b3', B[2])
    return str


#######################################################################

TILE_S1 = ReplaceB(TILE_S1, B)

#print TILE_S1

#######################################################################

TILE_S1 = isl.Set(TILE_S1).coalesce()

print colored('TILE_S1','green')
print TILE_S1

print '---'



#######################################################################

lex_s1 = ' ( (tt > ttp) or (tt = ttp && ii > iip) or (tt=ttp && ii=iip && jj > jjp) ) '

lex_s1_g = ' ( (tt < ttp) or (tt = jjp && ii < iip) or (tt=ttp && ii=iip && jj < jjp) ) '

iig0 = ' tt >= 0 && ii >= 0 && jj >= 0 && ttp >= 0 && iip >= 0 && jjp >= 0 && '

bilb1 = ' 0 + b1*tt <= T-1 && '
bilb1p = '  0 + b1*ttp <= T-1 && '
bilb1 = ''

bilb2 =  ' 1 + b2*ii <= N-2 && '
bilb2p =  ' 1 + b2*iip <= N-2 && '
bilb2 =  ''

bilb3 = 'b3*jj + 1 <= N-2 && '
bilb3p = 'b3*jjp + 1 <= N-2 && '
bilb3 = ''


tile_ip_s1 = tile_i_s1.replace('tt', 'ttp')
tile_jp_s1 = tile_j_s1.replace('ii', 'iip')
tile_kp_s1 = tile_k_s1.replace('jj', 'jjp')

def template(a):
    return '[N,T,tt,ii,jj] -> {[t,i,j,0] : exists ttp,iip,jjp : ('


#######################################################################
# LT
#######################################################################

TILE_LT_S1_S1= template(9)
TILE_LT_S1_S1 += lex_s1 + ' && ' + iig0
TILE_LT_S1_S1 += bilb1 + bilb1p + bilb2 + bilb2p + bilb3 + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1

TILE_LT_S1_S1 += IinTILE + ')}'

TILE_LT_S1_S1 = ReplaceB(TILE_LT_S1_S1, B)

print TILE_LT_S1_S1

TILE_LT_S1_S1 = isl.Set(TILE_LT_S1_S1).coalesce()

print '---'
print colored('TILE_LT_S1_S1', 'green')
print TILE_LT_S1_S1

#######################################################################
# GT
#######################################################################

TILE_GT_S1_S1 = template(9)
TILE_GT_S1_S1 += lex_s1_g + ' && ' + iig0
TILE_GT_S1_S1 += bilb1 + bilb1p + bilb2 + bilb2p + bilb3 + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1

TILE_GT_S1_S1 += IinTILE + ')}'

TILE_GT_S1_S1 = ReplaceB(TILE_GT_S1_S1, B)

print TILE_GT_S1_S1

TILE_GT_S1_S1 = isl.Set(TILE_GT_S1_S1).coalesce()

print '---'
print colored('TILE_GT_S1_S1','green')
print TILE_GT_S1_S1



#######################################################################



TILE_LT_S1 = TILE_LT_S1_S1
TILE_GT_S1 = TILE_GT_S1_S1

print '------'

print TILE_GT_S1.apply(Rplus).coalesce()

TILE_ITR1 = TILE_S1.subtract(TILE_GT_S1.apply(Rplus)).coalesce()
print 'TILE_ITR1'
print TILE_ITR1

TVLD_LT1 = (TILE_LT_S1.intersect(TILE_ITR1.apply(Rplus))).subtract(TILE_GT_S1.apply(Rplus)).coalesce()

print 'TVLD_LT1'
print TVLD_LT1

TILE_VLD1 = TVLD_LT1.union(TILE_ITR1).coalesce()

print 'TILE_VLD1'
print TILE_VLD1

TILE_VLD = TILE_VLD1

#######################################################################

Rapply = GetRapply(['t','i','j'], ['tt','ii','jj'], 'tt,ii,jj,N,T,')
TILE_VLD_EXT1 = tiling_v3.Project(TILE_VLD1.apply(Rapply).coalesce(), ['tt','ii','jj'])
Rmap = isl.Map( '{[tt,ii,jj,t,i,j] -> [0, tt,0, ii,0, jj,0, t,0, i,0,j]; } ' )

#TILE_VLD_EXT1 = TILE_VLD_EXT1.apply(Rmap).coalesce()

TILE_VLD_EXT = TILE_VLD_EXT1

#TILE_VLD_EXT =imperf_tile.SimplifySlice(TILE_VLD_EXT)

#RSched = '[N] -> {[i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12]->[i1,i2+i4,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12] : ';
#in_ = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6','i7','i8','i9','i10','i11','i12']
#RSched = RSched + copyconstr.GetConstrSet(in_, TILE_VLD_EXT) + "}"

#Rsched = isl.Map(RSched)

print 'TILE_VLD_EXT'
print TILE_VLD_EXT

#print 'RSCHED'
#print Rsched

#######################################################################

loop_x = iscc.iscc_communicate("L :=" + str(TILE_VLD_EXT) + "; codegen L;")
print '-------------'
print loop_x


print '-------------'

S1 = 'life[(t + 1) % 2][i][j] = b2s23(life[t % 2][i][j], life[t % 2][i - 1][j + 1] + life[t % 2][i - 1][j] + life[t % 2][i - 1][j - 1] + life[t % 2][i][j + 1] + life[t % 2][i][j - 1] + life[t % 2][i + 1][j + 1] + life[t % 2][i + 1][j] + life[t % 2][i + 1][j - 1]);'

S1 = S1.replace('life', 'zyc')
lines = loop_x.split('\n')

loop = []

for line in lines:
    if line.endswith(');'):
        tab = imperf_tile.get_tab(line)
        line = line.replace(' ', '')
        line = line[:-2]
        line = line[1:]

        arr = line.split(',')

        s = S1


        jrep = arr[3]
        irep = arr[4]
        krep = arr[5]

        s = s.replace('t', jrep)
        s = s.replace('i', irep)
        s = s.replace('j', krep)

        s = s.replace('zyc', 'life')
        s = s.replace('for (int', 'for(')



        print tab + s
        loop.append(tab + s)

    else:
        line = line.replace('for (int', 'for(')
        print line
        loop.append(line)


rtile = tiling_schedule.get_RTILE(TILE_VLD_EXT, ['tt','ii','jj'], rel, False)
print rtile