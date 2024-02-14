import time as t
import pyautogui as pag
t.sleep(3)
BFfirst = pag.locateOnScreen('D:\code\PYTHON\pyauto\BFfirst.png')
pag.moveTo(BFfirst)
# pag.click(BFfirst)
t.sleep(1)
BFstart = pag.locateOnScreen('D:\code\PYTHON\pyauto\BFstart.png')
pag.click(BFstart)
t.sleep(1)
RandS = pag.locateOnScreen('D:\code\PYTHON\pyauto\RandS.png')
pag.click(RandS)

