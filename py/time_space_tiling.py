import os, glob
import re
import sys
import time
from termcolor import colored

import numpy


try:
    import islpy as isl
except ImportError as e:
    print(e)
    print("pip install ispy")
    sys.exit()


import convert_loop
import Dependence
import clanpy
import tiling_v3
import tiling_v5
import iscc
import sched_parser
import imperf_tile


def MakesSpaceConstr(st, vars, sym_exvars, symb, B, i):

    tile_part = ' && '

    if (st.bounds[i]['step'] == 1 or st.bounds[i]['step'] == '1'):
        tile_part += st.bounds[i]['lb'] + ' + ' + B[i] + '*' + sym_exvars[i] + ' <= ' + vars[i] + ' <= '
        tile_part += B[i] + '*(1+' + sym_exvars[i] + ') + ' + st.bounds[i]['lb'] + '-1, ' + st.bounds[i]['ub']
        tile_part += ' && ' + sym_exvars[i] + ' >= 0 } '
    if (st.bounds[i]['step'] == '-1'):
        tile_part += st.bounds[i]['lb'] + ' - ' + B[i] + '*' + sym_exvars[i] + ' >= ' + vars[i] + ' >= -'
        tile_part += B[i] + '*(1+' + sym_exvars[i] + ') + ' + st.bounds[i]['lb'] + '+1, ' + st.bounds[i]['ub']
        tile_part += ' && ' + sym_exvars[i] + ' >= 0 } '


    #tile_part +=  st.bounds[i]['lb'] + ' + ' + B[i] + '*' + sym_exvars[i] + ' <= ' + vars[i] + ' <= '
    #tile_part +=  B[i] + '*(1+' + sym_exvars[i] + ') + ' + st.bounds[i]['lb'] + '-1, ' + st.bounds[i]['ub']
    #tile_part +=  ' && ' + sym_exvars[i] + ' >= 0 }'
    return tile_part



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
    print('TIME SPACE TILING Module')




    LPetit = "tmp/tmp_petit"+L+".t"

    BLOCK = block.split(',')
    BLOCK2 = BLOCK

    for i in range(len(BLOCK),10):
        BLOCK.append(BLOCK[len(BLOCK)-1])


    linestring = open(plik, 'r').read()
    lines = linestring.split('\n')

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
    loop = Dependence.Kernel_Loop(LPetit,1)

    loop.Load_Deps()

    loop.Load_instrukcje()
    loop.PreprocessPet()
    loop.Get_Arrays()
    end = time.time()
    elapsed = end - start


    print("Dependence analysis: time taken: ", elapsed, "seconds.")

    print(colored('R', 'green'))
    print(loop.isl_rel)

    isl_symb = loop.Deps[0].Relation.get_var_names(isl.dim_type.param)

    symb_prefix = ''
    if len(isl_symb) > 0:
        symb_prefix = '[' + ','.join(isl_symb) + '] -> '

    cl = clanpy.ClanPy()
    cl.loop_path = plik
    cl.Load()


    arr = list(map(int, loop.dane))
    arr = sorted(list(set(arr)))
    for i in range(0, len(cl.statements)):
        cl.statements[i].petit_line = arr[i]
        cl.statements[i].bounds = tiling_v5.GetBounds(petit_loop, cl.statements[i].petit_line, BLOCK2, 0)
        print(cl.statements[i].scatering)



    for i in range(0, len(cl.statements)):
        cl.statements[i].domainpet = isl.Set(symb_prefix + ' { S'+ str(cl.statements[i].petit_line) +'[' + ','.join(cl.statements[i].original_iterators) +'] : ' + cl.statements[i].domain + '}')
        #print cl.statements[i].domainpet

    IS = isl.UnionSet(str( cl.statements[0].domainpet))
    for i in range(1, len( cl.statements)):
        IS = IS.union(cl.statements[i].domainpet)
        IS = IS.coalesce()

    print(colored('IS', 'green'))
    print(IS)


    #isl schedule
    text = 'R:= ' + str(loop.isl_rel) + '; IS := ' + str(IS) + '; schedule IS respecting R minimizing R;'

    print(colored('ISL output', 'green'))

    sched_dump = iscc.iscc_communicate(text)

    print(sched_dump)
    sched_dump = sched_dump.decode('utf-8')

    lines = sched_dump.split('\n')
    sched_maps = sched_parser.parse(lines, cl, symb_prefix)


    print(colored('ISL schedules', 'green'))

    for m in sched_maps:
        print(m)

    SCHED = isl.UnionMap(str(sched_maps[0]))
    for i in range(1, len(sched_maps)):
        SCHED = SCHED.union(sched_maps[i])
        SCHED = SCHED.coalesce()



    #SCHED = isl.UnionMap('[N] -> { S27[i, j] -> [-i + j, 2,j] : N > 0 and 0 <= i <= -2 + N and i < j < N; S20[i, j, k] -> [-i + j, 0,0,1,k] : N > 0 and 0 <= i <= -2 + N and 2 + i <= j < N and i < k < j; S23[i, j, k] -> [-i + j, 0,k,2, j] : N > 0 and 0 <= i <= -2 + N and 2 + i <= j < N and i < k <= -2 + j; S26[i, j] -> [-i + j, 1,j] : N > 0 and 0 <= i <= -2 + N and i < j < N; S16[i, j, k, m] -> [-i + j, 0,k, 0,m] : N > 0 and 0 <= i <= -2 + N and 2 + i <= j < N and i < k <= -2 + j and k < m <= -3 - i + j + k and m < j }')

    #SCHED = isl.UnionMap('[n, loop] -> { S12[l, i, k] -> [l,i,k] : n >= 2 and loop > 0 and 0 < l <= loop and 0 < i < n and 0 <= k < i }')


    print(colored('SCHED', 'green'))
    print(SCHED)

    #print colored('deltas R', 'green')

    # SPACE

    # wykryj liczbe na razie globalnie

    islR = Scatter(loop.isl_rel, cl, True)
    D = loop.isl_rel.deltas()
    spaces_num = sys.maxsize

    for i in range(0, len(cl.statements)):
        depth = len(cl.statements[i].original_iterators)
        nums = 0
        for j in range(0, depth):
            direct = ' < '
            print(cl.statements[i].bounds[j]['step'])  # decrementation
            if cl.statements[i].bounds[j]['step'] == '-1':
                direct = ' > '

            TEST = '{ S' + str(cl.statements[i].petit_line) + '[' + ','.join(
                cl.statements[i].original_iterators) + '] : ' + cl.statements[i].original_iterators[j] + direct + ' 0 }'
            print(TEST)
            TEST = isl.Set(TEST)

            TEST = D.intersect(TEST)
            if (TEST.is_empty()):
                nums = nums + 1
            else:
                break  # sa ujemne
        # print nums
        if (nums < spaces_num):
            spaces_num = nums

    print(colored('SPACES NUMBER', 'green'))
    print(spaces_num)

    if spaces_num == 0:
        print('No spaces or manually input calculated number')
        spaces_num = int(input())

    # vars

    vars = []
    sym_exvars = []

    for st in cl.statements:
        if (len(st.original_iterators) == loop.maxl):
            vars = st.original_iterators
            break

    for v in vars:
        sym_exvars.append(v * 2)

    ##################################

    SPACES = {}
    space = ''

    for st in cl.statements:
        tmpspaces = []
        for i in range(0, spaces_num):
            space = st.domainpet
            space = space.insert_dims(isl.dim_type.param, 0, 1)
            space = space.set_dim_name(isl.dim_type.param, 0, sym_exvars[i])
            space = str(space)
            space = space.replace('}', MakesSpaceConstr(st, vars, sym_exvars, isl_symb, BLOCK, i))
            print(space)
            space = isl.Set(space)

            tmpspaces.append(space)
            #print space

        SPACES["S" + str(st.petit_line)] = tmpspaces

    ##################################
    #experimental Rk

    if False:

        print("==============================================")

        spaceunion = None

        for s in SPACES:
            print(s)
            tmpspace = None
            for ss in SPACES[s]:
                if tmpspace is None:
                    tmpspace = isl.UnionSet(str(ss))
                else:
                    tmpspace = tmpspace.union(ss).coalesce()

            if spaceunion is  None:
                spaceunion = tmpspace
            else:
                spaceunion = spaceunion.union(tmpspace).coalesce()


        if(1==0):
            print("Experimental Rk")
            print("SPACE")
            print(spaceunion)

            print("new R")
            R = loop.isl_rel.from_domain_and_range(spaceunion, spaceunion).coalesce()
            print(R)


            #Rk = R.power()
            #print "Rk"
            print(Rk)

            print("==============================================")


    ###################################

    sched_maps_i = sched_maps  #SCHED_1 SCHED_2
    TIMES = []



    if(spaces_num < cl.maxdim):

        print(colored("SCHED_1:=SCHED^-1", 'green'))


        for i in range(0, len(sched_maps_i)):
            sched_maps_i[i] = sched_maps_i[i].fixed_power_val(-1).coalesce()

            print(sched_maps_i[i])

            #if i == 3:
            #    sched_maps_i[i] = isl.Map('[N] -> {[i0, 0] -> S20[i, j = i0 + i]: N > 0 and 0 <= i <= -2 + N and i0=1}')



            TIMES.append(sched_maps_i[i])

            tmp = ''

            if("i0" in str(TIMES[i])):


                TIMES[i] = TIMES[i].insert_dims(isl.dim_type.param, 0, 1)
                TIMES[i] = TIMES[i].set_dim_name(isl.dim_type.param, 0, 'c')
                TIMES[i] = TIMES[i].insert_dims(isl.dim_type.param, 0, 1)
                TIMES[i] = TIMES[i].set_dim_name(isl.dim_type.param, 0, 'i0')
                tmp = str(TIMES[i])


                if 'i1' in tmp:
                    v = 'i1'
                else:
                    v = 'i0'


                tmp = tmp.replace('}', " && "+str(BLOCK[spaces_num])+"c<="+v+"<="+str(BLOCK[spaces_num])+"*(c+1)-1 && i0=i0' }" )  # podmien na bloki

            else:
                tmp = str(TIMES[i])




            TIMES[i] = isl.Map(tmp).range()






        print(colored("TIMEi", 'green'))

        for s in TIMES:
            print(s)

        print(colored("TIME", 'green'))
    else:
        print(colored("TIME: all distance vectors elements are positive", 'green'))
        for i in range(0, len(sched_maps_i)):
            TIMES.append(sched_maps_i[i].subtract(sched_maps_i[i]).complement().domain().coalesce())



    ######################################### TIMES experimental code



    TIME = isl.UnionSet(str(TIMES[i]))
    for i in range(1, len(TIMES)):
        TIME = TIME.union(TIMES[i])
        TIME = TIME.coalesce()

    print(TIME)

    #########################################

    TILES = []

    for i in range(0, len(TIMES)):
        TILES.append(TIMES[i])
        for j in range(0, spaces_num):
            TILES[i] = TILES[i].intersect(SPACES['S' + str(cl.statements[i].petit_line)][j]).coalesce()


    TILE = isl.UnionSet(str(TILES[0]))
    for i in range(1, len(TILES)):
        TILE = TILE.union(TILES[i])
        TILE = TILE.coalesce()

    print(colored("TILE", 'green'))
    print(TILE)
    print("Making MAP %%%")

    ###########################################

    # MAKE MAP

    TILE = str(TILE).split('->')[1]

    # j=i-i0 crazy thing

    ####################################################   wstawia oryginalne iteratory, dodaje rownania i scattering
    strTILE = TILE.split(';')
    for st in cl.statements:
        s = 'S' + str(st.petit_line)
        for i in range(0, len(strTILE)):
            if s in strTILE[i]:
                res = re.findall(r'S\d+\[[^\]]+', strTILE[i])


                a = st.scatering
                b = st.original_iterators[:]

                for k in range(0, st.getDim()):
                    if st.bounds[k]['step'] == '-1':
                        b[k] = '-' + b[k]

                if(len(a)<cl.maxdim+1):
                    for k in range(len(a), cl.maxdim+1):  #wyrownaj zerami
                        a.append('0')

                if(len(b)<cl.maxdim):
                    for k in range(len(b), cl.maxdim):  #wyrownaj zerami
                        b.append('0')

                c = a + b         #scatter
                c[::2] = a
                c[1::2] = b




                strTILE[i] = strTILE[i].replace(res[0], s + '[' + ','.join(c))
                res = res[0].split('[')[1].replace(' ', '').split(',')
                for r in res:
                    if '=' in r:
                        strTILE[i] = strTILE[i].replace(':', ': ' + r + ' and ')
                break
            else:
                continue



    TILE = ';'.join(strTILE)
    print(TILE)


    #####################################################

    arr = []
    arr.append('t')
    timet = []
    if spaces_num == 0:
        timet.append('0')
    for i in range(0, spaces_num):
        arr.append(sym_exvars[i])
        timet.append(sym_exvars[i])
    arr.append('i0')
    arr.append('c,')
    arr = ','.join(arr)

    TILE = TILE.replace('[', '[' + arr)



    timet = ' t = ' + '+'.join(timet)

    if (spaces_num >= cl.maxdim):  # dodatnie wektory
        timet += ' and  c = 0 and i0 = 0 '


    TILE = symb_prefix + TILE.replace(':' , ':' + timet + ' and ')




    for st in cl.statements:
        s = 'S' + str(st.petit_line)
        TILE = TILE.replace(s, s + '[' + ','.join(st.original_iterators) + '] -> ')

    print(colored("MAP", 'green'))
    print(TILE)

    print('MAP in ISL')
    print(isl.UnionMap(TILE).coalesce())

    #loop_x = iscc.iscc_communicate("L :=" + str(TILE) + "; codegen L;")
    #print loop_x

    print(colored("ISL AST", 'green'))

    loop_x = iscc.isl_ast_codegen_map(isl.UnionMap(TILE))
    print(loop_x)

    # **************************************************************************
    lines = loop_x.split('\n')

    # *********** post processing ****************

    print(colored("POSTPROCESSING", 'green'))

    loop_str = []

    for line in lines:
        if line.endswith(');'):
            tab = imperf_tile.get_tab(line)
            line = line.replace(' ', '')
            line = line[:-2]
            line = line[1:]

            line = line.split('(')


            petit_st = line[0].replace('S', '')
            line = line[1]

            arr = line.split(',')

            s = ''

            for i in range(0, len(cl.statements)):

                # TODO if petit_st has 'c' get all statements make if from petit_line and insert to s, solution for loop over st
                if 'c' in petit_st:
                    combo_st = '{'
                    for j in range(0, len(cl.statements)):
                        combo_st += '\n' + tab
                        combo_st += 'if( ' + petit_st + ' == ' + str(cl.statements[j].petit_line) + ' ) ' + \
                                    cl.statements[j].body
                    s = combo_st + '\n' + tab + '}'
                elif cl.statements[i].petit_line == int(petit_st):  # st.petit_line
                    s = cl.statements[i].body

            for i in range(0, len(vars)):  # todo oryginal iterators for loops with mixed indexes

                if(i+1 > len(arr)):
                    continue

                subt = arr[i]
                if (('+' in subt) or ('-' in subt)):
                    subt = '(' + subt + ')'
                s = re.sub(r'\b' + vars[i] + r'\b', subt, s)

            loop_str.append(tab + s)

        else:
            line = line.replace('for (int', 'for(')
            loop_str.append(line)

    # *********** post processing end ****************

    lines_out = []
    if(1==1):
        for line in loop_str:
            if 'for( c1 ' in line and spaces_num < cl.maxdim:
                print(imperf_tile.get_tab(line) + colored('#pragma omp parallel for', 'green'))
                lines_out.append('#pragma omp parallel for\n')
            print(line)
            lines_out.append(line + '\n')

        filePaths = glob.glob(plik)
        if (output_file != ""):
            nazwa = output_file
        else:
            for filePath in filePaths:
                base = os.path.basename(filePath)
                nazwa = os.path.splitext(base)[0] + "_tiling" + os.path.splitext(base)[1]

        f = open(nazwa, 'w')
        f.writelines(lines_out)
        f.close()

    # VALIDITY

    # Lex_Neg2:=[N]->{ [i0, i1]: (i0=0 and i1=0 ) or i0<0  or i0=0 and i1<0 };


    # VALIDITY

    SCHED2 = Scatter(SCHED, cl, False)





    L = 2*cl.maxdim+1

    lexvar = ["i%d" % i for i in range(0, L)]

    lexneg = '{[' + ','.join(lexvar) + '] : ('

    for i in range(0, L):
        lexneg += lexvar[i] + '=0' + ' and '

    lexneg += '1=1) or '

    for i in range(0, L):
        lexneg += lexvar[i] + ' < 0 and '
        for j in range(0, i):
            lexneg += lexvar[j] + ' = 0 and '
        lexneg += ' 1 = 1 or '
    lexneg += ' 1 = 0 }'

    lexneg = isl.Set(lexneg)


    C =  (SCHED2.fixed_power_val(-1).apply_range(islR)).apply_range(SCHED2)

    P = C.deltas().intersect(lexneg).coalesce()

    if P.is_empty():
        print(colored('VALIDATION OK', 'green'))
    else:
        print(colored('VALIDATION FAILED !!', 'red'))

    print(colored('lexneg', 'yellow'))
    print(lexneg)
    print(colored('C = (SCHED^-1(R))(SCHED)', 'yellow'))
    print(C)
    print(colored ('P = C.deltas()', 'yellow'))
    print(C.deltas())
    print(colored('P*C', 'yellow'))
    print(P)

    for d in loop.Deps:
        del d.Relation

    print('Output sevad: ' + nazwa)



