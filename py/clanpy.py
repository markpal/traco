# CLAN & CANDL INTERFACE FOR TRACO 2015

from easyprocess import EasyProcess
import sys
import re
import convert_loop



try:
    import islpy as isl
except ImportError as e:
    print(e)
    print("pip install ispy")
    sys.exit()

#---------------------------------------------------------
class ReadWrite:
    op = ""  # READ OR WRITE
    var = ""
    eq = []

    def __init__(self):
        self.eq = []


class ClanStatement:
    original_iterators = []
    body = ''
    domain = ''
    domainpet = ''
    domain_map = ''
    read_write = []
    nest = []
    scatering = []
    bounds = []
    scop = 0
    pet_symbol = ''
    petit_line = 0


    def __init__(self):
        self.original_iterators = []
        self.read_write = []
        self.nest = []
        self.scatering = []

    def getDim(self):
        return len(self.nest)-1



class ClanPy:
    no_statements = 0
    params = []
    statements = []
    clan_path = ''
    loop_path = ''
    candl_out = ''
    arr = []
    deps = []
    maxdim = 0

    def __init__(self):
        self.no_statements = 0
        self.params = []
        self.statements = []
        self.clan_path = 'clan'
        #self.loop_path = '/home/marek/clan-0.8.0/test.c'
        self.arr = []  # arrays and variables

    def Load(self):
        cmd = self.clan_path + " " + self.loop_path
        lines = EasyProcess(cmd).call(timeout=5).stdout

        fo = open("test.clan", "w")
        fo.write(lines)
        fo.close()

        #print lines

        lines = ''.join(lines).split('\n')  # convert array of characters to array of strings




        st = -1
        scop = -1

        for i in range(0, len(lines)):
            if "# NULL scop" == lines[i]:
                print("No loop in scop! NULL scop")
                break

            #print lines[i]
            if '# Number of statements'  == lines[i]:
                self.no_statements = int(lines[i+1])
                for j in range(0, self.no_statements):
                    self.statements.append(ClanStatement())
                scop += 1

            if '# Parameters are provided' == lines[i]:
                self.params = lines[i+3].split(' ')
            #    sys.exit(0);

            if '== Statement' in lines[i]:
                st = st + 1
                self.statements[st].scop = scop

            if "# List of original iterators" == lines[i]:
                self.statements[st].original_iterators = lines[i+1].split(' ')

                #ile zagniezdzen poziom najwiekszy
                if (len(self.statements[st].original_iterators)) > self.maxdim:
                    self.maxdim = len(self.statements[st].original_iterators)

                # Zbuduj domene
                _w = ''
                if(len(self.params) > 0):
                    _w = '[' + ','.join(self.params) + '] -> '

                _w = _w + ' {[' + ','.join(self.statements[st].original_iterators) + '] : ' + self.statements[st].domain + ' }'
                self.statements[st].domain_map = _w


            if "# Statement body expression" == lines[i]:
                self.statements[st].body = lines[i+1]

            if "DOMAIN" == lines[i]:
                _w = ""
                j = 0
                while '# ------------' not in lines[i+j]:
                    if '# Union part' in lines[i+j] and _w != '':
                        _w = _w[:-3] + ' or '
                    if '##' in lines[i+j]:
                        _w = _w + lines[i+j].split('##')[1] + " && "
                    j = j+1

                if(len(_w) > 3):
                    _w = _w[:-3]
                self.statements[st].domain = _w.replace('==', '=')


            if "READ" == lines[i] or "WRITE" == lines[i]:
                rw = ReadWrite()
                rw.op = lines[i]
                l = int(lines[i+1].split(' ')[0])
                rw.var = lines[i+3].split('==')[1].replace(' ', '')

                if not rw.var in self.arr:  # save arrays and variables
                    self.arr.append(rw.var)

                for j in range(0, l-1):
                    rw.eq.append(lines[i+j+4].split('==')[1].replace(' ', ''))
                self.statements[st].read_write.append(rw)

            if "SCATTERING" == lines[i]:
                l = int(lines[i+1].split(' ')[0])
                for j in range(0,l,2):
                    self.statements[st].nest.append(int(lines[i+3+j].split('==')[1].replace(' ', '')))

                for j in range(0,l,2):
                    self.statements[st].scatering.append(lines[i+3+j].split('==')[1].replace(' ', ''))

                #print self.statements[st].scatering


        # dopisz teraz granice

        linestring = open(self.loop_path, 'r').read()
        lines = linestring.split('\n')
        start_search = 0
        j= 0
        for j in range(0,len(self.statements)):
            st = self.statements[j]
            for i in range(start_search, len(lines)):
                if st.body in lines[i]:
                    start_search = i
                    break

            l = len(st.original_iterators)-1
            for i in range(start_search, 0, -1):


                if 'for' in lines[i]:
                    stuff = convert_loop.functions.Loop(lines[i])
                    if stuff['var'] == st.original_iterators[l]:
                        self.statements[j].bounds.insert(0, stuff)
                        l = l-1


                if l < 0:
                    break

        #print self.statements[0].bounds


        #print self.statements[st].read_write[0].op
        #print self.statements[st].read_write[0].var
        #print self.statements[st].read_write[0].eq[0]
        #print self.statements[st].read_write[0].eq[1]

        #print self.statements[st].read_write[1].op
        #print self.statements[st].read_write[1].var
        #print self.statements[st].read_write[1].eq[0]
        #print self.statements[st].read_write[1].eq[1]

        #print self.statements[1].nest[1]

    def RunCandl(self):
        cmd = "candl test.clan"
        self.candl_out = Proc(cmd).call(timeout=5).stdout

    def DepAnalysis(self):

        self.RunCandl()


        lines = ''.join(self.candl_out).split('\n')  # convert array of characters to array of strings



        for line in lines:
            if '->' in line:
                b = BuildRelation(line, self)
                r = b.GetRelation()

                d = Dependence()
                d.relation = r
                if r.dim(isl.dim_type.in_) == r.dim(isl.dim_type.out):
                    d.delta = r.deltas()
                else:
                    d.delta = "-1"   # obliczyc potem jak petit
                #print d.delta
                d.source = b.rc.GetSourceStatement()
                d.destination = b.rc.GetDestinationStatement()
                d.kind = b.rc.KindDep()
                d.sourceref = b.rc.GetSourceRef()
                d.destinationref = b.rc.GetDestinationRef()
                d.depth = b.rc.GetDepth()

                self.deps.append(d)


