

import re
import os
import sys

import convert_loop

import gen



#sys.exit("Error message")
#import glob
import shutil
import tiling_v2
import tiling_v3
import tiling_v4
import tiling_v5
import time_space_tiling
import tiling
import scc
import iscc
import slicing

import petit_int
      
SIMPLIFY = False
permute = False
rplus_file = ''



# check barvinok
barv_location = os.path.dirname(sys.argv[0]).replace('py', 'barv_script')    
barv_script = open(barv_location, 'r').read().split(' ')[0]

if(not os.path.exists(barv_script)):
    print "Barvinok not found. Please setup the tool or check a path in the file: barv_script"
    sys.exit()
else:
    iscc.barv_script = barv_script 

# delete the previous work
if(os.path.exists('tmp')):
    shutil.rmtree('tmp')
    
if not os.path.exists("tmp"):
    os.makedirs("tmp")
#files = glob.glob('tmp/*')
#for f in files:
#    os.remove(f)

if len(sys.argv) == 2:
    print 'Usage PAR:\n issf input_file.c [--codegen=0,1,2 --tc=0,1,2, --silent=0,1 (moredebug in  tmp/debug.txt)]'
    print 'Usage TILE:\n --tile (source to source), experimental: --tiling3, --tiling5, --permute'
    print 'Usage PAR+TILE:\n --partile (source to source)'
    print 'Usage (other):\n --scc, --simplify (slow polyhedral hull for better code), --slicing, --fs, --acc, --scop'
    sys.exit()
    

if not os.path.exists(sys.argv[1]):
    print 'File not found'
    sys.exit()






linestring = open(sys.argv[1], 'r').read()

rpath = sys.argv[2]
gen.SetPath(rpath, sys.argv)
gen.rpath = rpath

block = '16'
rplus_mode = ''

if('--simplify' in sys.argv):
    SIMPLIFY = True

scop = False
acc = False  # OpenACC suport



for item in sys.argv:
    if "--scop" in item:
        scop = True

for item in sys.argv:
    if "--acc" in item:
        acc = True
        print 'OpenACC mode enabled'

for item in sys.argv:
    if "--petit" in item:
        petit_int.Dep_Analysis(sys.argv[1])
        sys.exit()


if len(sys.argv) > 3:
    if('--tiling' in sys.argv[3] or '--partile' in sys.argv[3] or '--tile' in sys.argv[3] or '--slicing' in sys.argv[3] or '--fs' in sys.argv[3] or '--tstile' in sys.argv[3]):

        perfect_mode = False
        if(len(sys.argv) >= 5):
            if('--perfect' in sys.argv[4]):
                perfect_mode = True

        

        for i in range(4, len(sys.argv)):
            if('--permute' in sys.argv[i]):
                permute = True
            if('--rplus' in sys.argv[i]):
                rplus_file = sys.argv[i].replace('--rplus=', '')
                rplus_mode = rplus_file


        if('=' in sys.argv[3]):
            line_tmp = sys.argv[3].replace('--tiling=', '')
            line_tmp = line_tmp.replace('--tile=', '')
            line_tmp = line_tmp.replace('--tiling2=', '')
            line_tmp = line_tmp.replace('--tiling3=', '')
            line_tmp = line_tmp.replace('--tiling5=', '')
            line_tmp = line_tmp.replace('--partile=', '')
            line_tmp = line_tmp.replace('--tstile=', '')
            if(line_tmp != ''):
                block = line_tmp
        #dla imperfectly
        if('--tiling2' in sys.argv[3]):
            tiling_v2.tile(sys.argv[1], block)
            sys.exit()


        partile = '--partile' in sys.argv[3];

        if('--tiling3' in sys.argv[3] or partile):
            tiling_v3.tile(sys.argv[1], block, permute, "", "0", SIMPLIFY, perfect_mode, partile, rplus_file)
            sys.exit()

        if('--tiling5' in sys.argv[3] or partile):
            tiling_v5.tile(sys.argv[1], block, permute, "", "0", SIMPLIFY, perfect_mode, partile, rplus_mode)
            sys.exit()

        if('--tstile' in sys.argv[3] or partile):
            time_space_tiling.tile(sys.argv[1], block, permute, "", "0", SIMPLIFY, perfect_mode, partile, rplus_mode)
            sys.exit()

        if('--tile' in sys.argv[3] or partile):
            tiling_v4.tile(sys.argv[1], block, permute, "", "0", SIMPLIFY, perfect_mode, partile, rplus_file)
            sys.exit()
            
        if('--slicing' in sys.argv[3]):
            slicing.sfs(sys.argv[1],0, SIMPLIFY, 0, acc)
            sys.exit()

        # fs bez rk
        if('--fsnew' in sys.argv[3]):
            slicing.sfs(sys.argv[1],0, SIMPLIFY, 2, acc)
            sys.exit()

        if('--fs' in sys.argv[3]):
            slicing.sfs(sys.argv[1],0, SIMPLIFY, 1, acc)
            sys.exit()


        
        if('--tiling' in sys.argv[3]):
            tiling.tile(sys.argv[1], block)
            sys.exit()
            
        gen.tile_stuff = [block, permute]
        

