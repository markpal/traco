from subprocess import Popen, PIPE, STDOUT
import pexpect
import re
import correct
import sys
import time
import subprocess
import islpy as isl
import codegen_ultra
import islpy as isl
ctx = isl.Context()


barv_script = "/home/marek/traco/barvinok-0.39/iscc"
oc_script = "/home/marek/traco/omega_calc/obj/oc < tmp/oc.txt"

    #start = time.time()
    #end = time.time()
    #elapsed = end - start
    #print "Time taken: ", elapsed, "seconds." 

def CreateLex(array1, array2, n):
    #n = len(array1)
    lex = "("

    for i in range(0,n):
        if(lex != "("):
            lex = lex + " || ("
        for j in range(0,i):
            lex = lex + array1[j] + " = " + array2[j] + " && "
        lex = lex + array1[i] + " > " + array2[i]
        if(i>0):
            lex = lex + ")"
        
    return lex + ")"   
        


def iscc_communicate(text, omega=0):
    cmd = barv_script
    if(omega):
        cmd = cmd + ' --format=omega '
    cmd = cmd + ' ' # --isl-no-ast-build-exploit-nested-bounds
    cmd = cmd + ' '
    p= Popen(cmd, shell=True, stdout=PIPE, stdin=PIPE)
    stdout_data = p.communicate(input=text)[0]
    return stdout_data

def isl_ast_codegen(S):
    b = isl.AstBuild.from_context(isl.Set("{:}"))

    m = isl.Map.from_domain_and_range(S, S)
    m = isl.Map.identity(m.get_space())
    m = isl.Map.from_domain(S)

    ast = b.ast_from_schedule(m)
    p = isl.Printer.to_str(isl.DEFAULT_CONTEXT)
    p = p.set_output_format(isl.format.C)
    p.flush()
    p = p.print_ast_node(ast)

    return p.get_str()

def isl_ast_codegen_map(m):
    b = isl.AstBuild.from_context(isl.Set("{:}"))

    ast = b.ast_from_schedule(m)
    p = isl.Printer.to_str(isl.DEFAULT_CONTEXT)
    p = p.set_output_format(isl.format.C)
    p.flush()
    p = p.print_ast_node(ast)

    return p.get_str()

def oc_communicate(s):

    isl_symb = s.get_var_names(isl.dim_type.param)
    outFile = open('tmp/oc.txt', 'w')
    for sym in isl_symb:
        outFile.write('symbolic ' + sym + ";")
    outFile.write('S :=')
    outFile.close()

    outFile = open('tmp/oc.txt', 'a')
    s.print_(outFile, 0, 3)
    outFile.close()

    outFile = open('tmp/oc.txt', 'a')
    outFile.write(';codegen S;')
    outFile.close()

    cmd = oc_script
    p= Popen(cmd, shell=True, stdout=PIPE, stdin=PIPE)
    stdout_data = p.communicate(input='')[0]

    stdout_data = stdout_data.split('\n')
    codegen = []
    for line in stdout_data:
        if not '#' in line and line != '':
            codegen.append(line.replace("s1(", "(").replace("intDiv", "floord"))

    return '\n'.join(codegen)


def s1_to_vec(line,i):
    reg = re.compile('[a-zA-Z]\w*')
    symb = re.findall(reg, line)
    symb = list(set(symb))
    symb_var = ""
    for s in symb:
        symb_var = symb_var + s + ","
    symb_var = symb_var[:-1]    
    
    tmp = line.replace(" ", "")
    tmp = tmp.replace(";", "")
    tmp = tmp.replace("(", "[")
    tmp = tmp.replace(")", "]")
    tmp = "S"+str(i)+" := ["+symb_var+"] -> {" + tmp + "};"
    return tmp

# no barvinok header
def s1_to_vec2(line,i):
    reg = re.compile('[a-zA-Z]\w*')
    symb = re.findall(reg, line)
    symb = list(set(symb))
    symb_var = ""
    for s in symb:
        symb_var = symb_var + s + ","
    symb_var = symb_var[:-1]

    tmp = line.replace(" ", "")
    tmp = tmp.replace(";", "")
    tmp = tmp.replace("(", "[")
    tmp = tmp.replace(")", "]")
    tmp = "["+symb_var+"] -> {" + tmp + "};"
    return tmp

