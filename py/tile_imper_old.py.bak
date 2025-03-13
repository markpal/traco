# problemy preprocessing , rozne wymiary, wyliczanie REST


import convert_loop
import functions
import gen
import subprocess
import re
import sys
import glob, os
import shutil
import loop_tools
import tiling_schedule
import correct
import iscc
import priv_engine
import time
import os.path

import imperf_tile

sys.path.insert(1, '/home/marek/issf/py/CPython')
import codegen

# nowosc isl w pythonie do testow
import islpy as isl
ctx = isl.Context()



schedule_mode = 0
maxl = 0   # ile gniazd jest w petli

barv_script = "~/barvinok-0.36/iscc"


DEBUG = True
DEBUG2 = False
DEBUG3 = False

def duplicates(lst, item):
    return [i for i, x in enumerate(lst) if x == item]

def CreateLex(array1, array2):
    n = len(array1)
    lex = "("

    for i in range(0,n):
        if(lex != "("):
            lex = lex + " || ("
        for j in range(0,i):
            lex = lex + array1[j] + " = " + array2[j] + " && "
        lex = lex + array1[i] + " > " + array2[i]
        if(i>0):
            lex = lex + ")"
        
    return lex + ")"   
        
        
def Constr_Dowolny(vars, sym_exvars, stuff, BLOCK, i,iloczyn, j):  
    
    return stuff[j]['lb'] + " <= " + vars[i] + " <= " +  stuff[j]['ub'] + " && " + iloczyn  + " <= " +  stuff[j]['ub'] + " && "

def Constr_Przed(vars, sym_exvars, stuff, BLOCK, i, iloczyn,j):  
    return stuff[j]['lb'] + " <= " + vars[i] + " <= " +  iloczyn + "-1 && " + iloczyn + " <= " +  stuff[j]['ub'] + " && "
      

def Constr_Wbloku(vars, sym_exvars, stuff, BLOCK, i, iloczyn, j):
    return iloczyn + ","+ stuff[j]['lb'] +" <= " + vars[i] + " <= " +  stuff[j]['ub'] + "," + iloczyn + "+" + BLOCK[i] + "-1 && "



def Constr_Za(vars, sym_exvars, stuff, BLOCK, i, iloczyn, j):  
    return iloczyn + "+" + BLOCK[i] +" <= " + vars[i] + " <= " +  stuff[j]['ub'] + " && "
 
        
# zaleznosci w relacjach
def Constraint(vars, sym_exvars, stuff, BLOCK, dane,par_vars):
    s = ""
    for i in range(0,dane["nest"]): # len(vars)
#        s = s + sym_exvars[i] + '<= ' + vars[i] + '<= ' + sym_exvars[i] + '+' + str(BLOCK[i]) + '- 1, ' + stuff[i]['ub'] + ' && ';
##       s = s + sym_exvars[i] + '*' + str(BLOCK[i]) +  ',' + stuff[i]['lb']  + '<= ' + vars[i] + '<= ((' + sym_exvars[i] + '+1)*' + str(BLOCK[i]) + '- 1), ' + stuff[i]['ub'] + ' && ';

        s = s + Constr_Wbloku(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i])
        # i przedostatni element
        #
             
    for i in range(dane["nest"], len(vars)):
        s = s + vars[i] + " = -1 && "
    
  ##########################################
  ##########################################
    if(dane["max_loop"] == dane["nest"]):
        for i in range(dane["max_loop"], len(sym_exvars)):
            s = s + sym_exvars[i] + " = 0 && "
    else:
        for i in range(dane["nest"], len(sym_exvars)):
            s = s + BLOCK[i] + "*" + sym_exvars[i] + " <= " + stuff[i]['ub'] + "-"+ stuff[i]['lb']   +" && " 
            s = s + BLOCK[i] + "*" + sym_exvars[i] + " > " + stuff[i]['ub'] + "-"+ stuff[i]['lb'] +"-"+ BLOCK[i]   +" && " 
              
            # tu powinno byc ub - lb / b
            #s = s + sym_exvars[i] + " = "+stuff[i]['ub']+"&& "
    return s


