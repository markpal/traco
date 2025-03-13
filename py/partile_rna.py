import sys
import iscc
import imperf_tile
import relation_util
import copyconstr
import tiling_v3
import tiling_schedule

try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()


def get_RTILE(isl_TILEbis, sym_exvars, isl_rel, Extend, opt=0):

        rbis = isl.Map.from_domain_and_range(isl_TILEbis, isl_TILEbis).coalesce()



        rel_ = tiling_v3.ExtendMap(isl_rel, sym_exvars, True).coalesce()

        Rel_W = "{["
        for i in range(0, 4 * len(sym_exvars)+1):
            Rel_W = Rel_W + "i" + str(i) + ","
        Rel_W = Rel_W[:-1] + "] -> ["
        for i in range(0, 4 * len(sym_exvars)+1):
            Rel_W = Rel_W + "o" + str(i) + ","
        Rel_W = Rel_W[:-1] + "] : not ("
        for i in range(0, 2 * len(sym_exvars)):
            Rel_W = Rel_W + "i" + str(i) + " = " + "o" + str(i) + " and "
        Rel_W = Rel_W[:-4] + ")}"

        rel_simple = rbis.intersect(rel_).coalesce()

        print rel_simple



        relw = isl.Map(Rel_W).coalesce()


        rel_simple = rel_simple.intersect(relw)



        rel_simple = rel_simple.coalesce()


        return rel_simple

# 16x16x16
# Input tiled code

N = 'N'
TILE_VLD_EXT = "[N] -> { [0, i1, 0, i3, 0, i5, 0, i7, 0, 1 + 16i3 + i7, 0, i11, 1] : N = "+N+"  and  0 <= i5 < i3 and i7 >= -16 + N - 16i1 and 0 <= i7 <= -2 + N - 16i1 and i7 <= -2 + N - 16i3 and 16i5 <= i11 <= 15 + 16i5; " \
               "[0, i1, 0, i3, 1, 0, 0, i7, 0, i9, 0, i11, 1] : N = "+N+"  and i7 >= -16 + N - 16i1 and 0 <= i7 < N - 16i1 and i9 <= 16 + 16i3 + i7 and i9 < N and i11 < -i7 + i9 and ((i3 >= 0 and i11 > 16i3) or (i7 <= -2 + N - 16i1 and i9 >= 2 + 16i3 + i7 and i11 >= 0)); " \
               "[0, i1, 0, i3, 0, i3, 0, -1 + N - 16i1, 0, i9, 0, 16i3, 1] : N = "+N+"  and  16i1 < N and i3 >= 0 and N - 16i1 + 16i3 <= i9 <= 15 + N - 16i1 + 16i3 and i9 < N; " \
               "[0, i1, 0, i3, 0, i5, 0, -1 + N - 16i1, 0, i9, 0, i11, 1] : N = "+N+"  and  16i1 < N and 0 <= i5 < i3 and N - 16i1 + 16i3 <= i9 <= 15 + N - 16i1 + 16i3 and i9 < N and 16i5 <= i11 <= 15 + 16i5; " \
               "[0, i1, 0, i3, 1, 0, 0, i7, 0, i9, 1, 0, 2] : N = "+N+"  and i3 >= 0 and i7 >= -16 + N - 16i1 and 0 <= i7 < N - 16i1 and 16i3 + i7 < i9 <= 16 + 16i3 + i7 and i9 < N; " \
               "[0, i1, 0, i3, 0, i3, 0, i7, 0, 1 + 16i3 + i7, 0, 16i3, 1] : N = "+N+"  and i3 >= 0 and i7 >= -16 + N - 16i1 and 0 <= i7 <= -2 + N - 16i1 and i7 <= -2 + N - 16i3 }"

TILE_VLD_EXT = isl.Set(TILE_VLD_EXT)
#TILE_VLD_EXT = tiling_v3.Project(TILE_VLD_EXT, ['N']).coalesce()

Rel = "[N] -> { [i, j, k, v = 1] -> [i' = i, j' = j, k', v' = 1] : N = "+N+" and i >= 0 and j < N and k >= 0 and k < k' < -i + j; " \
      "[i, j, k, v = 1] -> [i' = i, j', k' = -i + j, v' = 1] : N = "+N+" and i >= 0 and 0 <= k < -i + j and j < j' < N; " \
      "[i, j, k, v = 1] -> [i', j' = j, k' = -1 + i - i', v' = 1] : N = "+N+" and j < N and 0 <= k < -i + j and 0 <= i' < i; " \
      "[i, j, k, v = 1] -> [i' = -1 + i, j' = 1 + j, k' = 0, v' = 2] : N = "+N+" and i > 0 and j <= -2 + N and 0 <= k < -i + j; " \
      "[i, j, k, v = 1] -> [i' = i, j' = j, k' = 0, v' = 2] : N = "+N+" and i >= 0 and j < N and 0 <= k < -i + j; [i, j, k = 0, v = 2] -> [i' = i, j', k' = -i + j, v' = 1] : i >= 0 and j > i and j < j' < N; " \
      "[i, j, k = 0, v = 2] -> [i', j' = j, k' = -1 + i - i', v' = 1] : N = "+N+" and i < j < N and 0 <= i' < i; [i, j, k = 0, v = 2] -> [i' = -1 + i, j' = 1 + j, k' = 0, v' = 2] : i > 0 and i < j <= -2 + N }"
Rel = isl.Map(Rel)
#Rel = tiling_v3.Project(Rel, ['N']).coalesce()

RSched = '[N] -> {[i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13]->[i1,i2,i3,i4,i5,i6,i7,-i8,i9,i10,i11,i12,i13] : ';
in_ = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6', 'i7', 'i8', 'i9', 'i10', 'i11', 'i12', 'i13']
RSched = RSched + copyconstr.GetConstrSet(in_, TILE_VLD_EXT) + "}"
Rsched = isl.Map(RSched)


# RTILE
sym_exvars = ['ii', 'jj', 'kk']

rtile = get_RTILE(TILE_VLD_EXT, sym_exvars, Rel, True)
print "RTILE:"
print rtile

sys.exit(0)

# UDS

UDS_TILE = rtile.domain().subtract(rtile.range()).coalesce()
print UDS_TILE

loop_x = iscc.iscc_communicate("L :=" + str(UDS_TILE) + "; codegen L;")

print loop_x

L1 = UDS_TILE.apply(rtile).coalesce()
J = rtile.range().coalesce()

Lay1 = L1.subtract(J).coalesce()

loop_x = iscc.iscc_communicate("L :=" + str(Lay1) + "; codegen L;")

print loop_x

J = Lay1
L2 = Lay1.apply(rtile).coalesce()

Lay2 = L2.subtract(J).coalesce()

loop_x = iscc.iscc_communicate("L :=" + str(Lay2) + "; codegen L;")

print loop_x


