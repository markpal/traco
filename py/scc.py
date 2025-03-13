import gen
import re
import subprocess
import functions
import shutil
import sys
import correct



import loop_tools

import imperf_tile

import os
import iscc


#sys.path.append('..')
#sys.path.append('/usr/lib/graphviz/python/')
#sys.path.append('/usr/lib64/graphviz/python/')
import pygraphviz as gv

import islpy as isl



import tiling_v3

ctx = isl.Context()



# Import pygraph
from pygraph.classes.graph import graph
from pygraph.classes.digraph import digraph
from pygraph.algorithms.searching import breadth_first_search
from pygraph.readwrite.dot import write
from pygraph.algorithms.accessibility import mutual_accessibility
from pygraph.algorithms.cycles import find_cycle

# check barvinok
# barv_location = os.path.dirname(sys.argv[0]).replace('py', 'barv_script')
# barv_script = open(barv_location, 'r').read().split(' ')[0]
#
# if(not os.path.exists(barv_script)):
#     print("Barvinok not found. Please setup the tool or check a path in the file: barv_script")
#     sys.exit()
# else:
#     iscc.barv_script = barv_script

iscc.barv_script = "barvinok-0.41/iscc"

loop_fuse = True

def get_tab(line):
    return " " * (len(line) - len(line.lstrip()))


def find_instr(komponent, instrukcje):
    results = [int(a) for a in komponent]
    i = 0
    for instr in instrukcje:
        if set(results).issubset(set(instr['st'])):
            return i
        else:
            i = i+1
    return -1



def DepGraph(j):
    
    linestring = open('tmp/deps'+str(j)+'.txt', 'r').read()
    lines = linestring.split('\n')  
    
    deps = []
    for _deps in lines:
        ar = _deps.split() 
        if len(ar) > 0:
            deps.append({'from': ar[1].replace(':',''),'to': ar[4].replace(':',''),'vec': ar[6]})

    # znajdz wszystkie instrukcje IND i dodaj je tu
    # deps.append({'from': '12','to': '12','vec': ''})
    # przejrzyj  tmp/petit_loop_0.t  znajdz wszystkie instrukcje od for

    gr = digraph()
    
    
    
    for dep in deps:
        if not gr.has_node(dep['from']):
            gr.add_nodes([dep['from']])
        if not gr.has_node(dep['to']):
            gr.add_nodes([dep['to']])
        
    
    for dep in deps:
        if not gr.has_edge((dep['from'],dep['to'])):
            gr.add_edge((dep['from'],dep['to']))

    # Draw as PNG
    dot = write(gr)
    #gvv = gv.readstring(dot)
    gvv = gv.AGraph(string=dot)
    gvv.layout(prog='dot')  # Poprawne wywołanie layout()
    #gv.render(gvv,'png','tmp/scc_'+str(j)+'.png')
    #gv.render(gvv, 'eps', 'tmp/scc_' + str(j) + '.eps')


    gvv.draw('tmp/scc_' + str(j) + '.png', format='png')  # Eksport do PNG
    gvv.draw('tmp/scc_' + str(j) + '.eps', format='eps')  # Eksport do EPS

    return gr



def getSCC(gr):

    z = mutual_accessibility(gr)


    z_sorted = []
    for zz in z:
        z_sorted.append(zz)

    komp = []
    for zz in z_sorted:
        if not z[zz] in komp:
            komp.append(z[zz])


# SCC POLICZONE

    komp2 = komp[:]

    for i in (0, len(komp)):
        for item in komp:
            for stam in item:
                for item2 in komp:
                    if item != item2:
                        for stam2 in item2:
                           if gr.has_edge((stam,stam2)):
                               a = komp2.index(item2)
                               b = komp2.index(item)
                               if(a < b): #zamien miejscami
                                   komp2[b], komp2[a] = komp2[a], komp2[b]

    komp3 = []
    for komponent in komp2:
        con = 0
        if komp3 == []:
            komp3.append(komponent)
            item = komponent
        else:
            for node in komponent:
                for node2 in item:
                    if gr.has_edge((node2, node)):
                        con = 1
            if(con == 1):
                komp3.append(komponent)
                item = komponent
            else:
                for node in komponent:
                    item.append(node)


    if(loop_fuse):
        komp2 = komp3



    return komp2


def GenerateSCC(j, permute):

    gr = DepGraph(j)

    z = mutual_accessibility(gr)


    z_sorted = []
    for zz in z:
        z_sorted.append(zz)

    komp = []
    for zz in z_sorted:
        if not z[zz] in komp:
            komp.append(z[zz])


   
