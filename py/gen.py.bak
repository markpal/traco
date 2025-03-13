import re
import os
import sys

import output_gen

import subprocess
import priv_engine
import reduce

import loop_tools

import parfine



import scc




from easyprocess import Proc
import tiling_v3
from multiprocessing import Pool



# zainstalowac python-pip, pip install easyprocess

rpath = ""

# moze wywalic te apostrofy z kodu przy zmiennych

PAR_ALWAYS = 0

path_issf = os.path.dirname(os.path.realpath(__file__))[:-3]


path_framework = path_issf + "/framework/obj/framework "
path_oc = path_issf + "/omega_calc/obj/oc "
path_petit = path_issf + "/petit/obj/petit -g -4 "
path_petit_rel = path_issf + "/petit/obj/petit -bg -4 "
silent_mode = " --silent=1 --nomenu=1 --tc=1 --codegen=0 --path_issf=" + path_issf
out_command = " --output_C="

tile_stuff = []

# wstawia pragmach private zmienne

def SetPath(r, arg):
    rpath = r 
    path_framework = r + "/framework/obj/framework "
    path_petit = r + "/petit/obj/petit -g -4 "

   # silent_mode = " --silent=1 --tc=1 --codegen=0 --fs_pragma=" + r

def CorrectFile(name, priv_vars_extra, reduce_op):

    file = open(name, 'r')
    lines = file.readlines()
    
    #popraw apostrofy
    pattern = re.compile('t\d+\'')
    for i in range(0, len(lines)-1):
        varsx = pattern.findall(lines[i])
        for varx in varsx:
            _vx = varx.replace('\'', '_')
            lines[i] = lines[i].replace(varx, _vx)


    
    _sz = 0
    priv_vars = []
    i = 0
    brac = 0
    
    
    for i in range(0, len(lines)-1):
        lines[i] = lines[i].replace("\n", "")
        pattern = re.compile("\\bint\\b\\s*")
        lines[i] = pattern.sub("", lines[i])

    
    i = 0

    for line in lines:
        if "#pragma omp parallel for" in line:
            _sz = 1
            priv_vars = []
            pragma_line = i
            i = i + 1
            continue
        if(_sz == 1 and ("for(" in line or "for (" in line)):            
            op = "for\W*\([A-Za-z_]+[A-Za-z\d_']*"   
            _var = re.findall(op, line)

            _var[0] = _var[0].replace("for(", "")
            _var[0] = _var[0].replace("for (", "")
            priv_vars.append(_var[0])
        if(_sz == 1 and "{" in line):
            brac = brac + 1
        if(_sz == 1 and "}" in line):
            brac = brac - 1
            
        if(_sz == 1 and brac == 0):
            _str = ""
            priv_vars = list(set(priv_vars))
            for v in priv_vars:
                _str = _str + v + ","
                
 # dodaj priv z prywatyzacji skalarow
            for v in priv_vars_extra:
                _str = _str + v + ","                 
                
            _str = _str[:-1]
            
          
            
            _str = _str + ")"
            lines[pragma_line] = lines[pragma_line] + " private(" + _str + ' ' + reduce_op
            _sz = 0

   
    
        i = i + 1

        


    b = 0   
    noi = 0


    for i in range(0, len(lines)-1):
 
        if('{' in lines[i]):
            b = b+1
            if b==1 :
                noi = 1 # nie przesuwaj lini z pierwsza klamra
        if('}' in lines[i]):
            b = b-1
 
        if(len(lines[i]) > 0 ):
            if(b > 0 and lines[i][0] != ' ' and lines[i][0] != '' and noi == 0):
                for j in range(0,2*b):
                    lines[i] = ' ' + lines[i]
        
        noi = 0      
        lines[i] = lines[i] + "\n"
        

    
    _file = open(name, 'w')
    lines = _file.writelines(lines)  
    _file.close()
    
    
              
# ---------------------------------------------------------


