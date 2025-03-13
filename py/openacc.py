def get_tab(line):
    return len(" " * (len(line) - len(line.lstrip())))

def CreateACCCode(lines, var_st):
    copys = CreateCopyClausules(var_st)
    acc = 100
    lines2 = []
    lines2.append("#pragma acc data" + copys)
    lines2.append("{")
    for i in range(0, len(lines)):
        if "pragma omp parallel for" in lines[i]:
            s = lines[i].replace("omp", "acc")
            s = s.replace("parallel", "")
            s = s.replace("for", "kernels loop")
            lines2.append(s)
            acc = get_tab(lines[i+1])
        else:
            if("for" in lines[i] and get_tab(lines[i]) > acc):
                lines2.append("#pragma acc loop")
            if(lines[i] != ""):
                lines2.append(lines[i])
    lines2.append("}")

    return lines2


def CreateCopyClausules(var_st):
    copyin = []
    copyout = []
    copyinout = []
    for _var in var_st.keys():
        rw = var_st[_var]
        if(rw[0] > 0 and rw[1] > 0):
            copyinout.append(_var)
        if(rw[0] > 0 and rw[1] == 0):
            copyin.append(_var)
        if(rw[0] == 0 and rw[1] > 0):
            copyout.append(_var)
    s = " "

    if(len(copyin)>0):
        s = s + "copyin(" + ",".join(copyin) + ") "
    if(len(copyout)>0):
        s = s + "copyout(" + ",".join(copyout) + ") "
    if(len(copyinout)>0):
        s = s + "copyinout(" + ",".join(copyinout) + ") "

    return s

