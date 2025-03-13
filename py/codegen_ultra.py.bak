# ta funkcja wylowala codegen i ustawi odpowiednio instrukcje
# opis w bugu traco
# moze kiedys andrea doda codegen do islpy :)

import iscc
import islpy as isl
import re
ctx = isl.Context()

#islset ze stringa
#instrukcje mozna je popbrac z petli petita
#offset dla tilingu, fs
# ReadStatementNests

# to wszystko dziala albo moze dzialac ale ja nie mam czasu tyle co skimo :)
 
# for(i=1; i<=n; i++){ 
#  for(j=1; j<=n; j++){ 
#    a[i][j] = a[i][j-1];
#  }
#  a[i][1] = 0;
#} 



########################################################################

#def printASTAsC(ast):
#  p = isl.Printer.to_str(ast.get_ctx())
#  p = p.set_output_format(isl.format.C)
#  p = p.print_ast_node(ast)
#  print(p.get_str())


#context = isl.Set("{ : }")
#domain = isl.Set("[T,N] -> { S[t,i] : 1<=t<=T and 1<=i<=N }")
#schedule = isl.Map("[T,N] -> { S[t,i] -> [t,i+t] }")
#schedule_domain = schedule.intersect_domain(domain)


#build = isl.AstBuild.from_context(context)
#ast = build.node_from_schedule_map(schedule.intersect_domain(domain))
#printASTAsC(ast)


#https://www.grosser.es/tutorials/polyhedral-ast-generation.html
########################################################################

def codegen(islSet, instrukcje, offset, vars, symexvars):
    # wyszukaj instrukcje z relacji
    # 0 0 
    # 1 0 # inkrementuj ostatni zeruj dalsze

    licznik = [0] * len(symexvars)
    isl_R = ""

    first = 1
    for item in instrukcje:
        if(first != 1):
            licznik[len(item['path'])-1] = licznik[len(item['path'])-1] + 1
            for i in range(len(item['path']), len(symexvars)):
                licznik[i] = 0

        #print licznik
        # buduj relacje
        # R = {[vars, ..., v] -> [licznik, vars, licznik, vars, v] : v nalezy do st } 
        R = "{[" + ','.join(symexvars) + "," + ','.join(vars) + ',v] -> [' + ','.join(symexvars) + ","
        for i in range(0, len(licznik)):
            R = R + str(licznik[i]) + ',' + vars[i] + ','
        R = R + 'v] : '
        
        for v in item['st']:
            R = R + 'v = ' + str(v) + ' or '
        R = R[:-3] + "}"
        
        if(first == 1):
            isl_R = isl.Map(str(R)).coalesce()
            first = 0
        else:
            isl_R = isl_R.union(isl.Map(str(R))).coalesce()
            
    isl_S = islSet.apply(isl_R).coalesce() 

    loop = iscc.iscc_communicate("L :=" + str(isl_S) + "; codegen L;")
    
    # zamien z powrotem s1
    lines = loop.split("\n")[:-1]
    loop2 = ""
    st = ""
    for i in range(0,len(lines)):
        tmp = lines[i]
        pattern = re.compile("^\W*\(")  # w przyszlosci moga byc s1 S1 s2 S2
        if pattern.match(tmp):
            tmp = tmp.split(",")
            count = len(symexvars) + len(vars)*2 
            tmp2 = []
            j = 0
            
            for i in range(0, count+1):
                if i >= len(symexvars) and i <= count -1:  # nie ruszaj symexvars
                    j = j+1
                    if(j % 2):
                        continue  # nie dodawaj tych
                    else:
                        tmp2.append(tmp[i])
                else:
                    tmp2.append(tmp[i])
                    
            loop2 = loop2 + ','.join(tmp2) + "\n"   
        else:
            loop2 = loop2 + tmp + "\n"

    print loop2
 
    return loop2