# 导入模块
import socket as sk

# 创建IP查找器，查找本机IP
finder = sk.socket(sk.AF_INET, sk.SOCK_DGRAM)
# 基于UDP协议连接公共DNS服务器 8.8.8.8 的80端口（默认为HTTP端口）
finder.connect(('8.8.8.8', 80))

# 获取本机IP地址
HOST = finder.getsockname()[0]
# 设置服务器监听的端口号
PORT = 3600


# 创建基于TCP协议的服务器
server = sk.socket(sk.AF_INET, sk.SOCK_STREAM)
# 设置服务器绑定的主机地址及端口号
server.bind((HOST, PORT))
# 开始监听（设置参数，使得允许最大排队个数为五）
server.listen(5)
# 打印服务器运行的地址及端口
print(f'server is running at {HOST}:{PORT}')

# 与发出连接邀请的客户端建立连接
# 返回值类型为一元组，第一个元素为socket.socket对象，
# 第二个元素为客户端的地址，包含IP地址及端口号的元组
conn, address = server.accept()

# 向客户端发送连接成功的提示信息
tip = f'The server has received a connection from {address[0]}:{address[1]}'
print(tip)
conn.send(tip.encode())


try:
    while True:
        # recv方法的参数为必填项，指定接受信息的最大字节数
        # 由于发送过来的数据为二进制，所以需要对数据进行解码。
        message = conn.recv(1024).decode()
        if message:
            print(message)
        # 由于input函数是阻塞式的，所以信息只能轮流发送
        # 若想不受input函数的限制，想发就发，可以考虑使用多线程（若有更好的方式，还请多多指教）
        think = input()
        if think:
            # 发送信息需要对其进行编码
            conn.send(f'【server】   {think}'.encode())

except ConnectionResetError:
    # 在客户端连接到服务器，若客户端发送一条或多条信息并断开连接，那么当服务器发送信息时（断开连接后）将触发该错误。
    print('The connection has been disconnected')
