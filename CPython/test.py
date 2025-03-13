#!/usr/bin/env python
  
import ctypes
  
LIBRARY_PATH = './my_library.so'


def makearr( L ):
    arr = (ctypes.c_char_p * (len(L) + 1))()
    arr[:-1] = L
    arr[ len(L) ] = None
    return arr

  
def cloog_gen(param, iterators, domains, scattering, str_context):
   
    my_library = ctypes.CDLL(LIBRARY_PATH)
    my_library.codegen.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.POINTER(ctypes.c_char_p), ctypes.POINTER(ctypes.c_char_p), ctypes.c_int, ctypes.POINTER(ctypes.c_char_p), ctypes.POINTER(ctypes.c_char_p)]

    my_library.codegen.restype = ctypes.c_char_p
    context = ctypes.c_char_p(str_context)
    loop = my_library.codegen(context, len(param), makearr(param), makearr(iterators), len(domains), makearr(domains), makearr(scattering))

    return loop
                                                                                                                                                
  
param = ["N"]
iterators = ["ii", "i","v"]
domains = ["[N] -> {[ii, i,6] : 0 <= ii <= 2 and 0 <= i < N}","[N] -> {[ii, i,8] : 0 <= ii <= 2 and 0 <= i < N}"]
scattering = ["[N] -> {[ii, i,v] -> [0, ii, 1,v]}","[N] -> {[ii, i,v] -> [0, ii, 2,v]}"]
str_context = "[N] -> { : N > 0}"

print cloog_gen(param, iterators, domains, scattering, str_context)[:-3]  # tu sa jakies smieci


