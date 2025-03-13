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

class Complex:
    def __init__(self):
        self.symb = []

# nowosc isl w pythonie do testow
import islpy as isl
ctx = isl.Context()

schedule_mode = 0

barv_script = "~/barvinok-0.36/iscc"


DEBUG = False

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
        
    for i in range(dane["nest"], len(sym_exvars)):
        s = s + sym_exvars[i] + " = 0 && "

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


def MakeBLTandBGT_v2(_SYM, vars, sym_exvars, par_vars, varsprim, exvars, stuff, BLOCK, dane):
    BLT = "_BLT := [" + _SYM
    #  tu trzeba dodac zmienne iib, jjb dla spar. tilingu
    BLT = BLT[:-1] + "] -> {["
    for s in vars:
        BLT = BLT + s + ","
    BLT = BLT + 'v' + '] : (( '
    BGT = BLT.replace('_BLT :=', '_BGT :=')
    n = dane["nest"]

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
            
    varcon = ") && ("
    for i in range(0,len(dane['st'])):
        varcon = varcon + " v = "+ str(dane['st'][i])
        if(i < len(dane['st'])-1):
            varcon = varcon + " || "
    varcon = varcon + ") "         
            
            
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

def tile(plik, block):
    
    EXP_CODE = True
    TilCompl = Complex()
    
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
            
    if(DEBUG):
        print stuff
    


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
    print "Time taken: ", elapsed, "seconds."  

    dane = dane.split("#")
   
    rel = dane[0]
    rel2 = rel
    
    

    
    dane.remove(rel)  
    dane = list(set(dane))


    
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

    # ISL ================================================================
    isl_rel = isl.Map(str(rel))
    isl_relclosure = isl_rel.transitive_closure()[0].coalesce()
    isl_symb = isl_rel.get_var_names(isl.dim_type.param)
    TilCompl.symb = isl_symb
    
    
    
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




    file = open("tmp/barv_tiling.txt", 'w')
    file.write('R:=' + rel + ';\n')
    
    if(DEBUG):
        file.write('print "R";')
        file.write('R;')
    
    file.write('Rstar:= R^+;');
    
    if(DEBUG):
        file.write('print "Rstar";')
        file.write('Rstar;')
    
   
    find_symb = re.compile("^[^(\]|\{)]*\]");
    if(rel2 == rel):
        tmp = re.findall(find_symb, rel) 
    else:
        tmp = re.findall(find_symb, rel2) 
    
    symb = []
    
    if(len(tmp) > 0):
        symb = tmp[0]
        symb = symb.replace("[", "");
        symb = symb.replace("]", "");
        symb = symb.replace(" ", "");
        symb = symb.split(",");
    
    vars = []  # i
    exvars = []  # ii'
    sym_exvars = []  # ii
    varsprim = []  # i'
    par_vars = [] # iib
    p_vars = [] #iib bez plusa lb
    p_symb = []
    

    
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
        
    #imperf
    #lexarrays = imperf_tile.get_array(instrukcje, sym_exvars, stuff_reduced, symb, _SYM[:-1], BLOCK)
    #print lexarrays 
    
    isl_Bij = ""

    for i in range(0, len(instrukcje)):
        Bij = MakeBij(_SYM, vars, sym_exvars, par_vars, stuff, BLOCK, instrukcje[i])
        
        
        isl_Bij_temp = isl.Set(str(Bij).replace("_Bij := ", ""))
        print isl_Bij
        
        file.write(Bij)
        if(i==0):
            file.write('Bij := _Bij;')
            isl_Bij = isl_Bij_temp
        else:
            file.write('Bij := Bij + _Bij;')
            isl_Bij = isl_Bij.union(isl_Bij_temp).coalesce()

    print isl_Bij
    
    if(DEBUG):
        file.write('print "Bij";')
        file.write('Bij;')
    
    for i in range(0, len(instrukcje)):
        BLGT = MakeBLTandBGT_v2(_SYM, vars, sym_exvars, par_vars, varsprim, exvars, stuff, BLOCK, instrukcje[i])
        file.write(BLGT[0])
        file.write(BLGT[1])
        if(i==0):
            file.write('BLT := _BLT;')
            file.write('BGT := _BGT;')
        else:
            file.write('BLT := BLT + _BLT;')
            file.write('BGT := BGT + _BGT;')
     
    #file.write(BLGT[0])
    
    if(DEBUG):
        file.write('print "BLT";')
        file.write('BLT;')
    
    #file.write(BLGT[1])
    
    if(DEBUG):
        file.write('print "BGT";')
        file.write('BGT;')
    
    file.write('X:= Rstar(BGT);')
    file.write('BCUR:=Bij - X;')
    
    if(DEBUG):
        file.write('print "BCUR";')


    
    file.write('BPREV:= Rstar(BCUR) * BLT;')
    
    if(DEBUG):
        file.write('print "BPREV";')
        file.write('BPREV;')
    
    file.write('BLOCK:= BCUR + BPREV;')

        
    if(DEBUG):
        file.write('print "BLOCK";')
        file.write('BLOCK;')
        file.write('print "$#$";')
    
    file.write('BLOCK;') 
    file.write('print "$$$#$$$";') 
    
    if(schedule_mode):
        file.write('codegen BLOCK;')  
    #file.write('BLOCK;') 
    
    file.close()
    

    # -------------------------------------------------------
    
    
    cmd = barv_script + " < tmp/barv_tiling.txt" 
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    process.wait()
    output = process.stdout.read()
    end = time.time()
    elapsed = end - start
    print "Time taken: ", elapsed, "seconds."  
    

 
    if(DEBUG):
        print output
    
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
    bl_2half = loop
    

    #eksperymentalnie 
    if(EXP_CODE):
        loops = iscc.NewTileGen(block_set, sym_exvars, vars, _SYM, symb, p_symb, par_tiling, rel, schedule_mode)
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
    
 

    if(len(loops) == 2):
        tiling_schedule.slice_tiling(loops[1], bl_2half, sym_exvars)
    if(len(loops) == 3): #fs
        tiling_schedule.slice_tiling(loops[2], bl_2half, sym_exvars, 1)
    
