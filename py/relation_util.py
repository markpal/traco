import sys

try:
    import islpy as isl
except ImportError as e:
    print(e)
    print("pip install ispy")
    sys.exit()



import copyconstr
from subprocess import Popen, PIPE, STDOUT
import tiling_v3
from termcolor import colored
import agent


oc_proc = '~/traco/traco-code/omega+/omega_calc/obj/oc < tmp/oc.txt'

# isl map to omega str
def islMaptoOmegaStr(R):

    p = isl.Printer.to_str(isl.DEFAULT_CONTEXT)
    p = p.set_output_format(isl.format.OMEGA)
    p.flush()

    return p.print_map(R).get_str()

def islSettoOmegaStr(R):

    p = isl.Printer.to_str(isl.DEFAULT_CONTEXT)
    p = p.set_output_format(isl.format.OMEGA)
    p.flush()

    return p.print_set(R).get_str()

def oc_IterateClosure(R):


    isl_symb = R.get_var_names(isl.dim_type.param)
    outFile = open('tmp/oc.txt', 'w')
    for sym in isl_symb:
        outFile.write('symbolic ' + sym + ";")

    outFile.write('R :=')
    str = islMaptoOmegaStr(R)

    str = str.replace('_', 'ul0')
    outFile.write(str)
    #sys.exit(0)
    outFile.write(';IterateClosure R;')
    #outFile.write(';R^+;')
    outFile.close()

    stdout_data = ''
    remote = 0
    if(remote == 0):
        cmd = oc_proc
        p= Popen(cmd, shell=True, stdout=PIPE, stdin=PIPE)
        stdout_data = p.communicate(input='')[0]
    else:
        ri = agent.remote_iterate()
        stdout_data = ri.iterate_closure()
        ri.disconnect()

    stdout_data = stdout_data.decode('utf-8')  # Decode the bytes to string
    stdout_data = stdout_data.split('\n')  # Now you can safely split the string

    relcl = ''
    now = False
    for i in range(0, len(stdout_data)):
        if 'Iterate' in stdout_data[i]:
            now = True
            continue
        if now:
            relcl += stdout_data[i]

    symprefix = ''
    if len(isl_symb) > 0:
        symprefix = '[' + ','.join(isl_symb) + '] -> '

    w = symprefix + relcl
    w = w.replace('} union {', ';')

    #print w

    if 'UNKNOWN' in w:
        print(colored('Iterate Closure Failed !!!! Abort !!!', 'red'))
        print('ISL approximation can be still used')
        sys.exit(0)

    rcl = isl.Map(w)

    return rcl



#r2 = "[n] -> {[i,j,2] -> [i',j,2] : 1 <= i < n && 1 <= j <= n && i' = i+ 1; [1,n,1] -> [2,2,2]}"
#r2 = isl.Map(r2)
#print r2
#print oc_IterateClosure(r2)


#nowa reducka wedlug pomyslu WB
def ReduceR(R):
    str = islMaptoOmegaStr(R)
    str = str.split(':')[0]
    str = str.replace('[', '')
    str = str.replace(']', '')
    str = str.replace('{', '')
    str = str.replace(' ', '')

    sets = str.split('->')
    inp = sets[0]
    outp = sets[1]

    inp = inp.split(',')
    outp = outp.split(',')

    exp = []
    for s in inp:
        exp.append('_ex_' + s)



    isl_symb = R.get_var_names(isl.dim_type.param)
    symb = ','.join(isl_symb)

    R2 = ''

    # symbolic variables
    if (len(isl_symb) > 0):
        R2 = R2 + '[' + symb + '] -> { '
    else:
        R2 = R2 + '{ '
    # tuple variables
    R2 = R2 + '[' + ','.join(inp) + '] -> [' + ','.join(outp) + '] : '

    if not R.is_empty():
        R2 = R2 + copyconstr.GetConstrSet(inp, R.domain()) + ' && '

    if not R.is_empty():
        R2 = R2 +  copyconstr.GetConstr(inp, outp, R) + ' && '



    R2 = R2 + ' not ( Exists ' + ','.join(exp) + ' : ( '

    R2 = R2 + tiling_v3.CreateLex(exp, inp) + ' && '

    #if not R.is_empty():
    #    R2 = R2 +  copyconstr.GetConstr(inp, exp, R.transitive_closure()[0]) + ' && '


    R2 = R2 + copyconstr.GetConstr(exp, outp, R)



    R2 = R2 + ' )) }'


    R2 = isl.Map(R2).coalesce()

    return R2




