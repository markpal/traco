import re
import numpy
import multipolyfit

def isint(x):
    return abs(float(x) - float(round(x))) < 0.0001

loop1 = '''for( c1 = 0; c1 <= floord(N - 1, 11); c1 += 1)
  for( c3 = 0; c3 <= min(floord(N - 2, 29), (11 * c1 + 9) / 29); c3 += 1)
    for( c4 = 0; c4 <= 1; c4 += 1) {
      if (c4 == 1) {
        for( c7 = max(-N + 11 * c1 + 1, -N + 29 * c3 + 2); c7 <= min(0, -N + 11 * c1 + 11); c7 += 1)
          for( c9 = 29 * c3 - c7 + 1; c9 <= min(N - 1, 29 * c3 - c7 + 29); c9 += 1)
            for( c10 = max(0, 29 * c3 - c7 - c9 + 2); c10 <= 1; c10 += 1) {
              if (c10 == 1) {
                S[(-c7)][c9] = S[(-c7)][c9] + S[(-c7)+1][c9-1];
              } else {
                if (N + c7 >= 11 * c1 + 2)
                  for( c11 = 0; c11 <= 29 * c3; c11 += 1)
                    S[(-c7)][c9] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9] + S[(-c7)][c9];
                for( c11 = 29 * c3 + 1; c11 < c7 + c9; c11 += 1)
                  S[(-c7)][c9] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9] + S[(-c7)][c9];
              }
            }
      } else
        for( c5 = 0; c5 <= 29 * c3 / 119; c5 += 1)
          for( c7 = max(-N + 11 * c1 + 1, -N + 29 * c3 + 2); c7 <= min(0, -N + 11 * c1 + 11); c7 += 1) {
            if (N + c7 >= 11 * c1 + 2) {
              for( c11 = 119 * c5; c11 <= min(29 * c3, 119 * c5 + 118); c11 += 1)
                S[(-c7)][(29*c3-c7+1)] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][(29*c3-c7+1)] + S[(-c7)][(29*c3-c7+1)];
            } else
              for( c9 = N - 11 * c1 + 29 * c3; c9 <= min(N - 1, N - 11 * c1 + 29 * c3 + 28); c9 += 1)
                for( c11 = 119 * c5; c11 <= min(29 * c3, 119 * c5 + 118); c11 += 1)
                  S[(N-11*c1-1)][c9] = S[(N-11*c1-1)][c11+(N-11*c1-1)] + S[c11+(N-11*c1-1)+1][c9] + S[(N-11*c1-1)][c9];
          }
    }

'''

loop = '''for( c1 = 0; c1 <= floord(26 * N - 33, 133); c1 += 1)
  #pragma omp parallel for
  for( c3 = max(0, c1 - (N + 6) / 7 + 1); c3 <= min((N - 2) / 19, (7 * c1 + 5) / 26); c3 += 1)
    for( c4 = 0; c4 <= 1; c4 += 1) {
      if (c4 == 1) {
        for( c7 = max(-N + 7 * c1 - 7 * c3 + 1, -N + 19 * c3 + 2); c7 <= min(0, -N + 7 * c1 - 7 * c3 + 7); c7 += 1)
          for( c9 = 19 * c3 - c7 + 1; c9 <= min(N - 1, 19 * c3 - c7 + 19); c9 += 1)
            for( c10 = max(0, 19 * c3 - c7 - c9 + 2); c10 <= 1; c10 += 1) {
              if (c10 == 1) {
                S[(-c7)][c9] = S[(-c7)][c9] + S[(-c7)+1][c9-1];
              } else {
                if (N + 7 * c3 + c7 >= 7 * c1 + 2)
                  for( c11 = 0; c11 <= 19 * c3; c11 += 1)
                    S[(-c7)][c9] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9] + S[(-c7)][c9];
                for( c11 = 19 * c3 + 1; c11 < c7 + c9; c11 += 1)
                  S[(-c7)][c9] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9] + S[(-c7)][c9];
              }
            }
      } else
        for( c5 = 0; c5 <= 19 * c3 / 49; c5 += 1)
          for( c7 = max(-N + 7 * c1 - 7 * c3 + 1, -N + 19 * c3 + 2); c7 <= min(0, -N + 7 * c1 - 7 * c3 + 7); c7 += 1) {
            if (N + 7 * c3 + c7 >= 7 * c1 + 2) {
              for( c11 = 49 * c5; c11 <= min(19 * c3, 49 * c5 + 48); c11 += 1)
                S[(-c7)][(19*c3-c7+1)] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][(19*c3-c7+1)] + S[(-c7)][(19*c3-c7+1)];
            } else
              for( c9 = N - 7 * c1 + 26 * c3; c9 <= min(N - 1, N - 7 * c1 + 26 * c3 + 18); c9 += 1)
                for( c11 = 49 * c5; c11 <= min(19 * c3, 49 * c5 + 48); c11 += 1)
                  S[(N-7*c1+7*c3-1)][c9] = S[(N-7*c1+7*c3-1)][c11+(N-7*c1+7*c3-1)] + S[c11+(N-7*c1+7*c3-1)+1][c9] + S[(N-7*c1+7*c3-1)][c9];
          }
    }

'''

