import islpy as isl
ctx = isl.Context()
#import subprocess
import gen
import glob, os
import correct
#import convert_loop
import re
#import shutil
#from easyprocess import Proc
#from subprocess import call

import iscc
import sys
import tiling
import tiling_v3


import imperf_tile

import slicing


import fs_rk
#import fs_karl






def fs_pragma(loops1):
    loop = []
    loops1 = loops1.split('\n')
    fg = 0
    c = 0
    c0 = 0
    ll = 1024

    for l in loops1:
        if('for (int c0' in l):
            c0 = 1
        tab = correct.whites(l)
        if (('for (int t' in l) or ('for (int c' in l))  and not('for (int t1' in l) and not('for (int c0' in l) and len(tab) <= ll and c0==1:
            loop.append("#pragma omp parallel for")
            fg = 1
            tab = correct.whites(l)
            ll = len(tab)


        loop.append(l)
    return loop


def slice_tiling(loops1, lines_block, sym_exvars, fs=0):
    #print lines_block
    
    lines_block = lines_block.split('\n')
    text_file = open("tmp/tile_par_debug.txt", "w")
    text_file.write(loops1)
    text_file.close()
    loops1 = loops1.split('\n')

    
    # wrzuc do bloku oryginalne instrukcje
    loop = tiling.postprocess_loop(lines_block)   
    text_file = open("pseudocode.txt", "w")
    text_file.write(loop)
    text_file.close()
    #names_info juz jest
    gen.ParsePrint("tmp/tmp_petit0.t")
    # instrukcje juz sa
    # usun puste linie i kopiuj
    file = open("out_pseudocode.txt", 'r')
    lines_block = file.readlines()
    ##############

    
    l_block = []
    for line in lines_block:
        z = line
        #print line
        for item in re.findall(r'''c\d+''', line):
            z = z.replace(item, item.replace("c", "t"))
        l_block.append(z)
        
    st_reg = re.compile(r'\s*\(.*\);')
    if(fs ==0):
        sli_file = 'tmp/tile_par.c'
    else:
        sli_file = 'tmp/tile_par_fs.c'
    file = open(sli_file, 'w')
    fg = 0
    c = 0
    for l in loops1:
        if (('for (int t' in l) or ('for (int c' in l))  and not('for (int t1' in l) and not('for (int c0' in l) and (fg == 0) and fs == 1:
            file.write("#pragma omp parallel for\n")
            fg = 1
        if fg == 1 and '{' in l:
            c = c +1
        if fg == 1 and '}' in l:
            c = c -1    
        if c ==0 and fg == 1:
            fg = 0
        if(st_reg.match(l)):
            #print l
            tab = correct.whites(l)
            z = l.replace("(", "")
            z = z.replace(");", "")
            z = z.replace(");", "")
            z = z.replace(" ", "")          
            vec = z.split(',')
            if(fs==1): # usunac zmienna k
                vec.pop(0)
            #file.write(tab + "{\n")
            tab = tab + "  "
            l_block_tmp = l_block[:]
            for i in range(0, len(sym_exvars)):
                #file.write(tab + sym_exvars[i] + " = " + vec[i] + ";\n")
                for j in range(0, len(l_block_tmp)):
                    tmp = "\\b"+sym_exvars[i]+"\\b"
                    reg = re.compile(tmp)
                    l_block_tmp[j] =  reg.sub(vec[i], l_block_tmp[j])
                    
                
            file.write('// block --------------------\n')
            for ll in l_block_tmp:
                file.write(tab + ll.replace('\n', '')+'\n')
            file.write('// end block --------------------\n')
            tab = tab[:-2]
            #file.write(tab + "}\n")
        else:
            file.write(l + '\n')
    file.close
    gen.ParsePrint("tmp/tmp_petit.t")

# This is the last Traco part in version 0.x
# Tiling + slicing + schedule + priv + permute
# Code is still experimental, however theory is ok.


