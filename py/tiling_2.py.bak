import convert_loop
import functions
import gen
import subprocess
import re
import sys
import glob, os
import shutil
import loop_tools

barv_script = "~/barvinok-0.36/iscc"


DEBUG = False

def CreateLex(array1, array2, n):
    #n = len(array1)
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
        
# zaleznosci w relacjach
def Constraint(vars, sym_exvars, stuff, BLOCK, dane):
    s = ""
    for i in range(0,dane["nest"]): # len(vars)
#        s = s + sym_exvars[i] + '<= ' + vars[i] + '<= ' + sym_exvars[i] + '+' + str(BLOCK[i]) + '- 1, ' + stuff[i]['ub'] + ' && ';
       s = s + sym_exvars[i] + '*' + str(BLOCK[i]) +  ',' + stuff[i]['lb']  + '<= ' + vars[i] + '<= ((' + sym_exvars[i] + '+1)*' + str(BLOCK[i]) + '- 1), ' + stuff[i]['ub'] + ' && ';
       
    #for i in range(dane["nest"], len(vars)):
     #   s = s + vars[i] + " = 1 && "
        
    #for i in range(dane["nest"], len(sym_exvars)):
    #    s = s + sym_exvars[i] + " = 0 && "

    return s


def MakeBij(_SYM, vars, sym_exvars, stuff, BLOCK, dane):   
    Bij = "_Bij := [";
    Bij = Bij + _SYM        
    Bij = Bij[:-1] + "] -> {["
    
    #for s in sym_exvars:
    for i in range(0, dane["nest"]):
        Bij = Bij + sym_exvars[i] + ","
    
    #for s in vars:
    for i in range(0, dane["nest"]):
        Bij = Bij + vars[i] + ","
        
    for i in range(dane["nest"]-1, len(sym_exvars)):
        Bij = Bij + "-1,"
        
    Bij = Bij + 'v' + '] : '
    Bij = Bij + Constraint(vars, sym_exvars, stuff, BLOCK,dane)
           
    for i in range(0, dane["nest"]):
        Bij = Bij + sym_exvars[i] + ">=0 && "
        Bij = Bij + BLOCK[i] + "*" + sym_exvars[i] + "<=" + stuff[i]['ub'] +" && "
        
    Bij = Bij + "("
    
    for i in range(0,len(dane['st'])):
        Bij = Bij + " v = "+ str(dane['st'][i])
        if(i < len(dane['st'])-1):
            Bij = Bij + " || "
        
    Bij = Bij + ")};"
    return Bij


def MakeBLTandBGT(_SYM, vars, sym_exvars, varsprim, exvars, stuff, BLOCK, dane):   
    BLT = "_BLT := [" + _SYM
    BLT = BLT[:-1] + "] -> {["
    
#    for s in sym_exvars:
#       BLT = BLT + s + ","
        
#   for s in varsprim:
#       BLT = BLT + s + ","
 
#for s in sym_exvars:
    for i in range(0, dane["nest"]):
        BLT = BLT + sym_exvars[i] + ","
    
#for s in vars:
    for i in range(0, dane["nest"]):
        BLT = BLT + varsprim[i] + ","
        
    for i in range(dane["nest"]-1, len(sym_exvars)):
        BLT = BLT + "-1,"
        
    BLT = BLT + 'v' + '] : Exists ( '
    
   # for s in exvars:
    #    BLT = BLT + s + ","
        
    for i in range(0, dane["nest"]):
        BLT = BLT + exvars[i] + ","
    
    for i in range(0, dane["nest"]):
        BLT = BLT + vars[i] + ","

    #for s in vars:
    #    BLT = BLT + s + ","
        
    BLT = BLT[:-1] + ": "
    
    BLT = BLT + Constraint(vars, sym_exvars, stuff, BLOCK,dane)
    
    for i in range(0, dane["nest"]):
        BLT = BLT + sym_exvars[i] + ">=0 && "
        BLT = BLT + BLOCK[i] + "*" + sym_exvars[i] + "<=" + stuff[i]['ub'] +" && "
        
    for i in range(0, dane["nest"]):
        BLT = BLT + exvars[i] + ">=0 && "
        BLT = BLT + BLOCK[i] + "*" + exvars[i] + "<=" + stuff[i]['ub'] +" && "
        
    BLT = BLT + Constraint(varsprim, exvars, stuff, BLOCK,dane)
    
    BLT = BLT + "("
    for i in range(0,len(dane['st'])):
        BLT = BLT + " v = "+ str(dane['st'][i])
        if(i < len(dane['st'])-1):
            BLT = BLT + " || "
    BLT = BLT + ") && "

    BGT = BLT.replace('_BLT :=', '_BGT :=')
    
    BLT = BLT + CreateLex(sym_exvars, exvars, dane["nest"]) + ")};"
    BGT = BGT + CreateLex(exvars, sym_exvars, dane["nest"]) + ")};" 
    
    BLGT = []
    BLGT.append(BLT)
    BLGT.append(BGT)  
    
    return BLGT 
    