def MakeBij(_SYM, vars, sym_exvars, par_vars, stuff, BLOCK, dane):   
    Bij = "_Bij := [";
    Bij = Bij + _SYM        
    Bij = Bij[:-1] + "] -> {["
    
    for s in vars:
        Bij = Bij + s + ","
        
    Bij = Bij + 'v' + '] : '
    Bij = Bij + Constraint(vars, sym_exvars, stuff, BLOCK,dane, par_vars)
    
    for s in sym_exvars:
        Bij = Bij + s + ">=0 && "
    
    #eksperymentalnie gorna granica zawsze wieksza od dolnej   
    for i in range(0,len(sym_exvars)):  #
        Bij = Bij + stuff[i]['lb'] + ' <= ' + stuff[i]['ub'] + ' && '

#    for i in range(0, dane["nest"]):
#        Bij = Bij + sym_exvars[i] + ">=0 && "
#        Bij = Bij + BLOCK[i] + "*" + sym_exvars[i] + "<=" + stuff[i]['ub'] +" && "
        
    Bij = Bij + "("
    
    for i in range(0,len(dane['st'])):
        Bij = Bij + " v = "+ str(dane['st'][i])
        if(i < len(dane['st'])-1):
            Bij = Bij + " || "
        
    Bij = Bij + ")};"
    return Bij


def MakeBLTandBGT_v2(_SYM, vars, sym_exvars, par_vars, varsprim, exvars, stuff, BLOCK, dane, dane2):
    global maxl
    BLT = "_BLT := [" + _SYM
    #  tu trzeba dodac zmienne iib, jjb dla spar. tilingu
    BLT = BLT[:-1] + "] -> {["
    for s in vars:
        BLT = BLT + s + ","
    BLT = BLT + 'v' + '] : (( '
    BGT = BLT.replace('_BLT :=', '_BGT :=')
    n = dane["nest"]
    m = dane2["nest"]

    if(dane["nest_id"] == dane2["nest_id"]):  # ta sama petla licz stara metoda
        for i in range(0,n):
            for j in range(0,i):
                tmp = Constr_Wbloku(vars, sym_exvars, stuff, BLOCK, j, par_vars[j], dane['path'][j])
                BLT = BLT + tmp
                BGT = BGT + tmp
            BLT = BLT + Constr_Przed(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i])
            BGT = BGT + Constr_Za(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i]) 
            for j in range(i+1,n):
                tmp = Constr_Dowolny(vars, sym_exvars, stuff, BLOCK, j, par_vars[j], dane['path'][j])
                BLT = BLT + tmp
                BGT = BGT + tmp
            BLT = BLT + " true )"
            BGT = BGT + " true )"
            if(i<n-1):
                BLT = BLT + " or ("
                BGT = BGT + " or ("
    else:
        for i in range(0,min(m,n)):
            tmp = Constr_Wbloku(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i])
            tmp = tmp[:-3] + " or "
            if(dane2["nest_id"] > dane["nest_id"]):
                BLT = BLT + tmp
                    
            if(dane2["nest_id"] < dane["nest_id"]):
                BGT = BGT + tmp
                
            BLT = BLT + Constr_Przed(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i])
            BGT = BGT + Constr_Za(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i])   
            
            BLT = BLT + " true )"
            BGT = BGT + " true )"
            if(i<min(m,n)-1):
                BLT = BLT + " or ("
                BGT = BGT + " or ("
         

            
            
        #    tmp = Constr_Dowolny(vars, sym_exvars, stuff, BLOCK, j, par_vars[j], dane['path'][j])
        #    BLT = BLT + tmp
        #    BGT = BGT + tmp
    

    varcon = ") && ("
    for i in range(0, dane["nest"]):
        varcon = varcon + sym_exvars[i] + ">=0 && "
        varcon = varcon + BLOCK[i] + "*" + sym_exvars[i] + "<=" + stuff[i]['ub'] +" && "
        
            
    
    for i in range(0,len(dane['st'])):
        varcon = varcon + " v = "+ str(dane['st'][i])
        if(i < len(dane['st'])-1):
            varcon = varcon + " || "
    varcon = varcon + ") "  
    
    #dodaj  j = -1 lub granice i granice na jj    lub -0 lub ub    
    for i in range(min(m,n),maxl):   
        if n < i+1:
            varcon = varcon + " && " + vars[i] + " = -1 "
            #if(dane["max_loop"] == dane["nest"]): 
            #     varcon = varcon + " && " + sym_exvars[i] + " = 0 "
            #else:
            #     varcon = varcon + " && " + sym_exvars[i] + " = 1 "    
        else:
            if m < i+1:  # granice
                varcon = varcon + "&& " + Constr_Dowolny(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i]) + sym_exvars[i] + " >= 0 && "+ Constr_Wbloku(vars, sym_exvars, stuff, BLOCK, i, par_vars[i], dane['path'][i])
                varcon = varcon[:-3]   
         
    BLT = BLT + varcon + "};"
    BGT = BGT + varcon + "};"  
 

    BLGT = []
    BLGT.append(BLT)
    BLGT.append(BGT) 
    

    return BLGT 


