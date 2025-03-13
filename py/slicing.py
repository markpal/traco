# TODO IND and another rap, 0 first

import sys
import re
import os


try:
    import islpy as isl
except ImportError as e:
    print(e)
    print("pip install ispy")
    sys.exit()

ctx = isl.Context()



import Dependence


import tiling_v3
import iscc
import convert_loop

import imperf_tile




from CPython import codegen
import openacc

import fs_rk
import fs_new
import relation_util





def SymbolicTuple(n):
    symb = []
    for i in range(0,n):
        symb.append("xoxo" + str(i))
    koma = ','.join(symb)
    tuple = "[" + koma + "]->{[" + koma + "]}"
    return [isl.Set(tuple), symb]

def Create_RUCS(isl_rel, isl_relclosure,  uds, udsi, dl = 0, Rel_Y = ""):

    n = uds.dim(isl.dim_type.set)

    symb_tuple = SymbolicTuple(n)
    _symb = symb_tuple[1]
    symb_tuple = symb_tuple[0]

    Sx = udsi.intersect(symb_tuple)
    Si = Sx.apply(isl_relclosure)

    if(dl == 1):
        Si = Si.apply(Rel_Y).coalesce()


    ris = isl_relclosure.fixed_power_val(-1)

    S2 = Si.apply(ris).intersect(uds).coalesce()      # Intersection(Range(Restrict_Domain(copy(Ris), copy(S1))), copy(UDS));   // All_UDS?
    rucs = isl.Map.from_domain_and_range(Sx, S2).coalesce()          # Relation RUCS = Cross_Product(copy(Sx), copy(S2));


    inp = []
    outp = []
    inp2 = []
    outp2 = []

    if(dl == 0):
        zakres = n
    else:
        zakres = n/2



    for i in range(0,n):
        inp.append("i" + str(i))
        outp.append("o" + str(i))
        if(i < zakres):
            inp2.append("i" + str(i))
            outp2.append("o" + str(i))


    rlex = "{[" + ",".join(inp) + "] -> [" + ",".join(outp) + "] : " + tiling_v3.CreateLex(outp2, inp2) + "}"
    rlex = isl.Map(rlex)


    rucs = rucs.intersect(rlex)
    rucs = tiling_v3.Project(rucs, _symb).coalesce()

    return rucs



def Create_UDS(isl_rel):
    domR = isl_rel.domain()
    ranR = isl_rel.range()
    uds = domR.subtract(ranR)
    return uds

def Create_Srepr(isl_rel, isl_relclosure):
    uds = Create_UDS(isl_rel)
    print(isl_rel)
    rucs =  Create_RUCS(isl_rel, isl_relclosure, uds, uds)
    srepr = uds.subtract(rucs.range()).coalesce()
    if srepr.is_empty():
        srepr = uds
    print(uds)
    return [srepr,rucs]




def sfs(plik, L=0, SIMPLIFY=False, fs=0, acc=False):

    LPetit = "tmp/tmp_petit"+str(L)+".t"
    LDeps = "tmp/deps"+str(L)+".txt"
    
    linestring = open(plik, 'r').read()
    lines = linestring.split('\n')

    petit_loop = convert_loop.convert_loop(lines)
    petit_loop.insert(0, "! start")

    file = open(LPetit, 'w')
    
    for line in petit_loop:
        file.write(line + '\n')
    file.close()



    loop = Dependence.Kernel_Loop(LPetit)




    
    #cmd = gen.path_petit + " " + LPetit + " > " + LDeps
    #process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    #process.wait()
    #dane = gen.RelPrint(LPetit, 1)


    dane = loop.dane
    isl_rel = loop.isl_rel

    new_rel = relation_util.ReduceR(isl_rel)

    #isl_rel = new_rel



    #experimental



    instrukcje = loop.instrukcje

    # ------------------------
    #dane2 = []
    #sts = imperf_tile.Get_ST(LPetit, dane2)
    #dane2 = dane2 + sts
    #combo = loop_tools.ReadStatementNests(LPetit, dane2)



    # Create LD
