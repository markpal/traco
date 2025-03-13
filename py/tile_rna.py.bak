import sys
import iscc
import imperf_tile
import relation_util
import copyconstr
import tiling_v3
import re

try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()


TILE_S1 = '[N,ii,jj,kk] -> '
TILE_S1 += '{[i,j,k,1] : '

tile_i_s1 = ' N-1 - b1 * ii >= i >= N-1-b1*(ii+1)+1, 0 && ii >=0 && '
tile_j_s1 = ' (i+1) + b2*jj <= j <= b2*(jj+1)+i+1-1, N-1 && jj >= 0 &&'
tile_k_s1 = ' b3*kk + 0 <= k <= b3*(kk+1)+0-1, j-i-1 && kk >= 0  '

TILE_S1 += tile_i_s1 + tile_j_s1 + tile_k_s1 + '}'

#######################################################################

TILE_S2 = '[N,ii,jj,kk] -> '
TILE_S2 += '{[i,j,k,2] : '

tile_k_s2 = ' k = 0 && kk=0 '

TILE_S2 += tile_i_s1 + tile_j_s1 + tile_k_s2 + '}'


#######################################################################

B = ['32', '32', '32']

def ReplaceB(str, B):
    str = str.replace('b1', B[0])
    str = str.replace('b2', B[1])
    str = str.replace('b3', B[2])
    return str



TILE_S1 = ReplaceB(TILE_S1, B)
TILE_S2 = ReplaceB(TILE_S2, B)


#######################################################################

TILE_S1 = isl.Set(TILE_S1).coalesce()
TILE_S2 = isl.Set(TILE_S2).coalesce()

print 'TILE_S1'
print TILE_S1

print '---'
print 'TILE_S2'
print TILE_S2

#######################################################################
# [S1 | S2]
# TILE_LT_S1
# TILE_GT_S1
# TILE_LT_S2
# TILE_GT_S2

# iloczyny

lex_s1 = ' ( (ii > iip) or (ii = iip && jj > jjp) or (ii=iip && jj=jjp & kk > kkp) ) '
lex_s2 = ' ( (ii > iip) or (ii = iip && jj > jjp) ) '
lex_s1s2 = ' ( (ii > iip) or (ii = iip && jj > jjp) or (ii=iip && jj=jjp)  ) '

lex_s1_g = ' ( (ii < iip) or (ii = iip && jj < jjp) or (ii=iip && jj=jjp & kk < kkp) ) '
lex_s2_g = ' ( (ii < iip) or (ii = iip && jj < jjp) ) '
lex_s1s2_g = ' ( (ii < iip) or (ii = iip && jj < jjp) or (ii=iip && jj=jjp)  ) '

iig0 = '' # ii >= 0 && jj >= 0 && kk>= 0 && iip >= 0 && jjp >= 0 && kkp>= 0 && '

#bilb1 = ' N-1 - b1*ii >= 0 && '
#bilb1p = ' N-1 - b1*iip >= 0 && '

#bilb2 = '(i+1) + b2 * jj <= N-1 && '
#bilb2p = '(i+1) + b2 * jjp <= N-1 && '

#bilb3 = 'b3*kk + 0 <= j-i-1 && '
#bilb3p = 'b3*kkp + 0 <= j-i-1 && '

bilb1 = ''
bilb1p = ''
bilb2 = ''
bilb2p = ''
bilb3 = ''
bilb3p = ''

tile_ip_s1 = tile_i_s1.replace('ii', 'iip')
tile_jp_s1 = tile_j_s1.replace('jj', 'jjp')
tile_kp_s1 = tile_k_s1.replace('kk', 'kkp')

def template(a):
    return '[N,ii,jj,kk] -> {[i,j,k,'+str(a)+'] : exists iip,jjp,kkp : ('

#######################################################################
# LT
#######################################################################

TILE_LT_S1_S1 = template(1)
TILE_LT_S1_S1 += lex_s1 + ' && ' + iig0
TILE_LT_S1_S1 += bilb1 + bilb1p + bilb2 + bilb2p + bilb3 + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1

TILE_LT_S1_S1 += IinTILE + ')}'

TILE_LT_S1_S1 = ReplaceB(TILE_LT_S1_S1, B)

TILE_LT_S1_S1 = isl.Set(TILE_LT_S1_S1).coalesce()

print '---'
print 'TILE_LT_S1_S1'
print TILE_LT_S1_S1

#######################################################################

TILE_LT_S1_S2 = template(2)
TILE_LT_S1_S2 += lex_s2 + ' && ' + iig0
TILE_LT_S1_S2 += bilb1 + bilb1p + bilb2 + bilb2p + bilb3

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_LT_S1_S2 += IinTILE + ' 1=1  )}'  #s2

