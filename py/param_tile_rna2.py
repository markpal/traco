# Parametric tiling for RNA

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


TILE_S1 = '[N,ii,jj, b, iib,  jjb] -> '
TILE_S1 += '{[i,j,k,1] : '

tile_i_s1 = ' N-1 - iib >= i >= N-1- iib -b +1, 0 && ii >=0 && '
tile_j_s1 = ' (i+1) + jjb <= j <= jjb+b+i+1-1, N-1 && jj >= 0 &&'
tile_k_s1 = ' 0 <= k <= j-i-1   '

TILE_S1 += tile_i_s1 + tile_j_s1 + tile_k_s1 + '}'

#######################################################################

TILE_S2 = '[N,ii,jj,iib,  jjb, b] -> '
TILE_S2 += '{[i,j,k,2] : '

tile_k_s2 = ' k = 0  '

TILE_S2 += tile_i_s1 + tile_j_s1 + tile_k_s2 + '}'


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

lex_s1 = ' ( (ii > iip) or (ii = iip && jj > jjp) or (ii=iip && jj=jjp ) ) '
lex_s2 = ' ( (ii > iip) or (ii = iip && jj > jjp) ) '
lex_s1s2 = ' ( (ii > iip) or (ii = iip && jj > jjp) or (ii=iip && jj=jjp)  ) '

lex_s1_g = ' ( (ii < iip) or (ii = iip && jj < jjp) or (ii=iip && jj=jjp ) ) '
lex_s2_g = ' ( (ii < iip) or (ii = iip && jj < jjp) ) '
lex_s1s2_g = ' ( (ii < iip) or (ii = iip && jj < jjp) or (ii=iip && jj=jjp)  ) '

iig0 = '  iip >= 0 && jjp >= 0 &&  '

bilb = ' N-1 - iib >= 0 &&  iib >= ii  && '
bilbp = ' N-1 - iipb >= 0 &&  iipb >= iip  && '

bilb = '(i+1) + jjb <= N-1 && jjb >= jj  && '
bilbp = '(i+1) + jjpb <= N-1 && jjpb >= jjp && '

bilb3 = ' '
bilb3p = ''

tile_ip_s1 = tile_i_s1.replace('ii', 'iip')
tile_jp_s1 = tile_j_s1.replace('jj', 'jjp')
tile_kp_s1 = tile_k_s1.replace('kk', 'kkp')

tile_ip_s1 = tile_i_s1.replace('iib', 'iipb')
tile_jp_s1 = tile_j_s1.replace('jjb', 'jjpb')
tile_kp_s1 = tile_k_s1.replace('kkb3', 'kkpb3')

common = 'ii >= 0 && jj >= 0 &&b >0 && b >0 &&  iib >= ii && jjb >= jj &&  iib <= ii*128 && jjb <= jj*128 && '

def template(a):
    return '[N,ii,jj,b, iib,  jjb] -> {[i,j,k,'+str(a)+'] : '+common+' exists iip,jjp, iipb,  jjpb  :  ( iipb >= iip && jjpb >= jjp  &&  iipb <= iip*128 && jjpb <= jjb*128 && '

#######################################################################
# LT
#######################################################################

TILE_LT_S1_S1 = template(1)
TILE_LT_S1_S1 += lex_s1 + ' && ' + iig0
TILE_LT_S1_S1 += bilb + bilbp + bilb + bilbp + bilb3 + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1

TILE_LT_S1_S1 += IinTILE + ')}'

#TILE_LT_S1_S1 = ReplaceB(TILE_LT_S1_S1, B)




TILE_LT_S1_S1 = isl.Set(TILE_LT_S1_S1).coalesce()

print '---'
print 'TILE_LT_S1_S1'

print TILE_LT_S1_S1

#######################################################################

TILE_LT_S1_S2 = template(2)
TILE_LT_S1_S2 += lex_s2 + ' && ' + iig0
TILE_LT_S1_S2 += bilb + bilbp + bilb + bilbp + bilb3

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_LT_S1_S2 += IinTILE + ' 1=1  )}'  #s2

