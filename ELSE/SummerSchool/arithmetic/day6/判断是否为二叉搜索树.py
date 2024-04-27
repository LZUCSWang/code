n = int(input())
gen = int(input())
flag = True
graph = [[float('inf'), float('inf')] for i in range(100005)]
for i in range(n-1):
    temp = list(map(int, input().split()))
    if (flag and (temp[1] and temp[0] > temp[2] or temp[1] == 0 and temp[0] < temp[2])):
        flag = False
    graph[temp[0]][temp[1]] = temp[2]


def zhong(root):
    if graph[root][0] != float('inf'):
        zhong(graph[root][0])
    print(root)
    if graph[root][1] != float('inf'):
        zhong(graph[root][1])


zhong(gen)
if flag:
    print("Yes")
else:
    print("No")
