import sys
from termcolor import colored
try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()

import copyconstr


def Valid1(Rsched, symb, in_, out_, s_in, sout, loop):
    # dodatkowo  ii <> ii' && i1 = i2 && ii,i1 ,    ii',i2 nalezy do VLDEXTY exists ma byc pusty
    VLD_VAL = Rsched.range()

    S_VALID = symb + '{[' + s_in + '] :' + copyconstr.GetConstrSet(in_,
                                                                   VLD_VAL) + ' && exists ' + sout + ' :  (' + copyconstr.GetConstrSet(
        out_, VLD_VAL) + ' && '

    for i in range(0, loop.maxl * 2):
        S_VALID += ' not ' + in_[i] + ' = ' + out_[i] + ' && '

    for i in range(loop.maxl * 2, loop.maxl * 4 + 1):
        S_VALID += in_[i] + ' = ' + out_[i] + ' && '

    S_VALID += ' 1=1 ) }'
    S_VALID = isl.Set(S_VALID)

    if (S_VALID.is_empty()):
        print colored('** Validation - no redundant statements in tiles - OK', 'green')
    else:
        print colored('Redundant statements in tiles - ERROR', 'red')
        sys.exit(0)