#TILE_LT_S1_S2 = ReplaceB(TILE_LT_S1_S2, B)

TILE_LT_S1_S2 = isl.Set(TILE_LT_S1_S2).coalesce()

print '---'

print 'TILE_LT_S1_S2'
print TILE_LT_S1_S2

#######################################################################

TILE_LT_S2_S1 = template(1)
TILE_LT_S2_S1 += lex_s1s2 + ' && ' + iig0
TILE_LT_S2_S1 += bilb + bilbp + bilb + bilbp + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1
TILE_LT_S2_S1 += IinTILE + ')}'

#TILE_LT_S2_S1 = ReplaceB(TILE_LT_S2_S1, B)

TILE_LT_S2_S1 = isl.Set(TILE_LT_S2_S1).coalesce()

print '---'
print 'TILE_LT_S2_S1'
print TILE_LT_S2_S1


#######################################################################

TILE_LT_S2_S2 = template(2)
TILE_LT_S2_S2 += lex_s2 + ' && ' + iig0
TILE_LT_S2_S2 += bilb + bilbp + bilb + bilbp

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_LT_S2_S2 += IinTILE + ' 1=1)}'

#TILE_LT_S2_S2 = ReplaceB(TILE_LT_S2_S2, B)

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
TILE_GT_S1_S1 += bilb + bilbp + bilb + bilbp + bilb3 + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1

TILE_GT_S1_S1 += IinTILE + ')}'

#TILE_GT_S1_S1 = ReplaceB(TILE_GT_S1_S1, B)

TILE_GT_S1_S1 = isl.Set(TILE_GT_S1_S1).coalesce()

print '---'
print 'TILE_GT_S1_S1'
print TILE_GT_S1_S1

#######################################################################

TILE_GT_S1_S2 = template(2)
TILE_GT_S1_S2 += lex_s1s2_g + ' && ' + iig0
TILE_GT_S1_S2 += bilb + bilbp + bilb + bilbp + bilb3

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_GT_S1_S2 += IinTILE + ' 1=1  )}'  #s2

#TILE_GT_S1_S2 = ReplaceB(TILE_GT_S1_S2, B)

TILE_GT_S1_S2 = isl.Set(TILE_GT_S1_S2).coalesce()

print '---'
print 'TILE_GT_S1_S2'
print TILE_GT_S1_S2

#######################################################################

TILE_GT_S2_S1 = template(1)
TILE_GT_S2_S1 += lex_s2_g + ' && ' + iig0
TILE_GT_S2_S1 += bilb + bilbp + bilb + bilbp + bilb3p

IinTILE = tile_ip_s1 + tile_jp_s1 + tile_kp_s1
TILE_GT_S2_S1 += IinTILE + ')}'

#TILE_GT_S2_S1 = ReplaceB(TILE_GT_S2_S1, B)

TILE_GT_S2_S1 = isl.Set(TILE_GT_S2_S1).coalesce()

print '---'
print 'TILE_GT_S2_S1'
print TILE_GT_S2_S1

#######################################################################

TILE_GT_S2_S2 = template(2)
TILE_GT_S2_S2 += lex_s2_g + ' && ' + iig0
TILE_GT_S2_S2 += bilb + bilbp + bilb + bilbp

IinTILE = tile_ip_s1 + tile_jp_s1
TILE_GT_S2_S2 += IinTILE + ' 1=1)}'

#TILE_GT_S2_S2 = ReplaceB(TILE_GT_S2_S2, B)

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



#TILE_VLD = TILE_VLD.intersect(isl.Set("[N, ii, jj, kk] -> { [i, j, k, l] :  i >= 32 and i <= N-32 and j <= N-32 and j > i + 32 and k > 32 and k < j-1-32 }")).coalesce()




#str_TV = str(TILE_VLD)

#str_TV = str_TV.replace('[N, ii, jj, kk] -> ', '')
#str_TV = str_TV.replace('[', '[ii,jj,kk,')
#str_TV = '[N] -> ' + str_TV



#print str_TV

#TILE_VLD_EXT = isl.Set(str_TV)


