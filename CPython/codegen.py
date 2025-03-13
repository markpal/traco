#!/usr/bin/env python
  
import ctypes
import sys
  
LIBRARY_PATH = '/home/marek/issf/py/CPython/my_library.so'


def makearr( L ):
    arr = (ctypes.c_char_p * (len(L) + 1))()
    arr[:-1] = L
    arr[ len(L) ] = None
    return arr

  
def cloog_gen(param, iterators, domains, scattering, str_context):
   
    my_library = ctypes.CDLL(LIBRARY_PATH)
    my_library.codegen.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.POINTER(ctypes.c_char_p), ctypes.POINTER(ctypes.c_char_p), ctypes.c_int, ctypes.POINTER(ctypes.c_char_p), ctypes.POINTER(ctypes.c_char_p)]

    my_library.codegen.restype = ctypes.c_char_p
    context = ctypes.c_char_p(str_context)
    loop = my_library.codegen(context, len(param), makearr(param), makearr(iterators), len(domains), makearr(domains), makearr(scattering))

    return loop
                                                                                                                                                
  
#param = ["N"]
#iterators = ["ii", "i","v"]
#domains = ["[N] -> {[ii, i,6] : 0 <= ii <= 2 and 0 <= i < N}","[N] -> {[ii, i,8] : 0 <= ii <= 2 and 0 <= i < N}"]
#scattering = ["[N] -> {[ii, i,v] -> [0, ii, 1,v]}","[N] -> {[ii, i,v] -> [0, ii, 2,v]}"]
#str_context = "[N] -> { : N > 0}"


def calculate_position(i, instrukcje, dim):
    path = instrukcje[i]['path']
    
    position = [0] * dim
    for k in range(0, dim):
        for j in range(0, i):
            if(len(instrukcje[i]['path']) > k and len(instrukcje[j]['path']) > k):
                if(instrukcje[i]['path'][k] == instrukcje[j]['path'][k]):
                    position[k] = position[k] + 2
                
    
    return position


def calculate_position2(i, instrukcje, dim):
    path = instrukcje[i]['path']
    
    
    z = 0
    if(i>0):
        path2 = instrukcje[i-1]['path']
        minnest = min(len(path), len(path2))
        for j in range(1, minnest):
            if path[j] == path2[j]:
                z = z+1

    
    position = [0] * dim
    for k in range(z, dim):
        for j in range(0, i):
            if(len(instrukcje[i]['path']) > k and len(instrukcje[j]['path']) > k):
                if(instrukcje[i]['path'][k] == instrukcje[j]['path'][k]):
                    position[k] = position[k] + 2
                
    
    return position

def tile_gen_short(vars, sym_exvars, symb,isl_BL,instrukcje, Extend):
    
    iterators = []
    for s in sym_exvars:
        iterators.append(s)
        iterators.append(s + "p")

    if(Extend):
        for s in vars:
            iterators.append(s)
            iterators.append(s + "v")

    iterators.append("v")
    
    param = symb
    str_context = "" 
    
    domains = [str(isl_BL)]      
    scattering = []
    
    s = "[" + ",".join(symb) + "] -> {[" + ",".join(iterators) + "] -> [0," + ",".join(iterators) + "]}"
    scattering.append(s)
        
    #str_context = "[N1,N2,N3,N4,N5,N6,N7,N8,N9,N10,N11] -> { : 1=1 && N1 >=1 && N2 >=1 && N3 >=1 && N4 >=1 && N5 >=1 && N6 >=1 && N7 >=1 && N8 >=1 && N9 >=1 && N10 >=1 && N11 >=1 }"
    str_context = "[] -> { : 1=1 }"


    cloog_gen(param, iterators, domains, scattering, str_context)  # tu sa jakies smieci
    l = open('tmp/cloog_loop.c', 'r').read()

    
    for i in range(0, 10):
        l = l.replace("S" + str(i) + "(", "(")

    return l

    
    

