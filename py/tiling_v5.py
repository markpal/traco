import os, glob
import re
import time
from termcolor import colored
import numpy
import sys

try:
    import islpy as isl
except ImportError as e:
    print(e)
    print("pip install ispy")
    sys.exit()


import iscc
import convert_loop
import imperf_tile
import relation_util
import Dependence
import clanpy
import tiling_v2
import tiling_v3
import copyconstr
import tiling5_valid
import tiling_schedule

import agent



ctx = isl.Context()


def GetBounds(lines, st_line, BLOCK2, simpl):
    for_level = 0
    lev = len(BLOCK2)

    bounds=[]
    for i in range(st_line-1,0,-1):
        line = lines[i]
        if 'endfor' in line:   # not my loop
            for_level = for_level - 1
        else:
            if 'for' in line:
                if(for_level < 0):  # not my loop
                    for_level = for_level + 1
                else:
                    items = line.split(' ')
                    step = 1
                    if 'by' in line:
                        step = items[7]

                    lev = lev - 1

                    if(not simpl):
                        bounds.insert(0, {'var' : items[1], 'lb' : items[3], 'ub' : items[5], 'step' : step, 'loop' : line})
                    else:
                        if step == '-1':
                            bounds.insert(0, {'var': items[1], 'lb': items[3] + ' + ' +  BLOCK2[lev], 'ub': items[5] + ' - ' +  BLOCK2[lev] , 'step': step, 'loop': line})
                        else:
                            bounds.insert(0, {'var': items[1], 'lb': items[3] + ' - ' + BLOCK2[lev], 'ub': items[5] + ' + ' + BLOCK2[lev], 'step': step, 'loop': line})




    return bounds
############################################################

def MakeTile(st, vars, sym_exvars, symb, B):

    TILE = '['+','.join(symb + sym_exvars) +'] -> { [' + ','.join(vars) + ',' + str(st.petit_line) + '] : '

    deeploop =  len(st.original_iterators)


    for i in range(0, len(vars)):
        if(i < deeploop):
            tile_part = ''
            if(st.bounds[i]['step'] == 1 or st.bounds[i]['step'] == '1'):
                tile_part +=  st.bounds[i]['lb'] + ' + ' + B[i] + '*' + sym_exvars[i] + ' <= ' + vars[i] + ' <= '
                tile_part +=  B[i] + '*(1+' + sym_exvars[i] + ') + ' + st.bounds[i]['lb'] + '-1, ' + st.bounds[i]['ub']
                tile_part +=  ' && ' + sym_exvars[i] + ' >= 0 && '
            if (st.bounds[i]['step'] == '-1'):
                tile_part += st.bounds[i]['lb'] + ' - ' + B[i] + '*' + sym_exvars[i] + ' >= ' + vars[i] + ' >= -'
                tile_part += B[i] + '*(1+' + sym_exvars[i] + ') + ' + st.bounds[i]['lb'] + '+1, ' + st.bounds[i]['ub']
                tile_part += ' && ' + sym_exvars[i] + ' >= 0 && '

            TILE += tile_part
        else:
            TILE +=  sym_exvars[i] + ' = 0 && ' + vars[i] + ' = 0 && '

    TILE += ' 1=1 }'

    #print TILE


    return TILE

############################################################

def MakeCustomLex(sym_exvars, sym_exvars_p, direct, size, eq):

    if size == 0:
        return ''

    constr = ' ( '
    part = ''
    comparator = ' > '   # LT

    if(direct == 'GT'):
        comparator = ' < '    # GT

    for i in range(0, size):
        part += '('
        for j in range(0, i):
            part += sym_exvars[j] + ' = ' + sym_exvars_p[j] + ' && '
        part += sym_exvars[i] + comparator + sym_exvars_p[i] + ' ) or '

    if(eq):
        part += ' ('
        for i in range(0, size):
            part += sym_exvars[i] + ' = ' + sym_exvars_p[i] + ' && '
        part = part[:-4] + ') '
    else:
        part = part[:-3]  # delete last or

    constr += part + ') && '
    return constr
############################################################

def fix_scat(arr, l):
    arr = arr[:l]
    arr = arr + ['0']*(l - len(arr))
    return arr

############################################################

def ReplaceB(tile, BLOCK):
    for i in range(0,10):
        tile = tile.replace('b' + str(i), BLOCK[i])
    return tile

def CompareScat(arr1, arr2, deep):
    l = len(arr1)
    if(len(arr2) < l):
        l = len(arr2)
    if (l > deep):
        l = deep
    for i in range(0,l):
        if(arr1[i] != arr2[i]):
            return i
    return l

def DebugPrint(label, arr, sts):
    print(colored(label, 'green'))
    for i in range(0, len(sts)):
        print(colored(str(sts[i].petit_line) + ':\t', 'yellow') + str(arr[i]))

############################################################

