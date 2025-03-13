import re

# --isl-no-ast-build-allow-else

def whites(a):
    return a[0:a.find(a.strip())]

def isl_tab(lines):
    lines2 = []
    tab = ''
    for line in lines:
        if line[-2:] == ';\n':
            lines2.append(tab + '  ' + line)
        else:
            lines2.append(line)
            tab = whites(line)
    return lines2

def Korekta(plik, lines = []):

    if(len(lines) == 0):
        linestring = open(plik, 'r').read()
        lines = linestring.split('\n')
    tab = ''
    lines2 = []
    bloki = []
    
    for line in lines:
        if '#pragma' in line:
            lines2.append(line)
            continue
        tab = whites(line)
        for item in reversed(bloki):
            if item >= len(tab):
                lines2.append(' '*item+'}')
                bloki.remove(item)
        if line[-1:] != ';' and line[-1:] != '{' and not "}" in line and line != '':
            lines2.append(line + " {")
            bloki.append(len(tab))
        else:
            if(line != ''):
                lines2.append(line)
    
    for item in reversed(bloki):
        lines2.append(' '*item)
        bloki.remove(item)
            
    #for line in lines2:
    #   print line
    
    return lines2


