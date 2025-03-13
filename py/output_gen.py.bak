import re
import os
import sys

import functions

# znajdz zmienne indeksowe w petli
# odczytaj geo i powstawiaj petle, dodaj private
# dodaj naglowki na koncu



def Output_Gen(input_code, Tile):
    par_loops = 0
    #input_code = "test.c"
    content = []
    
    if Tile:
        sufixo = "_tiled"
    else:
        sufixo = "_par"
    
    output_code = os.path.splitext(input_code)[0] + sufixo +  os.path.splitext(input_code)[1]
    
    # print output_code
    
    with open("tmp/geo.txt") as f:
        content = f.readlines()
    
    bounds = []  
    for c in content: 
        pattern = re.compile("\n")
        c = pattern.sub("", c)
        bounds.append(c.split(" "))
    
    
    ifile = open(input_code, 'r')
    array = []
    for line in ifile:
        array.append( line )
    
    ofile = open(output_code, 'w')
    index = 0
    i = 0
    vars = []
    private_vars = []
    
    for item in bounds:
        for j in range(int(index), int(item[0])-1):
            ofile.write(array[j])
            
        
        
        
        if os.path.exists("tmp/C_output_" + str(i) + ".c"):
            with open("tmp/C_output_" + str(i) + ".c") as f:
		par_loops = par_loops + 1;
                content = f.readlines()
                vars = functions.CollectVars_O(content, vars,private_vars)
                
# >>>>> i musi zaweirac pragme by zostawil oryginal!!!!
                
            for line in content:
                #dodaj private vars do pragmu
                ofile.write(line)
        else:
            for j in range(int(item[0])-1, int(item[1])-1):
                ofile.write(array[j])
            
        index = item[1]
        
        i = i+1
        
    for j in range(int(index), len(array)):
        ofile.write(array[j])
        
    ofile.close()
    
    # dodaj definicje zmiennych ( na razie jako globalne)
    
    ofile = open(output_code, 'r')
    array = []
    for line in ofile:
        array.append( line )
    ofile.close()
    
    linedef = "int "   
    for varx in vars:
        linedef = linedef + varx + ",";
        
    
    s1l=list(linedef)
    s1l[len(linedef)-1]=';'
    linedef=''.join(s1l)
    
    ofile = open(output_code, 'w')
    
    if Tile:
        ofile.write('#include <omp.h>\n#include <math.h>\n')
        ofile.write('#define ceild(n,d)  ceil(((double)(n))/((double)(d)))\n')
        ofile.write('#define floord(n,d) floor(((double)(n))/((double)(d)))\n')
        ofile.write('#define max(x,y)    ((x) > (y)? (x) : (y))\n')
        ofile.write('#define min(x,y)    ((x) < (y)? (x) : (y))\n')
    
    ofile.write(linedef + "\n\n")
    if not Tile:
        ofile.write("#include <omp.h>\n")
    for line in array:
        if not("pragma scop" in line or "pragma endscop" in line):
            ofile.write(line)
    ofile.close();

    if(Tile):
        print str(par_loops) + ' loops TILED.'
    else:
        print str(par_loops) + ' loops PARALLELIZED.'
    print output_code + ' generated.'
