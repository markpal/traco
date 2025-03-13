import islpy as isl
ctx = isl.Context()
from pygraph.classes.digraph import digraph

from pygraph.readwrite.dot import write
import functions
from easyprocess import Proc
import gen


import re
import os
import sys
import loop_tools
import scc

import gv






path_issf = os.path.dirname(os.path.realpath(__file__))[:-3]
path_petit_rel = path_issf + "/petit/obj/petit -bg -4 "

def Petit_Rel(file):
    cmd = path_petit_rel + " " + file
    return Proc(cmd).call(timeout=5).stdout



class Dependence:

    to = ""
    from_ = ""
    Relation = ""
    Orig_rel = ""
    vector = ""
    kind = ""
    var_in = ""
    var_out = ""
    graph = ""
    delta = ""
    user1 = ""
    prep = 0

    def print_dep(self):
        print "From: " + self.from_
        print "To: " + self.from_
        print "Kind: " + self.kind
        print "Var:" + self.var_in + " --> " + self.var_out
        print "Vector: " + self.vector
        print "Relation: " + str(self.Relation)


class Kernel_Loop:
    Deps = []
    nests = []
    dane = []
    plik = ""

    maxl = 0
    imperf = 0
    lines_deps = []
    st_lines = []  # statements in a loop
    var_st = []  # arrays and variables in a loop
    isl_rel = ''
    symb = []

    def __init__(self,plik,short_mode=0):
        isl.Map("{[i] : false}")
        self.plik = plik

        self.Load_Deps()


        self.Load_instrukcje()
        if(short_mode==0):
            self.Preprocess()
            self.Get_Arrays()


    def PreprocessPet(self):

        for i in range(0, len(self.Deps)):
            from_ = 'S' + str(self.Deps[i].from_)
            to =  'S' + str(self.Deps[i].to)
            rel = str(self.Deps[i].Relation)
            rel = rel.replace('{ [', '{ '+from_+'[')  #like aka Pet
            rel = rel.replace('> [', '> ' + to + '[')
            self.Deps[i].Relation = isl.Map(rel)
            print self.Deps[i].Relation



        self.isl_rel = isl.UnionMap(str(self.Deps[0].Relation))
        for i in range(1, len(self.Deps)):
            self.isl_rel = self.isl_rel.union(self.Deps[i].Relation)
            self.isl_rel = self.isl_rel.coalesce()



    def Load_Deps(self):

        lines = Petit_Rel(self.plik).split('\n')
        lines2 = []


        if (False):
            for line in lines:
                if 'must' in line:
                    continue
                else:
                    lines2.append(line)

        else:
            allow_to_add = True

            for i in range(0, len(lines)):
                if 'must' in lines[i]:
                    allow_to_add = False  # nie dodawaj lini po must chyba ze bedzie  nowa zaleznosc

                if '-->' in lines[i]:
                    allow_to_add = True

                if allow_to_add:
                    lines2.append(lines[i])

        lines = lines2



        for i in range(0, len(lines),4):
            dep = Dependence()
            info = lines[i].split()
            if len(info) == 0:
                continue
            #print lines[i]
            dep.kind = info[0]
            dep.var_in = info[2]
            #print info
            dep.var_out = info[5]
            dep.from_ = info[1].replace(':', '')
            dep.to = info[4].replace(':', '')
            dep.vector = info[6]
            dep.Relation = isl.Map(str(lines[i+2]))
            dep.delta = (str(lines[i+3]))
            self.Deps.append(dep)
            self.lines_deps.append(lines[i])   # dla priv



    def Get_ST(self):
        linestring = open(self.plik, 'r').read()
        lines = linestring.split('\n')
        self.Perfect_Check(lines)

        infor = 0
        i = 0
        sts = []

        for line in lines:
            i = i + 1
            if infor == 0 and 'for' not in line:
                continue
            if 'for ' in line:
                infor = 1
            if 'for ' not in line and 'if ' not in line and 'endfor' not in line and 'if(' not in line and 'then' not in line and 'endif' not in line and 'else' not in line and line.strip():
                sts.append(str(i))
                self.dane.append(str(i))
                self.st_lines.append(line)
            else:
                if infor == 1 and sts != []:
                    self.nests.append(sts)
                    sts = []

    def Load_instrukcje(self):
        self.Get_ST()
        combo = loop_tools.ReadStatementNests(self.plik, self.dane)
        self.instrukcje = combo[0]



        for item in self.instrukcje:
            if item['max_loop'] > self.maxl:
                self.maxl = item['max_loop']



    def Preprocess(self, imp = '-1'):

        self.isl_rel = isl.Map("{[i] : false}")
        self.isl_tmp = isl.Map("{[i] : false}")

        ii = 1
        w = -1
        for dep in self.Deps:

            if(dep.prep == 1):
                continue

            in_size = dep.Relation.dim(isl.dim_type.in_)


            out_size = dep.Relation.dim(isl.dim_type.out)

            dep.Relation = dep.Relation.insert_dims(isl.dim_type.in_, in_size, self.maxl-in_size+1)
            dep.Relation = dep.Relation.insert_dims(isl.dim_type.out, out_size, self.maxl-out_size+1)

            dep.Relation = dep.Relation.set_dim_name(isl.dim_type.in_, self.maxl, "_v1")
            dep.Relation = dep.Relation.set_dim_name(isl.dim_type.out, self.maxl, "_v2")

            invar = []
            outvar = []
            for i in range(0, in_size):
                invar.append("i" + str(i))
            for i in range(in_size, self.maxl):
                invar.append(imp)
            for i in range(0, out_size):
                outvar.append("o" + str(i))
            for i in range(out_size, self.maxl):
                outvar.append(imp)
            tmp = str("{[" + ",".join(invar) + ","+dep.from_+"] -> [" + ",".join(outvar) + ","+dep.to +"]}")
            tmp = isl.Map(tmp)

            dep.Relation = dep.Relation.intersect(tmp).coalesce()
            dep.prep = 1



            if self.isl_rel.is_empty():
                self.isl_rel = dep.Relation
            else:
                self.isl_rel = self.isl_rel.union(dep.Relation).coalesce()



        self.symb = isl_symb = self.isl_rel.get_var_names(isl.dim_type.param)
        #print self.symb



    # Perfect loop or imperfect?
    def Perfect_Check(self, petit_loop):
        endloop = 0
        startloop = 0
        for line in petit_loop:
            #sprawdz przy okazji jaka petla idealnie czy nie
            if 'for' in line and not 'endfor' in line:
                if startloop == 2:
                    self.imperf = 1
                startloop = 1
            else:
                if startloop == 1:
                    startloop = 2
            if 'endfor' in line:
                endloop = 1
            if endloop == 1 and 'endfor' not in line and not line.isspace() and line != '':
                self.imperf = 1
    ######################################

    def SCC(self):
        gr = digraph()

        for dep in self.Deps:

            if not gr.has_node(dep.from_):
                gr.add_nodes([dep.from_])
            if not gr.has_node(dep.to):
                gr.add_nodes([dep.to])

        for dep in self.Deps:
            if not gr.has_edge((dep.from_, dep.to)):
                gr.add_edge((dep.from_, dep.to))

        self.graph = gr

        return scc.getSCC(gr)

    def DrawGraph(self,nazwa):
        dot = write(self.graph)
        gvv = gv.readstring(dot)
        gv.layout(gvv,'dot')
        gv.render(gvv,'png',nazwa + '.png')
        gv.render(gvv, 'eps', nazwa + '.eps')

    def Get_Arrays(self):
        self.var_st = {}
        for st in self.st_lines:
            if 'then' in st or 'else' in st:
                continue
            varsn = []
            varsn = functions.CollectVars(varsn, st)
            for v in varsn:
                if v in self.var_st:
                    rw = RWCheck(v, st, self.var_st[v])
                    self.var_st[v] = rw
                    continue
                loop_var = False
                for inst in self.instrukcje:
                    if v in inst['vars']:
                        loop_var = True
                        break
                if not loop_var:
                    if not (( 'if' in st) and ('then' in st)):
                        rw = RWCheck(v, st, [0,0])
                        self.var_st.update({v:rw})