# SCC POLICZONE

    komp2 = komp[:]

    for i in (0, len(komp)):
        for item in komp:
            for stam in item:
                for item2 in komp:
                    if item != item2:
                        for stam2 in item2:
                           if gr.has_edge((stam,stam2)):
                               a = komp2.index(item2)
                               b = komp2.index(item)
                               if(a < b): #zamien miejscami
                                   komp2[b], komp2[a] = komp2[a], komp2[b]




    rel = gen.RelPrint("tmp/petit_loop_"+str(j)+".t", 1)



    
    dane = gr.nodes()
    paczka = loop_tools.ReadStatementNests("tmp/petit_loop_"+str(j)+".t", dane)
    combo = paczka[0]
    instrukcje = combo
    granice = paczka[2]

    max_nest = 0
    for c in combo:
        if c['nest'] > max_nest:
            max_nest = c['nest']
        
   
    pattern = re.compile("\n#.*$")
    rel = pattern.sub("", rel)
    pattern = re.compile(r"{.*\->")
    
    t = str(re.findall(pattern, rel)[0])
    t = t.replace(" ", "")
    t = t.replace("->", "")
    t = t + " : true};"



    # loop fuse to do in future and permutation too
    if(False):
        komp3 = []
        for komponent in komp2:
            con = 0
            if komp3 == []:
                komp3.append(komponent)
                item = komponent
            else:
                for node in komponent:
                    for node2 in item:
                        if gr.has_edge((node2, node)):
                            con = 1
                if(con == 1):
                    komp3.append(komponent)
                    item = komponent
                else:
                    for node in komponent:
                        item.append(node)

        loop_fuse = False

        if(loop_fuse):
            komp2 = komp3


        
    params = ""
    if("] -> {" in rel):
        params = re.findall(r".*\] -> \{", rel)[0].replace("{", "")
         

    zbiory = []
    for komponent in komp2:
        warunek = "("
        for line in komponent:
            if warunek != "(":
                warunek = warunek + "or"
            warunek = warunek + " v=" + line + " "
        warunek = warunek + ") and true"
        zbior = t.replace("true", warunek)
        zbiory.append(zbior)

    file = open("tmp/barv_scc.txt", 'w')
    
    if(1 == 1):
        file.write('R:=' + rel + ';\n')
        file.write('S:= dom R + ran R;')
        
        i = 0
        for zbior in zbiory:
            file.write('S'+str(i)+':=' + zbior)
            file.write('S'+str(i)+':= S * S'+str(i)+';')
            file.write('codegen S'+str(i)+';')
            i = i + 1
            
    i = 0
    permutate_list = []

    for komponent in komp2:
        set = params+"{["
        ll = find_instr(komponent, instrukcje)   # jesli komponent bedzie z loop fusion to trzeba wybrac najbardziej zagn. instrukcje
        vars = instrukcje[ll]['vars']

        #for q in range(0, max_nest+1):
        #    set = set + "i" + str(q) + ","
        set = set + ','.join(vars) + ",v ] : "

        #set = set[:-1] + "] : "
        for line in komponent:
            path = []
            for item in combo:
                for z in item['st']:
                    if int(line) == int(z):
                        path = item['path']
            for q in range(0, len(vars)):
                if(q < len(path)):
                    set = set + granice[path[q]]['lb'] + " <= "+ vars[q] +" <= " + granice[path[q]]['ub'] + " and "
                    #set = set + granice[path[q]]['lb'] + " <= i" + str(q) + " <= " + granice[path[q]]['ub'] + " and "
                else:
                    set = set + " " + vars[q] + " = -1 and "
            
            set = set + " v = " + line +" and true or "
        set = set + " false}; "


        if(1==0): #permute

            # tylko zaleznosci z scc TODO
            rel = imperf_tile.PermuteBlock("tmp/deps" + str(j) + ".txt", set, instrukcje[ll], params, len(instrukcje[ll]['vars']), permutate_list)



            set = isl.Set(str(set))

            # relacja identity - nie rob nic


            if(rel.is_equal(rel.identity(rel.get_space()))):
                permutate_list.pop()
            else:
                set = set.apply(rel)
            set_size = set.dim(isl.dim_type.set)
            set = set.insert_dims(isl.dim_type.set, set_size-1, max_nest+1-set_size)
            tmp_set = '{[' + ','.join(instrukcje[ll]['vars']) +',-1' * (max_nest - len(instrukcje[ll]['vars'])) + ',v]}'
            set = set.intersect(isl.Set(tmp_set)).coalesce()

            set = 'S'+str(i)+':=' + str(set) + ";"



            print(set)

            file.write(set)
            file.write('codegen S'+str(i)+';')
            i = i + 1
    
    
    file.close();




    
    cmd = barv_script + " < tmp/barv_scc.txt" 
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    process.wait()
    output = process.stdout.read()


