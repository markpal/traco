import sys

try:
    import islpy as isl
except ImportError as e:
    print(e)
    print("pip install ispy")
    sys.exit()



import iscc
import os
import imperf_tile
import tiling_v3
import tiling_schedule
import openacc
import clanpy
import iscc
import imperf_tile
import re
import correct
import copyconstr
import relation_util




def fs_new(rel, rel_plus, isl_relclosure, uds, LPetit, dane, plik, SIMPLIFY, rap, acc, loop, exact):

    #floyd
    #rel_ = isl.Map(str('{[i,j,k,v]->[i,jj,kk,v]}'))
    #rel = rel.intersect(rel_).coalesce()

    # R = R - R+ compose R


    # do zrobienia
    # 4. perf imperf rozroznic


    #codegen = 'barvinok'
    codegen = 'isl'

    #rel = "[n, loop] -> { [l, i, k, 13] -> [l, i+1, k', 13] : k'=0 && k = i-1 && 1<=l<=loop && 1<=i<n-1;" \
    #      "[l, i, 0, 13] -> [l, i, k', 13] : 1<=l<=loop && 1<=i<n &&  0 < k' <=i;" \
    #      "[l, n-1, n-2, 13] -> [l+1, 1, 0, 13] : 1 <=l < loop } "
    #rel = "{[i,k,8] -> [i+1,k',8] : k'=0 && k=i-1 && 1<=i<6; [i,0,8] -> [i,k',8] : 0 < k' <= i && 1 <= i <= 6}"
    #rel = isl.Map(rel)
    #rel_plus = rel.transitive_closure()[0]

    if(exact):
        print('R+ exact!')
    else:
        print('R+ approximated. Iterate way...!')

        r0p_plus = relation_util.oc_IterateClosure(rel)
        rel_plus = r0p_plus

        isl_relclosure =  rel_plus
        isl_ident = rel.identity(rel.get_space())
        isl_relclosure = isl_relclosure.union(isl_ident).coalesce()  # R* = R+ u I

        print('Checking (the Pugh method)')

        # R = R compose RINV

        if (rel_plus.subtract(rel_plus.apply_range(rel).union(rel)).coalesce().is_empty()):
            print(' .... OK !!')
        else:
            print('R+ failed.')
            sys.exit(0)

        #file = open('lu_rplus.txt', 'r')
        #isl_relclosure = isl.Map(file.read())
        #print isl_relclosure



    print('## R')


    print(rel)


    print('## R+')
    print(rel_plus)


    rel = rel.subtract(rel_plus.apply_range(rel))

    print('### R = R - R+ compose R')
    print(rel)

    global_size = rel.dim(isl.dim_type.in_)

    UDS = rel.domain().subtract(rel.range()).coalesce()
    UDD = rel.range().subtract(rel.domain()).coalesce()
    DOM_RAN = rel.range().union(rel.domain()).coalesce()

    cl = clanpy.ClanPy()
    cl.loop_path = plik
    cl.Load()
    cl.RunCandl()

    IS = DOM_RAN
    for i in range(0, len(cl.statements)):
        IS_ =  isl.Set(cl.statements[i].domain_map).coalesce()
        print(IS_)
        set_size = IS_.dim(isl.dim_type.set)

        for j in range(set_size, global_size-1):
            IS_ = IS_.insert_dims(isl.dim_type.set, j, 1)
            IS_ = IS_.set_dim_name(isl.dim_type.set, j, 'i' + str(j))
            c= isl.Constraint.eq_from_names(IS_.get_space(), {IS_.get_dim_name(isl.dim_type.set, j): -1, 1:-1})
            IS_ = IS_.add_constraint(c).coalesce()

        set_size = IS_.dim(isl.dim_type.set)

        IS_= IS_.insert_dims(isl.dim_type.set, set_size, 1)
        IS_ = IS_.set_dim_name(isl.dim_type.set, set_size, "v")

        #print cl.statements[i].body
        c= isl.Constraint.eq_from_names(IS_.get_space(), {"v": -1, 1:int(dane[i])})
        IS_ = IS_.add_constraint(c).coalesce()



        if i == 0:
            IS = IS_
        else:
            IS = IS.union(IS_).coalesce()

    print("IS")
    print(IS)




    IND = IS.subtract(DOM_RAN).coalesce()

    print("IND")
    print(IND)


    n = rel.dim(isl.dim_type.in_)

    inp = []
    outp = []
    for i in range(0,n):
        inp.append("i" + str(i))
        outp.append("o" + str(i))


    # Rlex
    rlex = "{[" + ",".join(inp) + "] -> [" + ",".join(outp) + "] : " + tiling_v3.CreateLex(outp, inp) + "}"
    rlex = isl.Map(rlex)


    print("RLEX")
    print(rlex)

    rip = rel_plus.fixed_power_val(-1)

    re_rel = isl.Map.from_domain_and_range(IS, IS)

    #print re

    print("### RE")

    re_rel = re_rel.intersect(rlex.subtract(rel_plus).subtract(rip)).coalesce()

    print(re_rel)


    # oblicz Re1
    #Re1 = GetRe1(re_rel, rel_plus)

    #print "### RE2"
    #re_rel = re_rel.subtract(Re1).coalesce()
    #print re_rel
    re2 = re_rel

    W = re_rel.domain().union(re_rel.range()).coalesce()
    D = re_rel.domain().subtract(re_rel.range()).coalesce()



    rel_inv = rel.fixed_power_val(-1)

    print("R^-1")
    print(rel_inv)


    # R = R compose RINV

    #RR = rel.apply_range(rel_inv)
    RR = rel_inv.apply_range(rel)


    # ------ Jesli RCHECK ----------

    if(1==0):
        RRR1 = rel.fixed_power_val(2)
        RRR2 = rel_inv.fixed_power_val(2)
        RRR = RRR1.union(RRR2).coalesce()
        RR = RR.union(RRR).coalesce()

    # ------------------------------

    RR = RR.intersect(rlex).coalesce()

    print("### RR")
    print(RR)

    IND_lexmin = IND.lexmin()


    IND0ToIND = isl.Map.from_domain_and_range(IND_lexmin, IND).coalesce()



    RRPLUS = RR.transitive_closure()
    RR_EXACT = RRPLUS[1]
    RRPLUS = RRPLUS[0]

    if not RR_EXACT:
        print('RR+ not exact')
        #sys.exit(0)


    # sprawdz dokladnosc



    R2 = GetR2(re_rel, RRPLUS)



    print('### RRPLUS')
    print(RRPLUS)

    print('### R2')
    R2 = R2.coalesce()
    print(R2)


    RRstar = RRPLUS
    RR_ident = RR.identity(RR.get_space())
    RRstar = RRstar.union(RR_ident).coalesce()  # R* = R+ u I


    print("### Rstar")
    print(RRstar)

    REPR = D.union(DOM_RAN.subtract(W)).coalesce()

    # poprawka
    REPR = R2.domain().subtract(R2.range()).coalesce()
    print('#REPR1')
    print(REPR)


    tmp = REPR.apply(RRstar).coalesce()
    REPR2 = DOM_RAN.subtract(tmp).coalesce()

    print('#REPR2')
    print(REPR2)
    REPR = REPR.union(REPR2).coalesce()

    #REPR =imperf_tile.SimplifySlice(REPR)

    #####
    #REPR1:= domain    RE2 - range    RE2;
    #REPR2:= (domain    R    union    R) -RR * (REPR1);


    #REPR = REPR.intersect(IS)
    print("### REPR")
    print(REPR)



    if(1==0):
        Rtmp = REPR.polyhedral_hull()
        if (Rtmp.subtract(REPR).coalesce().is_empty() and REPR.subtract(Rtmp).coalesce().is_empty()):
            print("upraszczanie")
            REPR = Rtmp

    R1 = RRstar.intersect_domain(REPR.coalesce())

  #  R1 = R1.intersect_range(IS)


    print('RSCHED obliczanie :')
    print(R1)
    print("IND0->IND")
    print(IND0ToIND)
    #print R3
    print("i razem")




    #RSCHED = R1.union(IND0ToIND).coalesce()
    RSCHED = R1





    #upraszczanie
    if(SIMPLIFY and 1==0):
        Rtmp = RSCHED.polyhedral_hull()
        if (Rtmp.subtract(RSCHED).coalesce().is_empty() and RSCHED.subtract(Rtmp).coalesce().is_empty()):
            print("upraszczanie")
            RSCHED = Rtmp

    #RSCHED = imperf_tile.SimplifyMap(RSCHED)


    print("### RSCHED")
    print(RSCHED)




    print("### Check ")
    Check_set = RSCHED.domain().union(RSCHED.range()).coalesce()

    Check_set = IS.subtract(IND).subtract(Check_set).coalesce()

    if Check_set.is_empty():
        print("OK")
    else:
        print(("ERROR ! " + str(Check_set)))
        sys.exit(0)


    # generowanie kodu

    D = RSCHED.domain()

    #if(SIMPLIFY):





    print("# DOMAIN RSCHED")



    print(D)

    D = D.apply(rap)

    #D = imperf_tile.SimplifySlice(D)
    D = D.coalesce()
    print(rap)
    print(D)

    if (codegen == 'barvinok'):
        looprepr = iscc.iscc_communicate("L :=" + str(D) + "; codegen L;")

    else:  # isl
        looprepr = iscc.isl_ast_codegen(D)

    for i in range(0,20):
        looprepr = re.sub('\\b'+'c' + str(i) +'\\b', 't' + str(i), looprepr)

    print(looprepr)

    looprepr  = looprepr.split('\n')








    st_reg = re.compile(r'\s*\(.*\);')
    vecs = []
    taby = []
    for line in looprepr:
        if(st_reg.match(line)):
            vecs.append(isl.Set(iscc.s1_to_vec3(line, len(vecs))))
            taby.append(iscc.correct.whites(line))


    slices = []
    for vec in vecs:
        slice = vec
        if(not RSCHED.is_empty()):
            slice_ = slice.apply(RSCHED)
            slice = slice.union(slice_).coalesce()
            slice = slice_

        print('-------- IS --------')
        print(IS)
        slice = slice.intersect(IS).coalesce()
        print(slice)
        #if(SIMPLIFY):
        #slice = imperf_tile.SimplifySlice(slice)


        # EKSPERIMENTAL CODE wywal z RE instrukcje nie nalezace do RE
        if(1==0):
            temp = slice.intersect(W).coalesce()
            if (not temp.is_empty()):
                slice = temp

        slice = slice.apply(rap)


        slices.append(slice.coalesce())



    new_loop = []
    i=0
    for line in looprepr:
        if(st_reg.match(line)):
            #print slices[i]
            if (codegen == 'barvinok'):
                petla = iscc.iscc_communicate("L :=" + str(slices[i]) + "; codegen L;")
                petla = petla.split('\n')
            else: #isl
                petla = iscc.isl_ast_codegen(slices[i]).split('\n')

            petla = correct.Korekta('', petla) # dodaj { } do for
            was_par = 0              # poprawic jak sie koncza petle i sa nowe
            for s in petla:
                if 'for (int c' in s and was_par == 0:
                    new_loop.append(taby[i] + imperf_tile.get_tab(s) + '#pragma omp parallel for')
                    if "{" in s:
                        was_par = 1
                new_loop.append(taby[i] + s)

                if was_par > 0:
                    if "{" in s:
                        was_par = was_par + 1
                    if "}" in s:
                        was_par = was_par - 1
            i = i + 1
        else:
            new_loop.append(line)


    nloop = ""
    for line in new_loop:
        if line != '':
