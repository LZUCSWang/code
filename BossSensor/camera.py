import cv2
import numpy, os, sys
import pyautogui

is_paused = False

def on_key_pressed(event):
    global is_paused
    # 修改为ctrl+shift+p暂停
    if event.name == "`":
        is_paused = not is_paused
        if is_paused:
            print("程序已暂停...")
        else:
            print("程序已继续...")
            
def switch_window():
    # python 模拟键盘按键 win+ctrl+right 使用pyautogui
    pyautogui.hotkey("win", "ctrl", "right")


def isPicChanged():
    """
    通过前后帧对比，判断画面是否改变
    :param dividePar = 4 # 对比隔点，减少计算量
    :param pointDelta = 50 # 像素点的差异大于该值认为是差异点
    :param judgeTh = 64 # 判断变化画面大小的阈值：画面(1/judgeTh)
    """
    dividePar = 4  # 对比隔点，减少计算量
    pointDelta = 50  # 像素点的差异大于该值认为是差异点
    judgeTh = 64  # 判断变化画面大小的阈值：画面(1/judgeTh)
    capIdx = 0  # 截图命名
    camIdx = -1
    while int(camIdx) < 0 or int(camIdx) > 10:
        # print("enter camera index in 0 and 10:")
        # camIdx = int(input())
        camIdx = 1

    if not (os.path.isdir("cap")):  # 创建存放截图的文件夹
        os.system("mkdir -p {}".format("cap"))

    cap = cv2.VideoCapture(camIdx)  # 调整参数实现读取视频或调用摄像头
    ret, frameBak = cap.read()
    for i in range(10):  # 刚打开相机时，曝光不稳定，清理10张
        ret, frameBak = cap.read()
    frame = frameBak
    frameWidth = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frameHeight = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    # print("frameWidth:{},frameHeight:{}".format(frameWidth, frameHeight))
    if frameWidth == 0:
        exit("camera is not available.")

    while True:
        if not is_paused:
            absCnt = 0
            frameBak = frame
            ret, frame = cap.read()
            for wIdx in range(int(frameWidth / dividePar)):
                for hIdx in range(int(frameHeight / dividePar)):
                    if (
                        abs(
                            int(frameBak[hIdx * dividePar][wIdx * dividePar][2])
                            - int(frame[hIdx * dividePar][wIdx * dividePar][2])
                        )
                        > pointDelta
                    ):
                        absCnt += 1


            # cv2.imshow("cap", frame)

            if absCnt > (frameWidth * frameHeight) / (dividePar * dividePar) / (
                judgeTh * judgeTh
            ):
                capIdx += 2
                # cv2.imwrite('cap/cap_{}.jpg'.format(capIdx), frame)
                # cv2.imwrite('cap/cap_{}.jpg'.format(capIdx+1), frameBak)
                print("get a pic:{}".format(capIdx / 2))
                switch_window()

            if cv2.waitKey(1) & 0xFF == ord("q"):
                break

    cap.release()
    cv2.destroyAllWindows()
import keyboard

def count_available_cameras():
    num_cameras = 0
    for i in range(2):  # 假设最多检测10个摄像头
        cap = cv2.VideoCapture(i)
        if not cap.read()[0]:
            break
        num_cameras += 1
        cap.release()
    return num_cameras

import threading
if __name__ == "__main__":
    pyautogui.FAILSAFE = False
    # isPicChanged()
    isPicChanged = threading.Thread(target=isPicChanged)
    isPicChanged.start()
    keyboard.on_press(on_key_pressed)

    # print(count_available_cameras())
