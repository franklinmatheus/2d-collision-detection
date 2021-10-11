import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

infile = "./data/1000squares.txt"
outfile = "./data/1000squares_out.txt"

firstline = True
window_size = 0
squares_x = []
squares_y = []
squares_size = []
for line in open(infile, "r", encoding="utf8").read().split('\n'):
    if (line != ''):
        if (firstline):
            window_size = int(line)
            firstline = False
        else:
            square = line.split(' ')
            squares_x.append(int(square[0]))
            squares_y.append(int(square[1]))
            squares_size.append(int(square[2]))

fig, ax = plt.subplots(figsize=(15,15))

for i in range(0,len(squares_x)):
    ax.add_patch(Rectangle((squares_x[i], squares_y[i]), squares_size[i], squares_size[i],
                edgecolor = 'red',
                facecolor = 'gray',
                fill=True,
                lw=1))
    #ax.text(squares_x[i], squares_y[i], str(i+1))

plt.xlim([0, window_size])
plt.ylim([0, window_size])
plt.axis('off')
fig.savefig("input.png", dpi=200)

firstline = True
window_size = 0
squares_x = []
squares_y = []
squares_size = []
squares_level = []
squares_collide = []

for line in open(outfile, "r", encoding="utf8").read().split('\n'):
    if (line != ''):
        if (firstline):
            window_size = int(line)
            firstline = False
        else:
            square = line.split(',')
            squares_x.append(int(square[0]))
            squares_y.append(int(square[1]))
            squares_size.append(int(square[2]))
            squares_collide.append(int(square[3]))

fig, ax = plt.subplots(figsize=(15,15))

for i in range(0,len(squares_x)):
    #if (squares_level[i] != 0): continue

    bgcolor = 'white'
    bordcolor = 'black'
    if (squares_collide[i] == 1): bgcolor = 'red'

    ax.add_patch(Rectangle((squares_x[i], squares_y[i]), squares_size[i], squares_size[i],
                edgecolor = bordcolor,
                facecolor = bgcolor,
                fill=True,
                lw=1))
    ax.text(squares_x[i], squares_y[i], str(i+1))

'''''
plt.hlines(100,0,200)
plt.vlines(100,0,200)

plt.hlines(150,0,200,'r')
plt.hlines(50,0,200,'r')
plt.vlines(150,0,200,'r')
plt.vlines(50,0,200,'r')

plt.hlines(175,0,200,'g')
plt.hlines(125,0,200,'g')
plt.hlines(75,0,200,'g')
plt.hlines(25,0,200,'g')
plt.vlines(175,0,200,'g')
plt.vlines(125,0,200,'g')
plt.vlines(75,0,200,'g')
plt.vlines(25,0,200,'g')
'''''

plt.xlim([0, window_size])
plt.ylim([0, window_size])
plt.axis('off')
fig.savefig("result.png", dpi=200)