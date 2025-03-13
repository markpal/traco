import re
import functions 
import sys


def convert_loop(input_loop, block=[]):

#    input_loop = []
    output_loop = []
    endl = []
    def_lines = []

    def_lines.append('builtin integer myfun()')

    for_level = 0  #ktora petla for zagniezdzona

    
#    input_loop.append("for(i=1; i<=100; i++){")
#    input_loop.append("  a1_1[i][i] = 11;")
#    input_loop.append("}")
    
    varsn = []
    funcs = []
    nest = 0
    odst = 0
    
    #dodaj klamry do brakujacych for
    curly = []


    for i in range(0,len(input_loop)):
        line = input_loop[i]
        line = line.replace("\t", "")
        line = line.replace(" ", "")

        line = line.replace("elseif", " else if")
        line = line.replace("int", "")
        # usun komentarze
        pattern = re.compile(r"//.*$")
        line = pattern.sub("", line)
        # zmien zmienna out
        pattern = re.compile(r"\\bout\\b")
        line = pattern.sub("out1", line)



        if(len(block) > 0):
            stuff = functions.Loop(line, block[for_level])
        else:
            stuff = functions.Loop(line)

        ifek = functions.If_Statement(line)

        if(stuff != 0):
            for_level = for_level + 1



        if(stuff != 0 or ifek != ""):
            if "{" in line:
                nest = 1
            else:
                nest = 0

            for j in range(i+1,len(input_loop)):
                line2 = input_loop[j]
                if line2.isspace():
                    continue
                if "{" in line2:
                    nest = nest + 1
                if "}" in line2:
                    nest = nest - 1
                if "for" in line2:
                    continue

                if nest == 0:
                    if ifek != "" and not 'else' in input_loop[j+1]:
                        #input_loop[j] = "endif"
                        curly.append([j, "endif"])
                    else:
                        if(stuff != 0):
                            curly.append([j, "endfor"])
                            for_level = for_level - 1
                        #input_loop[j] = "endfor"
                    break

    
    curly = sorted(curly, key=lambda curly: curly[0], reverse=True)
    for c in curly:
        input_loop.insert(c[0]+1, c[1])

    
    for line in input_loop:
        
        if "pragma" in line:
            continue
        
        nest = 0
        
        line = line.replace("\t", "")
        line = line.replace(" ", "")
        line = line.replace("elseif", " else if")
        line = line.replace("int", "")
        pattern = re.compile(r"//.*$")
        line = pattern.sub("", line)
        pattern = re.compile(r"\\bout\\b")
        line = pattern.sub("out1", line)
        
        if(len(block) > 0):
            stuff = functions.Loop(line, block[for_level])
        else:
            stuff = functions.Loop(line)
    
        if(stuff != 0):
            output_loop.append(stuff["new_loop"])
#            endl.append("endfor")

        ifek = functions.If_Statement(line)
        
        if(ifek != ""):
            output_loop.append(ifek)
      
        varsn = functions.CollectVars(varsn, line)

    
        pattern = re.compile(r"\W*(\}|\{)\W*")
    
        if(ifek == "" and stuff == 0 and (not pattern.match(line))):
            pattern = re.compile(r"\w+\(");
            items = pattern.findall(line)
            for item in items:
                z = item.replace("(", "")
                if (z == "max" or z == "MAX" or z == "min" or z == "MIN"): # petit je zna
                    continue


                if not (z in funcs):  # no reduncancy
                    funcs.append(z)


            output_loop.append(functions.ConvertSt(line))
            #print funcs
            #sys.exit(0)


    for f in funcs:
        def_lines.append('builtin integer ' + f +'()')
        if f in varsn:
            varsn.remove(f)        # remove variable witch is a fun()



         
    for _var in varsn:
        dim_var =functions._DIM(_var)
        if dim_var is not None and dim_var >= 0:
            defv = functions.MakeDef(_var, dim_var)
            def_lines.append(defv)
            
 #   for line in def_lines:
 #       print line
        
#    for line in output_loop:
#        print(line)
        
 #   for line in endl:
 #       print line

    return def_lines + output_loop #+ endl

