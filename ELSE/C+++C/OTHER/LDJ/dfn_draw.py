import networkx as nx
import matplotlib.pyplot as plt

# 创建图
G = nx.Graph()

# 添加节点
G.add_nodes_from([0, 1, 2, 3, 4])

# 添加边
G.add_edges_from([(0, 1), (0, 2), (1, 3), (2, 4)])

# 寻找最高节点作为起点
start_node = max(G.nodes, key=lambda x: G.degree(x))

# 进行深度优先搜索
dfs_edges = list(nx.dfs_edges(G, source=start_node))

# 绘制图形
pos = nx.spring_layout(G)  # 定义节点位置

colors = ['red' if edge in dfs_edges else 'black' for edge in G.edges()]

nx.draw(G, pos, with_labels=True, node_size=500, node_color='lightblue', font_size=10, font_color='black')
nx.draw_networkx_edges(G, pos, edgelist=dfs_edges, edge_color=colors, width=2)
nx.draw_networkx_edges(G, pos, edgelist=[edge for edge in G.edges() if edge not in dfs_edges], edge_color='black', width=1)

plt.title("Depth First Search (Starting from highest node)")
plt.show()
