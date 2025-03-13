#!/usr/local/bin/python

import sys
import correct

linestring = open(sys.argv[1], 'r').read()

lines = linestring.split('\n')

lines2 = []
fg = 0
c = 0
par_uds = 0
noconvert = 0
for line in lines:
    if "IND loop" in line:
        noconvert = 1
    if "// UDS loop ---" in line:
        par_uds = 1
    if "// FS loop ---" in line:
        par_uds = 0
    if par_uds == 1 and (('for(t' in line) or ('for(c' in line)):
        lines2.append("#pragma omp parallel for\n")
        par_uds = 0
    if (('for(t' in line) or ('for(c' in line))  and not('for(t1' in line) and not('for(c0' in line) and (fg == 0) and (noconvert == 0):
        lines2.append("#pragma omp parallel for\n")
        fg = 1
    if fg == 1 and '{' in line:
        c = c +1
    if fg == 1 and '}' in line:
        c = c -1    
    if c ==0 and fg == 1:
        fg = 0
    lines2.append(line + "\n")

if(len(sys.argv) == 2):    
    lines2 = correct.isl_tab(lines2)

file = open(sys.argv[1], 'w')
for line in lines2:
    if line != '\n':
        file.write(line)
file.close()


