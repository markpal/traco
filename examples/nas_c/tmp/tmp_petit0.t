integer i3
integer N1
integer N2
integer i2
integer N3
integer N4
integer i1
integer N5
integer N6
integer u(0:9999,0:9999,0:9999)
integer d1
integer d2
integer d3
integer z(0:9999,0:9999,0:9999)
integer N7
integer t1
integer N8
integer N9
integer N10
integer t2
integer N11
for i3 = N1 to N2 do
for i2 = N3 to N4 do
for i1 = N5 to N6 do
u(2*i1-d1,2*i2-d2,2*i3-d3)=u(2*i1-d1,2*i2-d2,2*i3-d3)+z(i1,i2,i3)
endfor
for i1 = 1 to N7 do
u(2*i1-t1,2*i2-d2,2*i3-d3)=u(2*i1-t1,2*i2-d2,2*i3-d3)+0.5*(z(i1+1,i2,i3)+z(i1,i2,i3))
endfor
endfor
for i2 = 1 to N8 do
for i1 = N9 to N10 do
u(2*i1-d1,2*i2-t2,2*i3-d3)=u(2*i1-d1,2*i2-t2,2*i3-d3)+0.5*(z(i1,i2+1,i3)+z(i1,i2,i3))
endfor
for i1 = 1 to N11 do
u(2*i1-t1,2*i2-t2,2*i3-d3)=u(2*i1-t1,2*i2-t2,2*i3-d3)+0.25*(z(i1+1,i2+1,i3)+z(i1+1,i2,i3)+z(i1,i2+1,i3)+z(i1,i2,i3))
endfor
endfor
endfor


