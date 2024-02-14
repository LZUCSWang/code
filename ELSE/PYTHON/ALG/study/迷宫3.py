import os
import sys
from queue import Queue
flags = [[1,0],[0,-1],[0,1],[-1,0]]
def next_states(_x,_y,row,col):
  res=[]
  for (dx,dy)in flags:
    x,y=_x+dx,_y+dy
    if (0<=x<row and 0<=y<col) and (maze[x][y]=='0'):
      res.append((x,y))
  return res
def gen_flagection(x1,y1,x2,y2):
  de_x=x2-x1
  de_y=y2-y1
  if de_x>0:
    return 'D'
  if de_y<0:
    return 'L'
  if de_y>0:
    return 'R'
  if de_x<0:
    return 'U'
maze="""01010101001011001001010110010110100100001000101010
00001000100000101010010000100000001001100110100101
01111011010010001000001101001011100011000000010000
01000000001010100011010000101000001010101011001011
00011111000000101000010010100010100000101100000000
11001000110101000010101100011010011010101011110111
00011011010101001001001010000001000101001110000000
10100000101000100110101010111110011000010000111010
00111000001010100001100010000001000101001100001001
11000110100001110010001001010101010101010001101000
00010000100100000101001010101110100010101010000101
11100100101001001000010000010101010100100100010100
00000010000000101011001111010001100000101010100011
10101010011100001000011000010110011110110100001000
10101010100001101010100101000010100000111011101001
10000000101100010000101100101101001011100000000100
10101001000000010100100001000100000100011110101001
00101001010101101001010100011010101101110000110101
11001010000100001100000010100101000001000111000010
00001000110000110101101000000100101001001000011101
10100101000101000000001110110010110101101010100001
00101000010000110101010000100010001001000100010101
10100001000110010001000010101001010101011111010010
00000100101000000110010100101001000001000000000010
11010000001001110111001001000011101001011011101000
00000110100010001000100000001000011101000000110011
10101000101000100010001111100010101001010000001000
10000010100101001010110000000100101010001011101000
00111100001000010000000110111000000001000000001011
10000001100111010111010001000110111010101101111000""".split()
row,col=len(maze),len(maze[0])
queue=Queue()
start=(0,0)
target=(row-1,col-1)

queue.put((0,0))
pres={start:start}
while not queue.empty():
  x,y=queue.get()
  if (x,y) ==target:
    break
  for (nx,ny) in next_states(x,y,row,col):
    if (nx,ny) not in pres.keys() and maze[nx][ny]=='0':
      queue.put((nx,ny))
      pres[(nx,ny)]=(x,y)
path=[]
cur=target
while cur!=start:
  path.append(cur)
  cur=pres[cur]
path.append((0,0))
path=path[::-1]
seq=[]
for i in range(1,len(path)):
  seq.append(gen_flagection(*path[i-1],*path[i]))
print(''.join(seq))
# 请在此输入您的代码