def postprocess_loop(lines):
    #dodaj s1 do petli
    loop = ""
    for i in range(0,len(lines)):
        tmp = lines[i]
        pattern = re.compile("^\W*\(")
        if pattern.match(tmp):
            tmp = tmp.replace("(", "s1(")
            tmp = tmp.replace(", ", ",")
        loop = loop + tmp
# if(i < len(lines)-1):
        loop = loop + "\n"
    return loop


def Project(S, sym_exvars):
    for s in sym_exvars:
        isl_symb = S.get_var_names(isl.dim_type.param)
        S = S.project_out(isl._isl.dim_type.param, isl_symb.index(s), 1)
        
    return S
        
def RemoveOtherSt(isl_BL, dane,sym_exvars):
    constr = ""
    for i in range(0,len(dane['st'])):
        constr = constr + " v = "+ str(dane['st'][i])
        if(i < len(dane['st'])-1):
            constr = constr + " || "
        
    CL = "{["
    for i in range(0, len(sym_exvars)):
        CL = CL + "x" + str(i) + ","
            
    CL = CL + "v] : " + constr + "}"
    CL = isl.Set(CL)
    isl_BL = isl_BL.intersect(CL)
    return isl_BL
########################################   

    

def TileGen(sym_exvars, vars, _SYM, symb, p_symb, par_tiling, rel, schedule, instrukcje, stuff_reduced, BLOCK, isl_TILEprim, varsprim, isl_IT, isl_REST_new):   
    
    ctx = isl.Context()
    
    tileall = []
    
    i = 0
    for isl_BL in isl_TILEprim:  
        TA = isl_BL  # tak bylo oryginalnie
        #TA =  RemoveOtherSt(isl_BL, instrukcje[i], sym_exvars)   
        tileall.append(Project(TA, sym_exvars))
        i = i + 1

    R = "R := ["
    R = R + _SYM
    
    # dodaj zmienne symb ilorazow
    if(par_tiling):
        for i in range(0,len(sym_exvars)):
            R = R + " fff" + str(i) + ","
    
    R = R[:-1] + "] -> {["
    for s in vars:
        R = R + s + ","
    R = R + "v] -> ["
    for s in sym_exvars:
        R = R + s + ","
    for s in vars:
        R = R + s + ","
    R = R + "v] : "  
    
    if(par_tiling):
        for i in range(0,len(sym_exvars)):
            R = R + " " + sym_exvars[i] + "<= fff" + str(i)+ " and "
    
    R = R + " true };\n"
    
    isl_Rapply = isl.Map(R.replace('R := ',''))
    

    isl_TILEALL = tileall[0]
    for i in range(1, len(tileall)):
        isl_TILEALL = isl_TILEALL.union(tileall[i])

    if(DEBUG):
        print "TILE_ALL"
        print isl_TILEALL
    
    isl_BL = []
    i=0
    for bl in isl_TILEprim:
        BLj1 = bl.apply(isl_Rapply).coalesce() # przepusc przez R
        BLj1 = Project(BLj1, sym_exvars) # wywal ii, jj z symb

        # wywal powtarzajace sie
        RA = "{[" + ",".join(sym_exvars) + "," + ",".join(vars) + ",v] -> [" + ",".join(varsprim) + "," + ",".join(vars) + ",v] : " + CreateLex(varsprim, sym_exvars) + "}"
        tmp1 = BLj1 .apply(isl.Map(RA))
        tmp1 = BLj1.intersect(tmp1)
        BLj1 = BLj1.subtract(tmp1)
        
        isl_BL.append(BLj1)  # mozna juz do gen code
        if(DEBUG):
            print "TILE_bis" + str(i)
            print BLj1
        i = i + 1

    for i in range(0, len(isl_REST_new)):
        isl_REST_new[i] = isl_REST_new[i].apply(isl_Rapply).coalesce() # przepusc przez R
        isl_REST_new[i] = Project(isl_REST_new[i], sym_exvars) # wywal ii, jj z symb

    isl_REST = []

    for i in range(0, len(isl_TILEprim)):       
        if(DEBUG):
            print "IT" + str(i)
            print isl_IT[i]

        tmp = isl_IT[i].subtract(isl_TILEALL)
        #tmp = SlowSimplify(tmp)
        isl_REST.append(tmp)
        if(DEBUG):
            print "REST" + str(i)
            print isl_REST[i]
       
               
    # na przyszlosc trzeba tutaj inaczej wyparsowac instrukcje oddzielic ###
    barv_cmds2 = ""
    for j in range(0, len(isl_REST)):      
        #if(not "-> {  }" in str(isl_REST[j])):
        if not isl_REST[j].is_empty():
            W = isl_REST[j].apply(isl_Rapply)
            barv_cmds2 = barv_cmds2 + "REST" + str(j) + ":= " + str(W) + ";codegen REST"+str(j)+";"   # isl_REST[j] bylo zamiast W
        


    start = time.time()
    loop = iscc.iscc_communicate(barv_cmds2)
    loop = ""
    with open("tmp/barv_tiling.txt", "a") as myfile:
        myfile.write(barv_cmds2)
    end = time.time()
    elapsed = end - start
    if(DEBUG):
        print "Time taken: ", elapsed, "seconds."  
    
    loop = codegen.tile_gen(vars, sym_exvars, symb,isl_BL,instrukcje, loop, isl_REST_new)

    loops = []
    loops.append(loop)
    
    return loops