loop1  = '''for( c1 = 0; c1 <= floord(40 * N - 51, 319); c1 += 1)
  #pragma omp parallel for
  for( c3 = max(0, c1 - (N + 10) / 11 + 1); c3 <= min((N - 2) / 29, (11 * c1 + 9) / 40); c3 += 1)
    for( c4 = 0; c4 <= 1; c4 += 1) {
      if (c4 == 1) {
        for( c7 = max(-N + 11 * c1 - 11 * c3 + 1, -N + 29 * c3 + 2); c7 <= min(0, -N + 11 * c1 - 11 * c3 + 11); c7 += 1)
          for( c9 = 29 * c3 - c7 + 1; c9 <= min(N - 1, 29 * c3 - c7 + 29); c9 += 1)
            for( c10 = max(0, 29 * c3 - c7 - c9 + 2); c10 <= 1; c10 += 1) {
              if (c10 == 1) {
                S[(-c7)][c9] = S[(-c7)][c9] + S[(-c7)+1][c9-1];
              } else {
                if (N + 11 * c3 + c7 >= 11 * c1 + 2)
                  for( c11 = 0; c11 <= 29 * c3; c11 += 1)
                    S[(-c7)][c9] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9] + S[(-c7)][c9];
                for( c11 = 29 * c3 + 1; c11 < c7 + c9; c11 += 1)
                  S[(-c7)][c9] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][c9] + S[(-c7)][c9];
              }
            }
      } else
        for( c5 = 0; c5 <= 29 * c3 / 119; c5 += 1)
          for( c7 = max(-N + 11 * c1 - 11 * c3 + 1, -N + 29 * c3 + 2); c7 <= min(0, -N + 11 * c1 - 11 * c3 + 11); c7 += 1) {
            if (N + 11 * c3 + c7 >= 11 * c1 + 2) {
              for( c11 = 119 * c5; c11 <= min(29 * c3, 119 * c5 + 118); c11 += 1)
                S[(-c7)][(29*c3-c7+1)] = S[(-c7)][c11+(-c7)] + S[c11+(-c7)+1][(29*c3-c7+1)] + S[(-c7)][(29*c3-c7+1)];
            } else
              for( c9 = N - 11 * c1 + 40 * c3; c9 <= min(N - 1, N - 11 * c1 + 40 * c3 + 28); c9 += 1)
                for( c11 = 119 * c5; c11 <= min(29 * c3, 119 * c5 + 118); c11 += 1)
                  S[(N-11*c1+11*c3-1)][c9] = S[(N-11*c1+11*c3-1)][c11+(N-11*c1+11*c3-1)] + S[c11+(N-11*c1+11*c3-1)+1][c9] + S[(N-11*c1+11*c3-1)][c9];
          }
    }
'''





b = [7,19,49]
b1 = [11,29,119]

loop = loop.split('\n')
loop1 = loop1.split('\n')


for i in range(0, len(loop)):
    vals = re.findall('c*\d+', loop[i])
    vals1 = re.findall('c*\d+', loop1[i])

    for j in range(len(vals)-1, -1, -1):  # remove c1, c2...
        if 'c' in vals[j]:
            del vals[j]
            del vals1[j]
        elif vals[j] == vals1[j]:   # remove const
            del vals[j]
            del vals1[j]



    parvals = []
    for j in range(0, len(vals)):
        if vals[j] == str(b[0]):
            parvals.append('b1')
        elif vals[j] == str(b[1]):
            parvals.append('b2')
        elif vals[j] == str(b[2]):
            parvals.append('b3')
        else:  #houston probelm
            w = []
            ww = ''
            x = [b[0], b1[0]]
            y = [int(vals[j]), int(vals1[j])]
            b1fit = numpy.polyfit(x, y, 1)

            if (isint(b1fit[0]) and isint(b1fit[1])):
                w = b1fit
                ww = 'b1'
            x = [b[1], b1[1]]
            b2fit = numpy.polyfit(x, y, 1)
            if (isint(b2fit[0]) and isint(b2fit[1])):
                if len(w) > 0:     # juz znalazl
                    if(abs(b2fit[1]) < abs(w[1])):  # wez mniejszy wyraz wolny
                        w = b2fit
                        ww = 'b2'
                else:
                    w = b2fit
                    ww = 'b2'


            x = [b[2], b1[2]]
            print x
            b3fit = numpy.polyfit(x, y, 1)
            print b3fit
            if (isint(b3fit[0]) and isint(b3fit[1])):
                if len(w) > 0:  # juz znalazl
                    if (abs(b3fit[1]) < abs(w[1])):
                        w = b3fit
                        ww = 'b3'
                else:
                    w = b3fit
                    ww = 'b3'


            lacznik = ''
            if(w[1] > 0):
                lacznik = '+'

            mn1 = str(w[0]).replace('.0', '')
            if(mn1 == '1'):
                mn1 = ''
            else:
                mn1 += '*'

            tmp = '(' + mn1 +  ww + lacznik + str(w[1]).replace('.0', '') + ')'

            parvals.append(tmp)

    #if(len(vals) > 0):
    #    print vals
    #    print vals1
    #    print parvals


    #print loop[i]
    s = loop1[i]

    for j in range(0, len(vals)):
        #s = s.replace(vals1[j], parvals[j])
        s = re.sub(r'\b'+vals1[j]+r'\b', parvals[j], s)

    print s






#x = [7,11,111,222]
#y = [12,20,220,442]
#print  numpy.polyfit(x, y,  1)