def tile(plik, block, permute, output_file="", L="0", SIMPLIFY="False", perfect_mode = False, parallel_option = False, rplus_mode = '', cpus=2):

    print('')
    print(colored(r'/\__  _\ /\  == \   /\  __ \   /\  ___\   /\  __ \   ', 'green'))
    print(colored(r'\/_/\ \/ \ \  __<   \ \  __ \  \ \ \____  \ \ \/\ \  ', 'green'))
    print(colored(r'   \ \_\  \ \_\ \_\  \ \_\ \_\  \ \_____\  \ \_____\ ', 'green'))
    print(colored(r'    \/_/   \/_/ /_/   \/_/\/_/   \/_____/   \/_____/ ', 'green'))
    print('')
    print('      An Automatic Parallelizer and Optimizer')
    print('based on the '+colored('TRA','green')+'nsitive '+colored('C', 'green')+'l'+colored('O', 'green')+'sure of dependence graphs')
    print('             traco.sourceforge.net               ')
    print('')

    DEBUG = True
    AGGRESSIVE_SIMPLIFY = False # TODO simpl_ub
    VALIDATION = 0    # levels

    FSSCHEDULE = 1 # RTILE expermiental
    INVERSE_TILING = 0




    LPetit = "tmp/tmp_petit"+L+".t"

    BLOCK = block.split(',')

    for i in range(len(BLOCK),10):
        BLOCK.append(BLOCK[len(BLOCK)-1])

    BLOCK2 = [0,6,6]
    # BLOCK2 = BLOCK


    linestring = open(plik, 'r').read()
    lines = linestring.split('\n')


    if AGGRESSIVE_SIMPLIFY:
        petit_loop = convert_loop.convert_loop(lines, BLOCK2)
        BLOCK2 = list(map(str, BLOCK2))
    else:
        petit_loop = convert_loop.convert_loop(lines)



    file = open(LPetit, 'w')

    imperf = 0
    endloop = 0
    startloop = 0
    for line in petit_loop:
        #sprawdz przy okazji jaka petla idealnie czy nie
        if 'for' in line and not 'endfor' in line:
            if startloop == 2:
                imperf = 1
            startloop = 1
        else:
            if startloop == 1:
                startloop = 2
        if 'endfor' in line:
            endloop = 1
        if endloop == 1 and 'endfor' not in line and not line.isspace() and line != '':
            imperf = 1

        file.write(line + '\n')

    file.close()


    start = time.time()
    loop = Dependence.Kernel_Loop(LPetit)

    loop.Load_Deps()
    loop.Load_instrukcje()
    loop.Preprocess('0')
    loop.Get_Arrays()
    end = time.time()
    elapsed = end - start


    print("Dependence analysis: time taken: ", elapsed, "seconds.")

    print(colored('R', 'green'))
    print(loop.isl_rel)



    print(colored('domain R', 'green'))
    print(loop.isl_rel.domain())
    print(colored('range R', 'green'))
    print(loop.isl_rel.range())

    IS = loop.isl_rel.domain().union(loop.isl_rel.range())
    #s = IS.compute_schedule(loop.isl_rel, loop.isl_rel)

    #print s
    #sys.exit(0)



    print(loop.dane)


    cl = clanpy.ClanPy()
    cl.loop_path = plik
    cl.Load()

    ##################################
    # move to clanpy
    # combine clan with Dependence
    arr = list(map(int, loop.dane))
    arr = sorted(list(set(arr)))
    i=0


    for i in range(0, len(cl.statements)):
        cl.statements[i].petit_line = arr[i]
        cl.statements[i].bounds = GetBounds(petit_loop, cl.statements[i].petit_line, BLOCK2, AGGRESSIVE_SIMPLIFY)
        i=i+1


    ############################################################

    ### R^+

    isl_rel = loop.isl_rel

    #for i in range(0, len(cl.statements)):
    #    print cl.statements[i].petit_line



    start = time.time()

    # **************************************************************************

    RPLUSUNION = True
    #RPLUSUNION = False # NESTED strong experimental with Pugh only Valid why?

    exact_rplus = '-1'
    isl_relclosure = isl_rel


    if(RPLUSUNION):

        islrp = True

        if(rplus_mode == 'iterate'):
            islrp = False

        exact_rplus = True

        if not isl_rel.is_empty() and rplus_mode != 'remote':
            if islrp:
                isl_relclosure = isl_rel.transitive_closure()
                exact_rplus = isl_relclosure[1]
                isl_relclosure = isl_relclosure[0]
            else:
                isl_relclosure = relation_util.oc_IterateClosure(isl_rel)
                exact_rplus = True



    else: #R_UNDER still experimental, requires testing
    #############################################################################
        print(colored('R_UNDER', 'green'))
        stline = []
        subgraphs = []

        isl_relclosure = isl.Map('{[i]->[i] : 1=0}').coalesce()

        for st in cl.statements:
            stline.append(st.petit_line)

        stline.sort()

        for i in range(0, len(stline)):
            w = 0
            for sg in subgraphs:
                if stline[i] in sg:  # it was used
                    w = 1
            if(w==1):
                continue

            mylist = []
            mylist.append(stline[i])
            for j in range(i+1, len(stline)):
                cutrel  = '{[' + ','.join(["a%d" % l for l in range(0, loop.maxl)]) + ',' + str(stline[i]) + ']->[' + ','.join(["b%d" % l for l in range(0, loop.maxl)]) + ',' + str(stline[j]) + '];'
                cutrel += '[' + ','.join(["a%d" % l for l in range(0, loop.maxl)]) + ',' + str(stline[j]) + ']->[' + ','.join(["b%d" % l for l in range(0, loop.maxl)]) + ',' + str(stline[i]) + ']}'
                cutrel = isl.Map(cutrel)
                cutrel = isl_rel.intersect(cutrel).coalesce()
                if not cutrel.is_empty():
                    mylist.append(stline[j])
            #mylist.append(maxst)
            subgraphs.append(mylist)

        print(subgraphs)

        for item in stline:
            count = 0
            for sg in subgraphs:
                if item in sg:
                    count = count + 1
            if count >1 and item != max(stline):
                print('R_UNDER untested, switch RPLUSUNION to true')
                #exit(1)


        ii = 0
        for sg in subgraphs:  # calculate R_UNDER and its R+
            ii = ii+1
            print(str(ii) + "/" + str(len(subgraphs)))
            grel = '{'
            for i in sg:
                for j in sg:
                    grel += '[' + ','.join(["a%d" % l for l in range(0, loop.maxl)]) + ',' + str(i) + ']->[' + ','.join(["b%d" % l for l in range(0, loop.maxl)]) + ',' + str(j) + '];'
            grel += '}'
            grel = isl.Map(grel)
            grel = isl_rel.intersect(grel).coalesce()

            gp = grel.transitive_closure()
            if not gp[1]:
                print("NOT EXEACT R+")
            #    print "iterate required"
            #    gp = relation_util.oc_IterateClosure(grel)  # iterate

            #else:
            gp = gp[0]

            if isl_relclosure.is_empty():
                isl_relclosure = gp
            else:
                isl_relclosure = isl_relclosure.union(gp).coalesce()
    #############################################################################


    if rplus_mode == 'remote':
        isl_relclosure, exact_rplus = agent.remote_tc(isl_rel)

    # **************************************************************************

    isl_relplus = isl_relclosure


    print('Rplus before')
    print(isl_relplus)

    # lata Pugh - eksperymentalnie
    #isl_rel = isl_rel.subtract(isl_relplus.apply_range(isl_rel))

    print(isl_rel)
    #isl_relclosure = isl_rel.transitive_closure()[0]
    #isl_relplus = isl_relclosure
    # ---------

    print('Rplus after')
    print(isl_relplus)

    end = time.time()
    elapsed = end - start
    print("Transitive closure: time taken: ", elapsed, "seconds.")

    isl_ident = isl_rel
    if not isl_rel.is_empty:
        isl_ident = isl_rel.identity(isl_rel.get_space())

    if (DEBUG and 1==0):
        print('R+')
        print(isl_relclosure)

    #isl_relclosure = rpp
    if (DEBUG):
        color = 'red'
        if(exact_rplus):
            color = 'yellow'
        print(colored("!! exact_rplus " + str(exact_rplus), color))


    isl_relclosure = isl_relclosure.union(isl_ident).coalesce()  # R* = R+ u I




    if(INVERSE_TILING):
        isl_relclosure = isl_relclosure.fixed_power_val(-1).coalesce()

    if (DEBUG):
        print(colored("R*", 'green'))
        print(isl_relclosure)




    # **************************************************************************
    start = time.time()

    B = (["b%d" % i for i in range(0,loop.maxl)])



    vars = []
    for st in cl.statements:
        if (len(st.original_iterators) == loop.maxl):
            vars = st.original_iterators
            break

    if(len(vars)==0):
        print('error 12, propably clan does not work')
        exit(12)

    # TODO to make abstract variubles bounds with variables must be also corrected

    sym_exvars = []
    sym_exvars_p = []
    print(vars)
    for v in vars:
        sym_exvars.append(v*2)
        sym_exvars_p.append(v * 2 + 'p')

    if (DEBUG and 1==0):
        print(sym_exvars)
        print(vars)

    isl_symb = isl_rel.get_var_names(isl.dim_type.param)

    BLOCK = block.split(',')

    for i in range(len(BLOCK),10):
        BLOCK.append(BLOCK[len(BLOCK)-1])

    # **************************************************************************

    TILE = []       #isl
    TILE_STR = []   #string

    for st in cl.statements:
        if len(isl_symb) == 0:
            isl_symb = isl.Map(st.domain_map).get_var_names(isl.dim_type.param)
        tile =  MakeTile(st, vars, sym_exvars, isl_symb, B)
        tile = ReplaceB(tile, BLOCK)
        TILE_STR.append(tile)
        tile = isl.Set(tile)

        # if statements before st
        domainv = isl.Set(st.domain_map)
        print(domainv)

        #if len(TILE) == 0:
        #    domainv = isl.Set('[N] -> {[i, j, k, m]: N > 0 and 0 <= i <= -2 + N and 2 + i <= j < N and i < k <= -2 + j and k < m <= -3 - i + j + k and m < j and k < m and j-m < 30}')

        dimdom = domainv.dim(isl.dim_type.set)
        domainv = domainv.insert_dims(isl.dim_type.set, dimdom, loop.maxl+1 - dimdom)


        tile = tile.intersect(domainv).coalesce()

        TILE.append(tile)



    if (DEBUG):
        DebugPrint('TILE', TILE, cl.statements)



    # **************************************************************************

    TILE_LT = []
    TILE_GT = []


    for i in range(0, len(cl.statements)):
        TILE_LT_I = ''
        TILE_GT_I = ''
        for j in range(0, len(cl.statements)):

            l = CompareScat(cl.statements[i].scatering, cl.statements[j].scatering, len(vars))

            tile_j = TILE_STR[j]

            PARTS = tile_j.split(':')
            for k in range(0, len(sym_exvars)):
                PARTS[1] = PARTS[1].replace(sym_exvars[k], sym_exvars_p[k])

            PARTS[1] = PARTS[1].replace('}', ')}')


            lex_s_lt = MakeCustomLex(sym_exvars, sym_exvars_p, 'LT', l, cl.statements[i].petit_line > cl.statements[j].petit_line)
            lex_s_gt = MakeCustomLex(sym_exvars, sym_exvars_p, 'GT', l, cl.statements[i].petit_line < cl.statements[j].petit_line)


            join_LT = ':  exists  ' + ','.join(sym_exvars_p) + ' : ( ' + lex_s_lt
            join_GT = ':  exists  ' + ','.join(sym_exvars_p) + ' : ( ' + lex_s_gt

            TILE_LT_IJ = PARTS[0] + join_LT +  PARTS[1]
            TILE_GT_IJ = PARTS[0] + join_GT +  PARTS[1]


            #print TILE_LT_IJ
            TILE_LT_IJ = isl.Set(TILE_LT_IJ)
            TILE_GT_IJ = isl.Set(TILE_GT_IJ)

            if(j==0):
                TILE_LT_I = TILE_LT_IJ
                TILE_GT_I = TILE_GT_IJ
            else:
                TILE_LT_I = TILE_LT_I.union(TILE_LT_IJ).coalesce()
                TILE_GT_I = TILE_GT_I.union(TILE_GT_IJ).coalesce()



        TILE_LT.append(TILE_LT_I)
        TILE_GT.append(TILE_GT_I)

    if(DEBUG):
        DebugPrint('TILE_LT', TILE_LT, cl.statements)
        DebugPrint('TILE_GT', TILE_GT, cl.statements)



    if (INVERSE_TILING):
        tmpx = TILE_LT[:]
        TILE_LT = TILE_GT
        TILE_GT = tmpx


