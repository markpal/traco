! loop indices
integer i, j

! constants
integer N1, N2, N3, N4

! variables
integer ki1, ki2, k, c2

! arrays
integer u(0:9999,0:9999,0:9999,0:9999), phi1(0:9999,0:9999), phi2(0:9999,0:9999)

for j=N1 to N2 do
  for i=N3 to N4 do
    
    k = ki1
    
    phi1(i,j) = c2*(  u(5,i,j,k) - 0.50 * (  u(2,i,j,k) ** 2 + u(3,i,j,k) ** 2 + u(4,i,j,k) ** 2 ) / u(1,i,j,k) )
    
    k = ki2
    
    phi2(i,j) = c2*(  u(5,i,j,k) - 0.50 * (  u(2,i,j,k) ** 2 + u(3,i,j,k) ** 2 + u(4,i,j,k) ** 2 ) / u(1,i,j,k) )
  endfor
endfor