def RWCheck(var, line,rw):
    sides = line.split("=")
    pattern = re.compile("\\b"+var+"\\b")
    if pattern.match(sides[0]):
        rw[1] = rw[1]+1
    if pattern.match(sides[1]):
        rw[0] = rw[0]+1
    return rw



def Relation_Inner(dim, c):

    invar = []
    outvar = []

    for i in range(0, dim):
        invar.append("i" + str(i))
    for i in range(0, c):
        outvar.append("i" + str(i))
    for i in range(c, dim):
        outvar.append("o" + str(i))
    tmp = str("{[" + ",".join(invar)+"] -> [" + ",".join(outvar) + "]}")

    return isl.Map(tmp)

def is_uniform(ds):
    if ds.is_bounded():
        if ds.count() <= 1:
            return True
        else:
            return False
    else:
        return False


def clear_pw(tmp):
    tmp = tmp.replace("{", "")
    tmp = tmp.replace("}", "")
    tmp = tmp.replace("[", "")
    tmp = tmp.replace("]", "")
    tmp = tmp.replace("(", "")
    tmp = tmp.replace(")", "")
    tmp = tmp.replace(" ", "")
    return int(tmp)


def Create_LD_petit(L, petit_loop):
    file = open("tmp/LD_petit_loop_" + L + ".t", 'w')
    file.write("integer xxyyyx" + "\n")
    in_loop = 0
    for line in petit_loop:
        if('! start' in line):
            continue
        if('for ' in line):
            in_loop = 1
        if in_loop == 0:
            file.write(line + "\n")
        else:
            if (('for' in line) or ('if ' in line) or (line.isspace()) or (line == '')):
                file.write(line + "\n")
            else:
                file.write("xxyyyx = 1" + "\n")
    file.close()

    LD_inp = "tmp/LD_petit_loop_" + L + ".t"
    dane2 = gen.RelPrint(LD_inp,1)
    dane2 = dane2.split("#")

    rel2 = dane2[0]
    if rel2 != '':
        isl_rel2 = isl.Map(str(rel2))
    else:
        isl_rel2 = None
    return isl_rel2