# **************************************************************************

    TILE_ITR = []

    for i in range(0, len(cl.statements)):
        if not isl_relclosure.is_empty():
            TILE_ITRI = TILE[i].subtract(TILE_GT[i].apply(isl_relclosure)).coalesce()
        else:
            TILE_ITRI = TILE[i]
        if(SIMPLIFY):
            TILE_ITRI = imperf_tile.SimplifySlice(TILE_ITRI)
        TILE_ITR.append(TILE_ITRI)

        #print 'R+(TILE_GT)*TILE[i]'
        #print i
      #  print TILE_GT[i].apply(isl_relclosure).intersect(TILE[i])

    if(DEBUG):
        DebugPrint('TILE_ITR', TILE_ITR, cl.statements)



# **************************************************************************

    TVLD_LT = []

    if not isl_relclosure.is_empty():
        for i in range(0, len(cl.statements)):
            TVLD_LTI = (TILE_LT[i].intersect(TILE_ITR[i].apply(isl_relclosure))).subtract(TILE_GT[i].apply(isl_relclosure)).coalesce()
            TVLD_LT.append(TVLD_LTI)

        if(DEBUG):
            DebugPrint('TVLD_LT', TVLD_LT, cl.statements)



# **************************************************************************

    TILE_VLD = []

    for i in range(0, len(cl.statements)):
        if not isl_relclosure.is_empty():
            TILE_VLDI = TVLD_LT[i].union(TILE_ITR[i]).coalesce()
        else:
            TILE_VLDI = TILE_ITR[i]
        if(SIMPLIFY):
            TILE_VLDI = imperf_tile.SimplifySlice(TILE_VLDI)
        TILE_VLD.append(TILE_VLDI)

    if (DEBUG):
        DebugPrint('TILE_VLD', TILE_VLD, cl.statements)