# for rap
def s1_to_vec3(line,i):

    newline = line.replace(" ", "");
    newline = newline.replace("(", "");
    newline = newline.replace(")", "");
    newline = newline.replace(";", "");
    #print newline

    dims = newline.split(',')
    #print dims
    dims2 = []
    for i in range(0, len(dims)):
        if ((i % 2 == 1) or (i == len(dims)-1)):
            dims2.append(dims[i])

    #print dims2
    tmp2 = ','.join(dims2)

    reg = re.compile('[a-zA-Z]\w*')
    symb = re.findall(reg, line)

    #print symb

    symb = list(set(symb))
    symb_var = ""
    for s in symb:
        symb_var = symb_var + s + ","
    symb_var = symb_var[:-1]

    tmp = "["+symb_var+"] -> {[" + tmp2 + "]};"

    return tmp

def RelationExists(rel, n, symb):

    rel_tab = rel.split('} union {')
       
    newrel = ""
    
    if(len(symb)>0):
        newrel = "["
        for s in symb:
            newrel = newrel + s + ","
        newrel = newrel[:-1] + "] -> "
    
    for s in rel_tab:
        reg = re.compile('\[[^\[]+\] -> \[[^\[]+] : ') 
        linia = reg.search(s).group()
        linia = linia.replace("[", "")
        linia = linia.replace("]", "")
        linia = linia.replace("->", ",")
        linia = linia.replace(" ", "")
        linia = linia.replace(":", "")
        zmienne = linia.split(",")
        ex_var = []
        nagl = "["
        for j in range(0,2):
            for i in range(0, n):
                nagl = nagl + zmienne[0] + ","
                del zmienne[0]
            nagl = nagl[:-1]
            for i in range(0, n+1):
                if not zmienne[0] in ex_var:
                    ex_var.append(zmienne[0])
                del zmienne[0]
            if j == 0 :
                nagl = nagl + "] -> ["
        nagl = nagl + "] : exists ( "
        ex_var = list(set(ex_var))
        for j in ex_var:
            nagl = nagl + j + ","
        nagl = nagl[:-1] + " : "
        tmp = reg.sub(nagl, s)
        if "}" in tmp:
            tmp = tmp.replace("}", ")}")
        else:
            tmp = tmp + "); "
        newrel = newrel + tmp

    return newrel

def RepairRk(_Rk, z):
    Rk = _Rk
    if(z > 0):
        Rk = _Rk[:1]
    
    # [1] -> [[
    
    reg = re.compile('\[[^\]]*\] -> \[\[') 
    
    i = 0
    wart_K = reg.findall(Rk)
    _Rk = Rk.split("]] : ")


    Rk = _Rk[0]
    for item in wart_K:
        i = i + 1
        s = item.replace(" -> [[", "")
        s = s.replace("[", "")
        s = s.replace("]", "")
        w = ""
        if(s != "k"):
            w = " k=" + s + " and "
            
        Rk = Rk + "]] : " + w + _Rk[i]
            
    Rk = reg.sub("[[", Rk)

    Rk = Rk.replace(", True)", "")
    Rk = Rk.replace(", False)", "")
    Rk = Rk.replace("[k] ->", "")
    Rk = Rk.replace("[[", "[")
    Rk = Rk.replace("]]", "]")

    if(Rk[0] != "["):
        Rk = "[k] ->" + Rk
    else:
        Rk = "[k," + Rk[1:]
    return Rk   


