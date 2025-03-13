import Dependence

import sys

try:
    import islpy as isl
except ImportError as e:
    print(e)
    print("pip install ispy")
    sys.exit()


def Dep_Analysis(LPetit ):

    loop = Dependence.Kernel_Loop(LPetit, 1)

    print("Statements: " + str(len(loop.st_lines)))

    linestring = open(LPetit, 'r').read()
    lines = linestring.split('\n')

    loops = 0

    for l in lines:
        if 'endfor' in l:
            loops = loops + 1

    print("Loops in loop: " + str(loops))


    flow = 0
    uniform = 0

    for d in loop.Deps:
        if 'In' in str(d.delta):
            uniform = uniform + 1
        if d.kind == 'flow':
            flow = flow + 1

    print('Uni-form: ' + str(uniform) + "/" + str(len(loop.Deps)))
    print('Flow: ' + str(flow) + "/" + str(len(loop.Deps)))


    un  = None


    for d in loop.Deps:
        print(d.delta)
        print(d.from_)
        print(d.to)

        if un is None:
            un = isl.UnionMap(str(d.Relation))
        else:
            un = un.union(d.Relation)


    print('---')
    print(un)