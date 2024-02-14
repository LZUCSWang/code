import heapq
import sys
import time

# t = time.time()
# inf = float('inf')
inf = 2 ** 31 - 1  # 题目规定了具体数值, 不能用上方无穷大

def dijkstra(start, g):  # 1, {1: [(2, 10), (4, 8)], 2: [(5, 5), ], ...}
    """
    给定起始点 start 和图 g, 求该点到其他所有点的最短距离
    return: 0 6 4 1
    """

    # 需要保存的信息及结构: [0, 距离s->1, 距离s->2, ...]
    dis = [inf] * 10010
    dis[0], dis[start] = 0, 0

    visited = [False] * 10010  # 编号基本连续, 用bool列表比set还快20%
    visited[0] = True

    q = []
    heapq.heappush(q, [0, start])

    # bfs 开始
    while q:
        # 在**routes中所有未访问过的点**中找最小值, 决定下一个点, 可以用堆优化
        min_weight, current = heapq.heappop(q)
        if visited[current]:
            continue

        visited[current] = True

        # 找到邻接顶点
        adj = g[current]  # adj = g[1] = [(3, 10), (5, 30), (6, 100)]

        # 根据当前点到邻接点的距离, 更新路径列表
        for vertex, weight in adj:
            min_weight_from_start = dis[current] + weight
            if min_weight_from_start < dis[vertex]:     # dijkstra 核心
                dis[vertex] = min_weight_from_start  # 3: 10

                # 如果 vertex 没有访问过, 就把当前最小权值和位置加进 q
                if not visited[vertex]:
                    heapq.heappush(q, [min_weight_from_start, vertex])

    return dis
n, m, s = map(int, sys.stdin.readline().split())
g = {i: [] for i in range(1, n+1)}
for i in range(m):
    u, v, w = map(int, sys.stdin.readline().split())
    g[u].append((v, w))

routes = dijkstra(s, g)

print(*routes[1:n+1])  # 用*可将序列解包, 元素之间自动加空格