###############################################################


def tile(plik, block):
        
    EXP_CODE = True

    BLOCK = block.split(',')
    par_tiling = False
    
    for i in range(len(BLOCK),10):
        BLOCK.append(BLOCK[len(BLOCK)-1])
        
    if(not BLOCK[0].isdigit()):
        par_tiling = True
        #EXP_CODE = False  # nie ma wsparcia na razie dla gen. poszerzonego zbioru dla spar. tilingu, petle zewn. generowane sa z strings

    linestring = open(plik, 'r').read()
    lines = linestring.split('\n')
    
    petit_loop = convert_loop.convert_loop(lines)
    file = open("tmp/tmp_petit.t", 'w')   
 
    for line in petit_loop:
        file.write(line + '\n')
    file.close()
    

    #zapisz zaleznosci
    

    cmd = gen.path_petit + " tmp/tmp_petit.t > tmp/deps.txt"
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    process.wait() 

 
    #prywatyzacja
    priv_stuff = priv_engine.PrivEng("tmp/deps.txt")
    
    
    lines = linestring.split('\n')
    stuff = []
    
    for line in lines:
        if 'for' in line:
            stuff.append(functions.Loop(line));
            
    start = time.time()
    if(schedule_mode==1):
        flag = 0
    else:
        flag = 1
    #pobierz relacje zaleznosci
    if(os.path.exists('rel.txt')):
        with open('rel.txt', 'r') as content_file:
            dane = content_file.read()
    else:
        if(len(priv_stuff[1]) > 0 and (priv_stuff[2] == 1 or False)):   # jest par czyli mozna tiling
            dane = gen.RelPrint_WithPriv("tmp/tmp_petit.t", priv_stuff[1])
        else:
            dane = gen.RelPrint("tmp/tmp_petit.t", flag)
        
    output = process.stdout.read()

    end = time.time()
    elapsed = end - start
    if(DEBUG):
        print "Time taken: ", elapsed, "seconds."  

    dane = dane.split("#")
   
    rel = dane[0]
    rel2 = rel

    
    dane.remove(rel)  
    dane = list(set(dane))

    if(DEBUG):
        print rel

    
    # -------------------------------------------------------
    # script for barvinok
    # gdy nie ma zaleznosci
    # problemy do rozwiazania
    # zmienne symboliczne nie wiadomo skad wziasc
    # numery instrukcji
    nodeps=0
    if(rel == ''):
        nodeps=1
        rel = "{["
        for i in range(0,len(stuff)):
            rel = rel + "i" + str(i) + ","
        rel = rel + "v] -> ["
        for i in range(0,len(stuff)):
            rel = rel + "i" + str(i) + "',"
        rel = rel + "v'] : false }"
        loop_tools.MakeLDPetit("tmp/tmp_petit.t", "tmp/tmp_ld_petit.t")
        dane = gen.RelPrint("tmp/tmp_ld_petit.t",1)
        dane = dane.split("#")
        rel2 = dane[0]
        dane.remove(rel2)
        dane = list(set(dane))
        
    for s in dane:
        if "UNKNOWN" in s:
            dane.remove(s)

    
    
    combo = loop_tools.ReadStatementNests("tmp/tmp_petit.t", dane)
    instrukcje = combo[0]
    

    
    
    nest_loop = combo[1]



    if len(instrukcje)==0:
        print 'blad - brak instrukcji'
        sys.exit()
        # wczytaj wszystkie
    
    
    # eksperymentalnie kasowanie innych poziomow
    stuff_reduced = stuff[:] #osobna kopia
    do_kas = []
    for i in range(1, max(nest_loop)+1):
        dups = duplicates(nest_loop, i)
        for s in dups:
            if s != min(dups):
                do_kas.append(s)
        
    for item in do_kas:
        stuff_reduced[item] = '!'
    
    for i in range(0,stuff_reduced.count('!')):
        stuff_reduced.remove('!') # remove
    # -------------------------------


   
    #find_symb = re.compile("^[^(\]|\{)]*\]");
    #if(rel2 == rel):
    #    tmp = re.findall(find_symb, rel) 
    #else:
    #    tmp = re.findall(find_symb, rel2) 

    isl_rel = isl.Map(str(rel))
    isl_relclosure = isl_rel.transitive_closure()[0].coalesce()
    isl_relplus = isl_relclosure
    
    #ident = "{["
    #for i in range(0, len(stuff_reduced)+1):
    #    ident = ident + "i" + str(i) + ","
    #ident = ident[:-1] + "] -> ["
    #for i in range(0, len(stuff_reduced)+1):
    #    ident = ident + "i" + str(i) + ","
    #ident = ident[:-1] +"]}"
    #isl_ident = isl.Map(ident)
    
    isl_ident = isl_rel.identity(isl_rel.get_space())
    isl_relclosure = isl_relclosure.union(isl_ident).coalesce()  # R* = R+ u I
    
    #LATEX
    isl_relclosure.print_(sys.stdout,0, 5)
    
    isl_symb = isl_rel.get_var_names(isl.dim_type.param)
    symb = isl_symb

    
    #if(len(tmp) > 0):
    #    symb = tmp[0]
    #    symb = symb.replace("[", "");
    #    symb = symb.replace("]", "");
    #    symb = symb.replace(" ", "");
    #    symb = symb.split(",");
    
    vars = []  # i
    exvars = []  # ii'
    sym_exvars = []  # ii
    varsprim = []  # i'
    par_vars = [] # iib
    p_vars = [] #iib bez plusa lb
    p_symb = []
    prev_vars = []
    

    
    # moze warto do iloczynu dodac lb a do floor N - lb
    # do testowania +'+'+s['lb']
    i = 0
    for s in stuff_reduced:
        vars.append(s['var']);
        sym_exvars.append(s['var']*2);
        exvars.append(s['var']*2+"'");
        varsprim.append(s['var']+"'");
        if par_tiling:
            par_vars.append(s['var']*2+'b'+'+'+s['lb'])
            p_vars.append(s['var']*2+'b')
        else:
            par_vars.append(s['var']*2 + "*" + BLOCK[i]+'+'+s['lb'])
            # na uzytel nieidealnie zagniezdzonych
            prev_vars.append("(" + s['var']*2 + "-1)*" + BLOCK[i]+'+'+s['lb'])
        i = i+1
        

   
    _SYM = ""
            
    for s in sym_exvars:
        _SYM = _SYM + s + ","
        
        
    for i in range(len(vars),10):
        BLOCK.pop()
        
    if(par_tiling):
        for s in p_vars:
            _SYM = _SYM + s + ","
            p_symb.append(s)
        for s in set(BLOCK):   #remove duplicates
            _SYM = _SYM + s + ","
            p_symb.append(s)        
                

    for s in symb:
        _SYM = _SYM + s + ","
        
    isl_TILE = []
    isl_TILE_LT = []
    isl_TILE_GT = []
    isl_TILE1 = []
    isl_TILE2 = []
    isl_TILEprim = []
    isl_TILEunion = ""
    isl_TILE_prev = []
    isl_TILE_nextcol = []
    isl_TILE_LT_prev = []
    isl_TILE_GT_prev = []
    isl_IT = []
    isl_REST_new = []
    
    for i in range(0, len(instrukcje)):
        iti = isl.Set(imperf_tile.GetIT(instrukcje, stuff_reduced, _SYM, vars, sym_exvars, BLOCK, i))
        isl_IT.append(iti)
    
    # utworz Bij_PREV czyli podmien w par_vars jeden wymiar na prev_vars
    # i unionem wszystkie polacz
    for i in range(0, len(instrukcje)):
        for j in range(0, instrukcje[i]["nest"]):
            tmp_par_vars = []
            for k in range(0, len(par_vars)):
                if(j==k):
                    tmp_par_vars.append(prev_vars[k])
                else:
                    tmp_par_vars.append(par_vars[k])
            S = MakeBij(_SYM, vars, sym_exvars, tmp_par_vars, stuff, BLOCK, instrukcje[i])
            S = isl.Set(str(S).replace("_Bij := ", ""))

            if(len(isl_TILE_prev) <= i):
                isl_TILE_prev.append(S)
                isl_TILE_nextcol.append(S)
            else:
                isl_TILE_prev[i] = isl_TILE_prev[i].union(S).coalesce()


    if(DEBUG):                
        for i in range(0, len(isl_TILE_prev)):
            print "LT'_" + str(i)
            print  isl_TILE_prev[i]

    
    for i in range(0, len(instrukcje)):
        Bij = MakeBij(_SYM, vars, sym_exvars, par_vars, stuff, BLOCK, instrukcje[i])
        if(DEBUG):
            print "TILE" + str(i)
            print Bij
        isl_TILE.append(isl.Set(str(Bij).replace("_Bij := ", "")))
        if(i==0):
            isl_TILEunion = isl_TILE[i]
        else:
            isl_TILEunion = isl_TILEunion.union(isl_TILE[i])
    
    global maxl
    maxl = 0
    for item in instrukcje:
        if item['max_loop'] > maxl:
            maxl = item['max_loop']

    
    SET_II = "[" + _SYM[:-1] + "] -> {[" + ",".join(vars) + ",v] : "
    for i in range(0, len(sym_exvars)):
        SET_II = SET_II + sym_exvars[i] + " >= 0 and " + par_vars[i] + " <= " + stuff[i]['ub'] + " and "
    SET_II = SET_II+ "1=1 }" 
    print SET_II
    isl_SETii = isl.Set(SET_II)   
    if(DEBUG):
        print isl_SETii

    
    for i in range(0, len(instrukcje)):
        Bij = MakeBij(_SYM, vars, sym_exvars, par_vars, stuff, BLOCK, instrukcje[i])
        if(DEBUG):
            print "======"
        
        bltc=0  # czy juz liczono blt
        bgtc=0  #   -- || --     bgt


        for j in range(0, len(instrukcje)):
            BLGT = MakeBLTandBGT_v2(_SYM, vars, sym_exvars, par_vars, varsprim, exvars, stuff, BLOCK, instrukcje[j], instrukcje[i])   # porownaj zagniezdzenia instrukcji

            isltmp = isl.Set(str(BLGT[0]).replace("_BLT := ", ""))
            if(bltc==0):
                isl_TILE_LT.append(isltmp)
                bltc=1
            else:
                isl_TILE_LT[i] = isl_TILE_LT[i].union(isltmp).coalesce()

            isltmp = isl.Set(str(BLGT[1]).replace("_BGT := ", ""))           
            if(bgtc==0):
                isl_TILE_GT.append(isltmp)
                bgtc=1
            else:
                isl_TILE_GT[i] = isl_TILE_GT[i].union(isltmp).coalesce()

        if(DEBUG):
            print "TILE_LT" + str(i)
            print isl_TILE_LT[i]
            print "TILE_GT" + str(i)
            print isl_TILE_GT[i]


        X = isl_TILE_GT[i].apply(isl_relclosure).coalesce()
        
        
        if(DEBUG):
            print "R*(TILE_GT" + str(i) + ")"
            print X


        isl_BCUR = isl_TILE[i].subtract(X).coalesce()

        isl_TILE1.append(isl_BCUR)
        
        if(DEBUG):
            print "TILE1_" + str(i)
            print isl_TILE1[i]


        
        C = isl_TILE[i].apply(isl_relplus).coalesce()
        if(DEBUG2):
            print "(R*(TILEi)"
            print C
        C = C.intersect(isl_TILE_LT[i]).coalesce()
        C = C.intersect(isl_IT[i]).coalesce() 
                
        A = isl_TILE_LT[i].apply(isl_relplus).coalesce()       
        A = A.intersect(isl_TILE_prev[i]).coalesce()
        #A = isl_TILE_prev[i]

        

        A = A.subtract(Project(isl_TILE1[i].union(C), sym_exvars)).coalesce()
        #A = A.subtract(Project(C, sym_exvars)).coalesce()
        if(DEBUG2): 
            print "(R+(LTi) intersect LT'i) - instrukcje [ belong to C and TILE1i ]"
            print A
            print "TILE2 (z wczesniejszym union C)"
                 
        A = A.union(C).coalesce()
        
        #dla ladniejszego zapisu
        A = A.intersect(isl_SETii).coalesce()
        #A = isl_TILE_prev[i]
        if(DEBUG2):
            print A    
            
        #print "=============== s" + str(i)
        # print isl_TILE1[i]
        Z = isl_TILE[i].subtract(isl_TILE1[i])
        Z = Project(Z, sym_exvars)
        Z = Z.intersect(isl_TILE_prev[i].intersect(isl_SETii)).coalesce()
        #print Z
        Z = Z.subtract(Project(C, sym_exvars)).coalesce()
        # A = LT'i intersect ( wszystkie punkty R*(TILE_GTi - ISi))
        Z1 = isl_TILE_GT[i].subtract(isl_IT[i])
        print "===="
        #print Z1.apply(isl_relclosure)
        #print isl_TILE1[i]
        #Z = Project(Z1.apply(isl_relclosure), sym_exvars)
        #print Z
        #Z = Z.intersect(isl_TILE_prev[i]).intersect(isl_SETii)
        A = Z.union(C)
        
        
        isl_REST_new.append(isl_TILE[i].subtract(Project(A.union(isl_TILE1[i]), sym_exvars)).coalesce())
        #print isl_REST_new[i]
        isl_TILE2.append(A)
        #isl_TILE2.append(A.intersect(isl_TILE_LT[i]).coalesce())
        
        if(DEBUG):
            print "TILE2_" + str(i)
            print isl_TILE2[i]
        
        isl_TILEprim.append(isl_TILE2[i].union(isl_BCUR).coalesce())
        if(DEBUG):
            print isl_SETii
        isl_TILEprim[i] = isl_TILEprim[i].intersect(isl_SETii)
        if(DEBUG):
            print "TILEprim_" + str(i)
            print isl_TILEprim[i]

    iR = isl_REST_new[1]
    for i in range(1, len(isl_REST_new)):
        iR = iR.union(isl_REST_new[i]).coalesce()
    iR = iR.apply(isl_relclosure)
    iR = Project(iR, sym_exvars)
    
    iT = isl_TILEprim[1]
    for i in range(1, len(isl_REST_new)):
        iT = iT.union(isl_TILEprim[i]).coalesce()
    iT = Project(iT, sym_exvars)
    
    print iT.intersect(iR).coalesce()
    sys.exit()
    

    if(DEBUG):
        print "============================================================================="
    for i in range(0, len(instrukcje)):
        for ii in range(0,2):
            constr = ""
            if i == 1:
                ubjj = 2
            else:
                ubjj = 1
            for jj in range(0,ubjj):
                if ubjj > 1:
                    constr = " && jj = " + str(jj) 

                bset = isl.BasicSet("[ii,jj] -> {[x, y,z] : ii = "+str(ii)+constr+"}")
                #print "TILE_LT" + str(i)
                #print "ii=" + str(ii) + ",jj=" + str(jj)
                #print isl_TILE_LT[i].intersect(bset).coalesce()
                #print "TILE_GT" + str(i)
                #print "ii=" + str(ii) + ",jj=" + str(jj)
                #print isl_TILE_GT[i].intersect(bset).coalesce()



    #file.write('BLOCK;') 
    
    file.close()
    


    # -------------------------------------------------------
    
    
    '''cmd = barv_script + " < tmp/barv_tiling.txt" 
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    process.wait()
    output = process.stdout.read()
    end = time.time()
    elapsed = end - start
    print "Time taken: ", elapsed, "seconds."  
            
    
    
    lines = output.split("\n")

    if(DEBUG):
        for i in range(0,lines.index('"$#$"')+1):
            lines.pop(0); 
           
    block_set = [] 
    for i in range(0,lines.index('"$$$#$$$"')+1):
        block_set.append(lines.pop(0));
    block_set.pop();
    
           
    lines = filter(lambda x:x!='',lines)              
    #dodaj s1 do petli
    loop = postprocess_loop(lines)
    bl_2half = loop'''
    
    
    #eksperymentalnie 
    if(EXP_CODE):
        loops = TileGen(sym_exvars, vars, _SYM, symb, p_symb, par_tiling, rel, schedule_mode,  instrukcje, stuff_reduced, BLOCK, isl_TILEprim, varsprim, isl_IT, isl_REST_new)
        loop_x = loops[0]
        loop_x = postprocess_loop(loop_x.split('\n'))
        loop = loop_x
    


    #zmienne 
    v = ""
    for s in stuff_reduced:
        v = v + s['var'] + ","
    v = v + "v"
    
    text_file = open("names_info.txt", "w")
    text_file.write(v)
    text_file.close()
    
    #print block_set # tu mozna rozszerzyc

    #pseudokod
    text_file = open("pseudocode.txt", "w")
    text_file.write(loop)
    text_file.close()
    
 
    
    #przywroc instrukcje
    if(EXP_CODE):
        gen.ParsePrint2("tmp/tmp_petit.t", len(sym_exvars))
    else:
        gen.ParsePrint("tmp/tmp_petit.t") 
        

        
    filePaths = glob.glob(plik)
 
    for filePath in filePaths:
        base = os.path.basename(filePath)
        nazwa = os.path.splitext(base)[0] + "_tiling" + os.path.splitext(base)[1]
    
        # usun puste linie i kopiuj
        file = open("out_pseudocode.txt", 'r')
        lines = file.readlines()
        # oryginalny z elsami
        lines_block = lines[:]
        
               
        if par_tiling and not EXP_CODE:
            for i in range(0, len(sym_exvars)):
                lines.insert(0,'register int ' + sym_exvars[i] + 'b=' + sym_exvars[i] + "*" +BLOCK[i] + ";\n")
                
        if par_tiling and EXP_CODE:
            for i in range(0, len(sym_exvars)):
                lines[i] = lines[i].replace('\n', '') + '{ register int ' + sym_exvars[i] + 'b=c'+str(i)+'*' +BLOCK[i] + ";\n"
                lines.append("}\n")
        
        file.close()
        
        #eksperymentalnie 
        if(not EXP_CODE):
            for i in range(0, len(sym_exvars)):
