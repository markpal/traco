import re
import sys
import islpy as isl

import imperf_tile

def parse(lines, cl, symb_prefix):


    statements = []
    iterators = []
    lev_st = {}
    maps_sched = []

    for st in cl.statements:
        statements.append('S' + str(st.petit_line))
        lev_st['S' + str(st.petit_line)] = len(st.original_iterators)
        if len(st.original_iterators) == cl.maxdim:
            iterators = st.original_iterators


    #print lines
    lev = -1
    sch_out = {}
    poziom = -1
    pairs = {}
    odstep = ''


    for l in lines:


        if "schedule" in l:



            if(len(odstep) <  len(imperf_tile.get_tab(l)) ):
                odstep = imperf_tile.get_tab(l)
                lev = lev + 1

            result = re.findall(r'{[^{]+}', l)

            #lev = lev + 1
            #print 'Loop nest ' + str(lev) + '   ### '

            for r in result:

                maps = r.split(';')
                for m in maps:

                    #print m;
                    #detect statement
                    res = re.findall(r'S\d+', m)
                    sd = res[0]
                    item = re.findall(r'\([^\(]+\)', m)[0].replace('(', '').replace(')', '')
                    #print sd + ' ' + item

                    if(pairs.has_key(sd)):
                        pairs[sd] = pairs[sd] + '+' + item
                    else:
                        pairs[sd] = item


            if str(lev) in sch_out:
                sch_out[str(lev)].update(pairs)
            else:
                sch_out[str(lev)] = pairs

            pairs = {}



    j=0
    for s in statements:
        map = symb_prefix + '{' + s + '['
        for i in range(0, lev_st[s]):
            map += iterators[i] + ','
        map = map[:-1] + '] -> ['


        for i in range(0, lev_st[s]):
            if sch_out.has_key(str(i)):
#                print sch_out[str(i)]
                if s in sch_out[str(i)]:
#                    if sch_out[str(i)][s]!= '0':
                    map += sch_out[str(i)][s] + ','
           # else:
            #    map += iterators[i] + ','

        map = map[:-1] + '] : ' + cl.statements[j].domain + '}'

        maps_sched.append(isl.Map(map))
        j = j+1


    return maps_sched





'''
domain: "[N] -> { S2[i, j] : i <= 0 and -i < j < N; S1[i, j, k] : i <= 0 and j < N and 0 <= k < i + j }"
child:
  schedule: "[N] -> [{ S2[i, j] -> [(i)]; S1[i, j, k] -> [(i)] }, { S2[i, j] -> [(j)]; S1[i, j, k] -> [(j)] }]"
  permutable: 1
  coincident: [ 1, 1 ]
  child:
    schedule: "[N] -> [{ S2[i, j] -> [(j)]; S1[i, j, k] -> [(k)] }]"
    permutable: 1
    coincident: [ 1 ]
'''

'''
{S1[i,j,k] -> [i+j,k,k]}
{S2[i,j] -> [i+j,j]}
'''
