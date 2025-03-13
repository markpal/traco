import islpy as isl
import relation_util


def GetConstr(list_in, list_out, rel):   #lista zmiennych wej, lista zmiennych wyj, relacja

    sep = '] :'
    conj_sep = 'union'

    #rel = isl.Map(rel)


    for i in range(0, len(list_in)):
        rel = rel.set_dim_name(isl.dim_type.in_, i, list_in[i])

    for i in range(0, len(list_out)):
        rel = rel.set_dim_name(isl.dim_type.out, i, list_out[i])


    z = relation_util.islMaptoOmegaStr(rel)


    conj_list = z.split(conj_sep)

    constraints = ''

    for c in conj_list:
        item = c.split(sep)[1]
        constraints = constraints + " ( " +  item  + " ) or "

    constraints = constraints.replace('}', '')
    constraints = constraints[:-3]

    constraints = " ( " + constraints + " ) "

    return constraints


def GetConstrSet(list_set, s):  # lista zmiennych wej, lista zmiennych wyj, relacja

        sep = '] :'
        conj_sep = 'union'

        # rel = isl.Map(rel)


        for i in range(0, len(list_set)):
            s = s.set_dim_name(isl.dim_type.set, i, list_set[i])


        z = relation_util.islSettoOmegaStr(s)

        conj_list = z.split(conj_sep)

        constraints = ''

        for c in conj_list:
            item = c.split(sep)[1]
            constraints = constraints + " ( " + item + " ) or "

        constraints = constraints.replace('}', '')
        constraints = constraints[:-3]

        constraints = " ( " + constraints + " ) "

        return constraints



#rel = "{ [i, j, 6] -> [i', j', 6] : i >= 0 and j >= 8 + i and i' <= 9 and j <= j' <= 9 and j' <= 7 + i'; [i, 5, 6] -> [i', j', 6] : i >= 0 and i' <= 9 and 7 + i <= j' <= 9 and j' <= 7 + i'; [i, j, 6] -> [i', 5, 6] : i >= 0 and 8 + i <= j <= 9 and -7 + j <= i' <= 9; [i, j, 6] -> [i', j, 6] : i >= 0 and 0 <= j <= 9 and i < i' <= 9; [i, j, v] -> [i, j, v] }"

#in_ = ["_i0", "_i1", "_i2"]
#out_ = ["_o0", "_o1", "_o2"]


#print GetConstr(in_, out_, rel)