def IND_Gen(inp, LD_inp, IND_loop):
 #LD IND LOOP
    line_r=Proc(path_framework + " " + inp + " --return=1 " +  silent_mode ).call(timeout=5).stdout
    line_ld=Proc(path_framework + " " + LD_inp + " --return=1 " +  silent_mode ).call(timeout=5).stdout
    #line_r = line_r.replace("\n", "")
    line_ld = line_ld.replace("\n", "")
    
#    fo = open("tmp/debug.txt", "wt")
#    fo.write(line_r);
#    fo.close()

    
    symb = ""
    if("Sym" in line_r):
        pattern = re.compile('Sym=.[^\]]*')
        symb = pattern.findall(line_r)
       # print symb
        symb =  symb[0].replace("Sym=[", "")
        
  #  print symb
        
    script_lines = []
    if(symb != ""):
        script_lines.append("symbolic " + symb + ";")
    
    #pattern = re.compile('====.*$')
    #RSPACE = pattern.findall(line_r)
    rss = line_r.split('====')[1]
    ldd = line_ld.split('====')[1]


    script_lines.append("RS := " + rss + ";")

    LD = pattern.findall(line_ld)
  #  print LD
    
    script_lines.append("LD := " + ldd + ";")
    script_lines.append("RS_S := domain RS union range RS;")
    script_lines.append("LD_S := domain LD union range LD;")
    script_lines.append("codegen LD_S - RS_S;")
    
    thefile = open("tmp/ld_script_oc", 'w')
    for item in script_lines:
        thefile.write("%s\n" % item)
    thefile.close();  
    
    output = Proc(path_oc + " " + "tmp/ld_script_oc").call(timeout=5).stdout
    
    output = output.split("\n")
    output2 = []
    was =0
    for item in output:
        if len(item) > 0: 
            if(item[0] != '#'):
                if('for' in item and was == 0):
                    output2.append("#pragma omp parallel for")
                    was = 1
                if not item.isspace():   # nie zapisuj pustych linii
                    output2.append(item)

    if(len(output2) > 0):   # jesli jest co zapisac IND
        thefile = open(IND_loop, 'w')
        for item in output2:
            thefile.write("%s\n" % item)
        thefile.close();         




def Tile_loop(i):
    outp = "tmp/C_output_" + str(i) + ".c"
    source_loop = "tmp/C_loop_" + str(i) + ".c"
    tiling_v3.tile(source_loop, tile_stuff[0], tile_stuff[1], outp, str(i))
    return ""