def tile(plik, block):
    
    BLOCK = block.split(',')
    for i in range(len(BLOCK),10):
        BLOCK.append(BLOCK[len(BLOCK)-1])
        

    linestring = open(plik, 'r').read()
    lines = linestring.split('\n')
    
    petit_loop = convert_loop.convert_loop(lines)
    file = open("tmp/tmp_petit.t", 'w')
    
 
    for line in petit_loop:
        file.write(line + '\n')
    file.close()
    
    
    lines = linestring.split('\n')
    stuff = []
    
    for line in lines:
        if 'for' in line:
            stuff.append(functions.Loop(line));
            
    if(DEBUG):
        print stuff
    
    #pobierz relacje zaleznosci
    dane = gen.RelPrint("tmp/tmp_petit.t")
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
    if(rel == ''):
        rel = "{["
        for i in range(0,len(stuff)):
            rel = rel + "i" + str(i) + ","
        rel = rel + "v] -> ["
        for i in range(0,len(stuff)):
            rel = rel + "i" + str(i) + "',"
        rel = rel + "v'] : false }"
        loop_tools.MakeLDPetit("tmp/tmp_petit.t", "tmp/tmp_ld_petit.t")
        dane = gen.RelPrint("tmp/tmp_ld_petit.t")
        dane = dane.split("#")
        rel2 = dane[0]
        dane.remove(rel2)
        dane = list(set(dane))
        
    print dane
    instrukcje = loop_tools.ReadStatementNests("tmp/tmp_petit.t", dane)
    #print instrukcje

   
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
    
    for s in stuff:
        vars.append(s['var']);
        sym_exvars.append(s['var']*2);
        exvars.append(s['var']*2+"'");
        varsprim.append(s['var']+"'");
   
    _SYM = ""
            
#    for s in sym_exvars:
#        _SYM = _SYM + s + ","

    for s in symb:
        _SYM = _SYM + s + ","

    
    for i in range(0, len(instrukcje)):
        Bij = MakeBij(_SYM, vars, sym_exvars, stuff, BLOCK, instrukcje[i])
        file.write(Bij)
        if(i==0):
            file.write('Bij := _Bij;')
        else:
            file.write('Bij := Bij + _Bij;')

    
    if(DEBUG):
        file.write('print "Bij";')
        file.write('Bij;')
    
    for i in range(0, len(instrukcje)):
        BLGT = MakeBLTandBGT(_SYM, vars, sym_exvars, varsprim, exvars, stuff, BLOCK, instrukcje[i])
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
    
    file.write('codegen BLOCK;')  

    
    file.close()
    
    # -------------------------------------------------------
    
    
    
    cmd = barv_script + " --isl-no-tile-scale-tile-loops < tmp/barv_tiling.txt " 
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    process.wait()
    output = process.stdout.read()
    
    #file = open("tmp/barv_tiling2.txt", 'w')
    #file.write('BLOCK:=' + output + ';\n')
    #file.write('codegen BLOCK;\n')
    #file.close()
    
    #cmd = barv_script + " < tmp/barv_tiling2.txt --isl-no-coalesce-bounded-wrapping" 
    #process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    #process.wait()
    #output = process.stdout.read()
    

    
    if(DEBUG):
        print output
    
    lines = output.split("\n")

    if(DEBUG):
        for i in range(0,lines.index('"$#$"')+1):
            lines.pop(0); 
        
    lines = filter(lambda x:x!='',lines)   
    
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
        
 
#zmienne 
    v = ""
    for s in stuff:
        v = v + s['var'] + ","
    v = v + "v"
    
    text_file = open("names_info.txt", "w")
    text_file.write(v)
    text_file.close()
    
    #pseudokod
    text_file = open("pseudocode.txt", "w")
    text_file.write(loop)
    text_file.close()
    #przywroc instrukcje
    gen.ParsePrint("tmp/tmp_petit.t")
    filePaths = glob.glob(plik)
 
    for filePath in filePaths:
        base = os.path.basename(filePath)
        nazwa = os.path.splitext(base)[0] + "_tiling" + os.path.splitext(base)[1]
    
        # usun puste linie i kopiuj
        file = open("out_pseudocode.txt", 'r')
        lines = file.readlines()
        file.close()
        
#        for i in range(0, len(sym_exvars)):
#            lines.insert(i, "for(int "+sym_exvars[i]+"="+stuff[i]['lb']+"; "+sym_exvars[i]+"<="+stuff[i]['ub']+"; "+sym_exvars[i]+"+="+str(BLOCK[i])+"){\n")       
#            lines.insert(i, "for(int "+sym_exvars[i]+"=0; "+sym_exvars[i]+"<=floord("+stuff[i]['ub']+","+str(BLOCK[i])+"); "+sym_exvars[i]+"++){\n")
#            lines.append("}\n")
              
        lines = filter (lambda a: a != '\n',lines)
        
        file = open("out_pseudocode.txt", 'w')
        lines = file.writelines(lines)
        file.close()

        shutil.copyfile("out_pseudocode.txt", nazwa)
    

    
    
    
    
