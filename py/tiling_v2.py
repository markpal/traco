# coding=utf-8
# S0 = RTILE
# I0 = domain(S0)
# for i = 0; ;i + + do <- Infinity loop
#
# if i = 0 then
#  J0 = range(S0)
#  FS0 = I0 − J0 <- Fair sources for s0
#  L0 = S0(FS0)
#  else
#  L0 = S0(Lay0)
#  J0 = J0 − Lay0
# end if
#
# D0 = S0(J0)
# Lay0 = L0 − D0
#
# if Lay0 = nulll then
#  Break <- End of algorithm
# end if
#
# codegen(Lay0) <- Generate loop for i-th Lay
#
# end for
import sys
import re
from termcolor import colored
import islpy as isl
ctx = isl.Context()

import iscc
import imperf_tile

def DynamicRTILE(rtile, TILE_VLD_ext, n, cl, vars, RFS):

    RFS = isl.Map(RFS).coalesce()

    I0 = rtile.domain();
    text_file = open("Output.txt", "w")

    for i in range(0,10000):
        if (i==0):
            J0 = rtile.range()
            FS0 = I0.subtract(J0).coalesce()
            L0 = FS0
        else:
            L0 = Lay0.apply(rtile)
            J0 = J0.subtract(Lay0)


        D0 = J0.apply(rtile)

        Lay0 = L0.subtract(D0).coalesce()


        if(Lay0.is_empty()):
            break

        Lay = Lay0.insert_dims(isl.dim_type.set, 2*n, 2*n)
        Lay = Lay.intersect(TILE_VLD_ext).coalesce()


        Lay = Lay.apply(RFS).coalesce()

        Lay = imperf_tile.SimplifySlice(Lay)


        loop = iscc.isl_ast_codegen(Lay)
        loop = loop.split('\n')
        if 'for' in loop[0]:
            if((('int c1') in loop[0]) or (('int c3') in loop[0]) or (('int c5') in loop[0])):
                loop.insert(0, "#pragma omp parallel for")

        loop_str = RestoreStatements2(loop, cl, n, vars)

        text_file.write(loop_str)

        # for line in loop_str:
        #     if '#pragma' in line:
        #         print colored(line, 'green')
        #     else:
        #         print line

    text_file.close()



def RestoreStatements2(loop, cl, n, vars):
    loop_str = []

    for line in loop:
        if line.endswith(');'):
            tab = imperf_tile.get_tab(line)
            line = line.replace(' ', '')
            line = line[:-2]
            line = line[1:]

            arr = line.split(',')

            petit_st = arr[4 * n]

            s = ''

            for i in range(0, len(cl.statements)):
                if (cl.statements[i].petit_line == int(petit_st)):  # st.petit_line
                    s = cl.statements[i].body

            for i in range(0, len(vars)):  # todo oryginal iterators for loops with mixed indexes
                subt = arr[2 * n + 2 * i + 1]
                if (('+' in subt) or ('-' in subt)):
                    subt = '(' + subt + ')'
                s = re.sub(r'\b' + vars[i] + r'\b', subt, s)

            loop_str.append(tab + s)

        else:
            line = line.replace('for (int', 'for(')
            loop_str.append(line)

    loop_str = '\n'.join(loop_str)
    return loop_str
