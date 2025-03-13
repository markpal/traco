import functions
import re
import sys

try:
    import islpy as isl
except ImportError, e:
    print e
    print "pip install ispy"
    sys.exit()

com = '''

head = '#include <math.h>\n#define ceild(n,d)  ceil(((double)(n))/((double)(d)))\n#define floord(n,d) floor(((double)(n))/((double)(d)))\n#define max(x,y)    ((x) > (y)? (x) : (y))\n#define min(x,y)    ((x) < (y)? (x) : (y))\n\n\n'

line = 'for(i=1; i<N; i++){'



def tile_loop(line):
    line = line.replace(' ', '')
    #print line
    stuff = functions.Loop(line)
    #print stuff
    tile_var = stuff['var'] + '_tile'
    l1_loop = 'for('+tile_var+'=0;'+tile_var+'<=(int)floord('+stuff['ub']+',TILE_SIZE);'+tile_var+'++)';
    l2_loop = 'for('+stuff['var']+'=max('+stuff['lb']+','+tile_var + '* TILE_SIZE);'+stuff['var']+'<=min('+stuff['ub']+',TILE_SIZE*'+tile_var+'+TILE_SIZE-1);'+stuff['var']+'++)';
    if "{" in line:
        l2_loop = l2_loop + "{"
    return [l1_loop, l2_loop]


def get_tab(line):
    x = len(line) -len(line.lstrip())
    tmp = ''
    for i in range(0,x):
        tmp = tmp + ' '
    return tmp


linestring = open('/home/marek/test1.c', 'r').read()
lines = linestring.split('\n')

tiled_lines = []

i=0

while(i<len(lines)):

    if('for' in lines[i] and 'for' in lines[i+1]):
        z = 1;
        while('for' in lines[i+z]):
            z = z + 1
        #print z

        for j in range (0, z):
            temp = tile_loop(lines[i+j])
            tab = get_tab(lines[i+j])
	    if(j == 0):
            	tiled_lines.append(tab + temp[0] + "\n")
            if(j > 0):   #zewn dodaj na koncu
                # tiled_lines.append(tab + temp[1] + "\n")
		tiled_lines.append(tab + lines[i+j] + "\n")
            else:
                tab = get_tab(lines[i+z-1]) + ' '
                sufix = tab + temp[1]
        tiled_lines.append(sufix + "\n")
        i = i + z  # przeskocz petle
    else:
        tiled_lines.append(lines[i] + "\n")
        i = i + 1

file = open("/home/marek/test_tiled.c", 'w')
file.writelines(head)
file.writelines(tiled_lines)
file.close()


'''


#for(i=1; i<N; i++){
#        for(j=1; j<=100; j++){
#            b[i][j] = b[i][j+1] + b[i+1][j];
#        }
#    }

def find_bracelet(i, lines):
    z = 0
    while(i<len(lines)):
        z = z + lines[i].count("{")
        z = z - lines[i].count("}")
        if(z == 0):
            break
        i = i + 1
    return i

def CorrectLoop(_file):
    linestring = open(_file, 'r').read()
    lines = linestring.split('\n')

    z1 = re.compile("\W*if\W*\(")
    z2 = re.compile("\)\W*{")
    z3 = re.compile("\W*for\W*\(")
    z4 = re.compile(" ")

    box = []  # tu przechowane sa warunki

    i=0
    while(i<len(lines)):
        line = lines[i]
        if(z1.match(line)):  #ify
            # if
            tmp = line
            tmp = z1.sub("", line)
            tmp = z2.sub("", tmp)
            tmp = z4.sub("", tmp)

            box_item = { 'con' : tmp, 'from' : i, "to" : find_bracelet(i, lines), "if" : 1}
            box.append(box_item)
        if(z3.match(line)):   #fory
            stuff = functions.Loop(line.replace(' ', ''))
            if(stuff==0):
		return -1
            constraint = stuff['var'] + " >= " + str(stuff["lb"]) + " && " + stuff["var"] + " <= " + str(stuff["ub"])
            constraint = z4.sub("", constraint)
            box_item = { 'con' : constraint, 'from' : i, "to" : find_bracelet(i, lines), "if" : 0}
            box.append(box_item)

        i = i + 1


    rem_lines = []
    for item in box:
        if(item['if'] == 1):
            tmp = item['con']
            tmp_items = tmp.split("&&")
            for item2 in box:
                if(item2['from'] != item['from']):
                    if(item2['from'] <= item['from'] and item2['to'] >= item['to']):
                        tmp2 = item2['con']
                        tmp2_items = tmp2.split("&&")
                        x = []
                        for element in tmp_items:
                            if element not in tmp2_items:
                                x.append(element)
                        tmp_items = x
            if(tmp_items == []):
                rem_lines.append(item['from'])
                rem_lines.append(item['to'])

    new_loop = []

    i=0
    while(i<len(lines)):
        if not (i in rem_lines):
            if(lines[i] != '' and lines[i].strip() != ''):
                new_loop.append(lines[i] + "\n")
        i = i + 1


    file= open(_file, 'w')
    file.writelines(new_loop)
    file.close()

