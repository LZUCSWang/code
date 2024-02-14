def Bfs(arr,x,y):#arr表示应处理的矩阵，xy表示起点（即最开始遍历的点）
    M=30#矩阵行数
    N=50##矩阵列数
    queue=[]
    queue.append((x,y))#首先把起点入队列
    seen=set()
    seen.add((x,y))#将起点设置已访问过
    parent={(x,y):None}#起点无父结点，字典记录
    while len(queue)>0:#只要队列不为空，把所有的点将会全部遍历完
        matex=queue.pop(0)#将队列中第一个点取出
        m=matex[0]
        n=matex[1]
        if m-1>=0 and arr[m-1][n]=='0' and (m-1,n) not in seen  :#限制条件，边界？值为0？是否见过？
            queue.append((m-1,n))#若合法，则将matex的邻居入队
            seen.add((m-1,n))#若合法，则置为已见
            parent[(m-1,n)]=matex#记录matex的邻居也即为他的父节点为mtex
        if  m+1<M and arr[m+1][n]=='0' and (m+1,n) not in seen :
            queue.append((m+1,n))
            seen.add((m+1,n))
            parent[(m+1,n)]=matex
        if  n-1>=0 and arr[m][n-1]=='0' and (m,n-1) not in seen :
            queue.append((m,n-1))
            seen.add((m,n-1))
            parent[(m,n-1)]=matex
        if n+1<N and  arr[m][n+1]=='0' and (m,n+1) not in seen :
            queue.append((m,n+1))
            seen.add((m,n+1))
            parent[(m,n+1)]=matex
    return parent#记录了所有点的父节点
M=30#矩阵行数
N=50##矩阵列数
arr="""01010101001011001001010110010110100100001000101010
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
d=[]
parent=Bfs(arr,0,0)#调用函数
v=(M-1,N-1)##(3,5)我们需要找的这个节点到起点的距离或路径
while v!=(0,0):
    m=parent[v]
    if m[0]==v[0] and m[1]-v[1]==1:
        d.append('L')
    if m[0]==v[0] and m[1]-v[1]==-1:
        d.append('R')
    if m[0]-v[0]==1 and m[1]==v[1]:
        d.append('U')
    if m[0]-v[0]==-1 and m[1]==v[1]:
        d.append('D')
    v=m
print(''.join(d[::-1]))#将数组转为字符串
    
    
    
    