def Scatter(R, cl, StatementinRange):

    R = str(R)
    strR = R.split(';')
    for st in cl.statements:
        s = 'S' + str(st.petit_line)
        for i in range(0, len(strR)):
            if s in strR[i]:


                res = re.findall(r'S'+str(st.petit_line)+r'\[[^\]]+', strR[i])


                a = st.scatering


                w = res[0]
                w = w.replace(s, '')
                w = w.replace('[', '')
                w = w.replace(']', '')

                b = w.split(',')

                if (len(a) < cl.maxdim + 1):
                    for k in range(len(a), cl.maxdim + 1):  # wyrownaj zerami
                        a.append('0')

                if (len(b) < cl.maxdim):
                    for k in range(len(b), cl.maxdim):  # wyrownaj zerami
                        b.append('0')

                c = a + b  # scatter



                c[::2] = a
                c[1::2] = b

                strR[i] = strR[i].replace(res[0], s + '[' + ','.join(c))

                if(StatementinRange == False):
                    res = re.findall(r'-> \[[^\]]+', strR[i])

                    a = st.scatering

                    w = res[0]
                    w = w.replace('-> ', '')
                    w = w.replace('[', '')
                    w = w.replace(']', '')

                    b = w.split(',')

                    if (len(a) < cl.maxdim + 1):
                        for k in range(len(a), cl.maxdim + 1):  # wyrownaj zerami
                            a.append('0')

                    if (len(b) < cl.maxdim):
                        for k in range(len(b), cl.maxdim):  # wyrownaj zerami
                            b.append('0')

                    c = a + b  # scatter
                    c[::2] = a
                    c[1::2] = b

                    strR[i] = strR[i].replace(res[0], '-> [' + ','.join(c))


    newR = ';'.join(strR)


    return isl.UnionMap(newR)