def NewTileGen(block_set, sym_exvars, vars, _SYM, symb, p_symb, par_tiling, rel, schedule, instrukcje):   
    

    block_set = "BL := " + block_set[0] + ";"
    #print block_set
    R = "R := ["
    R = R + _SYM
    
    
    # dodaj zmienne symb ilorazow
    if(par_tiling):
        for i in range(0,len(sym_exvars)):
            R = R + " fff" + str(i) + ","
    
    R = R[:-1] + "] -> {["
    for s in vars:
        R = R + s + ","
    R = R + "v] -> ["
    for s in sym_exvars:
        R = R + s + ","
    for s in vars:
        R = R + s + ","
    R = R + "v] : "  
    
    if(par_tiling):
        for i in range(0,len(sym_exvars)):
            R = R + " " + sym_exvars[i] + "<= fff" + str(i)+ " and "
    
    R = R + " true };"
    
    
    isl_BL = isl.Set(str(block_set).replace("BL := ", ""))
    isl_R = isl.Map(str(R).replace("R := ", ""))
    isl_BL = isl_BL.apply(isl_R).coalesce()
    isl_BL1 = isl_BL.project_out(isl._isl.dim_type.param, 0, len(sym_exvars)).coalesce()
    

    BL = iscc_communicate(block_set + R + "BL := R(BL);BL;")
    with open("tmp/barv_tiling.txt", "a") as myfile:
        myfile.write(block_set + R + "BL := R(BL);BL;")

    
    

    
    # usun symexvars z symb
    BL = BL.split("->")
    z = "["
    for s in symb:
        z = z + s + ","  
    for s in p_symb:
        z = z + s + "," 
    if(par_tiling):
        for i in range(0,len(sym_exvars)):
            z = z + " fff" + str(i) + ","

    if(z != "["):
        z = z[:-1]
    z = z +  "] -> "
    
    # poprawka gdyby za ii jj wejdzie stala

    pat = "\[" + "\w+,\s*" * len(vars)
    regex = re.compile(pat)
    tmp = "["
    for s in sym_exvars:
        tmp = tmp + s + ", "
    BB = re.sub(pat, tmp, BL[1])
    
    BL = "BL1 := " + z + BB + ";"
    
    if 0==1:
        Setii = iscc_communicate(BL + "BL1;")
        print Setii
    
    start = time.time()
    loop = iscc_communicate(BL + "codegen BL1;")
    islSet = isl.UnionSet(str(z + BB))
    codegen_ultra.codegen(islSet, instrukcje, len(sym_exvars), vars, sym_exvars)
    #sys.exit()
    
    with open("tmp/barv_tiling.txt", "a") as myfile:
        myfile.write(BL + "codegen BL1;")
    end = time.time()
    elapsed = end - start
    print "Time taken: ", elapsed, "seconds."  
 

    loops = []
    loops.append(loop)
    if(schedule == 0):
        return loops
    else:
    ##### OBLICZANIE REPR TILE
        
        nloop = ""
        srepr = ""
        with open('sources_of_slices.txt') as f:
            content = f.readlines()
            srepr = content[0]
    
        
        tmp = ""
        for s in sym_exvars:
            tmp = tmp + s + ","


        
        srepr = srepr.replace("{ [", "{ [" + tmp)
        srepr = srepr.replace("{[", "{ [" + tmp)
        
        Rel_Z = "R := {["
        
        for i in range(0, 2*len(sym_exvars)):
            Rel_Z = Rel_Z + "i" + str(i) + ","
        Rel_Z = Rel_Z + "m] -> ["
        for i in range(0, len(sym_exvars)):
            Rel_Z = Rel_Z + "i" + str(i) + ","
        Rel_Z = Rel_Z[:-1] + "] };"
        
        output = iscc_communicate(BL + "Srepr := " + srepr + ";"+Rel_Z +"B := BL1 * Srepr;card B;print \"###\";codegen R(B);").split('"###"')
        srepr_loop = output[1]
        
 
        
        ile = output[0]
        fs = 0 
        if("{ 1 :" in ile):
            fs = 1
        
        
        # ---------
        tmp = BL[:-1].replace("BL1 := ", "")

        rs = tmp + "->" + tmp + ";"
        #rs = iscc_communicate(tmp + "->" + tmp + ";")
        
        I = "I :={["
        for i in range(0,len(sym_exvars)):
            I = I + "i" + str(i) + ","
        I = I[:-1] + "] -> ["
        for i in range(0,len(sym_exvars)):
            I = I + "i" + str(i) + ","
        I = I[:-1] + "]};"
        
        start = time.time()
        rpaczka = iscc_communicate('R:=' + rel + ';Rst := R^+;Rst;'+I+'Rst+I;')
        rpaczka = rpaczka.split('\n')
        rplus = rpaczka[0]
        rstar = rpaczka[1]
        #rstar = iscc_communicate('R:=' + rel + ';'+I+'R^+ + I;')
        end = time.time()
        elapsed = end - start
        print "Time taken: ", elapsed, "seconds."  

        
        tmp = ""
        tmp2 = ""
        for s in sym_exvars:
            tmp = tmp + s + ","
            tmp2 = tmp2 + s + "',"
        
        rplus = rplus.replace("{ [","{ [" + tmp);
        rplus = rplus.replace("-> [","-> [" + tmp2);
        rplus = rplus.replace("; [","; [" + tmp);
        
        rstar = rstar.replace("{ [","{ [" + tmp);
        rstar = rstar.replace("-> [","-> [" + tmp2);
        rstar = rstar.replace("; [","; [" + tmp);
        
        rt_red = rel
        rt_red = rt_red.replace("{ [","{ [" + tmp);
        rt_red = rt_red.replace("-> [","-> [" + tmp2);
        rt_red = rt_red.replace("; [","; [" + tmp);
        
        sym_tmp = []
        rlex = "RLEX := {["
        for s in sym_exvars:
            rlex = rlex + s + ","
            sym_tmp.append(s+"'")
        rlex = rlex[:-1] + '] -> ['
        for s in sym_exvars:
            rlex = rlex + s + "',"
        rlex = rlex[:-1] + '] : '
        rlex = rlex + CreateLex(sym_tmp, sym_exvars, len(sym_exvars)) + "};" 

        rs = iscc_communicate("RS := " + rs + "Rplus := " + rstar + ";RS*Rplus;", 0)        
        #rp = iscc_communicate("RS := " + rs + ";Rplus := " + rplus + ";RS*Rplus;", 0)

        rt_red = iscc_communicate("RS:= " + rs + ";RTRED := " + rt_red + ";RS*RTRED;", 0)

        rs = iscc_communicate(rs + ";", 1).split('\n')[0]
        
        rs = RelationExists(rs, len(sym_exvars), symb)
       
        srepr_loop = srepr_loop.split('\n')
        
        for i in range(0, len(srepr_loop)):
            if "for" in srepr_loop[i]:
                srepr_loop.insert(i, "#pragma omp parallel for")
                break

        
        st_reg = re.compile('\s*\(.*\);')
        vecs = []
        taby = []
        for line in srepr_loop:
            if(st_reg.match(line)):
                vecs.append(s1_to_vec(line, len(vecs)))
                taby.append(correct.whites(line))
                
                
        #R_T = iscc_communicate("RS := " + rs + ";RS;")
        cmd = "RT :=" + rs + ";"     
        for i in range(0, len(vecs)):
            cmd = cmd + vecs[i] + "codegen RT(S" + str(i) + ');print "###";'
            
        
        cmd = iscc_communicate(cmd)

        
        
        cmd = cmd.split('"###"') 
        new_loop = []   
        i=0
        for line in srepr_loop:
            if(st_reg.match(line)):
                petla = cmd[i].split('\n')
                for s in petla:
                    new_loop.append(taby[i] + s)
                i = i + 1
            else:
                new_loop.append(line)
        
        #print new_loop
        nloop = ""
        for line in new_loop:
            if line != '':
                nloop = nloop + line + "\n"
        nloop = nloop[:-1]
        loops.append(nloop)


        
        #fs = 1
        if(fs==1):
            UDS = iscc_communicate('R := ' + rel + ";dom R - ran R;")
            tmp = "{ ["
            for s in sym_exvars:
                tmp = tmp + s + ","
                
            UDS = UDS.replace("{ [", tmp)
            UDS = UDS.replace("; [", tmp)
    
            tuds = iscc_communicate(BL + 'UDS := ' + UDS + ';'+Rel_Z+'R(BL1*UDS);')
            
            rt_red = iscc_communicate(rt_red + ";", 1).split('\n')[0]     
            rt_red= RelationExists(rt_red, len(sym_exvars), symb)
            

            rk = iscc_communicate(rlex + 'RT_RED := ' + rt_red + "*RLEX;pow RT_RED;")
            #rk = iscc_communicate('RT_RED := ' + rt_red + ";"+I+"Z := RT_RED-I;pow Z;")

            rk = RepairRk(rk, 1);
            #S(k) = Rk  (TILE_UDS) -  R_T+  compose  Rk (TILE_UDS)

            cmd_sk = rlex + I + "Rk := " + rk +";TUDS :=" + tuds + ";" + 'RT_RED := ' + rt_red + "*RLEX;RP :=RT_RED^+;Sk := Rk(TUDS) - RP(Rk(TUDS));Sk;"
            #cmd_sk = I + "Rk := " + rk +";TUDS :=" + tuds + ";" + "RP :=" + rp +"-I;Sk := Rk(TUDS) - RP(Rk(TUDS));Sk;"

            sk = iscc_communicate(cmd_sk)

            
            
            reg = re.compile("^[^{]+")
            tmp = "["
            for s in symb:
                tmp = tmp + s + ","
            tmp = tmp[:-1] + "] -> " 
            
            sk = reg.sub(tmp, sk)
            sk = sk.replace("{ [", "{ [k,")
            sk = sk.replace("; [", "; [k,")
            #print sk
            
            tudsk = tuds.replace("{ [", "{ [0,")
            tudsk = tudsk.replace("; [", "; [0,")
            
            fsloop = iscc_communicate("Sk := "+sk+";TUDS := "+tudsk+";Sk := Sk + TUDS; codegen Sk;")

            #usun k z symb i dodaj na poczatek krotek

            loops.append(fsloop)

    
        return loops



