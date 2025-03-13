import re
import string


def Reduction(deps_file):
    linestring = open('spmd.c', 'r').read()
    lines = linestring.split('\n')
    
    reduce = ''
    vars = ''
    zmienne = []
    
    for line in lines:
        if 'reduce_sum_int' in line:
            
            l = line.replace('reduce_sum_int(&', '')
            
            pattern = re.compile(",.*")
            
            l = pattern.sub('', l)
            l = l.replace(' ', '')
            
            
            if(reduce != '+' and reduce != ''):
                print 'error'
                
            reduce = '+'
            
            if(vars != ''):
                vars = vars + ','
            vars = vars + l
            zmienne.append(l)
        if 'reduce_product_int' in line:
            
            l = line.replace('reduce_product_int(&', '')
            
            pattern = re.compile(",.*")
            
            l = pattern.sub('', l)
            l = l.replace(' ', '')
            
            
            if(reduce != '*' and reduce != ''):
                print 'error'
                
            reduce = '*'
            
            if(vars != ''):
                vars = vars + ','
            vars = vars + l
            zmienne.append(l)
    reduce = 'reduction(' + reduce + ' : ' + vars + ')'

    if(vars == ''):
	reduce = ''    


    # sprawdz vars w deps.txt
    linestring = open(deps_file, 'r').read()
    lines = linestring.split('\n')
    
    _vars = []
    
    for line in lines:
        info = line.split() 
        if(len(info)>0):
            _vars.append(info[2])
            _vars.append(info[5])
    
    _vars = list(set(_vars))

    if _vars != zmienne:
        reduce = '';
    
    return reduce
            
            
