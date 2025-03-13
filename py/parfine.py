from shutil import copy
import re

class Tree:
    def __init__(self, value, *children):
        '''Singly linked tree, children do not know who their parent is.
        '''
        self.value = value
        self.children = tuple(children)
        self.koniec = 0
        self.parent = None
        self.parallel = 0
        self.id = 1
        
    @property
    def arguments(self):
        return (self.value,self.koniec,self.parallel) + self.children

    def __eq__(self, tree):
        return self.arguments == tree.arguments

    def __repr__(self):
        argumentStr = ', '.join(map(repr, self.arguments))
        return '%s(%s)' % (self.__class__.__name__, argumentStr)


def IsParallel(poczatek, koniec, poziom, deps):
    vecbase = '(' + '0,' * poziom
    vecbase = vecbase[:-1]
    if(poziom == 0):
        vecbase = '('
    for dep in deps:
        if vecbase in dep['vec'] and poczatek <= dep['from'] and koniec >= dep['to']:
            tmp = dep['vec'].replace(vecbase, '')
            tmp = tmp.replace(',','')
            if tmp[0] != '0':
                return False
    return True
            
def TryPar(t, level, deps):
    if IsParallel(t.value, t.koniec, level, deps):
        t.parallel = 1
    else:
        for potomek in t.children:
            TryPar(potomek, level+1, deps)
    

def CheckPar(t, loops):
    if t.parallel == 1:
        loops.append(t.id)
    for potomek in t.children:
        CheckPar(potomek, loops)   
    

def ParInner(j):

    linestring = open('tmp/deps'+str(j)+'.txt', 'r').read()
    lines = linestring.split('\n')  
    
    deps = []
    for _deps in lines:
        ar = _deps.split() 
        if len(ar) > 0:
            deps.append({'from': int(ar[1].replace(':','')),'to': int(ar[4].replace(':','')),'vec': ar[6]})
    
    linestring = open('tmp/petit_loop_'+str(j)+'.t', 'r').read()
    lines = linestring.split('\n')
    
    t = None
    i = 0
    root = None
    z = 1
    
    for line in lines:
        i = i+1
        if 'for' in line and not('endfor' in line):
            if t is None:
                t = Tree(i)
                root = t
            else:
                child = Tree(i)
                child.parent = t
                t.children = t.children + (child,)
                t = child 
            t.id = z    #zczytaj numer kolejny petli
            z = z+1
        if t is not None:
            if 'endfor' in line:
                t.koniec = i
                t = t.parent 
           
    loops = []

    TryPar(root,0, deps)
    
    CheckPar(root, loops)

    
    i=0
    
    new_loop = []
    
    if len(loops) > 0:
        linestring = open("tmp/C_loop_" + str(j) + ".c", 'r').read()
        lines = linestring.split('\n')

        find_loop = re.compile("(\W+|^)for");
        
        for line in lines:
            if(find_loop.match(line)):
                i=i+1
            if i in loops:
                new_loop.append("#pragma omp parallel for\n");
                loops.remove(i)
            new_loop.append(line + "\n");
        
        _file = open("tmp/C_output_" + str(j) + ".c", 'w')
        _file.writelines(new_loop)  
        _file.close()
         
    
