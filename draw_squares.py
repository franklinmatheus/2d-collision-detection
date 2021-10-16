import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

outfile = "./data/sample_out.txt"

firstline = True
window_size = 0
squares_x = []
squares_y = []
squares_size = []
squares_level = []
squares_collide = []
squares_comparisons = []

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
            squares_comparisons.append(int(square[4]))

fig, ax = plt.subplots(figsize=(10,10))

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
    #ax.text(squares_x[i]+1, squares_y[i]+1, str(i+1))


#plt.hlines(128,0,256,lw=5)
#plt.vlines(128,0,256,lw=5)

#plt.hlines(192,0,128,'r',lw=3)
#plt.vlines(64,128,256,'r',lw=3)

#plt.hlines(224,64,128,'g',lw=1)
#plt.vlines(96,192,256,'g',lw=1)

plt.xlim([0, window_size])
plt.ylim([0, window_size])
plt.axis('off')
fig.savefig("result.png", dpi=200)