#            lines.insert(i, "for(int "+sym_exvars[i]+"="+stuff[i]['lb']+"; "+sym_exvars[i]+"<="+stuff[i]['ub']+"; "+sym_exvars[i]+"+="+str(BLOCK[i])+"){\n")       
                lines.insert(i, "for(int "+sym_exvars[i]+"=0; "+sym_exvars[i]+"<=floord("+stuff[i]['ub']+"-"+stuff[i]['lb']+","+str(BLOCK[i])+"); "+sym_exvars[i]+"++){\n")
                lines.append("}\n")
        else:
            if par_tiling:
                # do rozwiazania
                for i in range(0, len(sym_exvars)):
                    lines.insert(i, "int fff"+str(i)+"=floord("+stuff[i]['ub']+"-"+stuff[i]['lb']+","+str(BLOCK[i])+");\n")
         
              
        lines = filter (lambda a: a != '\n',lines)
        
        if nodeps==1:
            lines.insert(0, "#pragma omp parallel\n") 

        
        file = open("out_pseudocode.txt", 'w')
        lines = file.writelines(lines)
        file.close()

        shutil.copyfile("out_pseudocode.txt", nazwa)

    '''if(len(loops) == 2):
        tiling_schedule.slice_tiling(loops[1], bl_2half, sym_exvars)
    if(len(loops) == 3): #fs
        tiling_schedule.slice_tiling(loops[2], bl_2half, sym_exvars, 1)'''
    
