
import time as t
import pyautogui as pag
import os
import subprocess
# subprocess.Popen(r"C:\\Program Files (x86)\\Microsoft\\Edge\Application\\msedge.exe")
subprocess.Popen(r"C:\\Program Files (x86)\\LeiGod_Acc\\leigod.exe")
t.sleep(0.5)
pag.hotkey('win','1')
t.sleep(1)
pag.hotkey('ctrl','t')
t.sleep(0.2)
pag.typewrite('wei')
t.sleep(0.2)
pag.press('enter')
t.sleep(10)
GGDspeed = pag.locateOnScreen('D:\code\PYTHON\pyauto\GGDspeed.png')
pag.moveTo(GGDspeed)
t.sleep(2)
BFstart = pag.locateOnScreen('D:\code\PYTHON\pyauto\BFstart.png')
pag.click(BFstart)
t.sleep(0.5)
RandS = pag.locateOnScreen('D:\code\PYTHON\pyauto\RandS.png')
pag.click(RandS)
# subprocess.Popen(r"C:\\Program Files (x86)\Steam\steamapps\\common\\Goose Goose Duck\\Goose Goose Duck.exe")