#            if 'for (int c1' in line:   # c0 przy perf,  c1 przy imperf
#                line = imperf_tile.get_tab(line) + "#pragma omp parallel for\n" +line
            nloop = nloop + line + "\n"



    nloop = nloop[:-1]


    nloop = nloop.split('\n')

    nloop = tiling_v3.postprocess_loop(nloop)
    lines = nloop.split('\n')



    loop = imperf_tile.RestoreStatements(lines, LPetit, dane, 0, 1, [])

    print("==========================")
    print("OUTPUT CODE")
    print(loop)


    print(UDS)
    print((UDS - REPR))




def GetRe1(re, relplus):

    isl_symb = relplus.get_var_names(isl.dim_type.param)
    dim = relplus.dim(isl.dim_type.out)

    in_ = []
    out_= []
    ex_ = []

    for i in range(0, dim):
        in_.append('_in'+str(i))
        out_.append('_out' + str(i))
        ex_.append('_ex' + str(i))


    symb = ','.join(isl_symb)

    Re1 = ''

    # symbolic variables
    if(len(isl_symb) > 0):
        Re1 = Re1 + '['+symb+'] -> { '
    else:
        Re1 = Re1 + '{ '
    #tuple variables
    Re1 = Re1 + '[' + ','.join(in_) + '] -> [' + ','.join(out_) + '] : '

    #s2 in Re(s1)
    Re1 = Re1 +  copyconstr.GetConstr(in_, out_, re)

    #exists s1' :
    Re1 = Re1 + 'and exists ' + ','.join(ex_) + ' : ('

    # s1' in Re(s1)
    Re1 = Re1 + copyconstr.GetConstr(in_, ex_, re)

    # s2 in R+(s1')
    Re1 = Re1 + ' and ' + copyconstr.GetConstr(ex_, out_, relplus)

    Re1 = Re1 + ') }'



    Re1 = isl.Map(Re1)
    Re1.coalesce()

    print("### Re1")
    print(Re1)

    return Re1


