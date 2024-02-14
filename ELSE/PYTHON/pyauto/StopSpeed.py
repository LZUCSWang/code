import time as t
import pyautogui as pag
t.sleep(5)
StopSpeed = pag.locateOnScreen('D:\code\PYTHON\pyauto\StopSpeed.png')
pag.click(StopSpeed)
t.sleep(1)
ConfirmStop = pag.locateOnScreen('D:\code\PYTHON\pyauto\ConfirmStop.png')
pag.click(ConfirmStop)