# **************************************************************************

    TILE_VLD_EXT = []

    Rapply = tiling_v3.GetRapply(vars, sym_exvars, ','.join(isl_symb + sym_exvars) + ',')

    for i in range(0, len(cl.statements)):
        TILE_VLD_EXTI = tiling_v3.Project(TILE_VLD[i].apply(Rapply).coalesce(), sym_exvars)

#####################################################################################################################
        if AGGRESSIVE_SIMPLIFY:

            cor_set = ''
            if (len(isl_symb) > 0):
                cor_set = '[' + ','.join(isl_symb) + '] -> '
            else:
                cor_set = ''

            cor_set = cor_set + '{[' + ','.join(sym_exvars) + ',' + ','.join(vars) + ',' + 'v] : '

            for k in range(0,i+1):
                for j in range(0, len(cl.statements[k].bounds)):
                    compar = ' <= '
                    add1 = ' - '
                    add2 = ' + '
                    if cl.statements[k].bounds[j]['step'] == '-1':
                        add1 = ' + '
                        add2 = ' - '
                        compar = ' >= '
                    cor_set = cor_set + vars[j] + compar + cl.statements[k].bounds[j]['ub'] + add1 + BLOCK2[j] + " && "
                    cor_set = cor_set + cl.statements[k].bounds[j]['lb'] + add2 + BLOCK2[j] +  compar +  vars[j] +  " && "

                cor_set = cor_set + "("
                cor_set = cor_set + " v = " + str(cl.statements[i].petit_line) + " "
                cor_set = cor_set + ")}"

                print(cor_set)

                cor_set = isl.Set(cor_set)

                print('**************************')

                TILE_VLD_EXTI = TILE_VLD_EXTI.intersect(cor_set)
