import iscc
import islpy as isl
import clanpy
import re

##############################################################################
# HUMAN SORTING   S8 S9 S12
def natural_sort(l):
    convert = lambda text: int(text) if text.isdigit() else text.lower()
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
    return sorted(l, key = alphanum_key)
##############################################################################

class Scop:
    R = ''
    LD = ''
    IND = ''



##############################################################################

scopfile = 'rna_pet.c'

#######################################################################
# BARVINOK + PET
cmd = 'p := parse_file "' + scopfile + '";'
cmd += 'Domain := p[0];'
cmd += 'Write := p[1] + p[2];'
cmd += 'Read := p[3];'
cmd += 'Schedule := map p[4];'
cmd += 'print "Schedule";'
cmd += 'print Schedule;'
cmd += 'Before := Schedule << Schedule;'
cmd += 'RaW := (Write . (Read^-1)) * Before;'
cmd += 'WaW := (Write . (Write^-1)) * Before;'
cmd += 'WaR := (Read . (Write^-1)) * Before;'
cmd += 'print "LD";'
cmd += 'print Domain;'
cmd += 'print "RaW deps";'
cmd += 'print RaW;'
cmd += 'print "WaW deps";'
cmd += 'print WaW;'
cmd += 'print "WaR deps";'
cmd += 'print WaR;'
cmd += 'R := WaR + WaW + RaW;'
cmd += 'print "R";'
cmd += 'R;'
cmd += 'LDR := domain R + range R;'
cmd += 'IND := Domain - LDR;'
cmd += 'print "IND";'
cmd += 'print IND;'
#######################################################################
# RESULT TO ISLPY

output = loop_x = iscc.iscc_communicate(cmd)

output = output.split('\n')

schedule = output[1]
ld = output[3]
rel = output[11]
ind = output[13]

ld = isl.UnionSet(ld)
ind = isl.UnionSet(ind)
schedule = isl.UnionMap(schedule)
strrel = rel

rel = isl.UnionMap(rel)
print rel

print schedule

########################################################################
rels = strrel.split(';')
prefix = re.findall(r'[^{]*{', rels[0])[0]

maps = []
for q in rels:
    if prefix not in q:
        q = prefix + q
    q += '}'
    maps.append(isl.Map(q))

########################################################################

#rel = isl.UnionMap(rel).coalesce()

print "LD"
print ld
#print "SCHEDULE"
#print schedule
#print "REL"
#print rel
# #print "IND"
#print ind

#######################################################################
# FINISH

# NEXT CLAN AND MATH LINES TO S_NUMBER

cl = clanpy.ClanPy()
cl.loop_path = scopfile

cl.Load()

#print cl.statements[len(cl.statements)-1].scop+1

statements = re.findall(r'S_\d+', str(ld))

statements = natural_sort(statements)

#assert len(cl.statements) == len(statements), "Pet & Clan return found different number of statements"

# for i in range(0, len(cl.statements)):
#    cl.statements[i].pet_symbol = statements[i]

#######################################################################

# SPlit all to scops  S_1[i,j]

items = re.findall(r'S_\d+[^\]]*\]', str(ld))
items = natural_sort(items)

items_ = []
for item in items:
    items_.append(isl.Set('{' + item + '}'))

#scop_number = cl.statements[len(cl.statements)-1].scop+1
#print items
#scop_number = 2;

#scops = []

#for i in range(0, scop_number):
 #   openscop = Scop()
  #  tmp_set = isl.UnionSet('{[]}')
   # for j in range(0, len(items)):
    #    if(cl.statements[j].scop == i):
     #       tmp_set = items_[j].union(tmp_set)
  #  openscop.LD = tmp_set.intersect(ld)
  #  openscop.IND = tmp_set.intersect(ind)

    #tmp_rel = isl.UnionMap.from_domain_and_range(tmp_set,tmp_set)
    #openscop.R = tmp_rel.intersect(rel)
#    scops.append(openscop)

#print openscop.LD



#######################################################################
