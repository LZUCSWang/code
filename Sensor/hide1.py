import win32gui

hwnd_title = dict()

def get_all_hwnd(hwnd, mouse):
    if (
        win32gui.IsWindow(hwnd)
        and win32gui.IsWindowEnabled(hwnd)
        and win32gui.IsWindowVisible(hwnd)
    ):
        hwnd_title.update({hwnd: win32gui.GetWindowText(hwnd)})


if __name__ in "__main__":
    win32gui.EnumWindows(get_all_hwnd, 0)
    for h, t in hwnd_title.items():
        if t is not "":
            print(h, t)