#     #dodaj s1 do petli
#     """
#     #lines = output.split(r"\n")
#
#     lines = filter(lambda x:x!='',lines)
#     loop = ""
#     for i in range(0,len(lines)):
#         tmp = lines[i]
#         # pattern = re.compile(r"^\W*\(")  # Poprawne jako komentarz
#
#         if pattern.match(tmp):
#             tmp = tmp.replace("(", "s1(")
#             tmp = tmp.replace(", ", ",")
#         loop = loop + tmp
# # if(i < len(lines)-1):
#         loop = loop + "\n"
#
#     linestring = open("tmp/petit_loop_"+str(j)+".t", 'r').read()
#     petit_lines = linestring.split('\n')
#
#     lines = loop.split("\n")
#
#     debug = False
#     loop = ""
#     for line in lines:
#         if("s1(" in line):
#             pattern = re.compile(",[^,]+\)")
#             st = pattern.findall(line)[0].replace(",", "").replace(")", "")
#             if(not st.isdigit()):
#                 print "== ERROR =="
#                 sys.exit()
#             numb_st = int(st)
#             st = petit_lines[int(st)-1]
#             st = st.replace(",", "][")
#
#             # nawiasy powinny byc zmienione jesli poprzedzaja je znaki
#             # alfanumeryczne, inaczej to nawiasy nie od tablic
#             st =  re.sub("\s*\(", "(", st)
#             st =  re.sub("\s*\)", ")", st)
#             st =  re.sub(r'(?<=[a-zA-Z0-9_])\(', '[', st)
#             st =  re.sub(r'(?<=[a-zA-Z0-9_])\)', ']', st)
#
#             # szukaj wektora
#             for item in combo:
#                 if numb_st in item['st']:
#                     vec = item['vars']
#                     if debug:
#                         loop = loop +  get_tab(line) + "// " + ",".join(item['vars']) + "\n"
#                     break
#
#             # nowy wektor
#             vec_new = line.replace("s1(", "").replace(");", "").replace(" ", "").split(",")[:-1]
#             if debug:
#                 loop = loop +  get_tab(line) + "// " + ",".join(vec_new) + "\n"
#
#             st2 = st
#             for i in range(0, len(vec)):
#                 st2 = re.sub('\\b'+vec[i]+'\\b', vec_new[i], st2)
#
#             if debug:
#                 loop = loop +  get_tab(line) + "// " + st + ";\n"
#
#             loop = loop + get_tab(line) + st2 + ";\n"
#         else:
#             loop = loop + line.replace('int ', '') + "\n"
#
#     #do poprawy - za duzo operacji na plikach przerobic korekte
#     """

    loop = tiling_v3.postprocess_loop(output.split('\n'))
    lines = loop.split('\n')
    loop = imperf_tile.RestoreStatements(lines, "tmp/petit_loop_"+str(j)+".t", dane,  0, 0, permutate_list)


    text_file = open("loop_scc.c", "w")
    text_file.write(loop)
    text_file.close()
    
    loop = ""
    for line in correct.Korekta("loop_scc.c"):
        loop = loop + line + "\n"
    
    text_file = open("loop_scc.c", "w")
    text_file.write(loop)
    text_file.close()
    
    # dopisz do instrukcji wektory zmiennych indeksowych petli
    # uzyskaj tabulacje
    # zastap instrukcje
    # nadaj format C
    
    
    
    if(1==0):
        
        linestring = open("tmp/C_loop_"+str(j)+".c", 'r').read()
        lines = linestring.split('\n')   
        
        lines = linestring.split('\n')
        stuff = []
        
        for line in lines:
            if 'for' in line:
                stuff.append(functions.Loop(line));
        
        v = ""
        for s in stuff:
            v = v + s['var'] + ","
        v = v + "v"
        
        text_file = open("names_info.txt", "w")
        text_file.write(v)
        text_file.close()
        
        text_file = open("pseudocode.txt", "w")
        text_file.write(loop)
        text_file.close()
        
        
        
        gen.ParsePrint("tmp/petit_loop_"+str(j)+".t")
     
        shutil.copyfile("out_pseudocode.txt", "tmp/C_loop_scc"+str(j)+".c")
    
    
    


   
    
