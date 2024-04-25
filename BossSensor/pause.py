import keyboard
import time
import threading

# 全局变量，用于控制程序是否暂停
is_paused = False

# 输出线程函数
def output_thread():
    count = 1
    while True:
        if not is_paused:
            print(count)
            count += 1
        time.sleep(1)

# 启动输出线程
output_thread = threading.Thread(target=output_thread)
output_thread.start()

# 监听按键事件的回调函数
def on_key_pressed(event):
    global is_paused
    if event.name == "p":
        is_paused = not is_paused
        if is_paused:
            print("程序已暂停...")
        else:
            print("程序已继续...")

# 绑定按键事件
keyboard.on_press(on_key_pressed)

# 持续监听键盘事件，直到程序退出
# keyboard.wait('esc')  # 当按下 ESC 键时退出程序