def GetR2(re, rrplus):

    isl_symb = re.get_var_names(isl.dim_type.param)
    dim = rrplus.dim(isl.dim_type.out)

    in_ = []
    out_= []
    ex_ = []

    for i in range(0, dim):
        in_.append('_in'+str(i))
        out_.append('_out' + str(i))
        ex_.append('_ex' + str(i))


    symb = ','.join(isl_symb)

    R2 = ''

    # symbolic variables
    if(len(isl_symb) > 0):
        R2 = R2 + '['+symb+'] -> { '
    else:
        R2 = R2 + '{ '
    #tuple variables
    R2 = R2 + '[' + ','.join(in_) + '] -> [' + ','.join(out_) + '] : '

    #s2 in Re(s1)
    if not re.is_empty():
        R2 = R2 +  copyconstr.GetConstr(in_, out_, re) + ' and '

      #  if not re.is_empty():
      #      R2 = R2 + copyconstr.GetConstr(out_, in_, re) + ' and '

    #s2 in RR+(s1)
    if not rrplus.is_empty():
        R2 = R2 +  copyconstr.GetConstr(in_, out_, rrplus) + ' and '

    #s1 in Domain(Re)
    if not re.is_empty():
        R2 = R2 + copyconstr.GetConstrSet(in_, re.domain())
    else:
        R2 = R2 + ' 1=1 '

    R2 = R2 + '}'

    print(R2)

    R2 = isl.Map(R2)
    #R2.coalesce()

    #print "### R2"
    #print R2

    return R2