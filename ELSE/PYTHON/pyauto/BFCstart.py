'''
Author: 王贤义
FilePath: \code\PYTHON\pyauto\BFCstart.py
Description: 
'''
import time as t
import pyautogui as pag
t.sleep(3)
CheatSignin = pag.locateOnScreen('D:\code\PYTHON\pyauto\CheatSignin.png')
pag.click(CheatSignin)
t.sleep(2)
pag.press('enter')
t.sleep(1)
StartCheat = pag.locateOnScreen('D:\code\PYTHON\pyauto\StartCheat.png')
pag.click(StartCheat)