def tile_par2(isl_TILEbis, sym_exvars, isl_rel, isl_relplus, isl_relclosure, Extend, _rap, Dodatek, SIMPLIFY):

    #with open('sources_of_slices.txt') as f:
    #    content = f.readlines()
    #    srepr = content[0]

    #srepr = isl.Set(srepr)

    #with open('rucs.txt') as f:
    #    content = f.readlines()
    #    rucs = content[0]



    #_rel = _rel.remove_dims(isl.dim_type.in_, 0,1)
    #_rel = _rel.remove_dims(isl.dim_type.out, 0,1)
    #print _rel
    '''
    ir = isl_rel
    print ir
    ir = ir.insert_dims(isl.dim_type.in_, 0, len(sym_exvars))
    ir = ir.insert_dims(isl.dim_type.out, 0, len(sym_exvars))


    print ir

    ir2 = ir.from_domain_and_range(isl_TILEbis, isl_TILEbis).coalesce()
    ir = ir2.intersect(ir).coalesce()
    print ir
    ir = ir.remove_dims(isl.dim_type.in_, len(sym_exvars),len(sym_exvars))
    ir = ir.remove_dims(isl.dim_type.out, len(sym_exvars),len(sym_exvars))
    ir = ir.coalesce()
    print ir

    sys.exit(0);
    '''


    srepr,rucs = slicing.Create_Srepr(isl_rel, isl_relclosure)
    print(srepr)


    ir = isl_rel.domain().union(isl_rel.range()).coalesce()
    ir = ir.insert_dims(isl.dim_type.set, 0, len(sym_exvars))
    for i in range(0, len(sym_exvars)):
        ir = ir.set_dim_name(isl.dim_type.set, i, sym_exvars[i])

    if(Extend):
        for i in range(0, 2*len(sym_exvars)):
            ir = ir.insert_dims(isl.dim_type.set, 2*i+1, 1)




    srepr = srepr.insert_dims(isl.dim_type.set, 0, len(sym_exvars))
    for i in range(0, len(sym_exvars)):
        srepr = srepr.set_dim_name(isl.dim_type.set, i, sym_exvars[i])

    if(Extend):
        for i in range(0, 2*len(sym_exvars)):
            srepr = srepr.insert_dims(isl.dim_type.set, 2*i+1, 1)



    x = 1
    if(Extend):
        x = 2

    #relacja do obliczenia poczatkow
    Rel_Z = "{["
    for i in range(0, 2*x*len(sym_exvars)):
        Rel_Z = Rel_Z + "i" + str(i) + ","
    Rel_Z = Rel_Z + "m] -> ["
    for i in range(0, x*len(sym_exvars)):
        Rel_Z = Rel_Z + "i" + str(i) + ","
    Rel_Z = Rel_Z[:-1] + "] };"

    Rel_Z = isl.Map(Rel_Z)

    #relacja do wylapania instrukcji z blokow
    Rel_Y = "{["
    for i in range(0, x*len(sym_exvars)):
        Rel_Y = Rel_Y + "i" + str(i) + ","
    for i in range(0, x*len(sym_exvars)+1):
        Rel_Y = Rel_Y + "j" + str(i) + ","
    Rel_Y = Rel_Y[:-1] + "] -> ["
    for i in range(0, x*len(sym_exvars)):
        Rel_Y = Rel_Y + "i" + str(i) + ","
    for i in range(0, x*len(sym_exvars)+1):
        Rel_Y = Rel_Y + "k" + str(i) + ","
    Rel_Y = Rel_Y[:-1] + "] };"

    Rel_Y = isl.Map(Rel_Y)

    TILE_SOUR = isl_TILEbis.intersect(srepr).coalesce()

    TILE_IND = isl_TILEbis.subtract(isl_TILEbis.intersect(ir)).coalesce()

    indloop =  iscc.iscc_communicate("L :=" + str(TILE_IND) + "; codegen L;")

    fs = 0
    if(TILE_SOUR.lexmax() == TILE_SOUR.lexmin()):
        print("FS")
        fs = 1
    else:
        print("SLICING")
        if(rucs.is_empty()):
            isl_rel = isl_rel.union(rucs)
            isl_relclosure = isl_relclosure.union(rucs)
            isl_relplus = isl_relplus.union(rucs)

    rplus = tiling_v3.ExtendMap(isl_relplus, sym_exvars, Extend)
    rstar = tiling_v3.ExtendMap(isl_relclosure, sym_exvars, Extend)
    rel_ = tiling_v3.ExtendMap(isl_rel, sym_exvars, Extend)
    #rucs = tiling_v3.ExtendMap(rucs, sym_exvars, Extend)

    rbis = isl.Map.from_domain_and_range(isl_TILEbis,isl_TILEbis)

    rs = rbis.intersect(rstar)
    rt_red = rbis.intersect(rplus)

    if(fs != 1):

        if(rucs.is_empty()):
            TILE_SOUR = TILE_SOUR.subtract(TILE_SOUR.apply(rplus)).coalesce()  # remove dependent blocks with srepr



        TILE_RUCS = slicing.Create_RUCS(rel_, rs, TILE_SOUR, TILE_SOUR, 1, Rel_Y)

        TILE_SOUR = TILE_SOUR.subtract(TILE_RUCS.range()).coalesce()



        z = TILE_SOUR.apply(Rel_Z).coalesce()

        if(SIMPLIFY):
            z = imperf_tile.SimplifySlice(z)




        srepr_loop = iscc.iscc_communicate("L :=" + str(z) + "; codegen L;")    # albo omega
        #srepr_loop = iscc.oc_communicate(z)
        print(srepr_loop)
        srepr_loop = srepr_loop.split('\n')



        for i in range(0, len(srepr_loop)):
            if "for" in srepr_loop[i]:
                srepr_loop.insert(i, "#pragma omp parallel for")
                break


        st_reg = re.compile(r'\s*\(.*\);')
        vecs = []
        taby = []
        for line in srepr_loop:
            if(st_reg.match(line)):
                vecs.append(isl.Set(iscc.s1_to_vec2(line, len(vecs))))
                taby.append(iscc.correct.whites(line))

        #print vecs

        permutate_maps = Dodatek[6]
        permutate_list = Dodatek[5]




        slices = []


        for i in range(0,len(vecs)):
            vecs[i] = vecs[i].intersect(z).coalesce()


        for vec in vecs:
            vec = vec.insert_dims(isl.dim_type.set, x*len(sym_exvars), x*len(sym_exvars)+1)
            slice = vec #.apply(rs)
            slice = slice.apply(Rel_Y)
            slice = slice.apply(rs).coalesce()


            # experimental permutate

            if(len(permutate_list) > 0):
                print("Tiling + slicing + permutation - experimental")
                RP = permutate_maps[0]

                RIDENT = RP.identity(RP.get_space())

                if(not RP.is_equal(RIDENT)):  #permute map is not an identity map
                    strRP = str(RP)
                    strh = ""
                    for i in range(0, x*len(sym_exvars)):
                        strh = strh + "xx" + str(i) + ","


                    if(Extend):
                        strkoma = strRP.split(",")
                        strRP = ""
                        for i in range(0, 2*len(sym_exvars)):
                            strRP = strRP + strkoma[i] + ", yy" + str(i%len(sym_exvars)) + ", "
                        strRP = strRP + strkoma[2*len(sym_exvars)]

                    strRP = strRP.replace("[", "[" + strh)
                    RP = isl.Map(strRP)


                    slice = slice.apply(RP).coalesce()
            # ---------------------------------------------------------

            if(SIMPLIFY):
                slice = imperf_tile.SimplifySlice(slice)
            slices.append(slice)
            print(slice)




        cmd = ""
        for i in range(0, len(vecs)):
            cmd = cmd + "codegen " + str(slices[i]) + ';print "###";'

        cmd = iscc.iscc_communicate(cmd)

        cmd = cmd.split('"###"')


        new_loop = []
        i=0
        for line in srepr_loop:
            if(st_reg.match(line)):
                petla = cmd[i].split('\n')
                for s in petla:
                     new_loop.append(taby[i] + s)
                i = i + 1
            else:
                new_loop.append(line)


        nloop = ""
        for line in new_loop:
            if line != '':
                nloop = nloop + line + "\n"
        nloop = nloop[:-1]

        #nloop = nloop + indloop
        nloop = nloop.split('\n')

        # Dodatek = [LPetit, dane,  maxl, step, nazwapar, permutate_list, permutate_maps]

        #permutate list
        nloop = tiling_v3.postprocess_loop(nloop)
        lines = nloop.split('\n')

        loop = imperf_tile.RestoreStatements(lines, Dodatek[0], Dodatek[1],  Dodatek[2], Dodatek[3], Dodatek[5])

        text_file = open(Dodatek[4], "w")
        text_file.write(loop)
        text_file.close()
        return ""
    else:
        print("fs (EXPERIMENTAL) ...")

        sym_tmp = []
        rlex = "{["
        for s in sym_exvars:
            rlex = rlex + s + ","
            sym_tmp.append(s+"'")
        rlex = rlex[:-1] + '] -> ['
        for s in sym_exvars:
            rlex = rlex + s + "',"
        rlex = rlex[:-1] + '] : '
        rlex = rlex + tiling_v3.CreateLex(sym_tmp, sym_exvars) + "};"

        rlex = isl.Map(rlex)

        rlex = rlex.insert_dims(isl.dim_type.in_, len(sym_exvars), len(sym_exvars)+1)
        rlex = rlex.insert_dims(isl.dim_type.out, len(sym_exvars), len(sym_exvars)+1)

        UDS = isl_rel.domain().subtract(isl_rel.range())

        UDS = UDS.insert_dims(isl.dim_type.set, 0, len(sym_exvars))
        for i in range(0, len(sym_exvars)):
            UDS = UDS.set_dim_name(isl.dim_type.set, i, sym_exvars[i])

        if(Extend):
            for i in range(0, 2*len(sym_exvars)):
                UDS = UDS.insert_dims(isl.dim_type.set, 2*i+1, 1)
                rlex = rlex.insert_dims(isl.dim_type.in_, 2*i+1, 1)
                rlex = rlex.insert_dims(isl.dim_type.out, 2*i+1, 1)

        tuds = UDS.intersect(isl_TILEbis).coalesce()
        #tuds = tuds.insert_dims(isl.dim_type.set, len(sym_exvars), len(sym_exvars)+1)

        rt_red = rt_red.intersect(rlex).coalesce()

        rk = rt_red.power()
        rk = rk[0]
        rk = isl.Map(iscc.RepairRk(str(rk), 0))

        rp = rt_red.transitive_closure()[0]
        sk = tuds.apply(rk).subtract(tuds.apply(rk).apply(rp)).coalesce()


        sk = sk.apply(Rel_Y).intersect(isl_TILEbis)
        sk = sk.insert_dims(isl.dim_type.set, 0, 1)
        sk = sk.set_dim_name(isl.dim_type.set, 0, "ink")

        c = isl.Constraint.eq_from_names(sk.get_space(), {"k": -1, "ink":1})
        sk = sk.add_constraint(c)
        sk = tiling_v3.Project(sk, ["k"])

        tuds = tuds.apply(Rel_Y).intersect(isl_TILEbis)
        tuds = tuds.insert_dims(isl.dim_type.set, 0, 1)
        tuds = tuds.set_dim_name(isl.dim_type.set, 0, "ink")

        c= isl.Constraint.eq_from_names(sk.get_space(), {1: 0, "ink":1})
        tuds = tuds.add_constraint(c)

        sk = sk.union(tuds)

        print(sk)

        fsloop = iscc.iscc_communicate("L :=" + str(sk) + "; codegen L;")

        nloop = fsloop.split('\n')
        nloop = tiling_v3.postprocess_loop(nloop)
        lines = fs_pragma(nloop)

        #Dodatek[2]+1 shift + 1  for k
        #if extend first shift shoud be one smaller
        if(Extend):
            sh = 1
        else:
            sh = 0

        loop = imperf_tile.RestoreStatements(lines, Dodatek[0], Dodatek[1],  Dodatek[2]+1, Dodatek[3], Dodatek[5], sh)

        text_file = open(Dodatek[4], "w")
        text_file.write(loop)
        text_file.close()
        return ""