if(1==0):

    Rapply = tiling_v3.GetRapply(['i','j','k'], ['ii','jj','kk'], 'ii,jj,kk,N,')
    TILE_VLD_EXT = tiling_v3.Project(TILE_VLD.apply(Rapply).coalesce(), ['ii','jj','kk'])

    Rmap = isl.Map( '{[ii,jj,kk,i,j,k,1] -> [0, ii,0, jj,0, kk,0, i,0, j,0,k,1]; [ii,jj,kk,i,j,k,2] -> [0, ii,0, jj,1, kk,0, i,0, j,1,k,2]  } ' )

    TILE_VLD_EXT = TILE_VLD_EXT.apply(Rmap).coalesce()

    RSched = '[N] -> {[i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13]->[i1,i2,i3,i4,i5,i6,i7,-i8,i9,i10,i11,i12,i13] : ';
    in_ = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6','i7','i8','i9','i10','i11','i12','i13']
    RSched = RSched + copyconstr.GetConstrSet(in_, TILE_VLD_EXT) + "}"

    Rsched = isl.Map(RSched)

else:
    Rapply = tiling_v3.GetRapply(['i','j','k'], ['ii','jj','0'], 'ii,jj,N,b,iib,jjb,')
    TILE_VLD_EXT1 = tiling_v3.Project(TILE_VLD1.apply(Rapply).coalesce(), ['ii','jj'])
    Rmap = isl.Map( '{[ii,jj,0,i,j,k,1] -> [0, ii,0, jj,0, 0,0, i,0, j,0,k,1]; } ' )



    TILE_VLD_EXT1 = TILE_VLD_EXT1.apply(Rmap).coalesce()


    TILE_VLD_EXT2 = tiling_v3.Project(TILE_VLD2.apply(Rapply).coalesce(), ['ii','jj'])
    Rmap = isl.Map( '{[ii,jj,0,i,j,k,1] -> [0, ii,0, jj,1, 0,0, i,0, j,0,k,1]; [ii,jj,0,i,j,k,2] -> [0, ii,0, jj,1, 0,0, i,0, j,1,k,2]; } ' )

    TILE_VLD_EXT2 = TILE_VLD_EXT2.apply(Rmap).coalesce()

    TILE_VLD_EXT = TILE_VLD_EXT1.union(TILE_VLD_EXT2).coalesce()

    RSched = '[N,b,  ff1, ff2,iib,jjb] -> {[i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13]->[i1,i2+i4,i3,i4,i5,i6,i7,-i8,i9,i10,i11,i12,i13] : i2 <= ff1 &&  i4 <= ff2 && b > 0 && b >0  &&  iib >= 0 && jjb >= 0 &&  iib <= ff1 && jjb <= ff2 &&  N>4 && iib <= i2*128 && jjb <= i4*128 && ';
    in_ = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6','i7','i8','i9','i10','i11','i12','i13']
    RSched = RSched + copyconstr.GetConstrSet(in_, TILE_VLD_EXT) + "}"
    Rsched = isl.Map(RSched).coalesce()
    print RSched



#TILE_VLD_EXT =imperf_tile.SimplifySlice(TILE_VLD_EXT)
print 'TILE_VLD_EXT'
print TILE_VLD_EXT

#print relation_util.islSettoOmegaStr(TILE_VLD_EXT )

#loop_x = iscc.isl_ast_codegen(TILE_VLD_EXT)
#loop_x = iscc.isl_ast_codegen(Rsched)

#print loop_x

loop_x = iscc.iscc_communicate("L :=" + str(Rsched) + "; codegen L;")
print loop_x

print '-------------'

S1 = 'S[i][j] = max(S[i][k+i] + S[k+i+1][j], S[i][j]);'
S2 = 'S[i][j] = max(S[i][j], S[i+1][j-1]  + can_par(RNA, i, j));'

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

        s = s.replace('i', irep)
        s = s.replace('j', jrep)
        s = s.replace('k', krep)

        s = s.replace('par', 'pair')
        s = s.replace('for (int', 'for(')

        print tab + s
        loop.append(tab + s)

    else:
        line = line.replace('for (int', 'for(')
        print line
        loop.append(line)


