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


#pragma scop
#for (j=0; j<n; j++)
#for (i=j-1; i>-1; i--)
#for (k=i; k<j; k++)
#d[i][j]=d[i][j] + d[i][k]+d[k][j];
#pragma endscop




rel = " [N] -> { [j,i,k,v] -> [j',i',k',v'] : ( i' = i and j' = j and v = 9 and v' = 9 and 0 <= i <= k < k' < j < n and i <= j-1, k'-1 and k <= j-2 and 0 <= j ) or ( i = k and j' = j and i' = k and v = 9 and v' = 9 and 0 <= k < k' < j < N and k <= j-2 and 0 <= j ) or ( i' = i and j' = j and v = 9 and v' = 9 and 0 <= i <= k < k' < j < N and i <= j-1, k'-1 and k <= j-2 and 0 <= j ) or ( i' = i and k' = j and v = 9 and v' = 9 and 0 <= i <= k < j < j' < N and i <= j-1, N-2, j'-1 and 0 <= j <= N-2 and 1 <= N and 0 <= j' ) or ( k' = i and j' = j and v = 9 and v' = 9 and 1, i'+1 <= i <= k < j < n and 0 <= i' < j and i < j and 1 <= j ) or ( i' = i and j' = j and v = 9 and v' = 9 and 0 <= i <= k < k' < j < N and i <= j-1, k'-1 and k <= j-2 and 0 <= j ) }"


Rplus = "[N] -> { [j, i, k, 9] -> [j', i', k', 9] : i <= k < j and j < j' < N and 0 <= i' < i and i' < k' < j'; [j, i, k, 9] -> [j' = j, i', k', 9] : j < N and i <= k < j and 0 <= i' < i and i' < k' < j; [j, i, k, 9] -> [j', i' = i, k', 9] : i >= 0 and i <= k < j and j' < N and j <= k' < j'; [j, i, k, 9] -> [j' = j, i' = i, k', 9] : j < N and i >= 0 and k >= i and k < k' < j }"


TILE_S1 = '[N,jj,ii,kk] -> '
TILE_S1 += '{[j,i,k,9] : '

tile_j_s1 = '0 + b1 * jj <= j <= b1*(jj+1) + 0 -1 ,N-1 && jj >=0 &&'
tile_i_s1 = ' j-1  - b2*ii >= i >= j-1-b2*(ii+1)+1, 0 && ii >= 0 && '
tile_k_s1 = ' b3*kk + i <= k <= b3*(kk+1)+i-1, j-1 && kk >= 0  '

TILE_S1 += tile_j_s1 + tile_i_s1 + tile_k_s1 + '}'

#######################################################################


B = ['16', '16', '16']

def ReplaceB(str, B):
    str = str.replace('b1', B[0])
    str = str.replace('b2', B[1])
    str = str.replace('b3', B[2])
    return str


#######################################################################

TILE_S1 = ReplaceB(TILE_S1, B)

print TILE_S1

#######################################################################

TILE_S1 = isl.Set(TILE_S1).coalesce()

print 'TILE_S1'
print TILE_S1

print '---'

#######################################################################

lex_s1 = ' ( (jj > jjp) or (jj = jjp && ii > iip) or (jj=jjp && ii=iip & kk > kkp) ) '

lex_s1_g = ' ( (jj < jjp) or (jj = jjp && ii < iip) or (jj=jjp && ii=iip & kk < kkp) ) '

iig0 = ' ii >= 0 && jj >= 0 && kk>= 0 && iip >= 0 && jjp >= 0 && kkp>= 0 && '

bilb1 = ' 0 + b1*jj <= N-1 && '
bilb1p = '  0 + b1*jjp <= N-1 && '

bilb2 = 'j-1 - b2 * jj >= 0 && '
bilb2p = 'j-1- b2 * jjp >= 0 && '

bilb3 = 'b3*kk + i <= j-1 && '
bilb3p = 'b3*kkp + i <= j-1 && '


bilb1 = '  '
bilb1p = '  '

bilb2 = ''
bilb2p = ''

bilb3 = ' '
bilb3p = ''
iig0 = ' '

tile_ip_s1 = tile_i_s1.replace('ii', 'iip')
tile_jp_s1 = tile_j_s1.replace('jj', 'jjp')
tile_kp_s1 = tile_k_s1.replace('kk', 'kkp')

def template(a):
    return '[N,ii,jj,kk] -> {[j,i,k,'+str(a)+'] : exists iip,jjp,kkp : ('


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
print 'TILE_LT_S1_S1'
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

TILE_GT_S1_S1 = isl.Set(TILE_GT_S1_S1).coalesce()

print '---'
print 'TILE_GT_S1_S1'
print TILE_GT_S1_S1

#######################################################################

Rplus = isl.Map(Rplus)

print 'Rplus'
print Rplus

TILE_LT_S1 = TILE_LT_S1_S1
TILE_GT_S1 = TILE_GT_S1_S1

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

Rapply = tiling_v3.GetRapply(['j','i','k'], ['jj','ii','kk'], 'jj,ii,kk,N,')
TILE_VLD_EXT1 = tiling_v3.Project(TILE_VLD1.apply(Rapply).coalesce(), ['jj','ii','kk'])
Rmap = isl.Map( '{[jj,ii,kk,j,i,k,9] -> [0, ii,0, jj,0, kk,0, j,0, i,0,k,9]; } ' )

TILE_VLD_EXT1 = TILE_VLD_EXT1.apply(Rmap).coalesce()

TILE_VLD_EXT = TILE_VLD_EXT1

TILE_VLD_EXT =imperf_tile.SimplifySlice(TILE_VLD_EXT)

RSched = '[N] -> {[i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13]->[i1,i2+i4,i3,i4,i5,i6,i7,i8,i9,-i10,i11,i12,i13] : ';
in_ = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6','i7','i8','i9','i10','i11','i12','i13']
RSched = RSched + copyconstr.GetConstrSet(in_, TILE_VLD_EXT) + "}"

Rsched = isl.Map(RSched)

print 'TILE_VLD_EXT'
print TILE_VLD_EXT

print 'RSCHED'
print Rsched

#######################################################################

loop_x = iscc.iscc_communicate("L :=" + str(Rsched) + "; codegen L;")


print '-------------'

S1 = 'd[i][j] = mxn(d[i][j], d[i][k] + d[k][j]);'


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


        jrep = arr[7]
        irep = arr[9]
        krep = arr[11]

        s = s.replace('j', jrep)
        s = s.replace('i', irep)
        s = s.replace('k', krep)

        s = s.replace('par', 'pair')
        s = s.replace('for (int', 'for(')

        s = s.replace('mxn', 'min')

        print tab + s
        loop.append(tab + s)

    else:
        line = line.replace('for (int', 'for(')
        print line
        loop.append(line)