#####################################################################################################################



        TILE_VLD_EXT.append(TILE_VLD_EXTI)


    if (DEBUG):
        DebugPrint('TILE_VLD_EXT', TILE_VLD_EXT, cl.statements)

# **************************************************************************

# TIME TO SCATTER - TO HONOUR ORDER OF STATEMENTS IN IMPERFECTLY NESTED LOOPS

    RMaps = []

    for i in range(0, len(cl.statements)):
        RMap = '{'
        lbx = 0
        ubx = i+1

        if (INVERSE_TILING):
            lbx = i
            ubx =  len(cl.statements)

        for j in range(lbx, ubx): # to przy odwrotnym tilngu moze trzeba poprawic
            RMap =  RMap +  '[' + ','.join(sym_exvars + vars) + ',' + str(cl.statements[j].petit_line) + '] -> ['

            scati = fix_scat(cl.statements[i].scatering, loop.maxl)
            scatj = fix_scat(cl.statements[j].scatering, loop.maxl)

            combo = [x for t in zip(scati + scatj, sym_exvars + vars) for x in t]  # obled

            RMap = RMap + ','.join(combo) + ',' + str(cl.statements[j].petit_line) + ']; '
            # normalize  j

        RMap = RMap[:-2] + '}'
        Rmap = isl.Map(RMap)
        RMaps.append(Rmap)

    if (DEBUG):
        DebugPrint('RMaps', RMaps, cl.statements)


    # **************************************************************************

    for i in range(0, len(cl.statements)):
        TILE_VLD_EXT[i] = TILE_VLD_EXT[i].apply(RMaps[i]).coalesce()

    if (DEBUG):
        DebugPrint('TILE_VLD_EXT after Map', TILE_VLD_EXT, cl.statements)


    TILE_VLD_EXT_union = TILE_VLD_EXT[0]

    for i in range(1, len(cl.statements)):
        TILE_VLD_EXT_union = TILE_VLD_EXT_union.union(TILE_VLD_EXT[i]).coalesce()



    if (DEBUG):
        print(colored('TILE_VLD_EXT to CodeGen', 'green'))
        print(TILE_VLD_EXT_union)

    #if(SIMPLIFY):
    #TILE_VLD_EXT_union= imperf_tile.SimplifySlice(TILE_VLD_EXT_union)