def tile_par(isl_TILEprim, isl_TILEbis, sym_exvars, symb, isl_rel, isl_relplus, isl_relclosure):

    nloop = ""
    srepr = ""
    with open('sources_of_slices.txt') as f:
        content = f.readlines()
        srepr = content[0]

    srepr = isl.Set(srepr)

    srepr = srepr.insert_dims(isl.dim_type.set, 0, len(sym_exvars))
    for i in range(0, len(sym_exvars)):
        srepr = srepr.set_dim_name(isl.dim_type.set, i, sym_exvars[i])

    Rel_Z = "{["
    for i in range(0, 2*len(sym_exvars)):
        Rel_Z = Rel_Z + "i" + str(i) + ","
    Rel_Z = Rel_Z + "m] -> ["
    for i in range(0, len(sym_exvars)):
        Rel_Z = Rel_Z + "i" + str(i) + ","
    Rel_Z = Rel_Z[:-1] + "] };"

    Rel_Z = isl.Map(Rel_Z)

    Bis_Combo = isl_TILEbis[0]
    for j in range(1, len(isl_TILEbis)):
        Bis_Combo = Bis_Combo.union(isl_TILEbis[j]).coalesce()


    TILE_SOUR = Bis_Combo.intersect(srepr).coalesce()
    print(TILE_SOUR)

    fs = 0
    if(TILE_SOUR.lexmax() == TILE_SOUR.lexmin()):
        print("FS")
        fs = 1
    else:
        print("SLICING")

    rplus = tiling_v3.ExtendMap(isl_relplus, sym_exvars)
    rstar = tiling_v3.ExtendMap(isl_relclosure, sym_exvars)
    rt_red = tiling_v3.ExtendMap(isl_rel, sym_exvars)

    rs = isl.Map.from_domain_and_range(Bis_Combo,Bis_Combo)

    rs = rs.intersect(rplus)
    rt_red = rs.intersect(rs)

    if(fs != 1):
        z = TILE_SOUR.apply(Rel_Z)

        srepr_loop = iscc.iscc_communicate("L :=" + str(z) + "; codegen L;")

        rs = iscc.iscc_communicate(str(rs) + ";", 1).split('\n')[0]
        rs = iscc.RelationExists(rs, len(sym_exvars), symb)

        srepr_loop = srepr_loop.split('\n')

        for i in range(0, len(srepr_loop)):
            if "for" in srepr_loop[i]:
                srepr_loop.insert(i, "#pragma omp parallel for")
                break


        st_reg = re.compile(r'\s*\(.*\);')
        vecs = []
        taby = []
        for line in srepr_loop:
            if(st_reg.match(line)):
                vecs.append(iscc.s1_to_vec(line, len(vecs)))
                taby.append(iscc.correct.whites(line))


        #R_T = iscc_communicate("RS := " + rs + ";RS;")
        cmd = "RT :=" + rs + ";"
        for i in range(0, len(vecs)):
            cmd = cmd + vecs[i] + "codegen RT(S" + str(i) + ');print "###";'

        cmd = iscc.iscc_communicate(cmd)

        cmd = cmd.split('"###"')
        new_loop = []
        i=0
        for line in srepr_loop:
            if(st_reg.match(line)):
                petla = cmd[i].split('\n')
                for s in petla:
                     new_loop.append(taby[i] + s)
                i = i + 1
            else:
                new_loop.append(line)

        #print new_loop

        nloop = ""
        for line in new_loop:
            if line != '':
                nloop = nloop + line + "\n"
        nloop = nloop[:-1]

        isl_TILEprim_ = isl_TILEprim[0].union(isl_TILEprim[1]);


        bl_2half = iscc.iscc_communicate("L :=" + str(isl_TILEprim[0]) + "; codegen L;")
        slice_tiling(nloop, bl_2half, sym_exvars)
    else:


        I = isl.Map.identity(isl.Space.create_from_names(ctx, in_=sym_exvars, out=sym_exvars)).coalesce()

        sym_tmp = []
        rlex = "{["
        for s in sym_exvars:
            rlex = rlex + s + ","
            sym_tmp.append(s+"'")
        rlex = rlex[:-1] + '] -> ['
        for s in sym_exvars:
            rlex = rlex + s + "',"
        rlex = rlex[:-1] + '] : '
        rlex = rlex + tiling_v3.CreateLex(sym_tmp, sym_exvars) + "};"

        rlex = isl.Map(rlex)


        UDS = isl_rel.domain().subtract(isl_rel.range())

        UDS = UDS.insert_dims(isl.dim_type.set, 0, len(sym_exvars))
        for i in range(0, len(sym_exvars)):
            UDS = UDS.set_dim_name(isl.dim_type.set, i, sym_exvars[i])

        tuds = UDS.intersect(isl_TILEbis[0]).coalesce().apply(Rel_Z).coalesce()

        rt_red = iscc.iscc_communicate(str(rt_red) + ";", 1).split('\n')[0]
        rt_red= iscc.RelationExists(rt_red, len(sym_exvars), symb)


        #rk = iscc_communicate(rlex + 'RT_RED := ' + rt_red + "*RLEX;pow RT_RED;")
        rt_red = isl.Map(rt_red).intersect(rlex).coalesce()
        rk = rt_red.power()

        rk = rk[0]
        rk = isl.Map(iscc.RepairRk(str(rk), 0))

        rp = rt_red.transitive_closure()[0]

        sk = tuds.apply(rk).subtract(tuds.apply(rk).apply(rp)).coalesce()

        sk = sk.insert_dims(isl.dim_type.set, 0, 1)

        sk = sk.set_dim_name(isl.dim_type.set, 0, "ink")

        c= isl.Constraint.eq_from_names(sk.get_space(), {"k": -1, "ink":1})

        sk = sk.add_constraint(c)

        sk = tiling_v3.Project(sk, ["k"])

        tuds = tuds.insert_dims(isl.dim_type.set, 0, 1)
        tuds = tuds.set_dim_name(isl.dim_type.set, 0, "ink")

        c= isl.Constraint.eq_from_names(sk.get_space(), {1: 0, "ink":1})
        tuds = tuds.add_constraint(c)

        sk = sk.union(tuds)

        fsloop = iscc.iscc_communicate("L :=" + str(sk) + "; codegen L;")

        bl_2half = iscc.iscc_communicate("L :=" + str(isl_TILEprim[0]) + "; codegen L;")
        slice_tiling(fsloop, bl_2half, sym_exvars , 1)


