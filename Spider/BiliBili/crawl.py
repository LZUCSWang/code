from selenium import webdriver
import time
from selenium.webdriver.common.keys import Keys

# 地理位置  经纬度
Location = [35.947357, 104.154051]  # 夏专 18#
from time import sleep
import smtplib
from email.mime.text import MIMEText
from email.header import Header
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
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

url = "https://space.bilibili.com/627131796/article"
import os
import urllib.request


# 获取返回内容
# url = "https://www.52mj1.net/type/3.html"
src_map = {}


def TargetWeb(url):
    option = Options()
    option.add_argument(
        r"--user-data-dir=C:\\Users\\wxy43\AppData\\Local\\Google\\Chrome\\User Data"
    )  # 设置自己的浏览器数据路径
    option.add_argument(
        "user-agent='Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36'"
    )
    option.add_experimental_option("excludeSwitches", ["enable-automation"])
    option.add_experimental_option("useAutomationExtension", False)
    # option.add_argument('--headless')
    # option.add_argument('--no-sandbox')
    option.add_argument("--disable-gpu")
    # option.add_argument('--disable-dev-shm-usage')

    # 指定ChromeDriver的路径
    # chrome_driver_path = r'C:\\Users\wxy43\wxy43\\Local\\Google\\Chrome\Application\\chromedriver.exe'
    browser = webdriver.Chrome(options=option)
    browser.execute_cdp_cmd(
        "Page.addScriptToEvaluateOnNewDocument",
        {
            "source": """
        Object.defineProperty(navigator, 'webdriver', {
        get: () => undefined
        })
    """
        },
    )
    browser.set_window_size(1920, 1050)
    browser.execute_cdp_cmd(
        "Emulation.setGeolocationOverride",
        {"latitude": Location[0], "longitude": Location[1], "accuracy": 100},
    )
    browser.get(url)
    browser.implicitly_wait(10)
    time.sleep(2)  # 暂停3s
    # 找到父元素
    parent_element = browser.find_element(
        By.CSS_SELECTOR,
        "#page-article > div > div.main-content > div:nth-child(2) > div > div > div",
    )

    # page-article > div > div.main-content > div:nth-child(2) > div > div > div > div:nth-child(1) > div > a
    # page-article > div > div.main-content > div:nth-child(2) > div > div > div > div:nth-child(1)
    # page-article > div > div.main-content > div:nth-child(2) > div > div > div > div:nth-child(3)
    # 遍历子项目并依次点击
    for i in range(1, 127):
        son = browser.find_element(
            By.CSS_SELECTOR,
            f"#page-article > div > div.main-content > div:nth-child(2) > div > div > div > div:nth-child({i})",
        )
        son.click()
        wait = WebDriverWait(browser, 10)
        hand = browser.window_handles
        browser.switch_to.window(hand[1])
        # 获取当前 #read-article-holder 下的所有 figure 元素
        sleep(2)
        wait = WebDriverWait(browser, 100)
        figures = wait.until(
            EC.presence_of_all_elements_located(
                (By.CSS_SELECTOR, "#read-article-holder figure")
            )
        )
        # html_content = browser.page_source
        # with open('page.html', 'w', encoding='utf-8') as file:
        #     file.write(html_content)
        # figures = browser.find_elements(By.CSS_SELECTOR, '#read-article-holder figure')
        # 打印这些元素
        for figure in figures[:-1]:
            img_element = figure.find_element(By.CSS_SELECTOR, "img")
            # 获取 img 元素的 src 属性
            try:
                img_src = "https:" + img_element.get_attribute("data-src")
                # 获取有效的文件名
                img_filename = img_src.split("/")[-1].split("@")[0]
                img_path = os.path.join("images", img_filename)
                src_map[img_src] = img_path
                # 下载图片
                sleep(0.5)
                urllib.request.urlretrieve(img_src, img_path)
                print(f"Downloaded {img_filename}")
            except:
                print("error")
                continue
        browser.close()
        hand = browser.window_handles
        wait = WebDriverWait(browser, 100)
        browser.switch_to.window(hand[0])

if __name__ == "__main__":
    print("开始执行")

    TargetWeb(url)
# read-article-holder > p:nth-child(1)
# read-article-holder > p:nth-child(2)
# read-article-holder > figure:nth-child(4)
