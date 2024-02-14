# 导入模块
import socket as sk


# 服务器信息
HOST = '210.26.112.27'
PORT = 5942

# 创建基于TCP协议的客户端
client = sk.socket(sk.AF_INET, sk.SOCK_STREAM)
# 开始连接服务器
client.connect((HOST, PORT))

while True:
    # 对接受到的信息进行解码
    message = client.recv(1024).decode()
    # 如果有信息则将其打印
    if message:
        print(message)
    think = input()
    client.send(f'【client】{think}'.encode())
