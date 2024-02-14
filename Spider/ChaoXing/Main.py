import requests
from bs4 import BeautifulSoup
from urllib.parse import urlparse
import time
import json
from browsermobproxy import Server
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import time
from selenium.webdriver.common.keys import Keys
import re

BMPserver = Server(
    r'D:\\TOOLS\browsermob-proxy-2.1.4\bin\browsermob-proxy.bat')
BMPserver.start()
BMPproxy = BMPserver.create_proxy()

# 配置代理启动webdriver
chrome_options = Options()
chrome_options.add_argument('--ignore-certificate-errors')
chrome_options.add_argument('--proxy-server={}'.format(BMPproxy.proxy))
chrome_options.add_argument('--ignore-certificate-errors')
chrome_options.add_argument(
    r'--user-data-dir=C:\\Users\\wxy43\AppData\\Local\\Google\\Chrome\\User Data')  # 设置自己的浏览器数据路径
chrome_options.add_argument(
        "user-agent='Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36'")
chrome_options.add_experimental_option('useAutomationExtension', False)

brosver = webdriver.Chrome(options=chrome_options)

# 获取返回内容
# url = "https://www.52mj1.net/type/3.html"
BMPproxy.new_har("video", options={
                 'captureContent': True, 'captureContent': True})

# username = "jjdjrss"
# passwd = "wxy438439"

# brosver.get('https://www.52mj1.net/user/login.html')
# brosver.implicitly_wait(60)

# elem = brosver.find_element_by_id("user_name")
# elem.send_keys(username)

# elem = brosver.find_element_by_id("user_pwd")
# elem.send_keys(passwd)
# brosver.find_element_by_xpath("//input[@id='btnLogin']").click()   #selenium实现自动登录
# time.sleep(1)
# alert = brosver.switch_to_alert()
# alert.accept()
brosver.get(
    'https://mooc1.chaoxing.com/course/227540488.html?edit=false&knowledgeId=630162318&module=2#content')
input()
# 2. 检查响应状态码
# 1. 发送HTTP请求获取页面内容
# visit = {}
# with open('F:\\visit.json', 'r') as json_file:
#     visit = json.load(json_file)
json_data = BMPproxy.har
result_json = json.dumps(json_data,indent=4)
with open("meijiao.json", "w", errors="igone") as f:
    f.write(result_json)
# urlMain = 'https://www.52mj1.net/'
# for i in range(2,6):
#     url = 'https://www.52mj1.net/type/'+str(i)+'-1.html'  # 将此URL替换为你要爬取的网站
#     response = requests.get(url)
#     num=2
#     if response.status_code == 200:
#         soup = BeautifulSoup(response.text, 'html.parser')
#         # with open('baidu.html', 'w', encoding='utf-8') as f:
#         #     f.write(soup.prettipfy())
#         links = soup.select('a')
#         for link in links:
#             try:
#                 if link['title'] == '尾页':
#                     s = link['href'].find('-')
#                     e = link['href'].find('.')
#                     num = int(link['href'][s+1:e])
#                     break
#             except:
#                 continue
#             # item_title = link['尾页']
#     for j in range(1,num+1):
#         url = 'https://www.52mj1.net/type/'+str(i)+'-'+str(j)+'.html'  # 将此URL替换为你要爬取的网站
#         # 使用cookie登录
#         # cookie = 'user_id=129214; user_name=jjdjrss; group_id=2; group_name=%E6%B3%A8%E5%86%8C%E4%BC%9A%E5%91%98; user_portrait=%2Fstatic%2Fimages%2Ftouxiang.png; user_check=3989a7f0cc6f95a067d078953e5a578c'
#         # headers = {'cookie': cookie}
#         headers = {}
#         response = requests.get(url, headers=headers)
#         if response.status_code == 200:
#             # 3. 使用BeautifulSoup解析HTML内容
#             soup1 = BeautifulSoup(response.text, 'html.parser')
#             # 将html内容保存到本地
#             # with open('baidu.html', 'w', encoding='utf-8') as f:
#             #     f.write(soup1.prettify())
#             links = soup1.select('a')
#         #     # 5. 遍历链接并进行进一步操作
#             for link in links:
#         #         # 6. 访问每个项的链接并进行操作，可以使用 link['href'] 获取链接
#                 item_url = link['href']
#                 if visit[item_url] == 1:
#                     continue
#                 visit[item_url] = 1
#                 if item_url[1:5] == 'play':
#                     print(item_url)
#                     brosver.get(urlMain + item_url)
#                     page_m = brosver.page_source
#                     title_start = page_m.find('在线播放-')
#                     title_end = page_m.find('-吾爱')
#                     title = page_m[title_start+5:title_end]
#                     print(title)
#                     # with open('page.html','w',encoding='utf-8') as f:
#                     #     f.write(page_m)
#                     # time.sleep(3)
#                     json_data = BMPproxy.har
#                     result_json = json.dumps(json_data,indent=4)
#                     # with open("meijiao.json", "w", errors="igone") as f:
#                     #     f.write(result_json)
#                     idx_start = result_json.rfind('/www.51player1.com')
#                     idx_end = result_json.find('index.m3u8',idx_start)
#                     m3u8_url = "https:/"+result_json[idx_start:idx_end+10].replace('\\','')
#                     print(m3u8_url)
#                     with open("F:\\index"+str(i)+".txt","a",encoding='utf-8') as f:
#                         f.write(title.replace(' ','-') + ',' + m3u8_url + '\n')
#             # time.sleep(1)
# json_str = json.dumps(visit, indent=4)
# with open('F:\\visit.json', 'w') as json_file:
#     json_file.write(json_str)
