#W2 := [N,ii] -> {[ii,10-1,3]};
#W1 := [N,ii,jj] -> {[ii,0, 1] };
#Z1 := dom (W1 << W2);
#Z1 := Z1 = W1;
#Z1;
#import tiling
import sys

import subprocess
import re
import tqdm

import loop_tools



try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()

import re
import time
import agent





ctx = isl.Context()

def GetIT(instrukcje, stuff_reduced, _SYM, vars, sym_exvars, BLOCK, l):
    # jak chcesz samo it porste daj symb zamiast _SYM oraz wywal vec z ii,jj

    it = "[" + _SYM[:-1] + "] -> {["
    for v in vars:
        it = it + v + ","
    it = it[:-1] + ",v] : "  
    
    item = instrukcje[l]

    for i in range(0,len(vars)):
        if i < len(item['path']):
            id_loop = item['path'][i]
            it = it + stuff_reduced[id_loop]['lb'] + "<=" + vars[i] + '<=' + stuff_reduced[id_loop]['ub'] + " and "
        else:
            it = it + vars[i] + " = -1 and "

    vec = "("
    for st in item['st']:
        vec = vec + " v = " + str(st) + " or "
    
    vec = vec[:-3] + ") and "

  
    it = it + vec[:-4]+ "};"  
                
                
    return it
    
    

def get_tab(line):
    return " " * (len(line) - len(line.lstrip()))

def RestoreStatements(lines, petit_file, dane, shift, step, permutate_list, shift_first = 0):
    paczka = loop_tools.ReadStatementNests(petit_file, dane)
    combo = paczka[0]
    granice = paczka[2]
    
    linestring = open(petit_file, 'r').read()
    petit_lines = linestring.split('\n')
    
    debug = False
    
    loop = ""
    for line in lines:
        if("s1(" in line):
            pattern = re.compile(",[^,]+\);")
            st = pattern.findall(line)[0].replace(",", "").replace(");", "")
            if(not st.isdigit()):
                print "== ERROR =="
                #sys.exit()
            numb_st = int(st)
            st = petit_lines[int(st)-1]
            st = st.replace(",", "][")
            
            # nawiasy powinny byc zmienione jesli poprzedzaja je znaki 
            # alfanumeryczne, inaczej to nawiasy nie od tablic
            st =  re.sub("\s*\(", "(", st)
            st =  re.sub("\s*\)", ")", st)
            st =  re.sub(r'(?<=[a-zA-Z0-9_])\(', '[', st)
            st =  re.sub(r'(?<=[a-zA-Z0-9_])\)', ']', st)
            
            # szukaj wektora
            for item in combo:
                if numb_st in item['st']:
                    vec = item['vars'][:]
                    if debug:
                        loop = loop +  get_tab(line) + "// " + ",".join(item['vars']) + "\n"
                    break
            
            # nowy wektor

            vec_new = line.replace("s1(", "").replace(");", "").replace(" ", "").split(",")[:-1]


            vec_new = vec_new[(shift - shift_first):]


            if(step == 1):  # usun co drugi element
                #print vec_new

                vec_new = vec_new[shift:]

                vec_new = vec_new[1:][::2]

                #print vec_new
                #sys.exit(0)



            if debug:
                loop = loop +  get_tab(line) + "// " + ",".join(vec_new) + "\n"
            
            st2 = st

            pp = ""


            for p in permutate_list:
                if p[0] == numb_st:
                    pp = p
                    if pp != "":
                        tmp = vec[pp[1]]
                        vec.pop(pp[1])
                        vec.append(tmp)

                        if(len(vec) < len(vec_new)):
                            vec_new[len(vec_new)-1], vec_new[len(vec)-1] = vec_new[len(vec)-1], vec_new[len(vec_new)-1]  # zamien instrukcje


            # blad jesli vec i vec_new sie powtarzaja
            # http://emilics.com/blog/article/multi_replace.html

            for v in vec:
                v = '\\b' + v + '\\b'

            #rdict = dict(zip(vec, vec_new))
            #print rdict
            #sys.exit()
            #robj = re.compile('|'.join(rdict.keys()))
            #st2 = robj.sub(lambda m: rdict[m.group(0)], st2)

            for i in range(0, len(vec)):
                st2 = re.sub('\\b'+vec[i]+'\\b', vec_new[i], st2)



            if debug:
                loop = loop +  get_tab(line) + "// " + st + ";\n"
                
            loop = loop + get_tab(line) + st2 + ";\n"
        else:
            loop = loop + line.replace('int ', '') + "\n"
            
    
   
    return loop

# sprawdza odwolania do tablic w relacjach z Petit
# jesli wszedzie wystepuja na tej samej pozycji zwroci relacje

