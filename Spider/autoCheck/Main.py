from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from msedge.selenium_tools import EdgeOptions
# options = EdgeOptions()
options = {'--user-data-dir': 'C:\\Users\wxy43\AppData\\Local\\Microsoft\\Edge\\User Data'}
# options.add_argument(
#     '--user-data-dir=C:\\Users\wxy43\AppData\\Local\\Microsoft\\Edge\\User Data')

browser = webdriver.Edge(capabilities=options)
browser.get('https://docs.qq.com/form/page/DSkpjeURSQVVUS3hs')
input()