# **************************************************************************

    # Optional Schedule

    s = ','.join(["i%d" % i for i in range(1, loop.maxl*4+2)])
    # RFS
    ss = s

    in_ = s.split(',')

    symb = ''
    if(len(isl_symb) > 0):
        symb += '['+ ','.join(isl_symb) + ']' + '->'

    RSched = symb + '{[' + s + '] -> ['

    RValid = RSched
    # RFS
    RFS = RSched

    # *****************************************************  LOOP SKEWING
    print(colored('Loop skewing testing...', 'green'))

    sdel = isl_rel.deltas()

    inp = []
    for i in range(0, sdel.dim(isl.dim_type.set)):
        inp.append("i" + str(i))

    stest = "{[" + ",".join(inp) + "] : " + inp[1] + " < 0 }"
    stest = isl.Set(stest)
    sdel = stest.intersect(sdel).coalesce()

    if(sdel.is_empty()):
        print(colored('Found:  i2 -> i2 + i4', 'yellow'))
        #s = s.replace('i2', 'i2 + i4')
        s = re.sub(r'\bi2\b', 'i2+i4', s)
    else:
        print(colored('Failed.', 'yellow'))

    #s = s.replace('i4', 'i6')
    #s = s.replace('i2', 'i2 + 2*i4')
    #s = s.replace('i', 'i8')
    #s = s.replace('i10', 'i10 + i8')
    #s = s.replace('i6', '2*i2 + i4 + i6')

    # *****************************************************  LOOP SKEWING


    # *****************************************************  DECREMENTATION
    index_arr = numpy.zeros(shape=(len(cl.statements),loop.maxl))
    for k in range(0,loop.maxl):
        for i in range(0, len(cl.statements)):
            if(k < len(cl.statements[i].bounds)):
                index_arr[i][k] = cl.statements[i].bounds[k]['step']

    print(colored('step array (st,loop)','green'))
    print(numpy.matrix(index_arr))

    for k in range(0, loop.maxl):
        vec = index_arr[:,k]
        dec = 1
        for i in range(0, len(cl.statements)):
            if(vec[i] != -1):
                dec = 0
                break
        if(dec==0):
            continue
        ind = str(2*loop.maxl+2*(k+1))
        print(colored('decrementation on ' + str(k+1) + ' loop', 'yellow'))
        s = s.replace('i'+ind, '-i'+ind)   # TODO rozdzielic na gniazda i v w przyszlosci
    # *****************************************************

    RSched += s + '] : '


    RFS += ss + '] : 1=1 }'

    RSched = RSched + copyconstr.GetConstrSet(in_, TILE_VLD_EXT_union) + "  }"

    print('RSCHEDULE')


    print(RSched)





    Rsched = isl.Map(RSched)


    print('VALIDATION CHECKING ')
    if(not isl_rel.is_empty() and 1==1):
        s_in = ','.join(["i%d" % i for i in range(1, loop.maxl * 4 + 2)])
        sout = ','.join(["i%d'" % i for i in range(1, loop.maxl * 4 + 2)])
        out_ = sout.split(',')

        i1 = in_[2*loop.maxl+1:4*loop.maxl+1:2] + [in_[loop.maxl * 4 ]]
        i2 = out_[2 * loop.maxl + 1:4 * loop.maxl + 1:2] + [in_[loop.maxl * 4]]

        RValid += sout + '] : '

        DomR = isl_rel.domain()

        RValid += copyconstr.GetConstrSet(i1, DomR) + ' && ' + copyconstr.GetConstr(i1, i2, isl_rel)


        s_in_ex = ','.join(["ex%d" % i for i in range(1, loop.maxl * 4 + 2)])
        s_out_ex = ','.join(["ex%d'" % i for i in range(1, loop.maxl * 4 + 2)])
        ex_sin = s_in_ex.split(',')
        ex_sout = s_out_ex.split(',')

        RValid += ' && exists ' + s_in_ex + ',' + s_out_ex +  ' : ('

        RValid += ' ( ' + tiling_v3.CreateLex(ex_sin, ex_sout) + ' ) && '

        RValid += ' ( ' + copyconstr.GetConstr(in_, ex_sin, Rsched) + ' ) && '
        RValid += ' ( ' + copyconstr.GetConstr(out_, ex_sout, Rsched) + ' ) '

        RValid += ' ) }'


        RValid = isl.Map(RValid).coalesce()




        if(RValid.is_empty()):
            print(colored('*** VALIDATION OK ***', 'green'))
        else:
            print(colored('*** VALIDADION FAILED ***', 'red'))
            print(colored(RValid, 'green'))
            if(FSSCHEDULE == 0):
                print(RValid)
                sys.exit(0)


        for st in cl.statements:
            z = st.domain_map

        z = isl.Set(z)

        # czy wszystkie z domain sa w TVLD_EXT    VLDUNION RELATION == v

        # I nalezy do TVLD_EXT and exists i,j,v i  nalezy do domain_map i   i,j,v != I ma byc pusty
        VLD_VAL = Rsched.range()


        if(VALIDATION > 0):
            tiling5_valid.Valid1(Rsched, symb, in_, out_, s_in, sout, loop)
    else:
        print("OK")



# **************************************************************************
    #### DISCOVER PARALLELISM -- empty

    # ii, jj -> ii, jj' : not  jj = jj'
    print(colored('Parallelism searching', 'green'))

    s = ','.join(["i%d" % i for i in range(1, loop.maxl*4+2)])
    in_ = s.split(',')
    sprim = ','.join(["i%d'" % i for i in range(1, loop.maxl*4+2)])
    out_ = sprim.split(',')

    Rel_base = symb + '{[' + s + '] -> [' + sprim + '] :   '

