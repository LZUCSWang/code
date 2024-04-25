from win32.lib import win32con
import win32gui
from time import sleep
import keyboard
import threading

# Global variables to control program behavior
is_paused = False
is_show = False

def handle_window(hwnd, extra):
    global is_paused, is_show
    
    if not is_paused:
        if win32gui.IsWindowVisible(hwnd):
            if "Microsoft​ Edge" in win32gui.GetWindowText(hwnd):
                sleep(0.5)
                win32gui.ShowWindow(hwnd, win32con.SW_HIDE)
                sleep(0.5)
                if is_show:
                    win32gui.ShowWindow(hwnd, win32con.SW_SHOW)

def running_thread():
    while True:
        win32gui.EnumWindows(handle_window, None)

def on_key_pressed(event):
    global is_paused, is_show
    
    if event.name == "p":
        is_paused = not is_paused
        if is_paused:
            print("程序已暂停...")
        else:
            print("程序已继续...")
    
    if event.name == "s":
        is_show = not is_show
        if is_show:
            print("程序已显示...")
        else:
            print("程序已隐藏...")

# Start the thread for continuously hiding the window
running_thread = threading.Thread(target=running_thread)
running_thread.start()

# Bind key events
keyboard.on_press(on_key_pressed)

# Keep the main thread alive
keyboard.wait('esc')
