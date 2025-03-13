import subprocess

space = [1,2,4,6,8,12,16,24,32,40,48,64,96,128,150,200,256,300,400,512]
l = len(space)

for i in range(0,l):
	for j in range(0,l):
		for k in range(0,l):
			ts = str(space[i]) + "," + str(space[j]) + "," + str(space[k])
			print ts 
			process = subprocess.Popen('./a.out ' + ts, shell=True, stdout=subprocess.PIPE)
			process.wait()
			print process.returncode