TILE_LT_S1_S2 = ReplaceB(TILE_LT_S1_S2, B)

TILE_LT_S1_S2 = isl.Set(TILE_LT_S1_S2).coalesce()

print '---'

print 'TILE_LT_S1_S2'
print TILE_LT_S1_S2

#######################################################################

TILE_LT_S2_S1 = template(1)
TILE_LT_S2_S1 += lex_s1s2 + ' && ' + iig0
TILE_LT_S2_S1 += bilb1 + bilb1p + bilb2 + bilb2p + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1
TILE_LT_S2_S1 += IinTILE + ')}'

TILE_LT_S2_S1 = ReplaceB(TILE_LT_S2_S1, B)

TILE_LT_S2_S1 = isl.Set(TILE_LT_S2_S1).coalesce()

print '---'
print 'TILE_LT_S2_S1'
print TILE_LT_S2_S1


#######################################################################

TILE_LT_S2_S2 = template(2)
TILE_LT_S2_S2 += lex_s2 + ' && ' + iig0
TILE_LT_S2_S2 += bilb1 + bilb1p + bilb2 + bilb2p

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_LT_S2_S2 += IinTILE + ' 1=1)}'

TILE_LT_S2_S2 = ReplaceB(TILE_LT_S2_S2, B)

TILE_LT_S2_S2 = isl.Set(TILE_LT_S2_S2).coalesce()

print '---'
print 'TILE_LT_S2_S2'
print TILE_LT_S2_S2

#######################################################################

#######################################################################
# GT
#######################################################################

TILE_GT_S1_S1 = template(1)
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

TILE_GT_S1_S2 = template(2)
TILE_GT_S1_S2 += lex_s1s2_g + ' && ' + iig0
TILE_GT_S1_S2 += bilb1 + bilb1p + bilb2 + bilb2p + bilb3

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_GT_S1_S2 += IinTILE + ' 1=1  )}'  #s2

TILE_GT_S1_S2 = ReplaceB(TILE_GT_S1_S2, B)

TILE_GT_S1_S2 = isl.Set(TILE_GT_S1_S2).coalesce()

print '---'
print 'TILE_GT_S1_S2'
print TILE_GT_S1_S2

#######################################################################

TILE_GT_S2_S1 = template(1)
TILE_GT_S2_S1 += lex_s2_g + ' && ' + iig0
TILE_GT_S2_S1 += bilb1 + bilb1p + bilb2 + bilb2p + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1
TILE_GT_S2_S1 += IinTILE + ')}'

TILE_GT_S2_S1 = ReplaceB(TILE_GT_S2_S1, B)

TILE_GT_S2_S1 = isl.Set(TILE_GT_S2_S1).coalesce()

print '---'
print 'TILE_GT_S2_S1'
print TILE_GT_S2_S1

#######################################################################

TILE_GT_S2_S2 = template(2)
TILE_GT_S2_S2 += lex_s2_g + ' && ' + iig0
TILE_GT_S2_S2 += bilb1 + bilb1p + bilb2 + bilb2p

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_GT_S2_S2 += IinTILE + ' 1=1)}'

TILE_GT_S2_S2 = ReplaceB(TILE_GT_S2_S2, B)

TILE_GT_S2_S2 = isl.Set(TILE_GT_S2_S2).coalesce()

print '---'
print 'TILE_GT_S2_S2'
print TILE_GT_S2_S2

#######################################################################

TILE_LT_S1 = TILE_LT_S1_S1.union(TILE_LT_S1_S2).coalesce()
TILE_LT_S2 = TILE_LT_S2_S1.union(TILE_LT_S2_S2).coalesce()
TILE_GT_S1 = TILE_GT_S1_S1.union(TILE_GT_S1_S2).coalesce()
TILE_GT_S2 = TILE_GT_S2_S1.union(TILE_GT_S2_S2).coalesce()

print 'TILE_LT_S1'
print TILE_LT_S1
print 'TILE_LT_S2'
print TILE_LT_S2
print 'TILE_GT_S1'
print TILE_GT_S1
print 'TILE_GT_S2'
print TILE_GT_S2

#######################################################################

# TILE_ITR = TILE - R+(TILE_GT)

#TILE_ITR_S1 = TILE_S1 - R+(TILE_GT)