def get_RTILE(isl_TILEbis, sym_exvars, isl_rel, Extend, opt=0):

    x = 1
    if(Extend):
        x = 2

    rbis = isl.Map.from_domain_and_range(isl_TILEbis,isl_TILEbis)
    rel_ = tiling_v3.ExtendMap(isl_rel, sym_exvars, Extend)


    if(opt==0):
        Rel_W = "{["
        for i in range(0, x*len(sym_exvars)):
            Rel_W = Rel_W + "i" + str(i) + ","
        Rel_W = Rel_W + "m1] -> ["
        for i in range(0, x*len(sym_exvars)):
            Rel_W = Rel_W + "o" + str(i) + ","
        Rel_W = Rel_W + "m2] : not ("
        for i in range(0, x*len(sym_exvars)):
            Rel_W = Rel_W + "i" + str(i) + " = " + "o" + str(i) + " and "
        Rel_W = Rel_W[:-4] + ")}"
    else:
        Rel_W = "{["
        for i in range(0, x*len(sym_exvars)):
            Rel_W = Rel_W + "i" + str(i) + ","
        Rel_W = Rel_W[:-1] + "] -> ["
        for i in range(0, x*len(sym_exvars)):
            Rel_W = Rel_W + "o" + str(i) + ","
        Rel_W = Rel_W[:-1] + "] : not ("
        for i in range(0, x*len(sym_exvars)):
            Rel_W = Rel_W + "i" + str(i) + " = " + "o" + str(i) + " and "
        Rel_W = Rel_W[:-4] + ")}"


    rel_simple = rbis.intersect(rel_)
    rel_simple = rel_simple.project_out(isl.dim_type.in_, x*len(sym_exvars),x*len(sym_exvars))
    rel_simple = rel_simple.project_out(isl.dim_type.out, x*len(sym_exvars),x*len(sym_exvars))

    relw = isl.Map(Rel_W)

    rel_simple = rel_simple.intersect(relw).coalesce()

    rel_simple = rel_simple.coalesce()

    #get_RCYCLE(rel_simple, 0)

    return rel_simple


