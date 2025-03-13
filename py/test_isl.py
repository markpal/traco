import sys
import os


folder =  os.path.dirname(os.path.realpath(__file__))[:-3]

sys.path.insert(0, folder + '/barvinok-0.39/')

#import isl

def StringToCard(s):
 #   set3 = isl.union_set(s)
    c = set3.card()
    c = str(c)
    return c