#    isl_rel2 = Dependence.Create_LD_petit(str(L), petit_loop)
#    ld_rel = isl_rel2.identity(isl_rel2.get_space())
#    s1 = isl_rel2.domain()
#    s2 = isl_rel2.range()
#    s_all = s1.union(s2).coalesce()
#    s1 = isl_rel.domain()
#    s2 = isl_rel.range()
#    s_rel = s1.union(s2).coalesce()
#    ind = s_all.subtract(s_rel).coalesce()
#    print ind


    #sys.exit(0)


    # ------------------------

    #print dane
    #dane = dane.split("#")
    #rel = dane[0]
    #dane.remove(rel)
    #dane = list(set(dane))

    #isl_rel = isl.Map(str(rel)).coalesce()

    #print isl_rel

    SQ = False
    if(SQ):
        #print isl_rel
        RR = isl.Map("{[i,j,k,v] -> [i,j',k',v']}")
        isl_rel = isl_rel.intersect(RR).coalesce()
        #isl_rel = isl_rel.set_dim_name(isl.dim_type.in_, 0, "i")
        #isl_rel = isl_rel.set_dim_name(isl.dim_type.out, 0, "i'")
        #c= isl.Constraint.eq_from_names(isl_rel.get_space(), {"i": 1, "i'":-1})
        #isl_rel = isl_rel.add_constraint(c).coalesce()


    #rel_= isl.Map(str('{[i,j,k,v]->[i,jj,kk,v]}'))
    #isl_rel = isl_rel.intersect(rel_).coalesce()


    isl_relclosure = isl_rel.transitive_closure()

    exact = isl_relclosure[1]
    isl_relclosure = isl_relclosure[0]
    isl_relplus = isl_relclosure
    isl_ident = isl_rel.identity(isl_rel.get_space())
    isl_relclosure = isl_relclosure.union(isl_ident).coalesce()  # R* = R+ u I


    # ------------------------------

    vars = []
    for i in range(0, isl_rel.dim(isl.dim_type.in_)-1):
        vars.append('i'+str(i))

    rap =  GetRapply(vars, instrukcje, len(instrukcje)-1)

    # ------------------------------

    if(fs == 1):
        fs_rk.fs_rk(isl_rel, isl_relplus, Create_UDS(isl_rel), LPetit, dane, plik, SIMPLIFY, rap, acc, loop)
        sys.exit()


    if(fs == 2):  # na samym R+
        fs_new.fs_new(isl_rel, isl_relplus, isl_relclosure, Create_UDS(isl_rel), LPetit, dane, plik, SIMPLIFY, rap, acc, loop, exact)
        sys.exit()


    srepr = Create_Srepr(isl_rel, isl_relclosure)
    rucs = srepr[1]
    srepr = srepr[0]

    #experimetnal
    # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#    srepr = srepr.union(ind).coalesce()

    map = isl.Map.from_domain_and_range(srepr, srepr).to_str()
    print("L :=" + str(map) + "; codegen L;")

    srepr_loop = iscc.iscc_communicate("L :=" + str(map) + "; codegen L;")


    print(srepr_loop)


    srepr_loop = srepr_loop.decode('utf-8')
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
    
    #print srepr_loop


    rucs_s = rucs.transitive_closure()[0].coalesce()

    for i in range(0,len(vecs)):
        vecs[i] = isl_rel.domain().intersect(vecs[i]).coalesce()

    slices = []
    for vec in vecs:
        slice = vec
        if(not rucs.is_empty()):
            slice_ = slice.apply(rucs_s)
            slice = slice.union(slice_).coalesce()
        slice = slice.apply(isl_relclosure)

        if(SIMPLIFY):
            slice = imperf_tile.SimplifySlice(slice)


        slice = slice.apply(rap)


        slices.append(slice.coalesce())
        

    cmd = ""



    print(vecs)
    for i in range(0, len(vecs)):
        print(slices[i])
        map = isl.Map.from_domain_and_range(slices[i], slices[i]).to_str()
        cmd = cmd + "codegen " + str(map) + ';print "###";'



    cmd = iscc.iscc_communicate(cmd)
    cmd = cmd.decode('utf-8')
    cmd = cmd.split('"###"')
    
    print(cmd)
    
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
    nloop = nloop.split('\n')
            
    nloop = tiling_v3.postprocess_loop(nloop)
    print(nloop)
    lines = nloop.split('\n')

    if(acc):
        lines = openacc.CreateACCCode(lines, loop.var_st)


    loop = imperf_tile.RestoreStatements(lines, LPetit, dane, 0, 1, [])


    for i in range(0, 5):
        if(loop[-1] == '\n'):
            loop = loop[:-1]
    loop = loop + "\n"

    base = os.path.basename(plik)
    nazwa = os.path.splitext(base)[0] + "_slicing" + os.path.splitext(base)[1]



    text_file = open(nazwa, "w")
    text_file.write(loop)
    text_file.close()

    print(nazwa + ' was created.')


def GetRapply(vars, instrukcje, i):
    R = "{["
    for s in vars:
        R = R + s + ","
    R = R + "v] -> ["
    for s in vars:
        R = R +  s + "v," + s + ","
    R = R + "v] : "

    z = ""

    z = z + "("

    for l in range(0, i+1):
        for st in instrukcje[l]['st']:
            z = z + " (v = " + str(st) + " and "
            j = 0
            for s in vars:
                pos = -1
                if j < len(instrukcje[l]['path']):  #poprawka bo niektore nie maja max zagniezdzen
                    pos = instrukcje[l]['path'][j]
                else:
                    codegen.calculate_position2(l, instrukcje, len(vars))[j]


                z = z + s + "v = " + str(pos) + " and "
                j = j + 1
            z = z[:-4] + ") or "


    R = R + z[:-3] + ")}"
    isl_Rapply = isl.Map(R)
    #print isl_Rapply
    return isl_Rapply
