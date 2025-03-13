#prywatyzacja zmiennych skalarnych

import re




def PrivEng(deps_file):
    linestring = open(deps_file, 'r').read()
    lines = linestring.split('\n')

    _vars = []
    privvars = []
    cand_privvars = []
    priv_st = []
    
    for line in lines:
        info = line.split() 
        if(len(info)>0):
            _vars.append(info[2])
            _vars.append(info[5])
    
    _vars = list(set(_vars))
    
    for var in _vars:
        if not "(" in var and not "..." in var:
            cand_privvars.append(var)
    
    
    for var in cand_privvars:        
        st = []
        add = 1
        for line in lines:
            
            info = line.split() 
            if(len(info)>0):
                if(info[2] == var):
                    st.append([info[1].replace(':', '')])
                    st.append([info[4].replace(':', '')])
       
        stt = []
        for item in st:
            stt.append(int(''.join(item)))

        priv_st.append([var,list(set(stt))])
        mins = min(stt)
        
        for line in lines:
            info = line.split() 
            if(len(info)>0):
                if(info[2] == var and (info[0] == 'anti' and mins == int(''.join(info[1].replace(':', ''))) or info[0] == 'reduce')):
                    add = 0
        
        if(add == 1):            
            privvars.append(var)
    # ------------------------------------
    
    #print privvars
    
    # sprawdz czy po prywatyzacji mozesz zrownoleglic petle badajac zaleznosci raz
    par = 1
    rem_deps = []
    i=0
       
    for line in lines:
            info = line.split() 
            i = i+1
            if(len(info)>0):
                if(info[2] in privvars):
                    if(("+" in info[6]) or ('*' in info[6]) or (re.match("[0-9]", info[6]))): # tylko 0 ?? 
                        rem_deps.append(i)  # dla priv                        
                    continue
                else:
                    if("(0" in info[6]):
                        continue
                    else:
                        par = 0    # nie mozna zrownoleglic od razu
                        
    
    
    # print rem_deps
    



# jesli nie, zaznacz ktore mozna usunac zaleznosc (+) 
    stuff = []
    stuff.append(privvars)
    stuff.append(rem_deps)
    stuff.append(par)
    stuff.append(priv_st)
    
    return stuff