def tile_gen(vars, sym_exvars, symb,isl_BL,instrukcje,rest_loop,isl_REST_new,stuff):
    #print "===================================================="
    
    iterators = sym_exvars + vars
    iterators.append("v")
    
    param = symb

    #print iterators
    #print param
    
    str_context = "" 
    
    domains = []
    for bl in isl_BL:
        domains.append(str(bl))
               
    #print domains
    for rest in isl_REST_new:
        domains.append(str(rest))
    
    prefix = "[" + ",".join(symb) + "] -> {[" + ",".join(iterators) + "] -> [0," + ",".join(sym_exvars) + ","
    prefix1 = "[" + ",".join(symb) + "] -> {[" + ",".join(iterators) + "] -> [1," + ",".join(sym_exvars) + ","
    buckets = [0] * len(sym_exvars)
    
    scattering = []

    for i in range(0, len(isl_BL)):
        nest = instrukcje[i]["nest"]
        for j in range(0, nest):
            buckets[j] = buckets[j] + 1 
        for j in range(nest, len(sym_exvars)):
            buckets[j] = 0
            
        str_buckets = (str(w) for w in buckets)
        scattering.append(prefix + ",".join(str_buckets) + ",v]}")

    # jeszcze  te reszty
    buckets = [0] * len(sym_exvars)
    for i in range(0, len(isl_REST_new)):
        nest = instrukcje[i]["nest"]
        for j in range(0, nest):
            buckets[j] = buckets[j] + 1
        for j in range(nest, len(sym_exvars)):
            buckets[j] = 0    
        str_buckets = (str(w) for w in buckets)
        scattering.append(prefix1 + ",".join(str_buckets) + ",v]}")

            
    #
    
    #param = ["N"]
    #iterators = ["ii", "i","v"]
    #domains = ["[N] -> {[ii, i,6] : 0 <= ii <= 2 and 0 <= i < N; [1,1,6]}","[N] -> {[ii, i,8] : 0 <= ii <= 2 and 0 <= i < N}"]
    #scattering = ["[N] -> {[ii, i,v] -> [0, ii, 1,v]}","[N] -> {[ii, i,v] -> [0, ii, 2,v]}"]
    str_context = "[] -> { : 1=1}"

        
        # za -1 podstaw dolna lub gorna granice tego wymairu w tym gniezdzie (instrukcje)
        # zostaw wspolne ii
        # jesli nie ma jj podstaw -1 lub gorna granice jesli juz bylo
        # jesli jest zostaw jj
        # jak jest drugi raz podstaw za jj dodaj gorna granice + 1 (plus wszystkie)
        
        # instrukcje path i stuff masz granice wszystkie i maxloop
        
    iterators = sym_exvars + vars
    prefix = "[" + ",".join(symb) + "] -> {"
    pref = "[" + ",".join(iterators) + ","

    scattering = []
    for i in range(0, len(instrukcje)):
        scater = prefix
        #for j in range(0, instrukcje[i]["nest"]):
        # tu zapis wszystkich aktualnych granic
        # odczytac path i zapisac z stuff do tablicy
        # jesli cos tu jest powiekszyc   
        for l in range(0, len(instrukcje)):
            prefix2 = "] -> [0,"
            for j in range(0, instrukcje[i]["nest"]):
                prefix2 = prefix2 + sym_exvars[j] + ","
            for j in range(instrukcje[i]["nest"], len(sym_exvars)):
                if (instrukcje[i]["max_loop"] <= j):
                    prefix2 = prefix2 + "-1,"
                else:
                    prefix2 = prefix2 + stuff[j]["ub"] + ","   # tu powinno byc odchowana granica w bloku i dodana
            
            for j in range(0, instrukcje[l]["nest"]):
                prefix2 = prefix2 + vars[j] + ","
            for j in range(instrukcje[l]["nest"], len(sym_exvars)):
                if (instrukcje[l]["max_loop"] <= j):
                    prefix2 = prefix2 + "0, "
                else:
                    prefix2 = prefix2 + stuff[j]["ub"] + ","
            
            for s in instrukcje[l]['st']:
                scater = scater + pref + str(s) + prefix2 + str(s) +"]; " 
        scater = scater[:-2] + "}"

        scattering.append(scater)
        

    #scattering  =  ["[] -> {[ii,jj,i,j,8] -> [0,ii,-1,i,j,8]; [ii,jj,i,-1,6] -> [0,ii,-1,i,0,6]}",               
    #              "[] -> {[ii,jj,i,j,8] -> [0,ii,jj,i,j,8]; [ii,jj,i,-1,10] -> [0,ii,jj,i,7,10] }",
    #              "[] -> {[ii,jj,i,j,10] -> [0,ii,7,i,7,10]}"]



    for s in scattering:
        print s


#
    l = cloog_gen(param, iterators, domains, scattering, str_context)  # tu sa jakies smieci


    
    for i in range(0, 10):
        l = l.replace("S" + str(i) + "(", "(")

    return l + rest_loop