sm = " --nomenu=1 --path_issf=" + gen.path_issf + " "
if len(sys.argv) > 3:
    for i in range(3, len(sys.argv)):
        sm = sm + " " + sys.argv[i] + " "
    gen.silent_mode = sm 




lines = linestring.split('\n')

i = 0;
loop_lines = []
loops = []
kl = 0
in_loop = 0
geo = []
count_loop = 0




for line in lines:
    if scop:
        break
    else:
        i = i + 1
        
        find_loop = re.compile("(\W+|^)for");
        
        if(in_loop == 0):
            if(find_loop.match(line)):
                loop_lines = []
                in_loop = 1
                loop_lines.append(line)
                geo.append([i,0])
                kl = kl + line.count("{")
		count_loop = count_loop + 1
                if(kl==0 and line.count(";") > 2):
                    in_loop = 0;  
                    geo[-1][1] = i  #-1 last element of list
                    loops.append(loop_lines)
                kl = kl - line.count("}")
                if(kl == 0 and line.count(";")>=3):
                    in_loop = 0; 
                    geo[-1][1] = i
                    loops.append(loop_lines)
                continue
            
                
                 
                    
        if(in_loop == 1):
            loop_lines.append(line)
            kl = kl + line.count("{")
            if(kl==0 and line.find(";") and not find_loop.match(line)):
                in_loop = 0;    
                geo[-1][1] = i
                loops.append(loop_lines)
            kl = kl - line.count("}")
            if(in_loop == 1 and kl == 0 and not find_loop.match(line)):
                in_loop = 0;   
                geo[-1][1] = i
                loops.append(loop_lines)


#for line in loop_lines:
#    print line
    


if scop:
    loops = []
    loop_lines = []
    in_loop = 0
    geo = []
    count_loop = 0
    i = 0;
    for line in lines:
        i = i + 1
        if "#pragma scop" in line:
            loop_lines = []
            geo.append([i,0])
            in_loop = 1
        if "#pragma endscop" in line:
            in_loop = 0
            geo[-1][1] = i
            loops.append(loop_lines)
            count_loop = count_loop + 1
        if(in_loop == 1):
            loop_lines.append(line)


    


i = 0   

for loop in loops:

    try:
        file = open("tmp/C_loop_" + str(i) + ".c", 'w')
        for line in loop:
            file.write(line + "\n")
        file.close()
    except IOError:
        print 'Coulnt save to file'
    petit_loop = convert_loop.convert_loop(loop)
    try:
        file = open("tmp/petit_loop_" + str(i) + ".t", 'w')
        file.write("integer xxyyyx" + "\n")
        for line in petit_loop:
            file.write(line + "\n")
        file.close()
    #LD loop
        file = open("tmp/LD_petit_loop_" + str(i) + ".t", 'w')
        file.write("integer xxyyyx" + "\n")
        in_loop = 0
        for line in petit_loop:
            if('for ' in line):
                in_loop = 1
            if in_loop == 0:
                file.write(line + "\n")  
            else:
                if (('for' in line) or ('if ' in line) or (line.isspace())): 
                    file.write(line + "\n")  
                else:
                    file.write("xxyyyx = 1" + "\n")      
        file.close() 
    except IOError:
        print 'Coulnt save to file'
    i = i+1
    try:
        file = open("tmp/geo.txt", 'w')
        for item in geo:
            file.write(str(item[0]) + " " + str(item[1]) + "\n")
        file.close()
    except IOError:
        print 'Coulnt save to file'

print str(count_loop) + ' loops found.';


s = 0
if len(sys.argv) > 3:
    if('--scc' in sys.argv[3]):
        s = 1
        
gen.Gen(sys.argv[1],s,permute);