#i1 = domain R 12 = R(i1)   ii,i1 nalezy do VLD_EXT i'i',i2 nalezy do VLDEXT i ogr. ponizej np  ii2 <> ii2' ii1 = ii1' relacja


    par_loop = []

    if (not isl_rel.is_empty() and 1==1):
        delta = isl_rel.deltas()
        chkc = isl.Set("{[0," + ",".join(vars) + "]}")
        delta = delta.subtract(chkc)


        for i in range(0,loop.maxl*4,2):
            j = -1
            print('c' + str(i+1), end=' ')
            Rel = Rel_base
            tmp = ''
            for j in range(0,i):
                tmp += in_[j] + ' = ' + out_[j] + ' && '

            tmp += ' not ( ' +  in_[j+1] + ' = ' + out_[j+1] + '  && ' + in_[j+2] + ' = ' + out_[j+2] + ' )  && '

            Rel += tmp
            Rel += copyconstr.GetConstrSet(i1, DomR) + ' && ' + copyconstr.GetConstr(i1, i2, isl_rel)

            Rel += ' && ( ' + copyconstr.GetConstrSet(in_, VLD_VAL) + ' ) && '
            Rel += ' ( ' + copyconstr.GetConstrSet(out_, VLD_VAL) + ' )  '

            Rel += ' }'
            #print Rel

            Rel = isl.Map(Rel)


            if(i==0):
                Rel = delta

            if(Rel.is_empty()):
                print(colored('found!', 'green'))
                par_loop.append('c' + str(i+1))
#                break
            else:
                print('no!')




    end = time.time()
    elapsed = end - start
    print("Algorithm: time taken: ", elapsed, "seconds.")

# **************************************************************************


    vars = list(map(str, vars))

    start = time.time()
    ast = 0
    if (ast == 1):
        loop_x = iscc.isl_ast_codegen_map(Rsched)
    else:
        loop_x = iscc.iscc_communicate("L :=" + str(Rsched) + "; codegen L;")

    loop_x = loop_x.decode('utf-8')
    print(loop_x)


    # **************************************************************************
    lines = loop_x.split('\n')

    loop_str = []


    for line in lines:
        if line.endswith(');'):
            tab = imperf_tile.get_tab(line)
            line = line.replace(' ', '')
            line = line[:-2]
            line = line[1:]

            arr = line.split(',')

            petit_st = arr[4*loop.maxl]

            s = ''

            for i in range(0,len(cl.statements)):

                # TODO if petit_st has 'c' get all statements make if from petit_line and insert to s, solution for loop over st
                if 'c' in petit_st:
                    combo_st = '{'
                    for j in range(0, len(cl.statements)):
                        combo_st += '\n' + tab
                        combo_st += 'if( ' + petit_st + ' == ' + str(cl.statements[j].petit_line) + ' ) ' + cl.statements[j].body
                    s = combo_st + '\n' + tab+ '}'
                elif cl.statements[i].petit_line == int(petit_st):   # st.petit_line
                    s = cl.statements[i].body




            for i in range(0, len(vars)):        # todo oryginal iterators for loops with mixed indexes
                subt = arr[2 * loop.maxl + 2 * i + 1]
                if (('+' in subt) or ('-' in subt)):
                    subt = '(' + subt + ')'
                s = re.sub(r'\b'+vars[i]+r'\b', subt, s)



            loop_str.append(tab + s)

        else:
            line = line.replace('for (int', 'for(')
            loop_str.append(line)


    end = time.time()
    elapsed = end - start
    print("Code Generation: time taken: ", elapsed, "seconds.\n\n")

    #loop_str = '\n'.join(loop_str)
    filePaths = glob.glob(plik)
    if(output_file != ""):
        nazwa = output_file
    else:
        for filePath in filePaths:
            base = os.path.basename(filePath)
            nazwa = os.path.splitext(base)[0] + "_tiling" + os.path.splitext(base)[1]

    text_file = open(nazwa, "w")

    for line in loop_str:
        if(len(par_loop) > 0):
            if('for( ' + par_loop[0] + ' ' in line):
                print(imperf_tile.get_tab(line) + colored('#pragma omp parallel for', 'green'))
                text_file.write(imperf_tile.get_tab(line) + '#pragma omp parallel for' + '\n')
        print(line)
        text_file.write(line + '\n')


    text_file.close()
    print('Output written to: ' + nazwa)

    for d in loop.Deps:
        del d.Relation

    sys.exit(0);