# stworz petle z relacjami do kazdej zmiennej w wejsciowym petit tez dodaj definicje
# by sie linie zgadzaly na koniec zapisz w wyjsciowym pliku
def MakeLDPetit(input, output):
    linestring = open(input, 'r').read()
    petit_loop = linestring.split('\n')
    file = open(output, 'w')
    file.write("integer xxyyyx" + "\n")
    in_loop = 0
    for line in petit_loop:
        if('for ' in line):
            in_loop = 1
        if in_loop == 0:
            file.write(line + "\n")
        else:
            if (('for' in line) or ('if ' in line) or (line.isspace())):
                file.write(line + "\n")
            else:
                if(line != ''):
                    file.write("xxyyyx = 1" + "\n")
    file.close()


def ReadStatementNests(plik, dane):
    instrukcje = []
    dane = map(int, dane)


    linestring = open(plik, 'r').read()
    petit_loop = linestring.split('\n')
    i = 1
    nest = 0
    nest_id = -1
    nest_loop = []
    bounds_loop = []
    nest_arr = [-1] # trzyma sciezke do petli
    var_arr = ["X"] # trzyma sciezke do petli
    newloop = 0
    loop_id = -1
    max_loop = 0
    for line in petit_loop:
        if("for " in line and not("endfor" in line)):
            idx_var = re.findall("for.*=", line)[0].replace("for", "").replace("=", "").replace(" ", "")
            lb = re.findall("=.*to", line)[0].replace("to", "").replace("=", "").replace(" ", "")
            ub = re.findall("to.*do", line)[0].replace("to", "").replace("do", "").replace(" ", "")

            nest = nest + 1
            nest_loop.append(nest)
            if max_loop < nest:
                max_loop = nest
            newloop = 1
            loop_id = loop_id + 1
            bounds_loop.append({'loop_id' : loop_id, 'lb' : lb, 'ub' : ub})
            if(len(nest_arr) < nest):
                nest_arr.append(loop_id)
                var_arr.append(idx_var)
            else:
                nest_arr[nest-1] = loop_id;
                var_arr[nest-1] = idx_var
        if("endfor" in line):
            nest = nest - 1
            newloop = 1  # zaznacz ze jestesmy poza wewn petla czyli nowa
            nest_arr.pop()
            var_arr.pop()

        if(i in dane):
            if(instrukcje == []):
                nest_id = nest_id + 1
                st = []
                st.append(i)
                instrukcje.append({'st' : st, 'nest' : nest, 'path' : nest_arr[:], 'vars': var_arr[:], 'max_loop' : max_loop, 'nest_id' : nest_id, 'scatter' : []})
                i = i + 1
                #newloop = 0
                continue
            if(newloop == 1):  # nest != instrukcje[-1]['nest']
                nest_id = nest_id + 1
                st = []
                st.append(i)
                instrukcje.append({'st' : st, 'nest' : nest, 'path' : nest_arr[:], 'vars' : var_arr[:], 'max_loop' : max_loop, 'nest_id' : nest_id, 'scatter' : []})
                newloop = 0
            else:
                instrukcje[-1]['st'].append(i)


        i = i +1

    #global_max = 1
    #for i in range(0,len(instrukcje)):
    #    if (instrukcje[i]['max_loop'] > global_max):
    #        global_max = instrukcje[i]['max_loop']

    #offsets = [0] * global_max
    #for i in range(0,len(instrukcje)):
    #    instrukcje[i]['scatter'] = instrukcje[i]['path'][:]

    #    for j in range(0, global_max):
    #        if(j < len(instrukcje[i]['scatter'])):
    #            instrukcje[i]['scatter'][j] = instrukcje[i]['scatter'][j] + offsets[j]
    #        else:
    #            instrukcje[i]['scatter'].append(offsets[j])
    #            offsets[j] = offsets[j]+1




    combo = []




    combo.append(instrukcje)
    combo.append(nest_loop)
    combo.append(bounds_loop)

    return combo




def MacroStatement(instrukcje, maxl):
    instrukcje2 = instrukcje[:]
    relat = []
    for i in range(0, len(instrukcje2)):
        if(len(instrukcje2[i]['st']) == 1):
            continue
        min_ = min(instrukcje2[i]['st'])
        rest = instrukcje2[i]['st'][:]
        print rest
        rest.remove(min_)
        print rest
        instrukcje2[i]['st'] = min_
        relat.append([min_, rest])