def get_RCYCLE(rel_simple, orig):

    #rel_simple = isl.Map("[n] -> {[i,j] -> [i',j'] : 1 <= i <= n && 1 <= j <= n && 1 <= i' <= n && 1 <= j' <= n}")

    rplus = rel_simple.transitive_closure()[0].coalesce()
    inp = []
    outp = []
    symb = []


    n = rel_simple.dim(isl.dim_type.in_)

    for i in range(0,n):
        inp.append("i" + str(i))
        outp.append("o" + str(i))
        symb.append("s" + str(i))

    rlex = "{[" + ",".join(inp) + "] -> [" + ",".join(outp) + "] : " + tiling_v3.CreateLex(outp, inp) + "}"
    rlex = isl.Map(rlex)

    invert_rel = rel_simple.fixed_power_val(-1).coalesce()




    r_out = rlex.intersect(rplus.intersect(invert_rel)).coalesce()


    print('R_CYCLE')
    print(r_out)

    if orig == 1:
        print("Oryginal TILES")

    print('#nowa prosta implementacja R_CYCLE')

    S = "[" + ",".join(symb) + "] -> {[" + ",".join(symb) + "]}"
    S = isl.Set(S)

    R_CYCLE2 = S.apply(rplus).intersect(S).coalesce()

    print(R_CYCLE2)


    return r_out






