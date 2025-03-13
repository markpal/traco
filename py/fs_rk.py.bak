try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()
    ctx = isl.Context()

import iscc
import sys
import os
import imperf_tile
import tiling_v3
import tiling_schedule
import openacc

#schedule with rk

def get_sq(sk, sk2, uds):
    # ---------- Obliczanie SQ
    d = 2  # tu bedzie wyliczona d i jeszcze q >= 0
    sq = sk

    print sk2
    print  sk2.lexmin()
    print  sk2.lexmax()


    z =[]
    l = sk.dim(isl.dim_type.set)
    for i in range(0, l):
        z.append("i" + str(i))
    tmp = isl.Set("[k] -> {["+",".join(z)+"] : k = 0}")
    tmp = tmp.intersect(uds).coalesce()
    sq = sq.union(tmp).coalesce()
    sq = sq.insert_dims(isl.dim_type.set, 0, 1)
    sq = sq.set_dim_name(isl.dim_type.set, 0, "q")
    sq = sq.set_dim_name(isl.dim_type.set, 1, "ii")
    var_i = sq.get_var_names(isl.dim_type.set)[1]


    # sys.exit()
    c= isl.Constraint.eq_from_names(sq.get_space(), {"q": -1, "ii":d,"k":1})
    sq = sq.add_constraint(c).coalesce()


    # -----------------------

    # ---------- Obliczanie kmax i imax
    z =  sk2.lexmax()

    z = z.remove_dims(isl.dim_type.set, 2, z.dim(isl.dim_type.set)-2)

    z = z.set_dim_name(isl.dim_type.set, 0, "kmax")
    z = z.set_dim_name(isl.dim_type.set, 1, "imax")
    z = z.insert_dims(isl.dim_type.set, 0, 1)
    z = z.set_dim_name(isl.dim_type.set, 0, "q")
    # q <= d*imax + kmax
    c= isl.Constraint.ineq_from_names(z.get_space(), {"q": -1, "imax":d,"kmax":1})
    z = z.add_constraint(c).coalesce()
    # q <= 0
    c= isl.Constraint.ineq_from_names(z.get_space(), {"q": 1})

    z = z.add_constraint(c).coalesce()
    z = z.remove_dims(isl.dim_type.set, 1, z.dim(isl.dim_type.set)-1)
    z = z.insert_dims(isl.dim_type.set, 1, l)

    sq = sq.intersect(z).coalesce()
    sq = tiling_v3.Project(sq, ["k"])

    #if(SIMPLIFY):
    #    sq = imperf_tile.SimplifySlice(sq)


    return sq
    # -----------------------



def fs_rk(rel, rel_plus, uds, LPetit, dane, plik, SIMPLIFY, rap, acc, loop):

    aprox = 0
    rk = rel.power()  #Rk
    if(rk[1]==0):
        print "rk approximated..."
        aprox = 1
    rk = rk[0].coalesce()


    rk = isl.Map(iscc.RepairRk(str(rk), 0)) # przesun k do symb
    sk = uds.apply(rk).subtract(uds.apply(rk).apply(rel_plus)).coalesce()

    sq_sk = sk


    sk = sk.insert_dims(isl.dim_type.set, 0, 1)
    sk = sk.set_dim_name(isl.dim_type.set, 0, "ink")

    c = isl.Constraint.eq_from_names(sk.get_space(), {"k": -1, "ink":1})
    sk = sk.add_constraint(c)
    sk = tiling_v3.Project(sk, ["k"])

    sq_sk2 = sk

    SQ = False
    if(SQ):
        sk = get_sq(sq_sk, sq_sk2, uds)
    else:

        uds = uds.insert_dims(isl.dim_type.set, 0, 1)
        uds = uds.set_dim_name(isl.dim_type.set, 0, "ink")

        c= isl.Constraint.eq_from_names(sk.get_space(), {1: 0, "ink":1})
        uds = uds.add_constraint(c)

        sk = sk.union(uds).coalesce()


    #if(SIMPLIFY):
    sk = imperf_tile.SimplifySlice(sk)

    rap = rap.insert_dims(isl.dim_type.in_, 0, 1)
    rap = rap.insert_dims(isl.dim_type.out, 0, 1)
    rap = rap.set_dim_name(isl.dim_type.in_,0, 'ik1')
    rap = rap.set_dim_name(isl.dim_type.out,0, 'ok1')

    c = isl.Constraint.eq_from_names(rap.get_space(), {'ik1': -1, 'ok1':1})
    rap = rap.add_constraint(c)
    rap = rap.coalesce()

    #print rap

    sk = sk.apply(rap)

    print sk

    if(aprox == 1):
        if(sk.is_bounded()):
            print "Approximation (no perfect FS) but Sk is bounded"
        else:
            print "Sk is not bounded. The result may not be valid!"
    else:
        print 'Rk exact'
        if (sk.is_bounded()):
            print 'Sk bounded.'
        else:
            print 'Sk NOT bounded'

    nloop = iscc.iscc_communicate("L :=" + str(sk) + "; codegen L;")



    # CODEGEN
    nloop = tiling_v3.postprocess_loop(nloop.split('\n'))


    lines = tiling_schedule.fs_pragma(nloop)

    if(acc):
        lines = openacc.CreateACCCode(lines, loop.var_st)




    loop = imperf_tile.RestoreStatements(lines, LPetit, dane, 1, 1, [], 1)

    for i in range(0, 5):
        if(loop[-1] == '\n'):
            loop = loop[:-1]
    loop = loop + "\n"



    base = os.path.basename(plik)
    nazwa = os.path.splitext(base)[0] + "_fs" + os.path.splitext(base)[1]

    text_file = open(nazwa, "w")
    text_file.write(loop)
    text_file.close()

    print nazwa + ' was created.'

def fs_rk1(rel, SIMPLIFY, indt):

    rk = rel.power()  #Rk
    if(rk[1]==0):
        print "rk approximated..."
    rk = rk[0].coalesce()
    #print rk


    rk = isl.Map(iscc.RepairRk(str(rk), 0)) # przesun k do symb

    print "RK"
    print rk
    uds = rel.domain().subtract(rel.range()).coalesce()

    # ADD INDEPENDENT TILES TO UDS
    #uds = uds.union(indt).coalesce()

    print "UDS"
    print uds
    
    rel_plus = rel.transitive_closure()[0]
    sk = uds.apply(rk).subtract(uds.apply(rk).apply(rel_plus)).coalesce()

    sk = sk.insert_dims(isl.dim_type.set, 0, 1)
    sk = sk.set_dim_name(isl.dim_type.set, 0, "ink")

    c = isl.Constraint.eq_from_names(sk.get_space(), {"k": -1, "ink":1})
    sk = sk.add_constraint(c)
    sk = tiling_v3.Project(sk, ["k"])

    uds = uds.insert_dims(isl.dim_type.set, 0, 1)
    uds = uds.set_dim_name(isl.dim_type.set, 0, "ink")



    c= isl.Constraint.eq_from_names(sk.get_space(), {1: 0, "ink":1})
    uds = uds.add_constraint(c)

    #x = isl.Set("{ [0, 0, 0, 6]}")
    #uds = uds.union(x).coalesce()

    print "TUDS"
    print uds





    sk = sk.union(uds).coalesce()



    if(SIMPLIFY):
        sk = imperf_tile.SimplifySlice(sk)

    return sk