# --------------------------------------------------------------------------------------------------------
# CANDL CLASSES

class Dependence:
    kind =""
    relation = None
    source = ""
    destination =""
    sourceref = ""
    destinationref = ""
    depth = ""
    delta = ""


class ReadCandl:

    line = ""

    def __init__(self,linia):
        self.line = linia

    def GetSourceStatement(self):
        return int(self.line.split('[')[0].split('->')[0].replace(' ', '').replace('S',''))

    def GetDestinationStatement(self):
        return int(self.line.split('[')[0].split('->')[1].replace(' ', '').replace('S',''))

    def KindDep(self):
        if 'RAW' in self.line:
            return 'RAW'
        if 'WAR' in self.line:
            return 'WAR'
        if 'WAW' in self.line:
            return 'WAW'

    # to zapisy WRITE READ w Clanie
    def GetSourceRef(self):
        return int(self.line.split('ref')[1].replace('"];','').split('->')[0].replace(' ', ''))

    def GetDestinationRef(self):
        return int(self.line.split('ref')[1].replace('"];','').split('->')[1].replace(' ', ''))

    def GetDepth(self):
        return int(self.line.split("depth ")[1].split(',')[0])


def AddApo(line, words):
    for w in words:
        pattern = r"\b" + w + r"\b"
        line = re.sub(pattern, w + "'", line)
    return line
# ---------------------------------------------------------------------------------------------------

def CreateLex(depth, array1, array2, order, scat):


    lex = "("

    nieostra = ""
    if(order > 0):
        nieostra = "="

    for i in range(0,depth):
        if(lex != "("):
            lex = lex + " || ("
        for j in range(0,i):
            lex = lex + array1[j] + " = " + array2[j] + "' && "
        w = ">"
        if('-' in scat[i]): w = "<"  # petla idzie odwrotnie
        lex = lex + array2[i] + "' " + w + nieostra + ' ' + array2[i]    # jesli s0 jest przed s1 to nierownosc nieostra
        if(i>0):
            lex = lex + ")"

    return lex + ")"

