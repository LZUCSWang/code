import networkx as nx
import matplotlib.pyplot as plt

# 创建一个空的有向图
G = nx.DiGraph()

# 添加边
edges = [(0, 1, 4), (1, 2, 8), (2, 3, 7), (2, 5, 4), (2, 8, 2), (3, 4, 9), (3, 5, 14), (4, 5, 10), (5, 6, 2), (6, 7, 1), (6, 8, 6), (7, 0, 8), (7, 1, 11), (7, 8, 7)]
G.add_weighted_edges_from(edges)

# 绘制图
pos = nx.spring_layout(G, k=2)  # Increase distance between nodes
nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=1500, edge_color='gray')
labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)

# 显示图
plt.show()