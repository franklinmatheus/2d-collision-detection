import numpy as np

n = 100
size_square = 10
size_window = 200

x = np.random.randint(low=0,high=size_window-size_square,size=n)
y = np.random.randint(low=0,high=size_window-size_square,size=n)

file = "data/"+str(n)+"squares.txt"
file = open(file,"w+",encoding="utf-8")
content = ""

content += str(size_window) + "\n"
for i in range(0,n):
    content += str(x[i]) + " " + str(y[i]) + " " + str(size_square) + "\n"

file.write(content)
file.close()