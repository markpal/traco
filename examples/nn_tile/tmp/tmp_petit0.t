integer out1
integer outputNeurons
integer sum(0:9999)
integer hid
integer hiddenNeurons
integer hidden(0:9999)
integer who(0:9999,0:9999)
integer actual(0:9999)
for out1=0 to (outputNeurons-1) do
sum(out1)=0.0
for hid=0 to (hiddenNeurons-1) do
sum(out1)+=hidden(hid)*who(hid,out1)
endfor
sum(out1)+=who(hiddenNeurons,out1)
actual(out1)=sum(out1)
endfor