#exact iteration method
Rplus = " [N] -> { [i, j, k, 1] -> [i', j', k', 1] : (k <= -1 - i + j and k >= 0 and i' >= 0 and i' <= -1 + i and j' <= -1 + N and k' >= 1 + j - i' and k' <= -1 - i' + j') or " \
        "(k <= -1 - i + j and k >= 0 and i' >= 0 and i' <= -1 + i and j' >= 1 + j and j' <= -1 + N and k' >= 0 and k' <= j - i'); [i, j, k, 1] -> [i, j, 0, 2] : i >= 0 and j <= -1 + N " \
        "and k <= -1 - i + j and k >= 0; [i, j, k, 1] -> [i', j', 0, 2] : (k <= -1 - i + j and k >= 1 and i' >= 0 and i' <= -2 + i and j' >= 1 + i + j - i' and j' <= -1 + N) " \
        "or (k <= -1 - i + j and k >= 1 and i' >= 0 and j' >= 1 + j and j' <= -1 + i + j - i' and j' <= -1 + N); [i, j, k, 1] -> [-1 + i, j, 0, 2] : i >= 1 and j <= -1 + N and k <= -1 - i + j " \
        "and k >= 0; [i, j, 0, 2] -> [i', j', k, 1] : (j >= 1 + i and i' >= 0 and i' <= -1 + i and j' <= -1 + N and k >= 1 + j - i' and k <= -1 - i' + j') or (j >= 1 + i and i' >= 0 " \
        "and i' <= -1 + i and j' >= 1 + j and j' <= -1 + N and k >= 0 and k <= j - i'); [i, j, 0, 2] -> [-1 + i, j', 0, 2] : i >= 1 and j >= 1 + i and j' >= 1 + j and j' <= -1 + N; " \
        "[i, j, k, 1] -> [i, j', k', 1] : i >= 0 and k <= -1 - i + j and k >= 0 and j' <= -1 + N and k' <= -1 - i + j' and k' >= -i + j; [i, j, k, 1] -> [i', j, k', 1] : j <= -1 + N " \
        "and k <= -1 - i + j and k >= 0 and i' >= 0 and i' <= -1 + i and k' >= 0 and k' <= -1 + j - i'; [i, j, 0, 2] -> [i', j', 0, 2] : (j >= 1 + i and i' >= 0 and j' >= 2 + j and " \
        "j' <= -1 + i + j - i' and j' <= -1 + N) or (j >= 1 + i and i' >= 0 and i' <= -2 + i and j' >= i + j - i' and j' <= -1 + N); [i, j, 0, 2] -> [-1 + i, j, 0, 2] : i >= 1 and " \
        "j >= 1 + i and j <= -1 + N; [i, j, 0, 1] -> [i', j', 0, 2] : j >= 1 + i and i' >= 0 and i' <= -1 + i and j' >= 1 + j and j' <= -1 + N; [i, j, k, 1] -> [i', i + j - i', 0, 2] : " \
        "k <= -1 - i + j and k >= 1 and i' >= 0 and i' <= -2 + i and i' >= 1 - N + i + j; [i, j, k, 1] -> [i, j', 0, 2] : i >= 0 and k <= -1 - i + j and k >= 0 and j' >= 1 + j and " \
        "j' <= -1 + N; [i, j, k, 1] -> [i', j, 0, 2] : j <= -1 + N and k <= -1 - i + j and k >= 0 and i' >= 0 and i' <= -2 + i; [i, j, k, 1] -> [-1 + i, j', 0, 2] : i >= 1 and k <= -1 - i + j " \
        "and k >= 1 and j' >= 2 + j and j' <= -1 + N; [i, j, 0, 2] -> [i, j', k, 1] : i >= 0 and j >= 1 + i and j' <= -1 + N and k <= -1 - i + j' and k >= -i + j; " \
        "[i, j, 0, 2] -> [i', j, k, 1] : j >= 1 + i and j <= -1 + N and i' >= 0 and i' <= -1 + i and k >= 0 and k <= -1 + j - i'; [i, j, k, 1] -> [i, j, k', 1] : i >= 0 and j <= -1 + N and k >= 0 " \
        "and k' <= -1 - i + j and k' >= 1 + k; [i, j, 0, 2] -> [i', 1 + j, 0, 2] : j >= 1 + i and j <= -2 + N and i' >= 0 and i' <= -2 + i; [i, j, k, 1] -> [-1 + i, 1 + j, 0, 2] : i >= 1 and j <= -2 + N " \
        "and k <= -1 - i + j and k >= 1; [i, j, 0, 2] -> [i, j', 0, 2] : i >= 0 and j >= 1 + i and j' >= 1 + j and j' <= -1 + N; [i, j, 0, 2] -> [i', j, 0, 2] : j >= 1 + i and j <= -1 + N and i' >= 0 and i' <= -2 + i }"

Rplus = isl.Map(Rplus)

print 'Rplus'
print Rplus


