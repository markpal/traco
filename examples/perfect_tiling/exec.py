import subprocess

CC = 'gcc'
compile = " -lgomp -O3 -lm"

def Run(arr):
    p = subprocess.Popen(arr, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    out = out.replace('\n', '')
    p.wait()
    print out
    return out


def Compiler(arr):
    print arr
    p = subprocess.Popen(arr)
    p.wait()


loops = ['UA_setup.f2p_16.c','UA_setup.f2p_16.c','UA_setup.f2p_16_TILE4.c','UA_setup.f2p_16_TILE4.c',
         'FT_auxfnct.f2p_2_TILE16.c', 'FT_auxfnct.f2p_2_TILE16.c','FT_auxfnct.f2p_2.c', 'FT_auxfnct.f2p_2.c']

variants = [['1 500', '2 500', '3 500'], ['1 700', '2 700', '3 700'], ['2 500', '3 500'], ['2 700', '3 700'],
['1 200', '2 200', '3 200'], ['1 500', '2 500', '3 500'], ['2 200', '3 200'], ['2 500', '3 500']]


i = 0
times = []
speedup = []
kop_tab = [3,4,7,8]

for loop in loops:
    vr = variants[i]
    tim = []
    s = []

    plik =  loop + compile
    komendy = plik.split(' ')
    komendy.insert(0, CC)

    Compiler(komendy)

    for v in vr:

        komendy = v.split(' ')
        komendy.insert(0, './a.out')
        print komendy
        czas = float(Run(komendy))

        if (len(times)+1 in kop_tab) and len(tim) == 0:
            tim.append(times[i-2][0])

        if len(tim) > 0:
            s.append(round(tim[0] / czas, 3))

        tim.append(czas)

    i = i+1
    times.append(tim)
    speedup.append(s)

print times
print speedup