def tile_par3(isl_TILEbis, sym_exvars, isl_rel, isl_relplus, isl_relclosure, Extend, _rap, Dodatek, SIMPLIFY, ii_SET):

    #print isl_TILEbis
    srepr,rucs = slicing.Create_Srepr(isl_rel, isl_relclosure)



    fs = 0

    ir = isl_rel.domain().union(isl_rel.range()).coalesce()
    ir = ir.insert_dims(isl.dim_type.set, 0, len(sym_exvars))
    for i in range(0, len(sym_exvars)):
        ir = ir.set_dim_name(isl.dim_type.set, i, sym_exvars[i])

    if(Extend):
        for i in range(0, 2*len(sym_exvars)):
            ir = ir.insert_dims(isl.dim_type.set, 2*i, 1)

    srepr = srepr.insert_dims(isl.dim_type.set, 0, len(sym_exvars))
    for i in range(0, len(sym_exvars)):
        srepr = srepr.set_dim_name(isl.dim_type.set, i, sym_exvars[i])

    if(Extend):
        for i in range(0, 2*len(sym_exvars)):
            srepr = srepr.insert_dims(isl.dim_type.set, 2*i, 1)





    x = 1
    if(Extend):
        x = 2

    #relacja do obliczenia poczatkow
    Rel_Z = "{["
    for i in range(0, 2*x*len(sym_exvars)):
        Rel_Z = Rel_Z + "i" + str(i) + ","
    Rel_Z = Rel_Z + "m] -> ["
    for i in range(0, x*len(sym_exvars)):
        Rel_Z = Rel_Z + "i" + str(i) + ","
    Rel_Z = Rel_Z[:-1] + "] };"

    Rel_Z = isl.Map(Rel_Z)

    #relacja do wylapania instrukcji z blokow
    Rel_Y = "{["
    for i in range(0, x*len(sym_exvars)):
        Rel_Y = Rel_Y + "i" + str(i) + ","
    for i in range(0, x*len(sym_exvars)+1):
        Rel_Y = Rel_Y + "j" + str(i) + ","
    Rel_Y = Rel_Y[:-1] + "] -> ["
    for i in range(0, x*len(sym_exvars)):
        Rel_Y = Rel_Y + "i" + str(i) + ","
    for i in range(0, x*len(sym_exvars)+1):
        Rel_Y = Rel_Y + "k" + str(i) + ","
    Rel_Y = Rel_Y[:-1] + "] };"

    Rel_Y = isl.Map(Rel_Y)


    Rel_W = "{["
    for i in range(0, x*len(sym_exvars)):
        Rel_W = Rel_W + "i" + str(i) + ","
    Rel_W = Rel_W + "m1] -> ["
    for i in range(0, x*len(sym_exvars)):
        Rel_W = Rel_W + "o" + str(i) + ","
    Rel_W = Rel_W + "m2] : not ("
    for i in range(0, x*len(sym_exvars)):
        Rel_W = Rel_W + "i" + str(i) + " = " + "o" + str(i) + " and "
    Rel_W = Rel_W[:-4] + ")}"

    TILE_SOUR = isl_TILEbis.intersect(srepr).coalesce()




    TILE_IND = isl_TILEbis.subtract(isl_TILEbis.intersect(ir)).coalesce()

    indloop =  iscc.iscc_communicate("L :=" + str(TILE_IND) + "; codegen L;")


    if(TILE_SOUR.lexmax() == TILE_SOUR.lexmin()):
        print("FS")
        fs = 1
    else:
        print("=========================================================================")
        print("SLICING + TILING")
        if(rucs.is_empty()):
            isl_rel = isl_rel.union(rucs)
            isl_relclosure = isl_relclosure.union(rucs)
            isl_relplus = isl_relplus.union(rucs)



    rplus = tiling_v3.ExtendMap(isl_relplus, sym_exvars, Extend)
    rstar = tiling_v3.ExtendMap(isl_relclosure, sym_exvars, Extend)
    rel_ = tiling_v3.ExtendMap(isl_rel, sym_exvars, Extend)
    rucs = tiling_v3.ExtendMap(rucs, sym_exvars, Extend)

    rbis = isl.Map.from_domain_and_range(isl_TILEbis,isl_TILEbis)





    rs = rbis.intersect(rstar)



    rs = rs.union(rucs.transitive_closure()[0].intersect(rbis)).coalesce()


    
    Exp = True
    TMP2 = TILE_SOUR
    if(Exp and fs != 1):
        rel_simple = rbis.intersect(rel_)
        print(rel_simple)

        rel_simple = rel_simple.project_out(isl.dim_type.in_, x*len(sym_exvars),x*len(sym_exvars))
        rel_simple = rel_simple.project_out(isl.dim_type.out, x*len(sym_exvars),x*len(sym_exvars))



        relw = isl.Map(Rel_W)
        rel_simple = rel_simple.intersect(relw).coalesce()

        rel_simple = rel_simple.coalesce()

        print("RT")
        print(rel_simple)

        #independent tiles


        indt = rel_simple.domain().union(rel_simple.range()).coalesce()


        print(indt)
        #print II_SET

        #indt = ii_SET.subtract(indt).coalesce()

        # II_SET z Clana




        rel_simple_plus = rel_simple.transitive_closure()[0]

        print("RT+")
        print(rel_simple_plus)

        srepr,rucs = slicing.Create_Srepr(rel_simple, rel_simple_plus)

        print(srepr)


        # NAPRAWIC

        # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        #add independent tiles for srepr


        #srepr = srepr.union(indt).coalesce()

        print("SREPR")
        print(srepr)
        print("RUCS")
        print(rucs)

        #sys.exit()



       # srepr = imperf_tile.SimplifySlice(srepr)
        srepr = srepr.insert_dims(isl.dim_type.set, x*len(sym_exvars), x*len(sym_exvars))
        TILE_SOUR = isl_TILEbis.intersect(srepr).coalesce()




        TMP2 = TILE_SOUR

    

    if(fs != 1):


        if(rucs.is_empty()):
            TILE_SOUR = TILE_SOUR.subtract(TILE_SOUR.apply(rplus)).coalesce()  # remove dependent blocks with srepr


        TILE_RUCS = slicing.Create_RUCS(rel_, rs, TILE_SOUR, TILE_SOUR, 1, Rel_Y)
        
        
        TILE_SOUR = TILE_SOUR.subtract(TILE_RUCS.range()).coalesce()

        print("TILE_RUCS")
        print(TILE_RUCS)
        print("TILE_SOUR")
        print(TILE_SOUR)


        TILE_SOUR = TMP2
        z = TILE_SOUR.apply(Rel_Z).coalesce()

        if(SIMPLIFY):
            z = imperf_tile.SimplifySlice(z)


        srepr_loop = iscc.iscc_communicate("L :=" + str(z) + "; codegen L;")    # albo omega
        #srepr_loop = iscc.oc_communicate(z)

        srepr_loop = srepr_loop.split('\n')



        for i in range(0, len(srepr_loop)):
            if "for" in srepr_loop[i]:
                srepr_loop.insert(i, "#pragma omp parallel for")
                break

        #print srepr_loop

        st_reg = re.compile(r'\s*\(.*\);')
        vecs = []
        taby = []
        for line in srepr_loop:
            if(st_reg.match(line)):
                vecs.append(isl.Set(iscc.s1_to_vec2(line, len(vecs))))
                taby.append(iscc.correct.whites(line))

        #print vecs

        permutate_maps = Dodatek[6]
        permutate_list = Dodatek[5]


        slices = []


        for i in range(0,len(vecs)):
            vecs[i] = vecs[i].intersect(z).coalesce()


        for vec in vecs:
            vec = vec.insert_dims(isl.dim_type.set, x*len(sym_exvars), x*len(sym_exvars)+1)
            #vec = vec.insert_dims(isl.dim_type.set, x*len(sym_exvars), 1)
            slice = vec #.apply(rs)
            slice = slice.apply(Rel_Y)
            slice = slice.apply(rs).coalesce()
            #print slice
            #print rs1


            #slice = slice.apply(rs1).coalesce()
            #slice = slice.insert_dims(isl.dim_type.set, x*len(sym_exvars), x*len(sym_exvars))
            #slice = slice.intersect(isl_TILEbis).coalesce()



            # experimental permutate

            if(len(permutate_list) > 0):
                print("Tiling + slicing + permutation - experimental")
                RP = permutate_maps[0]

                RIDENT = RP.identity(RP.get_space())

                if(not RP.is_equal(RIDENT)):  #permute map is not an identity map
                    strRP = str(RP)
                    strh = ""
                    for i in range(0, x*len(sym_exvars)):
                        strh = strh + "xx" + str(i) + ","


                    if(Extend):
                        strkoma = strRP.split(",")
                        strRP = ""
                        for i in range(0, 2*len(sym_exvars)):
                            strRP = strRP + strkoma[i] + ", yy" + str(i%len(sym_exvars)) + ", "
                        strRP = strRP + strkoma[2*len(sym_exvars)]

                    strRP = strRP.replace("[", "[" + strh)
                    RP = isl.Map(strRP)


                    slice = slice.apply(RP).coalesce()
            # ---------------------------------------------------------

            if(SIMPLIFY and False):
                slice = imperf_tile.SimplifySlice(slice)

            slices.append(slice)
            #print slice




        cmd = ""
        for i in range(0, len(vecs)):
            print("SLICE")
            print(slices[i])
            cmd = cmd + "codegen " + str(slices[i]) + ';print "###";'

        cmd = iscc.iscc_communicate(cmd)

        cmd = cmd.split('"###"')


        new_loop = []
        i=0
        for line in srepr_loop:
            if(st_reg.match(line)):
                petla = cmd[i].split('\n')
                for s in petla:
                     new_loop.append(taby[i] + s)
                i = i + 1
            else:
                new_loop.append(line)


        nloop = ""
        for line in new_loop:
            if line != '':
                nloop = nloop + line + "\n"
        nloop = nloop[:-1]

        nloop = nloop + "// independent statements \n" + indloop

        nloop = nloop.split('\n')

        # Dodatek = [LPetit, dane,  maxl, step, nazwapar, permutate_list, permutate_maps]

        #permutate list
        nloop = tiling_v3.postprocess_loop(nloop)
        lines = nloop.split('\n')

        loop = imperf_tile.RestoreStatements(lines, Dodatek[0], Dodatek[1],  Dodatek[2], Dodatek[3], Dodatek[5])

        text_file = open(Dodatek[4], "w")
        text_file.write(loop)
        text_file.close()
        return ""
    else:


        rel_ = rbis.intersect(rel_)


        rel_ = rel_.project_out(isl.dim_type.in_, x*len(sym_exvars),x*len(sym_exvars))
        rel_ = rel_.project_out(isl.dim_type.out, x*len(sym_exvars),x*len(sym_exvars))
        rel_ = rel_.coalesce()



        relw = isl.Map(Rel_W)

        rel_ = rel_.intersect(relw).coalesce()

        print("REL")
        print(rel_)

        #independent tiles
        #indt = rel_.domain().union(rel_.range()).coalesce()
        #indt = ii_SET.subtract(indt).coalesce()

        indt = ""



        # FS z RK
        sk = fs_rk.fs_rk1(rel_, SIMPLIFY, indt)


        # FS bez RK
        #sk = fs_karl.FSwithoutRG(rel_)

        sk = sk.insert_dims(isl.dim_type.set, x*len(sym_exvars)+1,x*len(sym_exvars))


        bis = isl_TILEbis.insert_dims(isl.dim_type.set, 0, 1)

        sk = bis.intersect(sk).coalesce()

        if(SIMPLIFY):
    	    sk = imperf_tile.SimplifySlice(sk)
        #sys.exit(0);
        print("SK")
        print(sk)

        print("Codegen now...")
        #fsloop = iscc.iscc_communicate("L :=" + str(sk) + "; codegen L;")

        fsloop =  iscc.isl_ast_codegen(sk)

        print("Codegen done.")

        nloop = fsloop.split('\n')
        nloop = tiling_v3.postprocess_loop(nloop)
        lines = fs_pragma(nloop)

        #Dodatek[2]+1 shift + 1  for k
        #if extend first shift shoud be one smaller
        if(Extend):
            sh = 1
        else:
            sh = 0

        loop = imperf_tile.RestoreStatements(lines, Dodatek[0], Dodatek[1],  Dodatek[2]+1, Dodatek[3], Dodatek[5], sh)

        text_file = open(Dodatek[4], "w")
        text_file.write(loop)
        text_file.close()
        return ""


    