def Gen(file_C, _scc, permute):
    # wywolaj esys


    z = 0
    with open("tmp/geo.txt") as f:
        content = f.readlines()
        z = len(content)
    
    Tile = False
    if len(tile_stuff) > 0:
        Tile = True
        
    if Tile:
        l = []
        for i in range(0, z):
            l.append(i)
        p = Pool(z)
        p.map(Tile_loop, l)
        
    for i in range(0, z):
        inp = "tmp/petit_loop_" + str(i) + ".t"
        LD_inp = "tmp/LD_petit_loop_" + str(i) + ".t"
        IND_loop = "tmp/IND_petit_loop_" + str(i) + ".t"
        outp = "tmp/C_output_" + str(i) + ".c"
        source_loop = "tmp/C_loop_" + str(i) + ".c"
        
        
        #tile
        if(Tile) > 0:
            #tiling_v3.tile(source_loop, tile_stuff[0], tile_stuff[1], outp)
            continue
       
        
        # zapisz zaleznosci w pliku desp.txt
        cmd = path_petit + " " + inp + " > tmp/deps"+str(i)+".txt"
        process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        process.wait()
        
        # dopisz spmd.c
        cmd = path_petit + " -W " + inp
        process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        process.wait()

        # zapisz zaleznosci w pliku _desp.txt dla tewi
        cmd = path_petit + " -b " + inp + " > tmp/_deps"+str(i)+".txt"
        process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        process.wait()
        
        if _scc==1:
            scc.GenerateSCC(i, permute)
            sys.exit() 
            
        scc.DepGraph(i)
        
        
        priv_stuff = priv_engine.PrivEng("tmp/deps"+str(i)+".txt")
        #print "tmp/deps"+str(i)+".txt"
        #remove deps
        _str = ''
        #print priv_stuff
        if len(priv_stuff[1]) > 0: 
            _str = " --rem_deps="
            for v in priv_stuff[1]:
                _str = _str + str(v) + ","                 
            _str = _str[:-1]

        reduce_op = reduce.Reduction("tmp/deps"+str(i)+".txt")
        if((reduce_op == '' and priv_stuff[2] == 0) or PAR_ALWAYS):     # no par, use framework
            
            # IND Loop
            try:
                IND_Gen(inp, LD_inp, IND_loop)
            except:
                print 'IND loop was not calculated'

            # PARALLELIZE LOOPS
            
            cmd = path_framework + " " + inp + " " + out_command + outp + " " + silent_mode + " --fs_pragma=" + rpath + " " + _str + " --ind_loop=" + IND_loop    
            #process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            #process.wait()
            stdout=Proc(cmd).call(timeout=5).stdout
            
            fo = open("tmp/debug.txt", "at")
            fo.write(stdout.encode('ascii', 'ignore'))
            fo.close()
        else:
            _file = open(outp, 'w')
            _file.write("#pragma omp parallel for")
            _file.close()

        

        
        
        if os.path.exists("tmp/C_output_" + str(i) + ".c"):
            
            # gdy nie ma zaleznosci
            file = open("tmp/C_output_" + str(i) + ".c", 'r')
            lines = file.readlines()
            file.close()
            
            if len(lines) == 1 and "#pragma" in lines[0]:
                file = open("tmp/C_loop_" + str(i) + ".c", 'r')
                lines2 = file.readlines()
                file.close()
                
                file = open("tmp/C_output_" + str(i) + ".c", 'w')
                lines[0] = lines[0] +"\n"
                file.writelines(lines)
                file.writelines(lines2)
                file.close()
            # --------------------
            
            #sprawdz czy nie ma samej pragmy jak tak to skopiuj pliki dodaj pragmy z private
            CorrectFile("tmp/C_output_" + str(i) + ".c", priv_stuff[0], reduce_op)  
            loop_tools.CorrectLoop("tmp/C_output_" + str(i) + ".c") 
        else:
            parfine.ParInner(i);
    
    # wywolaj output_gen
    output_gen.Output_Gen(file_C, Tile)

# wyswietla R dla Barvinoka
def RelPrint(file, only_tiling=0):
    cmd = path_framework + " " + file + " --relation_print --silent=1" 
    if only_tiling==1:
        cmd = cmd + " --no_sources=1" 
    print cmd
    return Proc(cmd).call(timeout=25).stdout

def RelPrint_WithPriv(file, deps_to_remove):
    deps = ""
    for s in deps_to_remove:
       deps = deps + str(s) + ","
    deps = deps[:-1]
    cmd = path_framework + " " + file + " --relation_print --silent=1 --no_sources --rem_deps=" + deps
    print cmd
    return Proc(cmd).call(timeout=3600).stdout
 
# przywraca orgynialne instrukcje
def ParsePrint(file):
    cmd = path_framework + " " + file + " --parse_print --silent=1"    
    return Proc(cmd).call(timeout=5).stdout

# przywraca orgynialne instrukcje - nieuzywane
def ParsePrint2(file, z):
    cmd = path_framework + " " + file + " --parse_print="+str(z)+" --silent=1"    
    return Proc(cmd).call(timeout=5).stdout
 


def Petit_Rel(file):
    cmd = path_petit_rel + " " + file
    return Proc(cmd).call(timeout=5).stdout