###################################################################################################

    if (FSSCHEDULE):

        rtile = tiling_schedule.get_RTILE(TILE_VLD_EXT_union, sym_exvars, isl_rel, True)  #Rsched.Range()

        rtile_ii = rtile

        #print rtile_ii


        for i in range(0, loop.maxl):
            rtile_ii = rtile_ii.remove_dims(isl.dim_type.in_, 2*loop.maxl-i*2-2, 1)
            rtile_ii = rtile_ii.remove_dims(isl.dim_type.out, 2*loop.maxl-i*2-2, 1)



        print(colored('RTILE', 'green'))



        print(rtile)

        sys.exit(0)

        if islrp:
            rtileplus, exact = rtile.transitive_closure()
        else:
            rtileplus = relation_util.oc_IterateClosure(rtile)
            exact = 1

        print(colored('RTILE+', 'green'))
        print(rtileplus)
        if(exact != 1):
            print(colored('RTILE+ approx', 'yellow'))
        else:
            print(colored('RTILE+ exact', 'green'))


    #    tiling_v2.DynamicRTILE(rtile, Rsched.range(), loop.maxl, cl, vars, RFS)





        try:
            p = int(cpus) # or int
        except ValueError:
            print('Bad cpus parameter. ')
            sys.exit(0)

        FI = symb + ' {[' + ','.join(sym_exvars) + ',v] ->  [p] : (exists k : ('


        item = ''
        for i in range(0,p):
            item = item + ' (p='+str(i)+' ' + ' && ' + sym_exvars[0] + ' - (2k + ' + str(i) + ') = 0 ) || '

        FI += item[:-3] + '  )) &&'




        vv = ["i%d" % i for i in range(1, loop.maxl * 4 + 2)]
        s_in = ','.join(vv)
        s_out = ','.join(["i%d" % i for i in range(2, loop.maxl*2+1,2)])  + ',' + vv[len(vv)-1]
        rmap_fi = '{[' + s_in + '] -> [' + s_out + ']}'
        rmap_fi = isl.Map(rmap_fi)

        II_SET = TILE_VLD_EXT_union.apply(rmap_fi).coalesce()

        print(colored('II_SET', 'green'))
        print(II_SET)


        FI += copyconstr.GetConstrSet(sym_exvars + ['v'], II_SET) + '}'

        FI = isl.Map(FI).coalesce()

        print(colored('FI', 'green'))
        print(FI)

        RPROC = symb + '{[' + ','.join(sym_exvars) + ',v] -> [' + ','.join(sym_exvars_p) + ',vp] : '


        domRTILE = rtile_ii.domain().coalesce()

        RPROC += copyconstr.GetConstrSet(sym_exvars + ['v'], domRTILE) + ' && ' + copyconstr.GetConstr(sym_exvars + ['v'], sym_exvars_p + ['vp'], rtile_ii)

        RPROC += ' && exists p,pp : ( not(p=pp) && ' + copyconstr.GetConstr(sym_exvars + ['v'], ['p'], FI) + ' && ' + copyconstr.GetConstr(sym_exvars_p + ['vp'], ['pp'], FI) +' ) }'

        #print RPROC
        RPROC = isl.Map(RPROC).coalesce()

        print(colored('RPROC', 'green'))
        print(RPROC)

        s = ','.join(["i%d" % i for i in range(0, loop.maxl + 1)])
        sv = s.split(',')
        s1 = ','.join(["o%d" % i for i in range(0, loop.maxl + 1)])
        sv1 = s1.split(',')
        s2 = ','.join(["ex%d" % i for i in range(0, loop.maxl + 1)])
        sve = s2.split(',')
        R_RESIDUAL = symb + '{[' + s + '] -> [' + s1 + '] : '
        R_RESIDUAL += copyconstr.GetConstrSet(sv, RPROC.domain().coalesce()) + '&& '
        R_RESIDUAL += copyconstr.GetConstr(sv, sv1, RPROC) + '&&  not exists ' + s2 + ' : ('
        R_RESIDUAL += tiling_v3.CreateLex(sve, sv) + ' && ' + copyconstr.GetConstr(sve, sv1, RPROC) + ')}'

        R_RESIDUAL = isl.Map(R_RESIDUAL).coalesce()

        print(colored('R_RESIDUAL', 'green'))
        print(R_RESIDUAL)
        irp = R_RESIDUAL.fixed_power_val(-1)

        R_P_RESIDUAL = symb + '{[' + ','.join(sym_exvars) + ',v] -> [p,' + ','.join(sym_exvars_p) + ',vp] : '
        R_P_RESIDUAL +=  copyconstr.GetConstr(sym_exvars_p + ['vp'], ['p'], FI) + ' && ' + copyconstr.GetConstr(sym_exvars+ ['v'], sym_exvars_p+ ['vp'], irp) + ' }'


        R_P_RESIDUAL = isl.Map(R_P_RESIDUAL)
        print(colored('R_P_RESIDUAL', 'green'))
        print(R_P_RESIDUAL)


    ###################################################################################################