TILE_ITR1 = TILE_S1.subtract(TILE_GT_S1.apply(Rplus)).coalesce()
TILE_ITR2 = TILE_S2.subtract(TILE_GT_S2.apply(Rplus)).coalesce()

print 'TILE_ITR1'
print TILE_ITR1
print 'TILE_ITR2'
print TILE_ITR2

# TVLD_LT = (R+(TILE_ITR) and TILE_LT) -R+(TILE_GT)

TVLD_LT1 = (TILE_LT_S1.intersect(TILE_ITR1.apply(Rplus))).subtract(TILE_GT_S1.apply(Rplus)).coalesce()
TVLD_LT2 = (TILE_LT_S2.intersect(TILE_ITR2.apply(Rplus))).subtract(TILE_GT_S2.apply(Rplus)).coalesce()

print 'TVLD_LT1'
print TVLD_LT1
print 'TVLD_LT2'
print TVLD_LT2


TILE_VLD1 = TVLD_LT1.union(TILE_ITR1).coalesce()
TILE_VLD2 = TVLD_LT2.union(TILE_ITR2).coalesce()



print 'TILE_VLD1'
print TILE_VLD1


print 'TILE_VLD2'
print TILE_VLD2



TILE_VLD = TILE_VLD1.union(TILE_VLD2)


print 'TILE_VLD'
print TILE_VLD




Rapply = tiling_v3.GetRapply(['i','j','k'], ['ii','jj','kk'], 'ii,jj,kk,N,')
TILE_VLD_EXT1 = tiling_v3.Project(TILE_VLD1.apply(Rapply).coalesce(), ['ii','jj','kk'])
Rmap = isl.Map( '{[ii,jj,kk,i,j,k,1] -> [0, ii,0, jj,0, kk,0, i,0, j,0,k,1]; } ' )

#TILE_VLD_EXT1 =imperf_tile.SimplifySlice(TILE_VLD_EXT1)

TILE_VLD_EXT1 = TILE_VLD_EXT1.apply(Rmap).coalesce()



TILE_VLD_EXT2 = tiling_v3.Project(TILE_VLD2.apply(Rapply).coalesce(), ['ii','jj','kk'])
Rmap = isl.Map( '{[ii,jj,kk,i,j,k,1] -> [0, ii,0, jj,1, kk,0, i,0, j,0,k,1]; [ii,jj,kk,i,j,k,2] -> [0, ii,0, jj,1, kk,0, i,0, j,1,k,2]; } ' )

#TILE_VLD_EXT2 =imperf_tile.SimplifySlice(TILE_VLD_EXT2)

TILE_VLD_EXT2 = TILE_VLD_EXT2.apply(Rmap).coalesce()

TILE_VLD_EXT = TILE_VLD_EXT1.union(TILE_VLD_EXT2).coalesce()

RSched = '[N] -> {[i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13]->[i1,i2+i4,i3,i4,i5,i6,i7,-i8,i9,i10,i11,i12,i13] : ';
in_ = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6','i7','i8','i9','i10','i11','i12','i13']
RSched = RSched + copyconstr.GetConstrSet(in_, TILE_VLD_EXT) + "}"

Rsched = isl.Map(RSched)



print 'TILE_VLD_EXT'
print TILE_VLD_EXT


loop_x = iscc.iscc_communicate("L :=" + str(Rsched) + "; codegen L;")


print '-------------'

S1 = 'S[i][j] = max(S[i][k+i] + S[k+i+1][j], S[i][j]);'
S2 = 'S[i][j] = max(S[i][j], S[i+1][j-1]  + can_pair(RNA, i, j));'

#S1 = 'S[i][j] = S[i][k+i] + S[k+i+1][j]+ S[i][j];'
#S2 = 'S[i][j] = S[i][j]+ S[i+1][j-1];'


lines = loop_x.split('\n')

loop = []

for line in lines:
    if line.endswith(');'):
        tab = imperf_tile.get_tab(line)
        line = line.replace(' ', '')
        line = line[:-2]
        line = line[1:]

        arr = line.split(',')

        if(arr[12] == '1'):
            s = S1
        else:
            s = S2

        irep = arr[7]
        jrep = arr[9]
        krep = arr[11]

        #s = s.replace('i', irep)
        #s = s.replace('j', jrep)
        #s = s.replace('k', krep)

        s = re.sub(r'\bi\b', irep, s)
        s = re.sub(r'\bj\b', jrep, s)
        s = re.sub(r'\bk\b', krep, s)

        s = s.replace('for (int', 'for(')

        print tab + s
        loop.append(tab + s)

    else:
        line = line.replace('for (int', 'for(')
        print line
        loop.append(line)


