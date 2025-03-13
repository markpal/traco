import re
import sys

VARS = []

keywords = ["if", "endif", "for", "endfor", "and", "or", "max", "min", "else", "MAX", "MIN"]

# przetwarza petle
def Loop(loop, extra_ub = 0):

    step = 0
    pattern = re.compile(r"\W*for\W*\(")
    if pattern.match(loop):
        line = pattern.sub("", loop)
        test = re.compile(r";").split(line)
        z1 = re.compile(r"=.*")
        var = z1.sub("",test[0])
        var = var.replace(" ", "")
        z1 = re.compile(r".*=")
        lb = z1.sub("",test[0])

        ub = ""
        z1 = re.compile(r".*<=")
        if(z1.match(test[1])):
            ub = z1.sub("",test[1])
        else:
            z1 = re.compile(r".*<")
            if(z1.match(test[1])):
                ub = z1.sub("",test[1]) + "-1"

        if ub == "":
            z1 = re.compile(r".*>=")
            if(z1.match(test[1])):
                ub = z1.sub("",test[1])
            else:
                z1 = re.compile(r".*>")
                if(z1.match(test[1])):
                    ub = z1.sub("",test[1]) + "+1"

        if(extra_ub != 0):
            ub = ub + " +  " + str(extra_ub)

        if (extra_ub != 0):
                lb = lb + " -  " + str(extra_ub)


        # przerobic na inne zmiany zmiennej indeksowej  += -=

        z1 = re.compile(r".*\+\+")
        
        if z1.match(test[2]):
            step = 1

        z1 = re.compile(r".*\-\-")
        if z1.match(test[2]):
            step = -1
        
        _z = test[2]
        _z = _z.replace(")", "")    
        
        if "+=" in _z:
            _z = _z.replace("+=", "")
            _z = _z.replace(var, "")
            step = _z
            
        if "-=" in _z:
            _z = _z.replace("-=", "")
            _z = _z.replace(var, "")
            step = "-" +_z



        new_loop = "for " + var + " = " + lb + " to " + ub;


        #new_loop += "endfor"
        if step != 1:
            new_loop = new_loop + ' by ' + str(step).replace("{", "")



            
        new_loop = new_loop + " do";
        
        
        stuff = { 'lb' : lb, 'ub' : ub, "var" : var, "step" : step, "new_loop" : new_loop }


        return stuff
    
    return 0

def If_Statement(line):
    tmp = line
    pattern = re.compile(r"\W*if\W*\(")
    if pattern.match(line) or 'else' in line:
        tmp= tmp.replace("{", "")
        tmp= tmp.replace("}", "")
        tmp= tmp.replace("&&", " and ")
        tmp= tmp.replace("||", " or ")
        if 'if' in line:
            tmp = tmp + " then"
        return tmp
    else:
        return ""
    
    
#szuka zmiennych
def CollectVars(varsn, loop1):
    op = r"[_A-Za-z_][_A-Za-z_\d']*"
    new_vars = re.findall(op, loop1)
    for zvar in new_vars:
        if not zvar in keywords:
            VARS.append([zvar, DimVar(zvar, loop1)])
    resulting_list = list(varsn)
    resulting_list.extend(x for x in new_vars if x not in resulting_list)
    return resulting_list 

def CollectVars_O(content, varsn, pvarsn):
    op = r"\W*for\W*\(\W*[_A-Za-z_][_A-Za-z_\d']*"
    for line in content:
        if(re.match(op, line)):
            varx = re.findall(op, line)
            varx = re.compile(r"\W*for\W*\(\W*").sub("", varx[0])
            if varx not in varsn:
                varsn.append(varx)
            pvarsn.append(varx)
    return varsn   #[varsn, pvarsn] potem
    
# pobiera wymiar zmiennej z lini
def DimVar(var, line):
    # dim = var + "\W*\[[^(\=|\<|\>|\+|\-|\*|\/|;)]*"
    line = line.replace("][", ",")

    dim = rf"{var}\[[^\]]*"
    z = re.findall(dim, line)

    if len(z) == 0:
        return 0;
    dim_var = z[0].count(',')+1   
    return dim_var

#pobiera wymiar zmiennej z tablicy (po wczytaniu)
def _DIM(var):
    for item in VARS:
        if(item[0] == var):
            return item[1]
    
# Definitions
def MakeDef(var, dim):
    defv = "integer " + var;
    if dim > 0:
        defv += "("; 
    for i in range(1, dim+1):
        defv += "0:9999," 
        
    defv = re.compile(r",$").sub(")", defv);
    return defv

#przeksztalca funkcje
def ConvertSt(st):


    st = re.compile(r"\]\W*\[").sub(",", st)
    st = re.compile(r"\[").sub("(", st)
    st = re.compile(r"\]").sub(")", st)
    st = st.replace(";", "")
    st = st.replace("%", " mod ")



    return st