# ---------------------------------------------------------------------------------------------------
class BuildRelation:

    line = ""
    rc = ReadCandl('')
    rel = ''
    cp = ''

    def __init__(self,linia,clanp):
        self.line = linia
        self.rc = ReadCandl(linia)
        self.rel = ''
        self.cp = clanp



    def GetRelation(self):

        debug = True


        rel = ''
        #PARAMS
        if len(self.cp.params) > 0:
            rel = rel + '[' + ','.join(self.cp.params) + '] -> '
        rel += '{ ['

        si = self.rc.GetSourceStatement()
        so = self.rc.GetDestinationStatement()



        inp_array = self.cp.statements[si].original_iterators[:]
        out_array = self.cp.statements[so].original_iterators[:]


        for i in range(0, len(out_array)):
            #if '-' in self.cp.statements[so].scatering[i] and i <= len(inp_array): #petla idzie odwrotnie
            #    inp_array[i] += "'"
            #else:
            out_array[i] += "'"


        #INPUT
        inop = ','.join(inp_array)
        rel += inop + '] -> ['

        #OUTPUT
        outop = ','.join(out_array)
        rel += outop+ '] : '

        inverse = False
        # dodaj rownania
        for j in range(0, len(self.cp.statements[si].read_write[self.rc. GetSourceRef()].eq)):
            if '-' in self.cp.statements[si].scatering[j] and self.rc.GetDepth() == 1 or inverse:  # petla idzie w dol  czy j ma byc rowne getdepth nie wiem !!!
                rel += self.cp.statements[so].read_write[self.rc. GetDestinationRef()].eq[j]
                rel += ' = '
                rel += AddApo(self.cp.statements[si].read_write[self.rc. GetSourceRef()].eq[j], self.cp.statements[si].original_iterators)
                rel += ' && '
                if(j==0):  #petla odwrotna raw na war itd.
                    inverse = True
            else:   #normalnie
                rel += self.cp.statements[si].read_write[self.rc. GetSourceRef()].eq[j]
                rel += ' = '
                rel += AddApo(self.cp.statements[so].read_write[self.rc. GetDestinationRef()].eq[j], self.cp.statements[so].original_iterators)
                rel += ' && '

        if(inverse): #odwroc domeny
            rel += self.cp.statements[so].domain + " && "
            rel += AddApo(self.cp.statements[si].domain, self.cp.statements[si].original_iterators) + " "
        else:
            #dodaj domene inputa
            rel += self.cp.statements[si].domain + " && "
            #dodaj domene ouputa
            rel += AddApo(self.cp.statements[so].domain, self.cp.statements[so].original_iterators) + " "

        # dodaj lex


        if self.rc.GetDepth() > 0:
            lex = CreateLex(self.rc.GetDepth(), self.cp.statements[si].original_iterators, self.cp.statements[so].original_iterators, so-si, self.cp.statements[si].scatering)
        else:
            lex = ' 1=1 '

        rel += " && " + lex +  " } "

        #print rel
        #if(debug):
            #print self.rc.line
            #print self.rc.GetDepth()
            #print lex
            #print rel

        rel = isl.Map(str(rel))


        return rel

        #print rel

# ---------------------------------------------------------------------------------------------------------------------------------

'''


plik = sys.argv[1]
cl = ClanPy()
cl.loop_path = plik

cl.Load()
cl.RunCandl()

lines = ''.join(cl.candl_out).split('\n')  # convert array of characters to array of strings

un  = None

for line in lines:
    if '->' in line:
        b = BuildRelation(line, cl)
        r  = b.GetRelation()

        if un is None:
            un = isl.UnionMap(str(r))
        else:
            un = un.union(r)
print '---'
print un

IS =  isl.Set(cl.statements[0].domain_map).coalesce()
RS =  un.domain().union(un.range()).coalesce()

IND = IS.subtract(RS).coalesce()
print IND

'''