def PermuteBlock(deps_file, TILEprim, instrukcje, symb, n, permutate_list):





    linestring = open(deps_file, 'r').read()
    lines = linestring.split('\n')

    if(len(instrukcje['vars']) == 1):
        return -1



    _vars = []
    for line in lines:
        info = line.split()
        if(len(info)>0):
            _vars.append(info[2])
            _vars.append(info[5])


    tmp_set = [""] * n * 2
    for v in _vars:
        if ")" in v:
            ind = v.replace(")", "").split("(")[1].split(",")
            for i in range(0,len(ind)):
                for c in instrukcje['vars']:
                    t = "\\b" + c + "\\b"
                    if (re.search(t, ind[i])):
                        if(tmp_set[i] == ""):
                            tmp_set[i] = c
                        else:
                            if(i == n-1 and tmp_set[i] != c):
                                return -1

    cand = tmp_set[-2]

    for i in range(1, len(tmp_set)+1):
        if tmp_set[-1*i] != '':
            cand =  tmp_set[-1*i]
            break

    if cand in instrukcje['vars']:
        where = instrukcje['vars'].index(cand)
    else:
        return -1


    if(where == n):
        return -1  #is ok




    rel = "{["
    for i in range(0, n):
        rel = rel + "i" + str(i) + ","
    rel = rel + "v] -> ["

    '''
    for i in range(0, n):
        if i == where:
            rel = rel + "i" + str(int(instrukcje["nest"]-1)) + ","
            continue
        if i == instrukcje["nest"]-1:
            rel = rel + "i" + str(where) + ","
            continue
        rel = rel + "i" + str(i) + ","
    '''
    for i in range(0, n):
        if i < where:
            rel = rel + "i" + str(i) + ","
        else:
            if i < n-1:
                rel = rel + "i" + str(i+1) + ","
              #  for st in instrukcje['st']:
               #     permutate_list.append([st, i+1, i])
            else:
                rel = rel + "i" + str(where) + ","
                for st in instrukcje['st']:
                    permutate_list.append([st, where, instrukcje["nest"]-1])

    
    rel = rel + "v]}"
    rel = isl.Map(rel)

    #print permutate_list

    return rel
            
               
def Get_ST(plik, dane):
    linestring = open(plik, 'r').read()
    lines = linestring.split('\n')

    infor = 0
    i = 0
    sts = []
    for line in lines:
        i = i + 1
        if infor == 0 and 'for' not in line:
            continue
        if 'for ' in line:
            infor = 1
        if 'for ' not in line and 'if ' not in line and 'endfor' not in line and 'endif' not in line and line.strip() and str(i) not in dane and 'then' not in line and 'else' not in line:
            sts.append(str(i))

    return sts


remote = 1

def SimplifySlice(slice):
    sets =  slice.get_basic_sets()

    rhull = ""
    if(remote == 1):
        rhull= agent.remote_hull()

    print 'Please wait, simplification... '
    #for i in tqdm.tqdm(range(0, len(sets))):
    for i in tqdm.trange(len(sets), desc='1st loop', leave=True):
        for j in tqdm.trange(len(sets), desc='2nd loop', leave=False):
        #for j in range(0, len(sets)):
        #for j in range(0, len(sets)):
            if(i!=j and not sets[i].is_equal(sets[j])):
                tmp = sets[i].union(sets[j])

                if(remote == 1):
                    tmp2 = rhull.hull(tmp)
                else:
                    tmp2 = tmp.polyhedral_hull()
                if(tmp.is_equal(tmp2) and len(tmp2.get_basic_sets()) == 1):
                    #print "i j " + str(i) + " " + str(j) + "joinable"
                    sets[i] = tmp2
                    sets[j] = tmp2
                #else:
                    #print "i j " + str(i) + " " + str(j) + "--"

    slice = sets[0]
    for i in range(1, len(sets)):
        slice = slice.union(sets[i]).coalesce()

    if (remote == 1):
        rhull.disconnect()


    return slice

def SimplifyMap(slice):
    sets =  slice.get_basic_maps()

    print 'Please wait, simplification... '
    for i in tqdm.tqdm(range(0, len(sets))):
        for j in range(0, len(sets)):
            if(i!=j and not sets[i].is_equal(sets[j])):
                tmp = sets[i].union(sets[j])
                tmp2 = tmp.polyhedral_hull()
                if(tmp.is_equal(tmp2) and len(tmp2.get_basic_maps()) == 1):
                    #print "i j " + str(i) + " " + str(j) + "joinable"
                    sets[i] = tmp2
                    sets[j] = tmp2
                #else:
                    #print "i j " + str(i) + " " + str(j) + "--"

    slice = sets[0]
    for i in range(1, len(sets)):
        slice = slice.union(sets[i]).coalesce()


    return slice